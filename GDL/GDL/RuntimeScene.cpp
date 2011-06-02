/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/RuntimeScene.h" // must be placed first, thx wx
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <sstream>
#include <iomanip>
#include "GDL/Scene.h"
#include "GDL/Game.h"
#include "GDL/ImageManager.h"
#include "GDL/Chercher.h"
#include "GDL/ExtensionsManager.h"
#include "GDL/Layer.h"
#include "GDL/EventsPreprocessor.h"
#include "GDL/profile.h"
#include "GDL/ExtensionsManager.h"
#include "GDL/Position.h"
#include "GDL/FontManager.h"
#include "GDL/ObjectsConcerned.h"
#include "GDL/AutomatismsSharedDatas.h"

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Config/config.h>
#include <llvm/Module.h>
#include <llvm/Target/TargetRegistry.h>
#include <llvm/Target/TargetSelect.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/TypeBuilder.h>
#undef _
#include <llvm/Support/system_error.h>

#if defined(GD_IDE_ONLY)
#include "GDL/ProfileEvent.h"
#include "GDL/BaseProfiler.h"
#include "GDL/BaseDebugger.h"
#endif

void MessageLoading( string message, float avancement ); //Prototype de la fonction pour renvoyer un message
//La fonction est impl�ment� diff�remment en fonction du runtime ou de l'�diteur

RuntimeLayer RuntimeScene::badLayer;

RuntimeScene::RuntimeScene(sf::RenderWindow * renderWindow_, RuntimeGame * game_) :
renderWindow(renderWindow_),
input(&renderWindow->GetInput()),
inputKeyPressed(false),
game(game_),
#if defined(GD_IDE_ONLY)
debugger(NULL),
profiler(NULL),
#endif
running(true),
pauseTime(0),
backgroundColorR(125),
backgroundColorG(125),
backgroundColorB(125),
firstLoop(true),
isFullScreen(false),
realElapsedTime(0),
elapsedTime(0),
timeScale(1),
timeFromStart(0),
specialAction(-1)
{
    //ctor
    soundManager = SoundManager::GetInstance();
    renderWindow->ShowMouseCursor( true );

    //Calque par d�faut
    sf::View defaultView( sf::FloatRect( 0.0f, 0.0f, game->windowWidth, game->windowHeight ) );
    Layer layer;
    layer.SetCamerasNumber(1);

    layers.push_back(RuntimeLayer(layer, defaultView));

    ChangeRenderWindow(renderWindow);
}

RuntimeScene::~RuntimeScene()
{
}

void RuntimeScene::Init(const RuntimeScene & scene)
{
    renderWindow = scene.renderWindow;
    game = scene.game;
    soundManager = scene.soundManager;
    input = scene.input;
    #if defined(GD_IDE_ONLY)
    debugger = scene.debugger;
    profiler = scene.profiler;
    #endif
    running = scene.running;

    objectsInstances = scene.objectsInstances.CopyAndCloneAllObjects();

    variables = scene.variables;
    textes = scene.textes;
    timers = scene.timers;
    pauseTime = scene.pauseTime;
    backgroundColorR = scene.backgroundColorR;
    backgroundColorG = scene.backgroundColorG;
    backgroundColorB = scene.backgroundColorB;

    firstLoop = scene.firstLoop;
    isFullScreen = scene.isFullScreen;
    realElapsedTime = scene.realElapsedTime;
    elapsedTime = scene.elapsedTime;
    timeScale = scene.timeScale;
    timeFromStart = scene.timeFromStart;
    specialAction = scene.specialAction;

    automatismsSharedDatas.clear();
    for (boost::interprocess::flat_map < unsigned int, boost::shared_ptr<AutomatismsRuntimeSharedDatas> >::const_iterator it = scene.automatismsSharedDatas.begin();
         it != scene.automatismsSharedDatas.end();++it)
    {
    	automatismsSharedDatas[it->first] = it->second->Clone();
    }
}

RuntimeScene::RuntimeScene(const RuntimeScene & scene) : Scene(scene)
{
    Init(scene);
}

RuntimeScene& RuntimeScene::operator=(const RuntimeScene & scene)
{
    if( (this) != &scene )
    {
        Scene::operator=(scene);
        Init(scene);
    }

    return *this;
}

void RuntimeScene::ChangeRenderWindow(sf::RenderWindow * newWindow)
{
    if ( newWindow == NULL )
    {
        cout << "Try to change renderWindow to a NULL window." << endl;
        return;
    }

    renderWindow = newWindow;
    input = &renderWindow->GetInput();
    renderWindow->SetTitle(title);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double windowRatio = static_cast<double>(renderWindow->GetWidth())/static_cast<double>(renderWindow->GetHeight());
    gluPerspective(oglFOV, windowRatio, oglZNear, oglZFar);
}

#ifndef RELEASE
void DisplayProfile(sf::RenderWindow * renderWindow, CProfileIterator * iter, int x, int & y)
{
    FontManager * fontManager = FontManager::GetInstance();

    y += 15;
    while ( !iter->Is_Done() )
    {
        sf::Text text("", *fontManager->GetFont("consola.ttf"));
        text.SetCharacterSize(12);
        ostringstream texte;
        if ( CProfileManager::Get_Frame_Count_Since_Reset() != 0 )
            texte << fixed <<  iter->Get_Current_Name()   << " Calls/Frame:" << iter->Get_Current_Total_Calls()/CProfileManager::Get_Frame_Count_Since_Reset()
                                                << " Time/Frame:" << iter->Get_Current_Total_Time()/CProfileManager::Get_Frame_Count_Since_Reset()
                                                << " %Time/Parent " << iter->Get_Current_Total_Time()/iter->Get_Current_Parent_Total_Time()*100.0f;
        text.SetString(texte.str());
        text.SetPosition(x,y);
        renderWindow->Draw(text);

        //Childs
        CProfileIterator * childIter = CProfileManager::Get_Iterator();
        *childIter = *iter;
        childIter->Enter_Child(0);
        DisplayProfile(renderWindow, childIter, x+15, y);
        CProfileManager::Release_Iterator(childIter);

        y += 15;
        iter->Next();
    }
}
#endif

////////////////////////////////////////////////////////////
/// Avancer l'�tat de la sc�ne et la dessiner
/// Appel� habituellement � chaque tour de boucle de jeu
////////////////////////////////////////////////////////////
int RuntimeScene::RenderAndStep(unsigned int nbStep)
{
    BT_PROFILE("RenderAndStep");
    for (unsigned int step = 0;step<nbStep;++step)
    {
        //Gestion pr�-�v�nements
        ManageRenderTargetEvents();
        UpdateTime();
        ManageObjectsBeforeEvents();
        ManageSounds();

        #if defined(GD_IDE_ONLY)
        if( profiler )
        {
            if ( firstLoop ) profiler->Reset();
            profiler->eventsClock.reset();
        }
        #endif

        const std::vector< llvm::GenericValue > args;
        EE->runFunction(eventsEntryFunction, args);

        #if defined(GD_IDE_ONLY)
        if( profiler && profiler->profilingActivated )
        {
            profiler->lastEventsTime = profiler->eventsClock.getTimeMicroseconds();
            profiler->renderingClock.reset();
        }
        #endif

        //Gestions post-�v�nements
        ManageObjectsAfterEvents();

        #if defined(GD_IDE_ONLY)
        if( debugger )
            debugger->Update();
        #endif

        //Rendering
        Render();
        textes.clear(); //Legacy texts

        #if defined(GD_IDE_ONLY)
        if( profiler && profiler->profilingActivated )
        {
            profiler->lastRenderingTime = profiler->renderingClock.getTimeMicroseconds();
            profiler->totalSceneTime += profiler->lastRenderingTime + profiler->lastEventsTime;
            profiler->totalEventsTime += profiler->lastEventsTime;
            profiler->Update();
        }
        #endif


        if ( firstLoop ) firstLoop = false; //The first frame is passed
    }

    return specialAction;
}

////////////////////////////////////////////////////////////
/// Gestion des �v�nements basiques de la fen�tre
////////////////////////////////////////////////////////////
void RuntimeScene::ManageRenderTargetEvents()
{
    inputWheelDelta = 0;
    inputTextEntered.clear();

    sf::Event event;
    while ( renderWindow->GetEvent( event ) )
    {
        // Close window : exit
        if ( event.Type == sf::Event::Closed )
        {
            running = false;
            #if defined(GD_IDE_ONLY)
            renderWindow->Close();
            #endif
        }
        else if (event.Type == sf::Event::KeyPressed)
            inputKeyPressed = true;
        else if (event.Type == sf::Event::KeyReleased )
            inputKeyPressed = false;
        else if (event.Type == sf::Event::MouseWheelMoved )
            inputWheelDelta = event.MouseWheel.Delta;
        else if (event.Type == sf::Event::TextEntered )
            inputTextEntered += event.Text.Unicode;
        else if (event.Type == sf::Event::Resized)
        {
            //Resetup OpenGL
            glEnable(GL_DEPTH_TEST);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glDepthMask(GL_TRUE);
            glClearDepth(1.f);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            double windowRatio = static_cast<double>(event.Size.Width)/static_cast<double>(event.Size.Height);
            gluPerspective(oglFOV, windowRatio, oglZNear, oglZFar);
        }
    }
}

////////////////////////////////////////////////////////////
/// Affichage simple
////////////////////////////////////////////////////////////
void RuntimeScene::RenderWithoutStep()
{
    ManageRenderTargetEvents();

    Render();

    #if defined(GD_IDE_ONLY)
    if( debugger )
        debugger->Update();
    #endif
}

////////////////////////////////////////////////////////////
/// Affichage dans une sf::RenderWindow
////////////////////////////////////////////////////////////
void RuntimeScene::Render()
{
    renderWindow->Clear( sf::Color( backgroundColorR, backgroundColorG, backgroundColorB ) );

    //Sort object by order to render them
    ObjList allObjects = objectsInstances.GetAllObjects();
    OrderObjectsByZOrder( allObjects );

    //To allow using OpenGL to draw :
    glClear(GL_DEPTH_BUFFER_BIT); // Clear the depth buffer
    renderWindow->SaveGLStates();
    renderWindow->SetActive();

    //Draw layer by layer
    for (unsigned int layerIndex =0;layerIndex<layers.size();++layerIndex)
    {
        if ( layers.at(layerIndex).GetVisibility() )
        {
            for (unsigned int cameraIndex = 0;cameraIndex < layers[layerIndex].GetCamerasNumber();++cameraIndex)
            {
                RuntimeCamera & camera = layers[layerIndex].GetCamera(cameraIndex);

                //Prepare OpenGL rendering
                renderWindow->RestoreGLStates();

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(oglFOV, camera.GetSFMLView().GetSize().x
                                    /camera.GetSFMLView().GetSize().y, oglZNear, oglZFar);

                const sf::FloatRect & viewport = camera.GetSFMLView().GetViewport();
                glViewport(viewport.Left*renderWindow->GetWidth(),
                           renderWindow->GetHeight()-(viewport.Top+viewport.Height)*renderWindow->GetHeight(), //Y start from bottom
                           viewport.Width*renderWindow->GetWidth(),
                           viewport.Height*renderWindow->GetHeight());

                renderWindow->SaveGLStates();

                //Prepare SFML rendering
                renderWindow->SetView(camera.GetSFMLView());

                //Rendering all objects
                for (unsigned int id = 0;id < allObjects.size();++id)
                {
                    //Affichage de l'objet si il appartient au calque
                    if ( allObjects[id]->GetLayer() == layers[layerIndex].GetName() )
                        allObjects[id]->Draw( *renderWindow );
                }

                //Texts
                DisplayLegacyTexts(layers.at(layerIndex).GetName());
            }
        }
    }

        //Internal profiler
        #ifndef RELEASE
        if ( renderWindow->GetInput().IsKeyDown(sf::Key::F2))
            CProfileManager::Reset();

        renderWindow->SetView(sf::View(sf::FloatRect(0.0f,0.0f, game->windowWidth, game->windowHeight)));

        CProfileIterator * iter = CProfileManager::Get_Iterator();
        int y = 0;
        DisplayProfile(renderWindow, iter, 0,y);
        CProfileManager::Increment_Frame_Counter();
        #endif

    // Display window contents on screen
    renderWindow->RestoreGLStates();
    renderWindow->Display();
}

////////////////////////////////////////////////////////////
/// Renvoie le calque avec le nom indiqu�
////////////////////////////////////////////////////////////
RuntimeLayer & RuntimeScene::GetLayer(string name)
{
    for (unsigned int i = 0;i<layers.size();++i)
    {
    	if( layers[i].GetName() == name )
            return layers[i];
    }

    cout << "Impossible de trouver le calque \""+name+"\".";
    return badLayer;
}

////////////////////////////////////////////////////////////
/// Renvoie le calque avec le nom indiqu�
////////////////////////////////////////////////////////////
const RuntimeLayer & RuntimeScene::GetLayer(string name) const
{
    for (unsigned int i = 0;i<layers.size();++i)
    {
    	if( layers[i].GetName() == name )
            return layers[i];
    }

    cout << "Impossible de trouver le calque \""+name+"\".";
    return badLayer;
}

////////////////////////////////////////////////////////////
/// Met � jour le temps
////////////////////////////////////////////////////////////
bool RuntimeScene::UpdateTime()
{
    //Temps �coul� depuis la derni�re frame
    realElapsedTime = renderWindow->GetFrameTime();
    realElapsedTime -= pauseTime; //On enl�ve le temps de pause

    //On modifie ce temps �coul� si il est trop bas.
    if ( game->minFPS != 0 && realElapsedTime > 1.f/static_cast<float>(game->minFPS) )
        realElapsedTime = 1.f/static_cast<float>(game->minFPS); //On ralentit le jeu si les FPS sont trop bas.

    elapsedTime = realElapsedTime*timeScale; //Le temps �coul� par le jeu est modifi� suivant l'�chelle du temps

    timeFromStart += elapsedTime;
    pauseTime = 0;

    for (unsigned int i =0;i<timers.size();++i)
        timers[i].UpdateTime(elapsedTime);

    return true;
}

////////////////////////////////////////////////////////////
/// Met � jour un tableau contenant l'ordre d'affichage des objets
////////////////////////////////////////////////////////////
bool RuntimeScene::OrderObjectsByZOrder( ObjList & objList )
{
    if ( standardSortMethod )
        std::sort( objList.begin(), objList.end(), SortByZOrder() );
    else
        std::stable_sort( objList.begin(), objList.end(), SortByZOrder() );

    return true;
}

////////////////////////////////////////////////////////////
/// Affiche le texte
////////////////////////////////////////////////////////////
bool RuntimeScene::DisplayLegacyTexts(string layer)
{
    for ( unsigned int i = 0;i < textes.size();i++ )
    {
        if ( textes[i].layer == layer )
            textes[i].Draw(*renderWindow);
    }

    return true;
}

////////////////////////////////////////////////////////////
/// Stoppe toutes les musiques de la sc�ne
////////////////////////////////////////////////////////////
bool RuntimeScene::StopMusic()
{
    SoundManager * soundManager = SoundManager::GetInstance();

    //Arr�t des musiques : simples musiques
    for ( unsigned int i = 0;i < soundManager->musics.size();i++ )
    {
        soundManager->musics.at( i )->Stop();
    }
    soundManager->musics.clear();

    //Arr�t des musiques : musiques sur channels
    for ( unsigned int i = 0;i < MAX_CANAUX_MUSIC;i++ )
    {
        soundManager->GetMusicOnChannel(i)->Stop();
    }

    //Arr�t des sons
    for ( unsigned int i = 0;i < soundManager->sounds.size();i++ )
    {
        soundManager->sounds.at( i )->sound.Stop();
    }
    soundManager->sounds.clear();

    //Arr�t des sons : sons sur channels
    for ( unsigned int i = 0;i < MAX_CANAUX_SON;i++ )
    {
        soundManager->GetSoundOnChannel(i)->sound.Stop();
    }

    return true;
}

////////////////////////////////////////////////////////////
/// Efface les musiques et sons termin�s
////////////////////////////////////////////////////////////
void RuntimeScene::ManageSounds()
{
    //Bruitages sans canaux. On les d�truits si besoin est.
    for ( int i = soundManager->sounds.size() - 1;i >= 0;i-- )
    {
        if ( soundManager->sounds.at( i )->sound.GetStatus() == sf::Sound::Stopped )
        {
            delete soundManager->sounds.at( i ); //Les sounds sont ger�s par pointeurs
            soundManager->sounds.erase( soundManager->sounds.begin() + i );
        }
    }


    //Musiques sans canaux.
    for ( unsigned int i = 0;i < soundManager->musics.size();i++ )
    {
        if ( soundManager->musics.at( i )->GetStatus() == sf::Music::Stopped )
        {
            soundManager->musics.erase( soundManager->musics.begin() + i );
        }
    }
}

/**
 * Delete objects, updates time and launch automatisms
 */
void RuntimeScene::ManageObjectsAfterEvents()
{
    ObjList allObjects = objectsInstances.GetAllObjects();
    for (unsigned int id = 0;id<allObjects.size();++id)
    {
    	if ( allObjects[id]->GetObjectIdentifier() == 0 ) //0 stand always for object without name, to delete.
            objectsInstances.RemoveObject(allObjects[id]); //Remove from objects Instances, not from the temporary list !

    }

    allObjects = objectsInstances.GetAllObjects();
    for (unsigned int id = 0;id<allObjects.size();++id)
    {
        allObjects[id]->SetX( allObjects[id]->GetX() + ( allObjects[id]->TotalForceX() * GetElapsedTime() ));
        allObjects[id]->SetY( allObjects[id]->GetY() + ( allObjects[id]->TotalForceY() * GetElapsedTime() ));
        allObjects[id]->UpdateTime( GetElapsedTime() );
        allObjects[id]->UpdateForce( GetElapsedTime() );
        allObjects[id]->DoAutomatismsPostEvents(*this);
    }
}

/**
 * Manage objects before launching events
 */
void RuntimeScene::ManageObjectsBeforeEvents()
{
    ObjList allObjects = objectsInstances.GetAllObjects();
    for (unsigned int id = 0;id<allObjects.size();++id)
        allObjects[id]->DoAutomatismsPreEvents(*this);

}

void RuntimeScene::GotoSceneWhenEventsAreFinished(int scene)
{
    specialAction = scene;
}

RuntimeScene * tempRSpointer;

////////////////////////////////////////////////////////////
/// Ouvre un jeu, et stocke dans les tableaux pass�s en param�tres.
////////////////////////////////////////////////////////////
bool RuntimeScene::LoadFromScene( const Scene & scene )
{
    MessageLoading( "Loading scene", 10 );

    //Clear RuntimeScene datas
    objectsInstances.Clear();
    textes.clear();
    timers.clear();
    layers.clear();
    firstLoop = true;
    elapsedTime = 0;
    realElapsedTime = 0;
    pauseTime = 0;
    timeScale = 1;
    timeFromStart = 0;
    specialAction = -1;

    //Copy inherited datas
    initialObjects = scene.initialObjects;
    objectGroups = scene.objectGroups;
    initialLayers = scene.initialLayers;
    variables = scene.variables;

    events = CloneVectorOfEvents(scene.events);

    backgroundColorR = scene.backgroundColorR;
    backgroundColorG = scene.backgroundColorG;
    backgroundColorB = scene.backgroundColorB;
    standardSortMethod = scene.standardSortMethod;
    title = scene.title;
    oglFOV = scene.oglFOV;
    oglZNear = scene.oglZNear;
    oglZFar = scene.oglZFar;

    //Add global object groups
    copy(game->objectGroups.begin(), game->objectGroups.end(), back_inserter(objectGroups));

    //Initialize runtime layers
    sf::View defaultView( sf::FloatRect( 0.0f, 0.0f, game->windowWidth, game->windowHeight ) );
    for (unsigned int i = 0;i<initialLayers.size();++i)
    {
        layers.push_back(RuntimeLayer(initialLayers[i], defaultView));
    }

    //Load resources of initial objects
    MessageLoading( "Loading objects resources", 30 );
    for (unsigned int i = 0; i < scene.initialObjects.size();++i)
        scene.initialObjects[i]->LoadResources(*this, *game->imageManager);

    //Load resources of global objects
    //TODO : Make this only one time during game
    for (unsigned int i = 0; i < game->globalObjects.size();++i)
        game->globalObjects[i]->LoadResources(*this, *game->imageManager);

    //Create object instances which are originally positionned on scene
    MessageLoading( "Adding objects to their initial position", 66 );
    for(unsigned int i = 0;i < scene.initialObjectsPositions.size();++i)
    {
        int IDsceneObject = Picker::PickOneObject( &initialObjects, scene.initialObjectsPositions[i].objectName );
        int IDglobalObject = Picker::PickOneObject( &game->globalObjects, scene.initialObjectsPositions[i].objectName );

        ObjSPtr newObject = boost::shared_ptr<Object> ();

        if ( IDsceneObject != -1 ) //We check first scene's objects' list.
            newObject = initialObjects[IDsceneObject]->Clone();
        else if ( IDglobalObject != -1 ) //Then the global object list
            newObject = game->globalObjects.at( IDglobalObject )->Clone();

        if ( newObject != boost::shared_ptr<Object> () )
        {
            newObject->SetX( scene.initialObjectsPositions[i].x );
            newObject->SetY( scene.initialObjectsPositions[i].y );
            newObject->SetZOrder( scene.initialObjectsPositions[i].zOrder );
            newObject->SetLayer( scene.initialObjectsPositions[i].layer );
            newObject->InitializeFromInitialPosition(scene.initialObjectsPositions[i]);
            newObject->SetAngle( scene.initialObjectsPositions[i].angle );

            if ( scene.initialObjectsPositions[i].personalizedSize )
            {
                newObject->SetWidth(scene.initialObjectsPositions[i].width);
                newObject->SetHeight(scene.initialObjectsPositions[i].height);
            }

            newObject->LoadRuntimeResources(*this, *game->imageManager);

            objectsInstances.AddObject(newObject);
        }
        else
            std::cout << "Could not find and put object " << scene.initialObjectsPositions[i].objectName << std::endl;
    }

    //Preprocess events
    MessageLoading( "Preprocessing events", 80 );

    //TODO : Only once
    {
        cout << "Loading libstdc++..." << std::endl;
        std::string error;
        llvm::sys::DynamicLibrary::LoadLibraryPermanently("libstdc++-6.dll", &error);
        cout << error;
    }

    llvm::InitializeNativeTarget();

    {
        llvm::error_code err = llvm::MemoryBuffer::getFile("mybitcode.txt", eventsBuffer);
        if ( err.value() != 0 )
            std::cout << "Failed to load mybitcode.txt: " << err.message() << std::endl;
        else
        {
            std::string parseError;
            Module = ParseBitcodeFile(eventsBuffer.get(), llvmContext, &parseError);
            std::cout << parseError;
        }
    }

    if (!Module)
    {
        cout << "Module creation failed";
    }
    else
    {
        std::string error;
        EE.reset( llvm::ExecutionEngine::createJIT(Module, &error));
        if (!EE)
        {
            cout << "unable to make execution engine: " << error << "\n";
        }
        else
        {
            eventsEntryFunction = Module->getFunction("main");
            if (!eventsEntryFunction)
                cout << "'main' function not found in module.\n";

            cout << "Mapping objects";
            {
                tempRSpointer = this;
                llvm::GlobalValue *globalValue = llvm::cast<llvm::GlobalValue>(Module->getOrInsertGlobal("pointerToRuntimeScene", llvm::TypeBuilder<void*, false>::get(Module->getContext())));
                EE->addGlobalMapping(globalValue, &tempRSpointer);
            }

            cout << "About to run";

            const std::vector< llvm::GenericValue > args;
            EE->runFunction(eventsEntryFunction, args);
            EE->runFunction(eventsEntryFunction, args);
        }
    }

    //Automatisms datas
    automatismsSharedDatas.clear();
    for(boost::interprocess::flat_map < unsigned int, boost::shared_ptr<AutomatismsSharedDatas> >::const_iterator it = scene.automatismsInitialSharedDatas.begin();
        it != scene.automatismsInitialSharedDatas.end();
        ++it)
    {
        automatismsSharedDatas[it->first] = it->second->CreateRuntimeSharedDatas();
    }

    if ( stopSoundsOnStartup ) StopMusic();

    MessageLoading( "Loading finished", 100 );

    return true;
}

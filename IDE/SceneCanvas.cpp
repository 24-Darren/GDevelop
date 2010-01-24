#include "SceneCanvas.h"
#include <string>
#include <SFML/System.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GDL/Object.h"
#include <cmath>
#include "GDL/Collisions.h"
#include "GDL/Event.h"
#include <iostream>
#include <sstream>
#include "GDL/Chercher.h"
#include "GDL/algo.h"
#include "GDL/StdAlgo.h"
#include "EditOptionsPosition.h"
#include <wx/log.h>
#include <wx/scrolbar.h>
#ifdef __WXMSW__
#include <wx/msw/winundef.h>
#endif
#include "GDL/SortByPlan.h"
#include "GDL/RuntimeScene.h"
#include "GDL/AppelEvent.h"
#include "GDL/Chercher.h"
#include "GDL/ImageManager.h"
#include "GDL/RuntimeGame.h"
#include "DndTextSceneEditor.h"
#include <wx/cursor.h>

const long SceneCanvas::ID_ADDOBJMENU = wxNewId();
const long SceneCanvas::ID_DELOBJMENU = wxNewId();
const long SceneCanvas::ID_PROPMENU = wxNewId();
const long SceneCanvas::ID_LAYERUPMENU = wxNewId();
const long SceneCanvas::ID_LAYERDOWNMENU = wxNewId();

SceneCanvas::SceneCanvas( wxWindow* Parent, Game & game_, Scene * scene_, RuntimeGame & runtimeGame_, MainEditorCommand & mainEditorCommand_, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style ) :
        wxSFMLCanvas( Parent, Id, Position, Size, Style ),
        gameEdited( game_ ),
        game(runtimeGame_),
        sceneEdited(scene_),
        scene(this, &game),
        mainEditorCommand( mainEditorCommand_ ),
        hasJustRightClicked(false),
        scrollBar1(NULL),
        scrollBar2(NULL)
{
    MemTracer.AddObj( "Editeur de sc�ne", ( long )this );

    //SetDropTarget(new wxTextDropTarget);
    SetView( scene.view );
    SetFramerateLimit( game.maxFPS );
    UseVerticalSync( game.verticalSync );
    Clear( sf::Color( 125, 125, 125, 255 ) );

    Connect(ID_ADDOBJMENU,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SceneCanvas::OnAddObjetSelected);
    Connect(ID_DELOBJMENU,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SceneCanvas::OnDelObjetSelected);
    Connect(ID_PROPMENU,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SceneCanvas::OnPropObjSelected);
    Connect(ID_LAYERUPMENU,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SceneCanvas::OnLayerUpSelected);
    Connect(ID_LAYERDOWNMENU,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SceneCanvas::OnLayerDownSelected);

    contextMenu.Append(ID_PROPMENU, _("Propri�t�s"));
    contextMenu.AppendSeparator();
    contextMenu.Append(ID_ADDOBJMENU, _("Ajouter un objet\tINSER"));
    contextMenu.Append(ID_DELOBJMENU, _("Supprimer la s�lection\tDEL"));
    contextMenu.AppendSeparator();
    contextMenu.Append(ID_LAYERUPMENU, _("Passer le(s) objet(s) sur le calque sup�rieur"));
    contextMenu.Append(ID_LAYERDOWNMENU, _("Passer le(s) objet(s) sur le calque inf�rieur"));

    contextMenu.FindItem(ID_ADDOBJMENU)->SetBitmap(wxImage( "res/addobjet.png" ) );
    contextMenu.FindItem(ID_DELOBJMENU)->SetBitmap(wxImage( "res/deleteicon.png" ) );
    contextMenu.FindItem(ID_LAYERUPMENU)->SetBitmap(wxImage( "res/up.png" ) );
    contextMenu.FindItem(ID_LAYERDOWNMENU)->SetBitmap(wxImage( "res/down.png" ) );

    SetDropTarget(new DndTextSceneEditor(*this));
}

void SceneCanvas::ChangeScenePtr(Scene * newScenePtr, bool refresh)
{
    assert(newScenePtr != NULL);

    sceneEdited = newScenePtr;
    if ( refresh ) Reload();
}

void SceneCanvas::SetScrollbars(wxScrollBar * scrollbar1_, wxScrollBar * scrollbar2_)
{
    scrollBar1 = scrollbar1_;
    scrollBar2 = scrollbar2_;
}

void SceneCanvas::OnKey( wxKeyEvent& evt )
{
    //Si on est en mode �diteur
    if ( scene.editing )
    {
        //ajout
        if ( evt.GetKeyCode() == WXK_INSERT )
        {
            wxCommandEvent unused;
            OnAddObjetSelected(unused);
        }
        //Suppression
        else if ( evt.GetKeyCode() == WXK_DELETE )
        {
            wxCommandEvent unused;
            OnDelObjetSelected(unused);
        }
    }
    evt.StopPropagation();
}


void SceneCanvas::OnUpdate()
{
    //On v�rifie qu'on ne doit pas mettre � jour la sc�ne
    if ( !scene.running || scene.editing )
    {
        if ( mainEditorCommand.QueryImagesNeedRefresh() )
        {
            game.imageManager.LoadImagesFromFile( gameEdited );
            mainEditorCommand.ImagesDontNeedRefresh(); //Les images sont recharg�s

            Reload();
            mainEditorCommand.SceneDontNeedRefresh();//La sc�ne aussi
        }
        else if ( mainEditorCommand.QuerySceneNeedRefresh() )
        {
            Reload();
            mainEditorCommand.SceneDontNeedRefresh();//La sc�ne aussi
        }
    }

    if ( scene.running )
    {
        int retourEvent = scene.RenderAndStep(1);

        if ( retourEvent == -2 )
            wxLogStatus( _( "Dans le jeu final, le jeu se terminera." ) );
        else if ( retourEvent != -1 )
            wxLogStatus( _( "Dans le jeu final, un changement de sc�ne s'effectuera." ) );

    }
    else if ( !scene.running && !scene.editing )
        scene.RenderWithoutStep();
    else
        scene.RenderEdittimeScene();

    UpdateScrollbars();
}

////////////////////////////////////////////////////////////
/// Met � jour les barres de d�filements
////////////////////////////////////////////////////////////
void SceneCanvas::UpdateScrollbars()
{
    if ( scrollBar1 == NULL )
        return;
    if ( scrollBar2 == NULL )
        return;

    //On calcule la position du thumb
    int thumbY = scene.view.GetCenter().y+scrollBar2->GetRange()/2-GetHeight()/2;
    scrollBar2->SetScrollbar(thumbY, GetHeight(), scrollBar2->GetRange(), GetHeight());

    int thumbX = scene.view.GetCenter().x+scrollBar1->GetRange()/2-GetWidth()/2;
    scrollBar1->SetScrollbar(thumbX, GetWidth(), scrollBar1->GetRange(), GetWidth());

    //On agrandit les scrollbars si besoin est
    if ( (thumbY+0) <= 0 || (thumbY+GetHeight()) >= scrollBar2->GetRange())
    {
        int ajout = 400;
        scrollBar2->SetScrollbar(thumbY+ajout/2, GetHeight(), scrollBar2->GetRange()+ajout, GetHeight());
    }

    if ( (thumbX+0) <= 0 || (thumbX+GetWidth()) >= scrollBar1->GetRange())
    {
        int ajout = 400;
        scrollBar1->SetScrollbar(thumbX+ajout/2, GetWidth(), scrollBar1->GetRange()+ajout, GetWidth());
    }
}

void SceneCanvas::UpdateContextMenu()
{
    //Peut on remonter les objets sur un calque plus haut ?
    int lowestLayer = GetObjectsSelectedLowestLayer();

    contextMenu.FindItem(ID_LAYERUPMENU)->Enable(false);
    if ( lowestLayer+1 < scene.layers.size() )
    {
        string name = scene.layers[lowestLayer+1].GetName();
        if ( name == "" ) name = _("Calque de base");
        contextMenu.FindItem(ID_LAYERUPMENU)->Enable(true);
        contextMenu.FindItem(ID_LAYERUPMENU)->SetItemLabel(string(_("Passer le(s) objet(s) sur le calque \"")) + name +"\"");
    }

    //Peut on descendre les objets sur un calque plus bas ? ( pl�onasme )
    int highestLayer = GetObjectsSelectedHighestLayer();

    contextMenu.FindItem(ID_LAYERDOWNMENU)->Enable(false);
    if ( highestLayer-1 >= 0 )
    {
        string name = scene.layers[highestLayer-1].GetName();
        if ( name == "" ) name = _("Calque de base");

        contextMenu.FindItem(ID_LAYERDOWNMENU)->Enable(true);
        contextMenu.FindItem(ID_LAYERDOWNMENU)->SetItemLabel(string(_("Passer le(s) objet(s) sur le calque \"")) + name +"\"");
    }
}

////////////////////////////////////////////////////////////
/// Bouton gauche : D�placement objet
////////////////////////////////////////////////////////////
void SceneCanvas::OnLeftDown( wxMouseEvent &event )
{
    SetFocus();

    if ( !scene.editing )
        return;

    if ( hasJustRightClicked )
    {
        hasJustRightClicked = false;
        return;
    }

    int idObject = scene.FindSmallestObject();

    //Suppression de la selection
    if ( idObject == -1 || /*Si clic n'importe o� */
        (( !scene.input->IsKeyDown(sf::Key::LShift) && !scene.input->IsKeyDown(sf::Key::RShift) ) && /*Ou si clic sur un objet sans Shift*/
         find(scene.idObjectsSelected.begin(), scene.idObjectsSelected.end(), idObject) == scene.idObjectsSelected.end() ))
    {
        scene.idObjectsSelected.clear();
        scene.xObjectsSelected.clear();
        scene.yObjectsSelected.clear();
    }

    //On ajoute l'objet surlign� dans les objets � bouger
    if ( idObject == -1 ) return;

    if ( find(scene.idObjectsSelected.begin(), scene.idObjectsSelected.end(), idObject) == scene.idObjectsSelected.end() )
    {
        scene.idObjectsSelected.push_back(idObject);

        //Et on renseigne sa position de d�part :
        scene.xObjectsSelected.push_back(scene.objets[idObject]->GetX());
        scene.yObjectsSelected.push_back(scene.objets[idObject]->GetY());
    }

    scene.isMovingObject = true;
    scene.oldMouseX = ConvertCoords(scene.input->GetMouseX(), 0).x; //Position de d�part de la souris
    scene.oldMouseY = ConvertCoords(0, scene.input->GetMouseY()).y;
}

////////////////////////////////////////////////////////////
/// Bouton gauche relach� : Fin du d�placement
////////////////////////////////////////////////////////////
void SceneCanvas::OnLeftUp( wxMouseEvent &event )
{
    //Relachement de la souris :
    //Pour les objets selectionn�s, leurs nouvelle
    //position de d�part est celle o� ils sont.
    if ( scene.isMovingObject )
    {
        for (unsigned int i = 0;i<scene.idObjectsSelected.size();++i)
        {
            int ID = scene.idObjectsSelected.at(i);

            if ( ID > -1 && static_cast<unsigned>(ID) < scene.objets.size() )
            {
                bool trouve = false;
                unsigned int j = 0;
                while ( j < sceneEdited->positionsInitiales.size() && !trouve )
                {
                    if ( sceneEdited->positionsInitiales.at( j ).objectName == scene.objets[ID]->GetName() &&
                            sceneEdited->positionsInitiales.at( j ).x == scene.objets[ID]->GetX() &&
                            sceneEdited->positionsInitiales.at( j ).y == scene.objets[ID]->GetY() )
                    {

                        scene.xObjectsSelected[i] = sceneEdited->positionsInitiales.at( j ).x;
                        scene.yObjectsSelected[i] = sceneEdited->positionsInitiales.at( j ).y;

                        trouve = true;
                    }

                    j++;
                }
            }
        }
    }

    scene.isMovingObject = false;
}

////////////////////////////////////////////////////////////
/// Double clic : insertion objet
////////////////////////////////////////////////////////////
void SceneCanvas::OnLeftDClick( wxMouseEvent &event )
{
    wxCommandEvent unused;
    OnAddObjetSelected(unused);
}

////////////////////////////////////////////////////////////
/// Insertion d'un objet
////////////////////////////////////////////////////////////
void SceneCanvas::OnAddObjetSelected( wxCommandEvent & event )
{
    //Seulement en mode �diteur
    if ( !scene.editing )
        return;

    scene.isMovingObject = false;

    if ( scene.objectToAdd == "" ) { wxLogMessage( _( "Vous n'avez selectionn� aucun objet � ajouter.\nS�lectionnez en un avec le bouton \"Choisir un objet � ajouter\" dans la barre d'outils." ) ); return;}
    if ( Picker::PickOneObject( &sceneEdited->objetsInitiaux, scene.objectToAdd ) == -1
        && Picker::PickOneObject( &game.globalObjects, scene.objectToAdd ) == -1 )
    {
        if ( wxMessageBox( _( "Vous tentez d'ajouter un objet qui n'existe pas ou plus dans la liste des objets.\n�tes vous sur de vouloir l'ajouter � la sc�ne ?" ), "L'objet n'existe pas dans la liste !",
                           wxYES_NO ) == wxID_NO )
        {
            return; //On arr�te si l'utilisateur ne veut pas rajouter son objet.
        }
    }

    InitialPosition pos;
    pos.objectName = scene.objectToAdd; //A choisir avec un dialog appropri� ou par drag'n'drop
    if ( scene.grid && scene.snap )
    {
        pos.x = static_cast<int>(ConvertCoords(scene.input->GetMouseX(), 0).x/scene.gridWidth)*scene.gridWidth;
        pos.y = static_cast<int>(ConvertCoords(0, scene.input->GetMouseY()).y/scene.gridHeight)*scene.gridHeight;
    }
    else
    {
        pos.x = ConvertCoords(scene.input->GetMouseX(), 0).x;
        pos.y = ConvertCoords(0, scene.input->GetMouseY()).y;
    }
    pos.direction = 0;
    pos.zOrder = 0;
    pos.layer = scene.addOnLayer;
    sceneEdited->positionsInitiales.push_back( pos );



    Reload();
}

////////////////////////////////////////////////////////////
/// Clic droit : edition propri�t�s objet
////////////////////////////////////////////////////////////
void SceneCanvas::OnRightUp( wxMouseEvent &event )
{
    if ( !scene.editing )
        return;

    int idObject = scene.FindSmallestObject();

    //Suppression de la selection
    if ( idObject == -1 || /*Si clic n'importe o� */
        (( !scene.input->IsKeyDown(sf::Key::LShift) && !scene.input->IsKeyDown(sf::Key::RShift) ) && /*Ou si clic sur un objet sans Shift*/
         find(scene.idObjectsSelected.begin(), scene.idObjectsSelected.end(), idObject) == scene.idObjectsSelected.end() ))
    {
        scene.idObjectsSelected.clear();
        scene.xObjectsSelected.clear();
        scene.yObjectsSelected.clear();
    }

    //On ajoute l'objet surlign� dans les objets � bouger
    if ( idObject == -1 ) return;

    if ( find(scene.idObjectsSelected.begin(), scene.idObjectsSelected.end(), idObject) == scene.idObjectsSelected.end() )
    {
        scene.idObjectsSelected.push_back(idObject);

        //Et on renseigne sa position de d�part :
        scene.xObjectsSelected.push_back(scene.objets[idObject]->GetX());
        scene.yObjectsSelected.push_back(scene.objets[idObject]->GetY());
    }

    OnUpdate(); //Pour afficher le rectangle de selection
    UpdateContextMenu();
    PopupMenu(&contextMenu);

    hasJustRightClicked = true;
}

////////////////////////////////////////////////////////////
/// D�placement de(s) objet(s) selectionn�(s) sur le calque sup�rieur
////////////////////////////////////////////////////////////
void SceneCanvas::OnLayerUpSelected(wxCommandEvent & event)
{
    int lowestLayer = GetObjectsSelectedLowestLayer();
    if ( lowestLayer+1 < 0 || static_cast<unsigned>(lowestLayer+1) >= scene.layers.size() )
        return;

    string layerName = scene.layers.at(lowestLayer+1).GetName();

    for (unsigned int i =0;i<scene.idObjectsSelected.size();++i)
    {
        //R�cup�rons la position initiale
        int posId = GetPositionInitialeIdFromObjectId(scene.idObjectsSelected[i]);
        if ( posId != -1 )
            sceneEdited->positionsInitiales.at(posId).layer = layerName;
            scene.objets[scene.idObjectsSelected[i]]->SetLayer(layerName);
    }
}

////////////////////////////////////////////////////////////
/// D�placement de(s) objet(s) selectionn�(s) sur le calque inf�rieur
////////////////////////////////////////////////////////////
void SceneCanvas::OnLayerDownSelected(wxCommandEvent & event)
{
    int highestLayer = GetObjectsSelectedLowestLayer();
    if ( highestLayer-1 < 0 || static_cast<unsigned>(highestLayer-1) >= scene.layers.size() )
        return;

    string layerName = scene.layers.at(highestLayer-1).GetName();

    for (unsigned int i =0;i<scene.idObjectsSelected.size();++i)
    {
        //R�cup�rons la position initiale
        int posId = GetPositionInitialeIdFromObjectId(scene.idObjectsSelected[i]);
        if ( posId != -1 )
        {
            sceneEdited->positionsInitiales.at(posId).layer = layerName;
            scene.objets[scene.idObjectsSelected[i]]->SetLayer(layerName);
        }
    }
}

////////////////////////////////////////////////////////////
/// Editer les valeurs initiales d'un objet sur la sc�ne
////////////////////////////////////////////////////////////
void SceneCanvas::OnPropObjSelected(wxCommandEvent & event)
{
    if ( !scene.editing )
        return;

    //Cherche l'objet sous la souris
    int IDpluspetit = scene.FindSmallestObject();
    if ( IDpluspetit == -1 ) return;

    unsigned int i = 0;
    bool trouve = false;

    //On cherche la position initiale correspondante
    while ( i < sceneEdited->positionsInitiales.size() && !trouve )
    {
        if ( sceneEdited->positionsInitiales.at( i ).objectName == scene.objets[IDpluspetit]->GetName() &&
                sceneEdited->positionsInitiales.at( i ).x == scene.objets[IDpluspetit]->GetX() &&
                sceneEdited->positionsInitiales.at( i ).y == scene.objets[IDpluspetit]->GetY() )
        {
            //Affichage des propri�t�s de l'objet sous la souris
            EditOptionsPosition DialogPosition( this, game, scene, sceneEdited->positionsInitiales.at( i ) );
            if ( DialogPosition.ShowModal() == 1 )
            {
                sceneEdited->positionsInitiales.at( i ) = DialogPosition.position;
            }


            Reload();
            return;
        }

        i++;
    }
}

////////////////////////////////////////////////////////////
/// Double clic droit : propri�t�s direct de l'objet
////////////////////////////////////////////////////////////
void SceneCanvas::OnRightDClick( wxMouseEvent &event )
{
    wxCommandEvent unusedEvent;
    OnPropObjSelected(unusedEvent);
}

////////////////////////////////////////////////////////////
/// Suppression de(s) objet(s) selectionn�(s)
////////////////////////////////////////////////////////////
void SceneCanvas::OnDelObjetSelected(wxCommandEvent & event)
{
    if ( !scene.editing )
        return;

    for (unsigned int i = 0;i<scene.idObjectsSelected.size();++i)
    {
        int ID = scene.idObjectsSelected.at(i);

        if ( ID > -1 && static_cast<unsigned>(ID) < scene.objets.size() )
        {
            bool trouve = false;
            unsigned int j = 0;
            while ( j < sceneEdited->positionsInitiales.size() && !trouve )
            {
                if ( sceneEdited->positionsInitiales.at( j ).objectName == scene.objets[ID]->GetName() &&
                        sceneEdited->positionsInitiales.at( j ).x == scene.objets[ID]->GetX() &&
                        sceneEdited->positionsInitiales.at( j ).y == scene.objets[ID]->GetY() )
                {
                    sceneEdited->positionsInitiales.erase(sceneEdited->positionsInitiales.begin() + j);
                    scene.objets[ID]->SetName( "" ); //On ne supprime pas l'objet pour le moment
                    trouve = true;
                }

                j++;
            }
        }
    }
    //Suppression effective des objets
    scene.objets.erase( std::remove_if( scene.objets.begin(), scene.objets.end(), MustBeDeleted ), scene.objets.end() );

    scene.idObjectsSelected.clear();
    scene.xObjectsSelected.clear();
    scene.yObjectsSelected.clear();
}

////////////////////////////////////////////////////////////
/// A chaque d�placement de la souris :
///
/// -affichage position
/// -bouger la vue si on suit la souris
////////////////////////////////////////////////////////////
void SceneCanvas::OnMotion( wxMouseEvent &event )
{
    //Milles merci laurent.
    int mouseXInScene = static_cast<int>(sf::RenderWindow::ConvertCoords(scene.input->GetMouseX(), 0).x);
    int mouseYInScene = static_cast<int>(sf::RenderWindow::ConvertCoords(0, scene.input->GetMouseY()).y);

    wxString Xstr = st( mouseXInScene );
    wxString Ystr = st( mouseYInScene );

    if ( !scene.editing )
        wxLogStatus( wxString( _( "Position " ) ) + Xstr + wxString( _( ";" ) ) + Ystr + wxString( _( "." ) ) );
    else
        wxLogStatus( wxString( _( "Position " ) ) + Xstr + wxString( _( ";" ) ) + Ystr + wxString( _( ". SHIFT pour s�lection multiple, clic droit pour plus d'options." ) ) );

    //Le reste concerne juste le mode �dition
    if ( scene.running )
        return;

    //D�placement avec la souris
    if ( scene.isMoving )
        scene.view.Move( scene.deplacementOX - mouseXInScene, scene.deplacementOY - mouseYInScene );

    //D�placement de la position initiale d'un objet
    if ( scene.isMovingObject )
    {
        for (unsigned int i = 0;i<scene.idObjectsSelected.size();++i)
        {
            int ID = scene.idObjectsSelected.at(i);

            if ( ID > -1 && static_cast<unsigned>(ID) < scene.objets.size() )
            {
                bool trouve = false;
                unsigned int j = 0;
                while ( j < sceneEdited->positionsInitiales.size() && !trouve )
                {
                    if ( sceneEdited->positionsInitiales.at( j ).objectName == scene.objets[ID]->GetName() &&
                            sceneEdited->positionsInitiales.at( j ).x == scene.objets[ID]->GetX() &&
                            sceneEdited->positionsInitiales.at( j ).y == scene.objets[ID]->GetY() )
                    {

                        //D�placement effectu� par la souris
                        int deltaX = mouseXInScene - scene.oldMouseX;
                        int deltaY = mouseYInScene - scene.oldMouseY;

                        //Anciennes et nouvelles coordonn�es
                        int oldX = scene.xObjectsSelected[i];
                        int oldY = scene.yObjectsSelected[i];
                        int newX = oldX + deltaX;
                        int newY = oldY + deltaY;

                        if ( scene.grid && scene.snap )
                        {
                            newX = static_cast<int>(newX/scene.gridWidth)*scene.gridWidth;
                            newY = static_cast<int>(newY/scene.gridHeight)*scene.gridHeight;
                        }

                        //Modification de l'emplacement initial
                        sceneEdited->positionsInitiales.at( j ).x = newX;
                        sceneEdited->positionsInitiales.at( j ).y = newY;

                        //On bouge aussi l'objet actuellement affich�
                        scene.objets[ID]->SetX( newX );
                        scene.objets[ID]->SetY( newY );

                        trouve = true;
                    }

                    j++;
                }
            }
        }
    }

}

////////////////////////////////////////////////////////////
/// Clic molette : Des/activer d�placement � la souris
////////////////////////////////////////////////////////////
void SceneCanvas::OnMiddleDown( wxMouseEvent &event )
{
    if ( !scene.isMoving )
    {
        scene.isMoving = true;
        scene.deplacementOX = ConvertCoords(scene.input->GetMouseX(), 0).x;
        scene.deplacementOY = ConvertCoords(0, scene.input->GetMouseY()).y;
        SetCursor( wxCursor( wxCURSOR_SIZING ) );
        return;
    }
    else
    {
        scene.isMoving = false;
        SetCursor( wxNullCursor );
    }
}

void SceneCanvas::OnMiddleUp( wxMouseEvent &event )
{
}


void SceneCanvas::Reload()
{
    game.LoadFromGame(gameEdited);

    scene.StopMusic();
    scene.LoadFromScene( *sceneEdited );

    UpdateScrollbars();
}

////////////////////////////////////////////////////////////
/// Zoom / dezoom � la molette
/// Il faut prendre garde � garder les proportions de la fen�tre
////////////////////////////////////////////////////////////
void SceneCanvas::OnMouseWheel( wxMouseEvent &event )
{
    if (scene.running)
        return;

    //La rotation de la molette
    float rotation = event.GetWheelRotation();
    scene.zoom += ( rotation / 25 );

    //Le rapport entre la largeur et la hauteur
    float qwoh = scene.view.GetSize().x / scene.view.GetSize().y;

    //La nouvelle hauteur
    float newheight = scene.view.GetSize().y + ( rotation / 25 );

    scene.view.SetSize( newheight*qwoh, newheight );
}

int SceneCanvas::GetObjectsSelectedHighestLayer()
{
    int highestLayer = 0;
    for (unsigned int i =0;i<scene.idObjectsSelected.size();++i)
    {
        //R�cup�rons la position initiale
        int posId = GetPositionInitialeIdFromObjectId(scene.idObjectsSelected[i]);
        if ( posId != -1 )
        {
            int layerObjId = 0;
            //On cherche le num�ro du calque de l'objet
            for (unsigned int layerId = 0;layerId<scene.layers.size();++layerId)
            {
                if ( scene.layers[layerId].GetName() == sceneEdited->positionsInitiales.at(posId).layer )
                   layerObjId = layerId;
            }

            if ( layerObjId > highestLayer )
                highestLayer = layerObjId;
        }
    }

    return highestLayer;
}

int SceneCanvas::GetObjectsSelectedLowestLayer()
{
    int lowestLayer = scene.layers.size()-1;
    for (unsigned int i =0;i<scene.idObjectsSelected.size();++i)
    {
        //R�cup�rons la position initiale
        int posId = GetPositionInitialeIdFromObjectId(scene.idObjectsSelected[i]);
        if ( posId != -1 )
        {
            int layerObjId = 0;
            //On cherche le num�ro du calque de l'objet
            for (unsigned int layerId = 0;layerId<scene.layers.size();++layerId)
            {
                if ( scene.layers[layerId].GetName() == sceneEdited->positionsInitiales.at(posId).layer )
                   layerObjId = layerId;
            }

            if ( layerObjId < lowestLayer )
                lowestLayer = layerObjId;
        }
    }

    return lowestLayer;
}

////////////////////////////////////////////////////////////
/// Renvoi l'ID d'une position initiale � partir d'un objet sur la sc�ne
////////////////////////////////////////////////////////////
int SceneCanvas::GetPositionInitialeIdFromObjectId(int ID)
{
    if ( ID > -1 && static_cast<unsigned>(ID) < scene.objets.size() )
    {
        for (unsigned int j = 0;j < sceneEdited->positionsInitiales.size();++j)
        {
            if ( sceneEdited->positionsInitiales.at( j ).objectName == scene.objets[ID]->GetName() &&
                    sceneEdited->positionsInitiales.at( j ).x == scene.objets[ID]->GetX() &&
                    sceneEdited->positionsInitiales.at( j ).y == scene.objets[ID]->GetY() )
            {
                return j;
            }
        }
    }

    return -1;
}

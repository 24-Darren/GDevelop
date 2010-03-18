/**
 *  Game Develop
 *  2008-2010 Florian Rival (Florian.Rival@gmail.com)
 */

#include <vector>
#include <string>
#include "GDL/Object.h"
#include <SFML/System.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "GDL/aCamera.h"
#include "GDL/Event.h"
#include <iostream>
#include <sstream>
#include "GDL/Chercher.h"
#include "GDL/algo.h"
#include "GDL/Force.h"
#include <iostream>
#include "GDL/Access.h"
#include "GDL/RuntimeScene.h"
#include "GDL/ObjectsConcerned.h"

/**
 * Change the render zone of a camera
 */
bool ActCameraViewport( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    std::string layer = action.GetParameter(0).GetPlainString();
    unsigned int cameraNb = eval.EvalExp(action.GetParameter(1));

    RuntimeCamera & camera = scene->GetLayer(layer).GetCamera(cameraNb);

    camera.GetCameraInfo().defaultViewport = false;
    camera.GetCameraInfo().viewport.Left = eval.EvalExp(action.GetParameter(0));
    camera.GetCameraInfo().viewport.Top = eval.EvalExp(action.GetParameter(1));
    camera.GetCameraInfo().viewport.Right = eval.EvalExp(action.GetParameter(2));
    camera.GetCameraInfo().viewport.Bottom = eval.EvalExp(action.GetParameter(3));
    camera.GetSFMLView().SetViewport(camera.GetCameraInfo().viewport);
}

/**
 * Change the size of a camera ( reset zoom )
 */
bool ActCameraSize( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    std::string layer = action.GetParameter(0).GetPlainString();
    unsigned int cameraNb = eval.EvalExp(action.GetParameter(1));

    RuntimeCamera & camera = scene->GetLayer(layer).GetCamera(cameraNb);

    camera.GetCameraInfo().defaultSize = false;
    camera.GetCameraInfo().size.x = eval.EvalExp(action.GetParameter(0));
    camera.GetCameraInfo().size.y = eval.EvalExp(action.GetParameter(1));
    camera.GetSFMLView().SetSize(camera.GetCameraInfo().size);
}

/**
 * Add a camera to a layer
 */
bool ActAddCamera( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    RuntimeLayer & layer = scene->GetLayer(action.GetParameter(0).GetPlainString());

    Camera cameraInfo;

    //Set the size of the camera
    if ( !action.GetParameter(1).GetPlainString().empty() || !action.GetParameter(2).GetPlainString().empty() )
        cameraInfo.defaultSize = false;

    cameraInfo.size.x = eval.EvalExp(action.GetParameter(1));
    cameraInfo.size.y = eval.EvalExp(action.GetParameter(2));

    //Set the viewport
    if ( !action.GetParameter(3).GetPlainString().empty() || !action.GetParameter(4).GetPlainString().empty() ||
         !action.GetParameter(5).GetPlainString().empty() || !action.GetParameter(6).GetPlainString().empty())
        cameraInfo.defaultViewport = false;

    cameraInfo.viewport.Left = eval.EvalExp(action.GetParameter(3));
    cameraInfo.viewport.Top = eval.EvalExp(action.GetParameter(4));
    cameraInfo.viewport.Right = eval.EvalExp(action.GetParameter(5));
    cameraInfo.viewport.Bottom = eval.EvalExp(action.GetParameter(6));

    //Create a runtime camera from the camera
    const sf::RenderWindow * window = scene->renderWindow;
    RuntimeCamera camera(cameraInfo, window ? window->GetDefaultView() : sf::View() );

    //Add the runtime camera to the layer
    layer.AddCamera(camera);
}


/**
 * Delete a camera of a layer
 */
bool ActDeleteCamera( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    unsigned int cameraNb = eval.EvalExp(action.GetParameter(1));

    RuntimeLayer & layer = scene->GetLayer(action.GetParameter(0).GetPlainString());

    layer.DeleteCamera(cameraNb);
}

////////////////////////////////////////////////////////////
/// Fixe la cam�ra sur un objet, sans d�passer un cadre
///
/// Type : FixCamera
/// Param�tre 1 : Objet
/// Param�tre 2 : Xmin
/// Param�tre 3 : Ymin
/// Param�tre 4 : Xmax
/// Param�tre 5 : Ymax
/// Param�tre 6 : Calque
////////////////////////////////////////////////////////////
bool ActFixCamera( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    ObjList list = objectsConcerned.Pick(action.GetParameter( 0 ).GetAsObjectIdentifier(), action.IsGlobal());

    if ( list.empty() ) return false;

    //Compatibilit� Game Develop < 1.1.5429 :
    std::string layer = "";
    if ( action.GetParameters().size() >= 7 )
        layer = action.GetParameter(6).GetPlainString();

    //Compatibilit� Game Develop < 1.2.8699 :
    unsigned int camera = 0;
    if ( action.GetParameters().size() >= 8 )
        camera = eval.EvalExp(action.GetParameter(7));

    sf::View & view = scene->GetLayer(layer).GetCamera(camera).GetSFMLView();

    float decalementX = 0;
    float decalementY = 0;

    //Prise en compte des d�placements de l'objet
    if ( action.GetParameters().size() < 6 )
    {
        decalementX = ( list[0]->TotalForceX() * scene->GetElapsedTime() );
        decalementY = ( list[0]->TotalForceY() * scene->GetElapsedTime() );
    }
    else if ( action.GetParameter(5).GetPlainString() != "no" && action.GetParameter(5).GetPlainString() != "non")
    {
        decalementX = ( list[0]->TotalForceX() * scene->GetElapsedTime() );
        decalementY = ( list[0]->TotalForceY() * scene->GetElapsedTime() );
    }

    //Si on est dans le cadre
    if ( list[0]->GetX() > eval.EvalExp(action.GetParameter( 1 ))
        && list[0]->GetX() < eval.EvalExp(action.GetParameter( 3 ))
        && list[0]->GetY() > eval.EvalExp(action.GetParameter( 2 ))
        && list[0]->GetY() < eval.EvalExp(action.GetParameter( 4 ))
        )
    {
        view.SetCenter(list[0]->GetX() + decalementX, list[0]->GetY() + decalementY);
    }

    //Si on n'est pas dedans.
    if ( ( list[0]->GetX() < eval.EvalExp(action.GetParameter( 1 ))
        || list[0]->GetX() > eval.EvalExp(action.GetParameter( 3 )) )
        && list[0]->GetY() > eval.EvalExp(action.GetParameter( 2 ))
        && list[0]->GetY() < eval.EvalExp(action.GetParameter( 4 )) )

    {
        view.SetCenter(view.GetCenter().x, list[0]->GetY() + decalementY);
    }
    if ( ( list[0]->GetY() < eval.EvalExp(action.GetParameter( 2 ))
        || list[0]->GetY() > eval.EvalExp(action.GetParameter( 4 )) )
        && list[0]->GetX() > eval.EvalExp(action.GetParameter( 1 ))
        && list[0]->GetX() < eval.EvalExp(action.GetParameter( 3 )))
    {
        view.SetCenter(list[0]->GetX() + decalementX, view.GetCenter().y);
    }

    return true;
}


////////////////////////////////////////////////////////////
/// Fixe la cam�ra sur un objet
///
/// Type : FixCamera
/// Param�tre 1 : Objet
/// Param�tre 2 : Prise en compte du d�placement ( Oui/Non )
/// Param�tre 3 : Calque
////////////////////////////////////////////////////////////
bool ActCentreCamera( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    ObjList list = objectsConcerned.Pick(action.GetParameter( 0 ).GetAsObjectIdentifier(), action.IsGlobal());

    if ( list.empty() ) return false;

    float decalementX = 0;
    float decalementY = 0;

    //Compatibilit� Game Develop < 1.1.5429 :
    std::string layer = "";
    if ( action.GetParameters().size() >= 3 )
        layer = action.GetParameter(2).GetPlainString();

    //Compatibilit� Game Develop < 1.2.8699 :
    unsigned int camera = 0;
    if ( action.GetParameters().size() >= 4 )
        camera = eval.EvalExp(action.GetParameter(3));

    sf::View & view = scene->GetLayer(layer).GetCamera(camera).GetSFMLView();

    //Prise en compte des d�placements de l'objet
    if ( action.GetParameters().size() < 2 )
    {
        decalementX = ( list[0]->TotalForceX() * scene->GetElapsedTime() );
        decalementY = ( list[0]->TotalForceY() * scene->GetElapsedTime() );
    }
    else if ( action.GetParameter(1).GetPlainString() != "no" && action.GetParameter(1).GetPlainString() != "non")
    {
        decalementX = ( list[0]->TotalForceX() * scene->GetElapsedTime() );
        decalementY = ( list[0]->TotalForceY() * scene->GetElapsedTime() );
    }

    view.SetCenter(list[0]->GetX() + decalementX,
                    list[0]->GetY() + decalementY);

    return true;
}

////////////////////////////////////////////////////////////
/// Zoomer / D�zoomer
///
/// Type : ZoomCamera
/// Param�tre 1 : Nouvelle valeur
/// Param�tre 2 : Calque
////////////////////////////////////////////////////////////
bool ActZoomCamera( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    //Compatibilit� Game Develop < 1.1.5429 :
    std::string layer = "";
    if ( action.GetParameters().size() >= 2 )
        layer = action.GetParameter(1).GetPlainString();

    //Compatibilit� Game Develop < 1.2.8699 :
    unsigned int cameraNb = 0;
    if ( action.GetParameters().size() >= 3 )
        cameraNb = eval.EvalExp(action.GetParameter(2));

    RuntimeCamera & camera = scene->GetLayer(layer).GetCamera(cameraNb);

    float newZoom = eval.EvalExp( action.GetParameter( 0 ) );
    if ( newZoom == 0 ) return false;

    camera.GetSFMLView().SetSize((camera.GetCameraInfo().size.x/newZoom), (camera.GetCameraInfo().size.y/newZoom));

    return true;
}

////////////////////////////////////////////////////////////
/// Faire tourner la cam�ra
///
/// Type : RotateCamera
/// Param�tre 1 : Nouvelle valeur
/// Param�tre 2 : Signe de la modification
/// Param�tre 3 : Calque
////////////////////////////////////////////////////////////
bool ActRotateCamera( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    //Compatibilit� Game Develop < 1.1.5429 :
    std::string layer = "";
    if ( action.GetParameters().size() >= 3 )
        layer = action.GetParameter(2).GetPlainString();

    //Compatibilit� Game Develop < 1.2.8699 :
    unsigned int camera = 0;
    if ( action.GetParameters().size() >= 4 )
        camera = eval.EvalExp(action.GetParameter(3));

    sf::View & view = scene->GetLayer(layer).GetCamera(camera).GetSFMLView();

    float value = eval.EvalExp( action.GetParameter( 0 ) );
    if ( action.GetParameter( 1 ).GetPlainString().empty() || action.GetParameter( 1 ).GetAsModOperator() == GDExpression::Set ) view.SetRotation(value);
    else if ( action.GetParameter( 1 ).GetAsModOperator() == GDExpression::Add ) view.SetRotation(view.GetRotation()+value);
    else if ( action.GetParameter( 1 ).GetAsModOperator() == GDExpression::Substract ) view.SetRotation(view.GetRotation()-value);
    else if ( action.GetParameter( 1 ).GetAsModOperator() == GDExpression::Multiply ) view.SetRotation(view.GetRotation()*value);
    else if ( action.GetParameter( 1 ).GetAsModOperator() == GDExpression::Divide ) view.SetRotation(view.GetRotation()/value);

    return true;
}

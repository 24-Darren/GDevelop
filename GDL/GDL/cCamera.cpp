/**
 *  Game Develop
 *      Player
 *
 *  Par Florian "4ian" Rival
 *
 */
/**
 *
 *
 *  Contient une ou plusieurs conditions
 */

#include <vector>
#include <string>
#include "GDL/Object.h"
#include <cmath>
#include "GDL/cADS.h"
#include "GDL/Event.h"
#include <iostream>
#include <sstream>
#include "GDL/Chercher.h"
#include "GDL/algo.h"
#include "GDL/Force.h"
#include <iostream>
#include "GDL/Access.h"
#include <SFML/Window.hpp>
#include "GDL/RuntimeScene.h"

#include "GDL/Instruction.h"

////////////////////////////////////////////////////////////
/// Test de la position X de la cam�ra
///
/// Type : CameraX
/// Param�tre 1 : Position x � tester
/// Param�tre 2 : Signe du test
/// Param�tre 3 : Calque
////////////////////////////////////////////////////////////
bool CondCameraX( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & condition, const Evaluateur & eval )
{
    sf::View * view = NULL;

    //Compatibilit� Game Develop < 1.1.5429 :
    if ( condition.GetParameters().size() >= 3 )
        view = &scene->ModLayer(condition.GetParameter(2).GetPlainString()).ModView();
    else
        view = &scene->ModLayer("").ModView();

    //Enfin, on teste vraiment.
    //optimisation : test du signe en premier
    if (( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Equal && (view->GetCenter().x - view->GetSize().x/2) == eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Inferior && (view->GetCenter().x - view->GetSize().x/2) < eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Superior && (view->GetCenter().x - view->GetSize().x/2) > eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::InferiorOrEqual && (view->GetCenter().x - view->GetSize().x/2) <= eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::SuperiorOrEqual && (view->GetCenter().x - view->GetSize().x/2) >= eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Different && (view->GetCenter().x - view->GetSize().x/2) != eval.EvalExp( condition.GetParameter( 0 ) ) )
        )
    {
        if ( !condition.IsInverted() ) return true;
    }
    else
    {
        if ( condition.IsInverted() ) return true;
    }

    return false;
}


////////////////////////////////////////////////////////////
/// Test de la position Y de la cam�ra
///
/// Type : CameraY
/// Param�tre 1 : Position x � tester
/// Param�tre 2 : Signe du test
/// Param�tre 3 : Calque
////////////////////////////////////////////////////////////
bool CondCameraY( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & condition, const Evaluateur & eval )
{
    sf::View * view = NULL;

    //Compatibilit� Game Develop < 1.1.5429 :
    if ( condition.GetParameters().size() >= 3 )
        view = &scene->ModLayer(condition.GetParameter(2).GetPlainString()).ModView();
    else
        view = &scene->ModLayer("").ModView();

    //Enfin, on teste vraiment.
    //optimisation : test du signe en premier
    if (( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Equal && (view->GetCenter().y - view->GetSize().y/2) == eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Inferior && (view->GetCenter().y - view->GetSize().y/2) < eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Superior && (view->GetCenter().y - view->GetSize().y/2) > eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::InferiorOrEqual && (view->GetCenter().y - view->GetSize().y/2) <= eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::SuperiorOrEqual && (view->GetCenter().y - view->GetSize().y/2) >= eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Different && (view->GetCenter().y - view->GetSize().y/2) != eval.EvalExp( condition.GetParameter( 0 ) ) )
       )
    {
        if ( !condition.IsInverted() ) return true;
    }
    else
    {
        if ( condition.IsInverted() ) return true;
    }

    return false;
}

////////////////////////////////////////////////////////////
/// Test de l'angle de la cam�ra
///
/// Type : CameraAngle
/// Param�tre 1 : Angle � tester
/// Param�tre 2 : Signe du test
/// Param�tre 3 : Calque
////////////////////////////////////////////////////////////
bool CondCameraAngle( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & condition, const Evaluateur & eval )
{
    sf::View * view = NULL;

    //Compatibilit� Game Develop < 1.1.5429 :
    if ( condition.GetParameters().size() >= 3 )
        view = &scene->ModLayer(condition.GetParameter(2).GetPlainString()).ModView();
    else
        view = &scene->ModLayer("").ModView();

    //Enfin, on teste vraiment.
    //optimisation : test du signe en premier
    if (( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Equal && (view->GetRotation()) == eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Inferior && (view->GetRotation()) < eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Superior && (view->GetRotation()) > eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::InferiorOrEqual && (view->GetRotation()) <= eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::SuperiorOrEqual && (view->GetRotation()) >= eval.EvalExp( condition.GetParameter( 0 ) ) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Different && (view->GetRotation()) != eval.EvalExp( condition.GetParameter( 0 ) ) )
       )
    {
        if ( !condition.IsInverted() ) return true;
    }
    else
    {
        if ( condition.IsInverted() ) return true;
    }

    return false;
}

/**
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

#include <vector>
#include <string>
#include "GDL/Object.h"
#include <cmath>
#include "GDL/cTime.h"
#include "GDL/Event.h"
#include <iostream>
#include <sstream>
#include "GDL/Chercher.h"
#include "GDL/CommonTools.h"
#include "GDL/Force.h"
#include <iostream>

#include <SFML/Window.hpp>
#include "GDL/RuntimeScene.h"
#include "GDL/ObjectsConcerned.h"
#include "GDL/Instruction.h"

////////////////////////////////////////////////////////////
/// Test d'un timer. Renvoie true si le timer est sup�rieur
/// ou �gal au temps indiqu�
///
/// Type : Timer
/// Param�tre 1 : Secondes
/// Param�tre 2 : Nom du timer
///
////////////////////////////////////////////////////////////
bool CondTimer( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & condition )
{
    string timerName = condition.GetParameter( 1 ).GetAsTextExpressionResult(scene, objectsConcerned);
    if ( timerName == "" ) return false;

    //Le timer existe il ? on parcourt la liste.
    for ( unsigned int i = 0;i < scene.timers.size();i++ )
    {
        //On cherche le nom du timer
        if ( scene.timers[i].GetName() == timerName )
        {
            if ( scene.timers[i].GetTime() >= condition.GetParameter( 0 ).GetAsMathExpressionResult(scene, objectsConcerned) )
            {
                if ( condition.IsInverted() ) return false;
                return true;
            }
            if ( condition.IsInverted() ) return true;
            return false;
        }

    }

    return true;
}

////////////////////////////////////////////////////////////
/// Teste si le chronom�tre est en pause.
///
/// Type : TimerPaused
/// Param�tre 1 : Nom du timer
////////////////////////////////////////////////////////////
bool CondTimerPaused( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & condition )
{
    string timerName = condition.GetParameter( 0 ).GetAsTextExpressionResult(scene, objectsConcerned);
    if ( timerName == "" ) return false;

    //Le timer existe il ? on parcourt la liste.
    for ( unsigned int i = 0;i < scene.timers.size();i++ )
    {
        //On cherche le nom du timer
        if ( scene.timers[i].GetName() == timerName )
        {
            if (scene.timers[i].IsPaused())
            {
                if ( condition.IsInverted() ) return false;
                    return true;
            }
            if ( condition.IsInverted() ) return true;
            return false;
        }

    }

    return false;
}

////////////////////////////////////////////////////////////
/// Tester l'�chelle du temps actuelle
///
/// Type : TimeScale
/// Param�tre 1 : Valeur � tester
/// Param�tre 2 : Signe de comparaison
///
////////////////////////////////////////////////////////////
bool CondTimeScale( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & condition )
{
    bool Ok = false;

    if (( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Equal && ( scene.GetTimeScale() ) == condition.GetParameter( 0 ).GetAsMathExpressionResult(scene, objectsConcerned) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Inferior && ( scene.GetTimeScale() ) < condition.GetParameter( 0 ).GetAsMathExpressionResult(scene, objectsConcerned) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Superior && ( scene.GetTimeScale() ) > condition.GetParameter( 0 ).GetAsMathExpressionResult(scene, objectsConcerned) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::InferiorOrEqual && ( scene.GetTimeScale() ) <= condition.GetParameter( 0 ).GetAsMathExpressionResult(scene, objectsConcerned) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::SuperiorOrEqual && ( scene.GetTimeScale() ) >= condition.GetParameter( 0 ).GetAsMathExpressionResult(scene, objectsConcerned) ) ||
            ( condition.GetParameter( 1 ).GetAsCompOperator() == GDExpression::Different && ( scene.GetTimeScale() ) != condition.GetParameter( 0 ).GetAsMathExpressionResult(scene, objectsConcerned) )
       )
    {
        Ok = true;
    }

    if ( condition.IsInverted() )
        return !Ok;

    return Ok;
}

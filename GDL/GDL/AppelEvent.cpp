/**
 *  Game Develop
 *  2008-2010 Florian Rival (Florian.Rival@gmail.com)
 */
#include <iostream>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GDL/Object.h"
#include "GDL/Event.h"
#include "GDL/Chercher.h"
#include "GDL/algo.h"
#include "GDL/MemTrace.h"
#include "GDL/Game.h"
#include "GDL/AppelEvent.h"
#include "GDL/RuntimeScene.h"
#include "GDL/ExtensionsManager.h"
#include "GDL/GDExpression.h"
#include "GDL/profile.h"
#include "GDL/ObjectsConcerned.h"

////////////////////////////////////////////////////////////
/// G�re les �v�nements
///
/// Renvoi le num�ro de la nouvelle sc�ne en cas de changement
////////////////////////////////////////////////////////////
EventsExecutor::EventsExecutor( RuntimeScene * scene_ ) :
nouvelleScene(-1),
scene(scene_),
eval( *scene->game, *scene )
{
}

int EventsExecutor::ExecuteEventsScene()
{

    return nouvelleScene;
}
/*
////////////////////////////////////////////////////////////
/// Execution des �v�nements
///
/// Parcourt tous les �v�nements et les execute.
/// Fonction r�cursive en cas de besoin avec les dossiers.
////////////////////////////////////////////////////////////
int EventsExecutor::ExecuteEvents(vector < Event > & events, ObjectsConcerned & objectsConcernedParent)
{
    BT_PROFILE("ExecuteEvents");
	vector<Event>::iterator e = events.begin();
	vector<Event>::const_iterator events_end = events.end();

    for ( ; e != events_end; ++e )
    {
        //On r�utilise les objets concern�s de l'�v�nement parent
        ObjectsConcerned objectsConcerned;
        objectsConcerned.InheritsFrom(&objectsConcernedParent);

        int retour = ActAllProcessed;

        if ( ExecuteConditions( *e, objectsConcerned ) == CondTrue )
        {
            //On execute les actions
            retour = ExecuteActions( *e, objectsConcerned, 0 );
            if ( retour == ActStopProcess) return ActStopProcess;

            //Sous �v�nements
            if ( !e->events.empty() && retour != ActAllProcessedAndDoNotSubEvents)
            {
                retour = ExecuteEvents( e->events, objectsConcerned);
                if ( retour == ActStopProcess) return ActStopProcess;
            }
        }
    }

    return ActAllProcessed;
}*/
/*
////////////////////////////////////////////////////////////
/// V�rification des conditions
///
/// V�rifie les conditions d'un �v�nement.
/// Renvoi vrai ou faux suivant le r�sultat des conditions.
////////////////////////////////////////////////////////////
int EventsExecutor::ExecuteConditions( Event & event, ObjectsConcerned & objectsConcerned, int startFrom )
{
    //La variable Vrai va �tre modifi� pour savoir si oui ou non on doit faire les actions
    //Dans le cas d'un test de type OU, on commence par faux, et si une condition est vraie, alors VRAI.
    bool Vrai = (event.type == "OR") ? false : true;

    if ( startFrom < 0 ) startFrom = 0;

    const size_t size = event.conditions.size();
    if ( static_cast<unsigned>(startFrom) >= size )
        return CondTrue;

    //1) On �tudie les conditions d'un �v�nements
    for ( unsigned int k = startFrom; k < size; ++k )
    {
        BT_PROFILE("Condition");
        bool Ok = false;
        eval.SetObjectsConcerned(&objectsConcerned);
        if ( event.conditions[k].function != NULL ) { Ok = event.conditions[k].function( scene, objectsConcerned, event.conditions[k], eval ); }
        else if (event.conditions[k].GetType() == "Toujours" ) {        Ok = !event.conditions[k].IsInverted(); }
        else if (event.conditions[k].GetType() == "DepartScene" ) {     Ok = scene->IsFirstLoop();}
        else if (event.conditions[k].GetType() == "Repeat" )
        {
            ObjectsConcerned objectsConcernedInRepeat;

            int nbRepeat = eval.EvalExp(event.conditions[k].GetParameter(0));
            if ( nbRepeat <= 0 ) return CondFalse;

            int retour = ActAllProcessed;

            for (unsigned int i = 0;i<static_cast<unsigned>(nbRepeat);++i)
            {
                //On repart � chaque fois des m�mes objets concern�s
                objectsConcernedInRepeat.InheritsFrom(&objectsConcerned);
                eval.SetObjectsConcerned(&objectsConcernedInRepeat);

                if ( ExecuteConditions( event, objectsConcernedInRepeat, k+1 ) == CondTrue )
                {
                    //On execute les actions
                    retour = ExecuteActions( event, objectsConcernedInRepeat, 0 );
                    if ( retour == ActStopProcess) return CondFalse;

                    //Sous �v�nements
                    if ( !event.events.empty() && retour != ActAllProcessedAndDoNotSubEvents )
                    {
                        retour = ExecuteEvents( event.events, objectsConcernedInRepeat);
                        if ( retour == ActStopProcess) return CondFalse;
                    }
                }
            }

            //On s'est occup� nous m�me de l'�v�nement, on s'arr�te l�.
            if ( retour == ActAllProcessed )
                return CondFalse;
            else
                k = retour;
        }
        else if (event.conditions[k].GetType() == "ForEach" )
        {
            ObjList list = objectsConcerned.PickAndRemove(event.conditions[k].GetParameter( 0 ).GetAsObjectIdentifier(), event.conditions[k].IsGlobal());

            ObjectsConcerned objectsConcernedInForEach;
            int retour = ActAllProcessed;

            ObjList::iterator obj = list.begin();
            ObjList::const_iterator obj_end = list.end();
            for ( ; obj != obj_end; ++obj )
            {
                //On repart � chaque fois des m�mes objets concern�s
                objectsConcernedInForEach.InheritsFrom(&objectsConcerned);
                eval.SetObjectsConcerned(&objectsConcernedInForEach);

                objectsConcernedInForEach.objectsPicked.AddObject(*obj);

                if ( ExecuteConditions( event, objectsConcernedInForEach, k+1 ) == CondTrue )
                {
                    //On execute les actions
                    retour = ExecuteActions( event, objectsConcernedInForEach, 0 );
                    if ( retour == ActStopProcess) return CondFalse;

                    //Sous �v�nements
                    if ( !event.events.empty() && retour != ActAllProcessedAndDoNotSubEvents  )
                    {
                        retour = ExecuteEvents( event.events, objectsConcernedInForEach);
                        if ( retour == ActStopProcess) return CondFalse;
                    }
                }
            }

            //On s'est occup� nous m�me de l'�v�nement, on s'arr�te l�.
            if ( retour == ActAllProcessed )
                return CondFalse;
            else
                k = retour;
        }
        else if (event.conditions[k].GetType() == "While" )
        {
            ObjectsConcerned objectsConcernedInWhile;

            int retour = ActAllProcessed;

            //On continue tant que la condition aura ce r�sultat.
            int resultExcepted = CondTrue;
            if ( event.conditions[k].GetParameter(0).GetPlainString() == "Faux" || event.conditions[k].GetParameter(0).GetPlainString() == "False" )
                resultExcepted = CondFalse;

            bool testIsTrue = ExecuteConditions( event, objectsConcerned, k+1 ) == resultExcepted;

            while (testIsTrue)
            {
                //On repart � chaque fois des m�mes objets concern�s
                objectsConcernedInWhile.InheritsFrom(&objectsConcerned);
                eval.SetObjectsConcerned(&objectsConcernedInWhile);

                if ( ExecuteConditions( event, objectsConcernedInWhile, k+2 ) == CondTrue )
                {
                    //On execute les actions
                    retour = ExecuteActions( event, objectsConcernedInWhile, 0 );
                    if ( retour == ActStopProcess) return CondFalse;

                    //Sous �v�nements
                    if ( !event.events.empty() && retour != ActAllProcessedAndDoNotSubEvents  )
                    {
                        retour = ExecuteEvents( event.events, objectsConcernedInWhile);
                        if ( retour == ActStopProcess) return CondFalse;
                    }
                }

                //TODO : Use objectsConcernedInWhile or ObjectsConcerned ?...
                testIsTrue = ExecuteConditions( event, objectsConcernedInWhile, k+1 ) == resultExcepted;
            }

            //On s'est occup� nous m�me de l'�v�nement, on s'arr�te l�.
            if ( retour == ActAllProcessed )
                return CondFalse;
            else
                k = retour;
        }

        //On regarde ce qu'a donn� la condition
        if ( Ok )
        {
            //Si la condition est vraie
            if (event.type == "OR" )
            {
                Vrai = true;    //Si le test est OU, alors le test est vrai !
            }
        }
        else
        {
            //Si la condition est fausse
            if (event.type == "AND" )  //Si le test est ET, alors le test est faux !
            {
                Vrai = false;
                return CondFalse;
            }
        }

    }
    if ( Vrai )
    {
        return CondTrue;

    }
    return CondFalse;
}*/
/*
////////////////////////////////////////////////////////////
/// Execution des actions
///
/// Renvoi faux si l'execution ne doit pas se continuer ( changement de sc�ne... )
////////////////////////////////////////////////////////////
int EventsExecutor::ExecuteActions( Event & event, ObjectsConcerned & objectsConcerned, int startFrom)
{
    if ( startFrom < 0 ) startFrom = 0;

    for ( unsigned int k = startFrom; k < event.actions.size();k++ )
    {
        BT_PROFILE("Action");
        eval.SetObjectsConcerned(&objectsConcerned);

        //2)1� Le type de l'action
        if ( event.actions[k].function != NULL ) {                    event.actions[k].function( scene, objectsConcerned, event.actions[k], eval ); }
        else if ( event.actions[k].GetType() == "Quit" ) {            nouvelleScene = -2; return ActStopProcess; }
        else if ( event.actions[k].GetType() == "Scene" )
        {
            string returnNom = eval.EvalTxt(event.actions[k].GetParameter(0));
            unsigned int i = 0;
            //On cherche la sc�ne vers laquelle aller
            for ( i = 0;i < scene->game->scenes.size() ; ++i )
            {
                if ( scene->game->scenes[i]->GetName() == returnNom )
                {
                    nouvelleScene = i;
                    return ActStopProcess; //On arr�te l'execution des �v�nements
                }
            }
        }
        else if (event.actions[k].GetType() == "Repeat" )
        {
            ObjectsConcerned objectsConcernedInRepeat;

            int nbRepeat = eval.EvalExp(event.actions[k].GetParameter(0));
            if ( nbRepeat <= 0 ) return ActAllProcessed;

            int retour = ActAllProcessed;

            for (unsigned int i = 0;i<static_cast<unsigned>(nbRepeat);++i)
            {
                //On repart toujours des m�mes objets concern�s
                objectsConcernedInRepeat.InheritsFrom(&objectsConcerned);
                eval.SetObjectsConcerned(&objectsConcernedInRepeat);

                //On execute les actions
                retour = ExecuteActions( event, objectsConcernedInRepeat, k+1 );
                if ( retour == ActStopProcess) return ActStopProcess;

                //Sous �v�nements
                if ( !event.events.empty() && retour != ActAllProcessedAndDoNotSubEvents)
                {
                    retour = ExecuteEvents( event.events, objectsConcernedInRepeat);
                    if ( retour == ActStopProcess) return ActStopProcess;
                }
            }

            if ( retour == ActAllProcessed || retour == ActAllProcessedAndDoNotSubEvents )
                return ActAllProcessedAndDoNotSubEvents;
            else
                k = retour;
        }
        else if (event.actions[k].GetType() == "ForEach" )
        {
            ObjList list = objectsConcerned.PickAndRemove(event.actions[k].GetParameter( 0 ).GetAsObjectIdentifier(), event.actions[k].IsGlobal());

            ObjectsConcerned objectsConcernedInForEach;
            int retour = ActAllProcessed;

            ObjList::iterator obj = list.begin();
            ObjList::const_iterator obj_end = list.end();
            for ( ; obj != obj_end; ++obj )
            {
                //On repart � chaque fois des m�mes objets concern�s
                objectsConcernedInForEach.InheritsFrom(&objectsConcerned);
                eval.SetObjectsConcerned(&objectsConcernedInForEach);

                objectsConcernedInForEach.objectsPicked.AddObject(*obj);

                //On execute les actions
                retour = ExecuteActions( event, objectsConcernedInForEach, k+1 );
                if ( retour == ActStopProcess) return ActStopProcess;

                //Sous �v�nements
                if ( !event.events.empty() && retour != ActAllProcessedAndDoNotSubEvents )
                {
                    retour = ExecuteEvents( event.events, objectsConcernedInForEach);
                    if ( retour == ActStopProcess) return ActStopProcess;
                }
            }

            //On s'est occup� nous m�me de l'�v�nement, on s'arr�te l�.
            if ( retour == ActAllProcessed || retour == ActAllProcessedAndDoNotSubEvents )
                return ActAllProcessedAndDoNotSubEvents;
            else
                k = retour;
        }
    }

    //On a finit avec les actions, on renvoie ActAllProcessed
    //pour signaler qu'on a trait� toutes les actions
    return ActAllProcessed;
}
*/

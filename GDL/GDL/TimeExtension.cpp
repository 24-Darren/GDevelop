/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/TimeExtension.h"
#include "GDL/RuntimeScene.h"

TimeExtension::TimeExtension()
{
    DECLARE_THE_EXTENSION("BuiltinTime",
                          _("Temps"),
                          _("Extension proposant des actions et conditions sur le temps, integr�e en standard"),
                          "Compil Games",
                          "Freeware")

    DECLARE_CONDITION("Timer",
                   _("Valeur d'un chronom�tre"),
                   _("Teste si le chronom�tre atteint ou d�passe le temps indiqu�."),
                   _("Le chronom�tre _PARAM1_ est sup�rieur � _PARAM0_ secondes"),
                   _("Temps et chronom�tres"),
                   "res/conditions/timer24.png",
                   "res/conditions/timer.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("expression", _("Temps en secondes"), "", false);
        instrInfo.AddParameter("string", _("Nom du chronom�tre"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("TimerElapsedTime").SetIncludeFile("GDL/TimeTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("TimeScale",
                   _("Echelle du temps"),
                   _("Teste si l'�chelle du temps actuelle correspond."),
                   _("L'�chelle du temps est _PARAM1_ � _PARAM0_"),
                   _("Temps et chronom�tres"),
                   "res/conditions/time24.png",
                   "res/conditions/time.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("expression", _("Valeur � tester"), "", false);
        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("GetTimeScale").SetManipulatedType("number").SetIncludeFile("GDL/TimeTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("TimerPaused",
                   _("Pause d'un chronom�tre"),
                   _("Teste si le chronom�tre indiqu� est en pause."),
                   _("Le chronom�tre _PARAM0_ est en pause"),
                   _("Temps et chronom�tres"),
                   "res/conditions/timerPaused24.png",
                   "res/conditions/timerPaused.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("string", _("Nom du chronom�tre"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("TimerPaused").SetIncludeFile("GDL/TimeTools.h");

    DECLARE_END_CONDITION()

    DECLARE_ACTION("ResetTimer",
                   _("Remettre � z�ro un chronom�tre"),
                   _("Remet � z�ro le chronom�tre indiqu�."),
                   _("Remettre � z�ro le chronom�tre _PARAM0_"),
                   _("Temps et chronom�tres"),
                   "res/actions/timer24.png",
                   "res/actions/timer.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("string", _("Nom du chronom�tre"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("ResetTimer").SetIncludeFile("GDL/TimeTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("PauseTimer",
                   _("Mettre en pause un chronom�tre"),
                   _("Met en pause le chronom�tre indiqu�."),
                   _("Mettre en pause le chronom�tre _PARAM0_"),
                   _("Temps et chronom�tres"),
                   "res/actions/pauseTimer24.png",
                   "res/actions/pauseTimer.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("string", _("Nom du chronom�tre"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("PauseTimer").SetIncludeFile("GDL/TimeTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("UnPauseTimer",
                   _("Enlever la pause d'un chronom�tre"),
                   _("Enl�ve la pause du chronom�tre indiqu�."),
                   _("Enlever la pause du chronom�tre _PARAM0_"),
                   _("Temps et chronom�tres"),
                   "res/actions/unPauseTimer24.png",
                   "res/actions/unPauseTimer.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("string", _("Nom du chronom�tre"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("UnPauseTimer").SetIncludeFile("GDL/TimeTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("RemoveTimer",
                   _("Supprimer un chronom�tre"),
                   _("Supprime un chronom�tre de la m�moire."),
                   _("Supprimer le chronom�tre _PARAM0_ de la m�moire"),
                   _("Temps et chronom�tres"),
                   "res/actions/time24.png",
                   "res/actions/time.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("string", _("Nom du chronom�tre"), "", false);
        instrInfo.cppCallingInformation.SetFunctionName("RemoveTimer").SetIncludeFile("GDL/TimeTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("ChangeTimeScale",
                   _("Changer l'�chelle du temps"),
                   _("Change la vitesse du d�roulement du jeu."),
                   _("Mettre � _PARAM0_ l'�chelle du temps"),
                   _("Temps et chronom�tres"),
                   "res/actions/time24.png",
                   "res/actions/time.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("expression", _("Echelle ( 1 : Normal, 2 : Double la vitesse, 0.5 : Ralenti de moiti�... )"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("SetTimeScale").SetIncludeFile("GDL/TimeTools.h");

    DECLARE_END_ACTION()

    DECLARE_EXPRESSION("TimeDelta", _("Temps �coul� depuis la derni�re image"), _("Temps �coul� depuis la derni�re image"), _("Temps"), "res/actions/time.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");

        instrInfo.cppCallingInformation.SetFunctionName("GetElapsedTime").SetIncludeFile("GDL/TimeTools.h");
        instrInfo.SetHidden();
    DECLARE_END_EXPRESSION()
    DECLARE_EXPRESSION("TempsFrame", _("Temps �coul� depuis la derni�re image"), _("Temps �coul� depuis la derni�re image"), _("Temps"), "res/actions/time.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");

        instrInfo.cppCallingInformation.SetFunctionName("GetElapsedTime").SetIncludeFile("GDL/TimeTools.h");
        instrInfo.SetHidden();
    DECLARE_END_EXPRESSION()
    DECLARE_EXPRESSION("ElapsedTime", _("Temps �coul� depuis la derni�re image"), _("Temps �coul� depuis la derni�re image"), _("Temps"), "res/actions/time.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");

        instrInfo.cppCallingInformation.SetFunctionName("GetElapsedTime").SetIncludeFile("GDL/TimeTools.h");
        instrInfo.SetHidden();
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("TimeFromStart", _("Temps �coul� depuis le d�but de la sc�ne"), _("Temps �coul� depuis le d�but de la sc�ne"), _("Temps"), "res/actions/time.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");

        instrInfo.cppCallingInformation.SetFunctionName("GetTimeFromStart").SetIncludeFile("GDL/TimeTools.h");
    DECLARE_END_EXPRESSION()
    DECLARE_EXPRESSION("TempsDebut", _("Temps �coul� depuis le d�but de la sc�ne"), _("Temps �coul� depuis le d�but de la sc�ne"), _("Temps"), "res/actions/time.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");

        instrInfo.cppCallingInformation.SetFunctionName("GetTimeFromStart").SetIncludeFile("GDL/TimeTools.h");
        instrInfo.SetHidden();
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("TimeScale", _("Echelle du temps"), _("Echelle du temps"), _("Temps"), "res/actions/time.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");

        instrInfo.cppCallingInformation.SetFunctionName("GetTimeScale").SetIncludeFile("GDL/TimeTools.h");
    DECLARE_END_EXPRESSION()
    DECLARE_EXPRESSION("TimeScale", _("Echelle du temps"), _("Echelle du temps"), _("Temps"), "res/actions/time.png")

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.cppCallingInformation.SetFunctionName("GetTimeScale").SetIncludeFile("GDL/TimeTools.h");
        instrInfo.SetHidden();
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("Time", _("Temps actuel"), _("Temps actuel"), _("Temps"), "res/actions/time.png")
        instrInfo.AddParameter("", _("Valeur � r�cup�rer :\n\nHeure : hour\nMinutes : min\nSecondes : sec\nJour du mois: mday\nMois depuis janvier : mon\nAnn�es depuis 1900 : year\nJours depuis dimanche :wday\nJours depuis le 1er Janvier : yday"), "",false);
        instrInfo.cppCallingInformation.SetFunctionName("GetTime").SetIncludeFile("GDL/TimeTools.h");
    DECLARE_END_EXPRESSION()
}

void TimeExtension::GetPropertyForDebugger(RuntimeScene & scene, unsigned int propertyNb, std::string & name, std::string & value) const
{
    if ( propertyNb < scene.timers.size() )
    {
        name = scene.timers[propertyNb].GetName();
        value = ToString(scene.timers[propertyNb].GetTime())+"s";

        return;
    }
}

bool TimeExtension::ChangeProperty(RuntimeScene & scene, unsigned int propertyNb, std::string newValue)
{
    if ( propertyNb < scene.timers.size() )
    {
        scene.timers[propertyNb].SetTime(ToFloat(newValue));

        return true;
    }

    return false;
}

unsigned int TimeExtension::GetNumberOfProperties(RuntimeScene & scene) const
{
    return scene.timers.size();
}

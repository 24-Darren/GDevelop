/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/SceneExtension.h"
#include "GDL/ExtensionBase.h"

SceneExtension::SceneExtension()
{
    DECLARE_THE_EXTENSION("BuiltinScene",
                          _("Fonctionnalit�s de manipulation des sc�nes"),
                          _("Extension permettant de manipuler les sc�nes, integr�e en standard"),
                          "Compil Games",
                          "Freeware")
    #if defined(GD_IDE_ONLY)

    DECLARE_EXPRESSION("Random", _("Valeur al�atoire"), _("Valeur al�atoire"), _("Al�atoire"), "res/actions/position.png")
        instrInfo.AddParameter("expression", _("Valeur maximale"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("Random").SetIncludeFile("GDL/CommonInstructions.h");
    DECLARE_END_EXPRESSION()

    DECLARE_CONDITION("DepartScene",
                   _("Au lancement de la sc�ne"),
                   _("Est vrai uniquement quand la sc�ne vient juste d'�tre lanc�e."),
                   _("Au lancement de la sc�ne"),
                   _("Sc�ne"),
                   "res/conditions/depart24.png",
                   "res/conditions/depart.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");

        instrInfo.cppCallingInformation.SetFunctionName("SceneJustBegins").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("Egal",
                   _("Comparaisons d'expressions"),
                   _("Teste les deux expressions"),
                   _("_PARAM0_ _PARAM2_ _PARAM1_"),
                   _("Autre"),
                   "res/conditions/egal24.png",
                   "res/conditions/egal.png");

        instrInfo.AddParameter("expression", _("Expression 1"), "",false);
        instrInfo.AddParameter("expression", _("Expression 2"), "",false);
        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("RelationTest").SetIncludeFile("GDL/CommonInstructions.h");

    DECLARE_END_CONDITION()

    DECLARE_ACTION("Scene",
                   _("Aller � une sc�ne"),
                   _("Change et d�marre la sc�ne sp�cifi�e."),
                   _("Aller � la sc�ne _PARAM1_"),
                   _("Sc�ne"),
                   "res/actions/goscene24.png",
                   "res/actions/goscene.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("string", _("Nom de la sc�ne"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("ChangeScene").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("Quit",
                   _("Quitter le jeu"),
                   _("Quitte le jeu."),
                   _("Quitter le jeu"),
                   _("Sc�ne"),
                   "res/actions/quit24.png",
                   "res/actions/quit.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");

        instrInfo.cppCallingInformation.SetFunctionName("StopGame").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("SceneBackground",
                   _("Changer la couleur d'arri�re plan"),
                   _("Remplace la couleur d'arri�re plan de la sc�ne par celle indiqu�e."),
                   _("Remplacer la couleur d'arri�re plan par _PARAM1_"),
                   _("Sc�ne"),
                   "res/actions/background24.png",
                   "res/actions/background.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("color", _("Couleur"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("ChangeSceneBackground").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_ACTION()
    #endif
}

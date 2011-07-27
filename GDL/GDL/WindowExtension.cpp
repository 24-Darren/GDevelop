/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/WindowExtension.h"
#include "GDL/ResourcesMergingHelper.h"
#include "GDL/Instruction.h"

WindowExtension::WindowExtension()
{
    DECLARE_THE_EXTENSION("BuiltinWindow",
                          _("Fonctionnalit�s de fen�trage"),
                          _("Extension permettant de manipuler la fen�tre de jeu, integr�e en standard"),
                          "Compil Games",
                          "Freeware")

    DECLARE_ACTION("EcrireTexte",
                   _("Afficher un texte"),
                   _("Affiche le texte sp�cifi� � l'�cran."),
                   _("Afficher _PARAM0_ en _PARAM1_;_PARAM2_ ( couleur : _PARAM3_ , taille : _PARAM4_, police : _PARAM5_ )"),
                   _("Sc�ne"),
                   "res/actions/texte24.png",
                   "res/actions/texte.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("string", _("Texte"), "",false);
        instrInfo.AddParameter("expression", _("Position X"), "",false);
        instrInfo.AddParameter("expression", _("Position Y"), "",false);
        instrInfo.AddParameter("color", _("Couleur"), "",false);
        instrInfo.AddParameter("expression", _("Taille"), "",false);
        instrInfo.AddParameter("police", _("Police"), "",true);
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",true).SetDefaultValue("\"\"");

        instrInfo.cppCallingInformation.SetFunctionName("DisplayLegacyTextOnScene").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("SetFullScreen",
                   _("(D�s)Activer le plein �cran"),
                   _("Cette action active ou d�sactive l'affichage du jeu en plein �cran."),
                   _("Activer le plein �cran :  _PARAM0_"),
                   _("Fen�tre de jeu"),
                   "res/actions/fullscreen24.png",
                   "res/actions/fullscreen.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("yesorno", _("Activer le plein �cran"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("SetFullscreen").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("SetWindowSize",
                   _("Changer la taille de l'�cran"),
                   _("Cette action change la taille de la fen�tre de jeu."),
                   _("Changer la taille de la fen�tre de jeu en _PARAM0_x_PARAM1_"),
                   _("Fen�tre de jeu"),
                   "res/actions/window24.png",
                   "res/actions/window.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("expression", _("Largeur"), "",false);
        instrInfo.AddParameter("expression", _("Hauteur"), "",false);
        instrInfo.AddParameter("yesorno", _("Utiliser cette taille pour la taille par d�faut des cam�ras des sc�nes ?"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("SetWindowSize").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_ACTION()

    DECLARE_EXPRESSION("SceneWindowWidth", "Largeur de la fen�tre de la sc�ne", "Largeur de la fen�tre de la sc�ne", "Ecran", "res/display16.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");

        instrInfo.cppCallingInformation.SetFunctionName("GetSceneWindowWidth").SetIncludeFile("GDL/RuntimeSceneTools.h");
    DECLARE_END_EXPRESSION()
    DECLARE_EXPRESSION("SceneWindowHeight", "Hauteur de la fen�tre de la sc�ne", "Hauteur de la fen�tre de la sc�ne", "Ecran", "res/display16.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");

        instrInfo.cppCallingInformation.SetFunctionName("GetSceneWindowHeight").SetIncludeFile("GDL/RuntimeSceneTools.h");
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("ScreenWidth", "Largeur de la r�solution actuelle", "Largeur de la r�solution actuelle", "Ecran", "res/display16.png")
        instrInfo.cppCallingInformation.SetFunctionName("GetScreenWidth").SetIncludeFile("GDL/RuntimeSceneTools.h");
    DECLARE_END_EXPRESSION()
    DECLARE_EXPRESSION("ScreenHeight", "Hauteur de la r�solution actuelle", "Hauteur de la r�solution actuelle", "Ecran", "res/display16.png")
        instrInfo.cppCallingInformation.SetFunctionName("GetScreenHeight").SetIncludeFile("GDL/RuntimeSceneTools.h");
    DECLARE_END_EXPRESSION()
    DECLARE_EXPRESSION("ColorDepth", "Profondeur de couleur de la r�solution actuelle", "Profondeur de couleur de la r�solution actuelle", "Ecran", "res/display16.png")
        instrInfo.cppCallingInformation.SetFunctionName("GetColorDepth").SetIncludeFile("GDL/RuntimeSceneTools.h");
    DECLARE_END_EXPRESSION()
}

#if defined(GD_IDE_ONLY)
void WindowExtension::PrepareActionsResourcesForMerging(Instruction & action, ResourcesMergingHelper & resourcesMergingHelper)
{
    if ( action.GetType() == "EcrireTexte" && !action.GetParameterSafely( 6 ).GetPlainString().empty() )
        action.SetParameter( 6, resourcesMergingHelper.GetNewFilename( action.GetParameterSafely( 6 ).GetPlainString() ) );
}
#endif

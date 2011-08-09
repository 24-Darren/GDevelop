/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/KeyboardExtension.h"
#include "GDL/ExtensionBase.h"

KeyboardExtension::KeyboardExtension()
{
    DECLARE_THE_EXTENSION("BuiltinKeyboard",
                          _("Fonctionnalit�s d'utilisation du clavier"),
                          _("Extension permettant d'utiliser le clavier, integr�e en standard"),
                          "Compil Games",
                          "Freeware")

    DECLARE_CONDITION("KeyPressed",
                   _("Une touche est appuy�e"),
                   _("Teste si une touche du clavier est appuy�e."),
                   _("La touche _PARAM1_ est appuy�e"),
                   _("Clavier"),
                   "res/conditions/keyboard24.png",
                   "res/conditions/keyboard.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("key", _("Touche � tester"), "",false);;

        instrInfo.cppCallingInformation.SetFunctionName("IsKeyPressed").SetIncludeFile("GDL/KeyboardTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("KeyFromTextPressed",
                   _("Une touche est appuy�e (Expression texte)"),
                   _("Teste si une touche du clavier, retrouv�e � partir du r�sultat de l'expression, est appuy�e."),
                   _("La touche _PARAM1_ est appuy�e"),
                   _("Clavier"),
                   "res/conditions/keyboard24.png",
                   "res/conditions/keyboard.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("string", _("Expression g�n�rant la touche � tester"), "",false);;

        instrInfo.cppCallingInformation.SetFunctionName("IsKeyPressed").SetIncludeFile("GDL/KeyboardTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("AnyKeyPressed",
                   _("N'importe quelle touche est appuy�e"),
                   _("Teste si n'importe quelle touche du clavier est appuy�e."),
                   _("Une touche du clavier est appuy�e"),
                   _("Clavier"),
                   "res/conditions/keyboard24.png",
                   "res/conditions/keyboard.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");

        instrInfo.cppCallingInformation.SetFunctionName("AnyKeyIsPressed").SetIncludeFile("GDL/KeyboardTools.h");

    DECLARE_END_CONDITION()
}

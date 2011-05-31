#include "GDL/KeyboardExtension.h"
#include "GDL/ExtensionBase.h"
#include "GDL/cClavier.h"

KeyboardExtension::KeyboardExtension()
{
    DECLARE_THE_EXTENSION("BuiltinKeyboard",
                          _T("Fonctionnalit�s d'utilisation du clavier"),
                          _T("Extension permettant d'utiliser le clavier, integr�e en standard"),
                          "Compil Games",
                          "Freeware")


    DECLARE_CONDITION("KeyPressed",
                   _T("Une touche est appuy�e"),
                   _T("Teste si une touche du clavier est appuy�e."),
                   _T("La touche _PARAM0_ est appuy�e"),
                   _T("Clavier"),
                   "res/conditions/keyboard24.png",
                   "res/conditions/keyboard.png",
                   &CondKeyPressed);

        DECLARE_PARAMETER("key", _T("Touche � tester"), false, "");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("KeyFromTextPressed",
                   _T("Une touche est appuy�e (Expression texte)"),
                   _T("Teste si une touche du clavier, retrouv�e � partir du r�sultat de l'expression, est appuy�e."),
                   _T("La touche _PARAM0_ est appuy�e"),
                   _T("Clavier"),
                   "res/conditions/keyboard24.png",
                   "res/conditions/keyboard.png",
                   &CondKeyFromTextPressed);

        DECLARE_PARAMETER("text", _T("Expression g�n�rant la touche � tester"), false, "");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("AnyKeyPressed",
                   _T("N'importe quelle touche est appuy�e"),
                   _T("Teste si n'importe quelle touche du clavier est appuy�e."),
                   _T("Une touche du clavier est appuy�e"),
                   _T("Clavier"),
                   "res/conditions/keyboard24.png",
                   "res/conditions/keyboard.png",
                   &CondAnyKeyPressed);

    DECLARE_END_CONDITION()
}

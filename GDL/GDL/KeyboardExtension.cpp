#include "GDL/KeyboardExtension.h"
#include "GDL/ExtensionBase.h"
#include "GDL/cClavier.h"

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
                   _("La touche _PARAM0_ est appuy�e"),
                   _("Clavier"),
                   "res/conditions/keyboard24.png",
                   "res/conditions/keyboard.png",
                   &CondKeyPressed);

        DECLARE_PARAMETER("key", _("Touche � tester"), false, "");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("KeyFromTextPressed",
                   _("Une touche est appuy�e (Expression texte)"),
                   _("Teste si une touche du clavier, retrouv�e � partir du r�sultat de l'expression, est appuy�e."),
                   _("La touche _PARAM0_ est appuy�e"),
                   _("Clavier"),
                   "res/conditions/keyboard24.png",
                   "res/conditions/keyboard.png",
                   &CondKeyFromTextPressed);

        DECLARE_PARAMETER("text", _("Expression g�n�rant la touche � tester"), false, "");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("AnyKeyPressed",
                   _("N'importe quelle touche est appuy�e"),
                   _("Teste si n'importe quelle touche du clavier est appuy�e."),
                   _("Une touche du clavier est appuy�e"),
                   _("Clavier"),
                   "res/conditions/keyboard24.png",
                   "res/conditions/keyboard.png",
                   &CondAnyKeyPressed);

    DECLARE_END_CONDITION()
}

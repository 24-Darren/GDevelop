/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */
#include "GDL/JoystickExtension.h"

JoystickExtension::JoystickExtension()
{
    DECLARE_THE_EXTENSION("BuiltinJoystick",
                          _("Fonctionnalit�s pour les joysticks"),
                          _("Extension permettant d'utiliser des joysticks, integr�e en standard"),
                          "Compil Games",
                          "Freeware")

    DECLARE_CONDITION("JoystickButtonDown",
                   _("Un bouton d'un joystick est appuy�"),
                   _("Teste si un bouton d'un joystick est appuy�."),
                   _("Le bouton _PARAM1_ du joystick _PARAM0_ est appuy�"),
                   _("Joystick"),
                   "res/conditions/joystick24.png",
                   "res/conditions/joystick.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("expression", _("Num�ro du joystick ( Premier joystick : 0 )"), "",false);
        instrInfo.AddParameter("expression", _("Num�ro du bouton"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("JoystickButtonDown").SetIncludeFile("GDL/JoystickTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("JoystickAxis",
                   _("Valeur d'un axe d'un joystick"),
                   _("Teste si la valeur de l'axe d'un joystick correspond."),
                   _("La valeur de l'axe _PARAM1_ du joystick _PARAM0_ est _PARAM3_ � _PARAM2_"),
                   _("Joystick"),
                   "res/conditions/joystick24.png",
                   "res/conditions/joystick.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("expression", _("Num�ro du joystick ( Premier joystick : 0 )"), "",false);
        instrInfo.AddParameter("joyaxis", _("Axe"), "",false);
        instrInfo.AddParameter("expression", _("Valeur � tester"), "",false);
        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GetJoystickAxisValue").SetManipulatedType("number").SetIncludeFile("GDL/JoystickTools.h");

    DECLARE_END_CONDITION()

    DECLARE_ACTION("GetJoystickAxis",
                   _("Obtenir la valeur de l'axe d'un joystick"),
                   _("Enregistre dans la variable de la sc�ne indiqu�e la valeur de l'axe du joystick ( de -100 � 100 )."),
                   _("Enregistrer dans _PARAM2_ la valeur de l'axe _PARAM1_ du joystick _PARAM0_"),
                   _("Joystick"),
                   "res/actions/joystick24.png",
                   "res/actions/joystick.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("expression", _("Num�ro du joystick ( Premier joystick : 0 )"), "",false);
        instrInfo.AddParameter("joyaxis", _("Axe"), "",false);
        instrInfo.AddParameter("scenevar", _("Variable de la sc�ne o� enregistrer la valeur"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("JoystickAxisValueToVariable").SetManipulatedType("number").SetIncludeFile("GDL/JoystickTools.h");

    DECLARE_END_ACTION()

    DECLARE_EXPRESSION("GetJoystickAxis",
                   _("Axe d'un joystick"),
                   _("Valeur de l'axe d'un joystick"),
                   _("Joystick"),
                   "res/conditions/joystick.png")

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("expression", _("Num�ro du joystick ( Premier joystick : 0 )"), "",false);
        instrInfo.AddParameter("joyaxis", _("Axe"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GetJoystickAxisValue").SetIncludeFile("GDL/JoystickTools.h");

    DECLARE_END_EXPRESSION()
}

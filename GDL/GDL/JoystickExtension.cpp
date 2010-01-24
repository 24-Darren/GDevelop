#include "GDL/JoystickExtension.h"
#include "GDL/cJoystick.h"
#include "GDL/aJoystick.h"

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
                   "res/conditions/joystick.png",
                   &CondJoystickButtonDown);

        DECLARE_PARAMETER("expression", _("Num�ro du joystick"), false, "");
        DECLARE_PARAMETER("expression", _("Num�ro du bouton"), false, "");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("JoystickAxis",
                   _("Valeur d'un axe d'un joystick"),
                   _("Teste si la valeur de l'axe d'un joystick correspond."),
                   _("La valeur de l'axe _PARAM1_ du joystick _PARAM0_ est _PARAM3_ � _PARAM2_"),
                   _("Joystick"),
                   "res/conditions/joystick24.png",
                   "res/conditions/joystick.png",
                   &CondJoystickAxis);

        DECLARE_PARAMETER("expression", _("Num�ro du joystick"), false, "");
        DECLARE_PARAMETER("joyaxis", _("Axe"), false, "");
        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "");
        DECLARE_PARAMETER("signe", _("Signe du test"), false, "");

    DECLARE_END_CONDITION()

    DECLARE_ACTION("GetJoystickAxis",
                   _("Obtenir la valeur de l'axe d'un joystick"),
                   _("Enregistre dans la variable de la sc�ne indiqu�e la valeur de l'axe du joystick ( de -100 � 100 )."),
                   _("Enregistrer dans _PARAM2_ la valeur de l'axe _PARAM1_ du joystick _PARAM0_"),
                   _("Joystick"),
                   "res/actions/joystick24.png",
                   "res/actions/joystick.png",
                   &ActGetJoystickAxis);

        DECLARE_PARAMETER("expression", _("Num�ro du joystick"), false, "");
        DECLARE_PARAMETER("joyaxis", _("Axe"), false, "");
        DECLARE_PARAMETER("scenevar", _("Variable de la sc�ne o� enregistrer la valeur"), false, "");

    DECLARE_END_ACTION()
}

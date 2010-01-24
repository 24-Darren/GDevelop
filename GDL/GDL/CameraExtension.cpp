#include "GDL/CameraExtension.h"
#include "GDL/ExtensionBase.h"
#include "GDL/cCamera.h"
#include "GDL/aCamera.h"
#include "GDL/eFreeFunctions.h"

CameraExtension::CameraExtension()
{
    DECLARE_THE_EXTENSION("BuiltinCamera",
                          _("Fonctionnalit�s sur les cam�ras"),
                          _("Extension cam�ra integr�e en standard"),
                          "Compil Games",
                          "Freeware")

    DECLARE_CONDITION("CameraX",
                   _("Position X de la cam�ra"),
                   _("Teste si la valeur de la position x de la cam�ra\ncorrespond au test effectu�."),
                   _("La position X de la cam�ra est _PARAM1_ � _PARAM0_"),
                   _("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png",
                   &CondCameraX);

        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
        DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _("Calque ( Calque de base si vide )"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraY",
                   _("Position Y de la cam�ra"),
                   _("Teste si la valeur de la position Y de la cam�ra\ncorrespond au test effectu�."),
                   _("La position Y de la cam�ra est _PARAM1_ � _PARAM0_"),
                   _("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png",
                   &CondCameraY);

        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
        DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _("Calque ( Calque de base si vide )"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraAngle",
                   _("Angle de la cam�ra d'un calque"),
                   _("Teste l'angle d'une cam�ra."),
                   _("L'angle de la cam�ra est _PARAM1_ � _PARAM0_� ( Calque : _PARAM2_ )"),
                   _("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png",
                   &CondCameraAngle);

        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
        DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _("Calque ( Calque de base si vide )"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_ACTION("RotateCamera",
                   _("Modifier l'angle de la cam�ra"),
                   _("Cette action modifie l'angle de la cam�ra du calque indiqu�."),
                   _("Faire _PARAM1__PARAM0_ � l'angle de la cam�ra"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActRotateCamera);

        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
        DECLARE_PARAMETER("signe", _("Signe de la modification"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _("Calque ( Calque de base si vide )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("ZoomCamera",
                   _("Changer le niveau de zoom de la cam�ra"),
                   _("Modifie le niveau de zoom de la cam�ra."),
                   _("Mettre le niveau de zoom de la cam�ra � _PARAM0_"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActZoomCamera);

        DECLARE_PARAMETER("expression", _("Valeur ( 1: Zoom initial, 2: Zoom avant x2, 0.5:Zoom arri�re x2... )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _("Calque ( Calque de base si vide )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("FixCamera",
                   _("Centrer la cam�ra sur un objet"),
                   _("Centre la cam�ra sur l'objet, dans les limites d�finies.\nIl est pr�f�rable d'appeler cette action vers la fin des �v�nements, quand toutes les actions\nde positionnement et de d�placement de l'objet ont �t� effectu�es."),
                   _("Centrer la cam�ra sur _PARAM0_ ( limites : de _PARAM1_;_PARAM2_ � _PARAM3_;_PARAM4_ )"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActFixCamera);

        DECLARE_PARAMETER("objet", _("Objet"), true, "")
        DECLARE_PARAMETER("expression", _("Cot� haut gauche de la limite : Position X"), false, "")
        DECLARE_PARAMETER("expression", _("Cot� haut gauche de la limite : Position Y"), false, "")
        DECLARE_PARAMETER("expression", _("Cot� bas droit de la limite : Position X"), false, "")
        DECLARE_PARAMETER("expression", _("Cot� bas droit de la limite : Position Y"), false, "")
        DECLARE_PARAMETER_OPTIONAL("yesorno", _("Anticiper le d�placement de l'objet ( oui par d�faut )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _("Calque ( Calque de base si vide )"), false, "")
        MAIN_OBJECTS_IN_PARAMETER(0)

    DECLARE_END_ACTION()

    DECLARE_ACTION("CentreCamera",
                   _("Centrer la cam�ra sur un objet"),
                   _("Centre la cam�ra sur l'objet indiqu�.\nIl est pr�f�rable d'appeler cette action vers la fin des �v�nements, quand toutes les actions\nde positionnement et de d�placement de l'objet ont �t� effectu�es."),
                   _("Centrer la cam�ra sur _PARAM0_"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActCentreCamera);

        DECLARE_PARAMETER("objet", _("Objet"), true, "")
        DECLARE_PARAMETER_OPTIONAL("yesorno", _("Anticiper le d�placement de l'objet ( oui par d�faut )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _("Calque ( Calque de base si vide )"), false, "")
        MAIN_OBJECTS_IN_PARAMETER(0)

    DECLARE_END_ACTION()

    DECLARE_EXPRESSION("cameraX", _("Position X de la cam�ra d'un calque"), _("Position X de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraX)
        DECLARE_PARAMETER("text", _("Calque"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_HIDDEN_EXPRESSION("VueX", _("Position X de la cam�ra d'un calque"), _("Position X de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraX)
        DECLARE_PARAMETER("text", _("Calque"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("cameraY", _("Position Y de la cam�ra d'un calque"), _("Position Y de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraY)
        DECLARE_PARAMETER("text", _("Calque"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_HIDDEN_EXPRESSION("VueY", _("Position Y de la cam�ra d'un calque"), _("Position Y de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraY)
        DECLARE_PARAMETER("text", _("Calque"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("cameraRotation", _("Angle de la cam�ra d'un calque"), _("Angle de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraRotation)
        DECLARE_PARAMETER("text", _("Calque"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_HIDDEN_EXPRESSION("VueRotation", _("Angle de la cam�ra d'un calque"), _("Angle de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraRotation)
        DECLARE_PARAMETER("text", _("Calque"), false, "")
    DECLARE_END_EXPRESSION()
}

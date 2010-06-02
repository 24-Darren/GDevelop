#include "GDL/CameraExtension.h"
#include "GDL/ExtensionBase.h"
#include "GDL/cCamera.h"
#include "GDL/aCamera.h"
#include "GDL/cLayer.h"
#include "GDL/aLayer.h"
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
                   _("La position X de la cam�ra _PARAM3_ est _PARAM1_ � _PARAM0_ ( Calque : _PARAM2_ )"),
                   _("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png",
                   &CondCameraX);

        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
        DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraY",
                   _("Position Y de la cam�ra"),
                   _("Teste si la valeur de la position Y de la cam�ra\ncorrespond au test effectu�."),
                   _("La position Y de la cam�ra _PARAM3_ est _PARAM1_ � _PARAM0_ ( Calque : _PARAM2_ )"),
                   _("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png",
                   &CondCameraY);

        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
        DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraWidth",
                   _("Largeur d'une cam�ra"),
                   _("Teste la largeur d'une cam�ra d'un calque."),
                   _("La largeur de la cam�ra _PARAM1_ du calque _PARAM0_ est _PARAM2_ � _PARAM3_"),
                   _("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png",
                   &CondCameraWidth);

        DECLARE_PARAMETER("layer", _("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER("expression", _("Num�ro de la cam�ra"), false, "")
        DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraHeight",
                   _("Hauteur d'une cam�ra"),
                   _("Teste la hauteur d'une cam�ra d'un calque."),
                   _("La hauteur de la cam�ra _PARAM1_ du calque _PARAM0_ est _PARAM2_ � _PARAM3_"),
                   _("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png",
                   &CondCameraHeight);

        DECLARE_PARAMETER("layer", _("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER("expression", _("Num�ro de la cam�ra"), false, "")
        DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraAngle",
                   _("Angle de la cam�ra d'un calque"),
                   _("Teste l'angle d'une cam�ra."),
                   _("L'angle de la cam�ra est _PARAM1_ � _PARAM0_� ( Calque : _PARAM2_, cam�ra : _PARAM3_  )"),
                   _("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png",
                   &CondCameraAngle);

        DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
        DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_ACTION("RotateCamera",
                   _("Modifier l'angle de la cam�ra"),
                   _("Cette action modifie l'angle de la cam�ra du calque indiqu�."),
                   _("Faire _PARAM1__PARAM0_ � l'angle de la cam�ra ( calque : _PARAM2_, cam�ra : _PARAM3_ )"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActRotateCamera);

        DECLARE_PARAMETER("expression", _("Valeur"), false, "")
        DECLARE_PARAMETER("signe", _("Signe de la modification"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("AddCamera",
                   _("Ajouter une cam�ra � un calque"),
                   _("Cette action ajoute une cam�ra � un calque."),
                   _("Ajouter une cam�ra au calque _PARAM0_"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActAddCamera);

        DECLARE_PARAMETER("layer", _("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Largeur"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Hauteur"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Position X du point haut gauche de la zone de rendu ( entre 0 et 1 )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Position Y du point haut gauche de la zone de rendu ( entre 0 et 1 )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Position X du point bas droit de la zone de rendu ( entre 0 et 1 )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Position Y du point bas droit de la zone de rendu ( entre 0 et 1 )"), false, "")
    DECLARE_END_ACTION()

    DECLARE_ACTION("DeleteCamera",
                   _("Supprimer une cam�ra d'un calque"),
                   _("Supprime la cam�ra indiqu�e d'un calque."),
                   _("Supprimer la cam�ra _PARAM1_ du calque _PARAM0_"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActDeleteCamera);

        DECLARE_PARAMETER("layer", _("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER("expression", _("Num�ro de la cam�ra"), false, "")
    DECLARE_END_ACTION()

    DECLARE_ACTION("CameraSize",
                   _("Modifier la taille d'une cam�ra"),
                   _("Cette action modifie la taille d'une cam�ra. Remet le zoom � sa valeur initiale."),
                   _("Changer la taille de la cam�ra _PARAM1_ du calque _PARAM0_ en _PARAM2_*_PARAM3_"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActCameraSize);

        DECLARE_PARAMETER("layer", _("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER("expression", _("Num�ro de la cam�ra"), false, "")
        DECLARE_PARAMETER("expression", _("Largeur"), false, "")
        DECLARE_PARAMETER("expression", _("Hauteur"), false, "")
    DECLARE_END_ACTION()

    DECLARE_ACTION("CameraViewport",
                   _("Modifier la zone de rendu d'une cam�ra"),
                   _("Cette action modifie la zone de rendu d'une cam�ra, exprim�e en facteur de la fen�tre."),
                   _("Mettre la zone de rendu de la cam�ra _PARAM1_ du calque _PARAM0_ � _PARAM2_;_PARAM3_ _PARAM4_;_PARAM5_"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActCameraViewport);

        DECLARE_PARAMETER("layer", _("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER("expression", _("Num�ro de la cam�ra"), false, "")
        DECLARE_PARAMETER("expression", _("Position X du point haut gauche de la zone ( entre 0 et 1 )"), false, "")
        DECLARE_PARAMETER("expression", _("Position Y du point haut gauche de la zone ( entre 0 et 1 )"), false, "")
        DECLARE_PARAMETER("expression", _("Position X du point bas droit de la zone ( entre 0 et 1 )"), false, "")
        DECLARE_PARAMETER("expression", _("Position Y du point bas droit de la zone ( entre 0 et 1 )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("ZoomCamera",
                   _("Changer le niveau de zoom de la cam�ra"),
                   _("Modifie le niveau de zoom de la cam�ra."),
                   _("Mettre le niveau de zoom de la cam�ra � _PARAM0_ ( calque : _PARAM1_, cam�ra : _PARAM2_ )"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActZoomCamera);

        DECLARE_PARAMETER("expression", _("Valeur ( 1: Zoom initial, 2: Zoom avant x2, 0.5:Zoom arri�re x2... )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("FixCamera",
                   _("Centrer la cam�ra sur un objet ( Limites )"),
                   _("Centre la cam�ra sur l'objet, dans les limites d�finies.\nIl est pr�f�rable d'appeler cette action vers la fin des �v�nements, quand toutes les actions\nde positionnement et de d�placement de l'objet ont �t� effectu�es."),
                   _("Centrer la cam�ra sur _PARAM0_ ( limites : de _PARAM1_;_PARAM2_ � _PARAM3_;_PARAM4_ ) ( calque : _PARAM6_, cam�ra : _PARAM7_ )"),
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
        DECLARE_PARAMETER_OPTIONAL("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
        MAIN_OBJECTS_IN_PARAMETER(0)

    DECLARE_END_ACTION()

    DECLARE_ACTION("CentreCamera",
                   _("Centrer la cam�ra sur un objet"),
                   _("Centre la cam�ra sur l'objet indiqu�.\nIl est pr�f�rable d'appeler cette action vers la fin des �v�nements, quand toutes les actions\nde positionnement et de d�placement de l'objet ont �t� effectu�es."),
                   _("Centrer la cam�ra sur _PARAM0_ ( calque : _PARAM2_, cam�ra : _PARAM3_ )"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActCentreCamera);

        DECLARE_PARAMETER("objet", _("Objet"), true, "")
        DECLARE_PARAMETER_OPTIONAL("yesorno", _("Anticiper le d�placement de l'objet ( oui par d�faut )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
        MAIN_OBJECTS_IN_PARAMETER(0)

    DECLARE_END_ACTION()

    DECLARE_ACTION("ShowLayer",
                   _("Afficher un calque"),
                   _("Rend visible un calque."),
                   _("Afficher le calque _PARAM0_"),
                   _("Calques et cam�ras"),
                   "res/actions/layer24.png",
                   "res/actions/layer.png",
                   &ActShowLayer);

        DECLARE_PARAMETER("layer", _("Calque ( Calque de base si vide )"), false, "")
        MAIN_OBJECTS_IN_PARAMETER(0)

    DECLARE_END_ACTION()

    DECLARE_ACTION("HideLayer",
                   _("Cacher un calque"),
                   _("Rend invisible un calque."),
                   _("Cacher le calque _PARAM0_"),
                   _("Calques et cam�ras"),
                   "res/actions/layer24.png",
                   "res/actions/layer.png",
                   &ActHideLayer);

        DECLARE_PARAMETER("layer", _("Calque ( Calque de base si vide )"), false, "")
        MAIN_OBJECTS_IN_PARAMETER(0)

    DECLARE_END_ACTION()

    DECLARE_CONDITION("LayerVisible",
                   _("Visibilit� d'un calque"),
                   _("Teste si un calque est affich�."),
                   _("Le calque _PARAM0_ est visible"),
                   _("Calques et cam�ras"),
                   "res/conditions/layer24.png",
                   "res/conditions/layer.png",
                   &CondLayerVisible);

        DECLARE_PARAMETER("layer", _("Calque ( Calque de base si vide )"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_EXPRESSION("cameraWidth", _("Largeur de la cam�ra d'un calque"), _("Largeur de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraWidth)
        DECLARE_PARAMETER("text", _("Calque"), false, "")
        DECLARE_PARAMETER("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("cameraHeight", _("Hauteur de la cam�ra d'un calque"), _("Hauteur de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraHeight)
        DECLARE_PARAMETER("text", _("Calque"), false, "")
        DECLARE_PARAMETER("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("cameraViewportLeft", _("Position X du cot� haut-gauche de la zone de rendu d'une cam�ra"), _("Position X du cot� haut-gauche de la zone de rendu d'une cam�ra"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraViewportLeft)
        DECLARE_PARAMETER("text", _("Calque"), false, "")
        DECLARE_PARAMETER("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("cameraViewportTop", _("Position Y du cot� haut-gauche de la zone de rendu d'une cam�ra"), _("Position Y du cot� haut-gauche de la zone de rendu d'une cam�ra"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraViewportTop)
        DECLARE_PARAMETER("text", _("Calque"), false, "")
        DECLARE_PARAMETER("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("cameraViewportRight", _("Position X du cot� bas-droit de la zone de rendu d'une cam�ra"), _("Position X du cot� bas-droit de la zone de rendu d'une cam�ra"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraViewportRight)
        DECLARE_PARAMETER("text", _("Calque"), false, "")
        DECLARE_PARAMETER("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("cameraViewportBottom", _("Position Y du cot� bas-droit de la zone de rendu d'une cam�ra"), _("Position Y du cot� bas-droit de la zone de rendu d'une cam�ra"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraViewportBottom)
        DECLARE_PARAMETER("text", _("Calque"), false, "")
        DECLARE_PARAMETER("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("cameraX", _("Position X de la cam�ra d'un calque"), _("Position X de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraX)
        DECLARE_PARAMETER_OPTIONAL("text", _("Calque"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_HIDDEN_EXPRESSION("VueX", _("Position X de la cam�ra d'un calque"), _("Position X de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraX)
        DECLARE_PARAMETER_OPTIONAL("text", _("Calque"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("cameraY", _("Position Y de la cam�ra d'un calque"), _("Position Y de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraY)
        DECLARE_PARAMETER_OPTIONAL("text", _("Calque"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_HIDDEN_EXPRESSION("VueY", _("Position Y de la cam�ra d'un calque"), _("Position Y de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraY)
        DECLARE_PARAMETER_OPTIONAL("text", _("Calque"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("cameraRotation", _("Angle de la cam�ra d'un calque"), _("Angle de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraRotation)
        DECLARE_PARAMETER_OPTIONAL("text", _("Calque"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_HIDDEN_EXPRESSION("VueRotation", _("Angle de la cam�ra d'un calque"), _("Angle de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png", &ExpCameraRotation)
        DECLARE_PARAMETER_OPTIONAL("text", _("Calque"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()
}

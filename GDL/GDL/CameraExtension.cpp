/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

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
                          _T("Fonctionnalit�s sur les cam�ras"),
                          _T("Extension cam�ra integr�e en standard"),
                          "Compil Games",
                          "Freeware")

    DECLARE_CONDITION("CameraX",
                   _T("Position X de la cam�ra"),
                   _T("Teste si la valeur de la position x de la cam�ra\ncorrespond au test effectu�."),
                   _T("La position X de la cam�ra _PARAM3_ est _PARAM1_ � _PARAM0_ ( Calque : _PARAM2_ )"),
                   _T("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png",
                   &CondCameraX);

        DECLARE_PARAMETER("expression", _T("Valeur � tester"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe du test"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _T("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraY",
                   _T("Position Y de la cam�ra"),
                   _T("Teste si la valeur de la position Y de la cam�ra\ncorrespond au test effectu�."),
                   _T("La position Y de la cam�ra _PARAM3_ est _PARAM1_ � _PARAM0_ ( Calque : _PARAM2_ )"),
                   _T("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png",
                   &CondCameraY);

        DECLARE_PARAMETER("expression", _T("Valeur � tester"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe du test"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _T("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraWidth",
                   _T("Largeur d'une cam�ra"),
                   _T("Teste la largeur d'une cam�ra d'un calque."),
                   _T("La largeur de la cam�ra _PARAM1_ du calque _PARAM0_ est _PARAM2_ � _PARAM3_"),
                   _T("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png",
                   &CondCameraWidth);

        DECLARE_PARAMETER("layer", _T("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER("expression", _T("Num�ro de la cam�ra"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe du test"), false, "")
        DECLARE_PARAMETER("expression", _T("Valeur � tester"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraHeight",
                   _T("Hauteur d'une cam�ra"),
                   _T("Teste la hauteur d'une cam�ra d'un calque."),
                   _T("La hauteur de la cam�ra _PARAM1_ du calque _PARAM0_ est _PARAM2_ � _PARAM3_"),
                   _T("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png",
                   &CondCameraHeight);

        DECLARE_PARAMETER("layer", _T("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER("expression", _T("Num�ro de la cam�ra"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe du test"), false, "")
        DECLARE_PARAMETER("expression", _T("Valeur � tester"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraAngle",
                   _T("Angle de la cam�ra d'un calque"),
                   _T("Teste l'angle d'une cam�ra."),
                   _T("L'angle de la cam�ra est _PARAM1_ � _PARAM0_� ( Calque : _PARAM2_, cam�ra : _PARAM3_  )"),
                   _T("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png",
                   &CondCameraAngle);

        DECLARE_PARAMETER("expression", _T("Valeur � tester"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe du test"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _T("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_ACTION("RotateCamera",
                   _T("Modifier l'angle de la cam�ra"),
                   _T("Cette action modifie l'angle de la cam�ra du calque indiqu�."),
                   _T("Faire _PARAM1__PARAM0_ � l'angle de la cam�ra ( calque : _PARAM2_, cam�ra : _PARAM3_ )"),
                   _T("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActRotateCamera);

        DECLARE_PARAMETER("expression", _T("Valeur"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe de la modification"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _T("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("AddCamera",
                   _T("Ajouter une cam�ra � un calque"),
                   _T("Cette action ajoute une cam�ra � un calque."),
                   _T("Ajouter une cam�ra au calque _PARAM0_"),
                   _T("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActAddCamera);

        DECLARE_PARAMETER("layer", _T("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Largeur"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Hauteur"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Position X du point haut gauche de la zone de rendu ( entre 0 et 1 )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Position Y du point haut gauche de la zone de rendu ( entre 0 et 1 )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Position X du point bas droit de la zone de rendu ( entre 0 et 1 )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Position Y du point bas droit de la zone de rendu ( entre 0 et 1 )"), false, "")
    DECLARE_END_ACTION()

    DECLARE_ACTION("DeleteCamera",
                   _T("Supprimer une cam�ra d'un calque"),
                   _T("Supprime la cam�ra indiqu�e d'un calque."),
                   _T("Supprimer la cam�ra _PARAM1_ du calque _PARAM0_"),
                   _T("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActDeleteCamera);

        DECLARE_PARAMETER("layer", _T("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER("expression", _T("Num�ro de la cam�ra"), false, "")
    DECLARE_END_ACTION()

    DECLARE_ACTION("CameraSize",
                   _T("Modifier la taille d'une cam�ra"),
                   _T("Cette action modifie la taille d'une cam�ra. Remet le zoom � sa valeur initiale."),
                   _T("Changer la taille de la cam�ra _PARAM1_ du calque _PARAM0_ en _PARAM2_*_PARAM3_"),
                   _T("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActCameraSize);

        DECLARE_PARAMETER("layer", _T("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER("expression", _T("Num�ro de la cam�ra"), false, "")
        DECLARE_PARAMETER("expression", _T("Largeur"), false, "")
        DECLARE_PARAMETER("expression", _T("Hauteur"), false, "")
    DECLARE_END_ACTION()

    DECLARE_ACTION("CameraViewport",
                   _T("Modifier la zone de rendu d'une cam�ra"),
                   _T("Cette action modifie la zone de rendu d'une cam�ra, exprim�e en facteur de la fen�tre."),
                   _T("Mettre la zone de rendu de la cam�ra _PARAM1_ du calque _PARAM0_ � _PARAM2_;_PARAM3_ _PARAM4_;_PARAM5_"),
                   _T("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActCameraViewport);

        DECLARE_PARAMETER("layer", _T("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER("expression", _T("Num�ro de la cam�ra"), false, "")
        DECLARE_PARAMETER("expression", _T("Position X du point haut gauche de la zone ( entre 0 et 1 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Position Y du point haut gauche de la zone ( entre 0 et 1 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Position X du point bas droit de la zone ( entre 0 et 1 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Position Y du point bas droit de la zone ( entre 0 et 1 )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("ZoomCamera",
                   _T("Changer le niveau de zoom de la cam�ra"),
                   _T("Modifie le niveau de zoom de la cam�ra."),
                   _T("Mettre le niveau de zoom de la cam�ra � _PARAM0_ ( calque : _PARAM1_, cam�ra : _PARAM2_ )"),
                   _T("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActZoomCamera);

        DECLARE_PARAMETER("expression", _T("Valeur ( 1: Zoom initial, 2: Zoom avant x2, 0.5:Zoom arri�re x2... )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _T("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("FixCamera",
                   _T("Centrer la cam�ra sur un objet ( Limites )"),
                   _T("Centre la cam�ra sur l'objet, dans les limites d�finies.\nIl est pr�f�rable d'appeler cette action vers la fin des �v�nements, quand toutes les actions\nde positionnement et de d�placement de l'objet ont �t� effectu�es."),
                   _T("Centrer la cam�ra sur _PARAM0_ ( limites : de _PARAM1_;_PARAM2_ � _PARAM3_;_PARAM4_ ) ( calque : _PARAM6_, cam�ra : _PARAM7_ )"),
                   _T("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActFixCamera);

        DECLARE_PARAMETER("object", _T("Objet"), true, "")
        DECLARE_PARAMETER("expression", _T("Cot� haut gauche de la limite : Position X"), false, "")
        DECLARE_PARAMETER("expression", _T("Cot� haut gauche de la limite : Position Y"), false, "")
        DECLARE_PARAMETER("expression", _T("Cot� bas droit de la limite : Position X"), false, "")
        DECLARE_PARAMETER("expression", _T("Cot� bas droit de la limite : Position Y"), false, "")
        DECLARE_PARAMETER_OPTIONAL("yesorno", _T("Anticiper le d�placement de l'objet ( oui par d�faut )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _T("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
        MAIN_OBJECTS_IN_PARAMETER(0)

    DECLARE_END_ACTION()

    DECLARE_ACTION("CentreCamera",
                   _T("Centrer la cam�ra sur un objet"),
                   _T("Centre la cam�ra sur l'objet indiqu�.\nIl est pr�f�rable d'appeler cette action vers la fin des �v�nements, quand toutes les actions\nde positionnement et de d�placement de l'objet ont �t� effectu�es."),
                   _T("Centrer la cam�ra sur _PARAM0_ ( calque : _PARAM2_, cam�ra : _PARAM3_ )"),
                   _T("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png",
                   &ActCentreCamera);

        DECLARE_PARAMETER("object", _T("Objet"), true, "")
        DECLARE_PARAMETER_OPTIONAL("yesorno", _T("Anticiper le d�placement de l'objet ( oui par d�faut )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("layer", _T("Calque ( Calque de base si vide )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
        MAIN_OBJECTS_IN_PARAMETER(0)

    DECLARE_END_ACTION()

    DECLARE_ACTION("ShowLayer",
                   _T("Afficher un calque"),
                   _T("Rend visible un calque."),
                   _T("Afficher le calque _PARAM0_"),
                   _T("Calques et cam�ras"),
                   "res/actions/layer24.png",
                   "res/actions/layer.png",
                   &ActShowLayer);

        DECLARE_PARAMETER("layer", _T("Calque ( Calque de base si vide )"), false, "")
        MAIN_OBJECTS_IN_PARAMETER(0)

    DECLARE_END_ACTION()

    DECLARE_ACTION("HideLayer",
                   _T("Cacher un calque"),
                   _T("Rend invisible un calque."),
                   _T("Cacher le calque _PARAM0_"),
                   _T("Calques et cam�ras"),
                   "res/actions/layer24.png",
                   "res/actions/layer.png",
                   &ActHideLayer);

        DECLARE_PARAMETER("layer", _T("Calque ( Calque de base si vide )"), false, "")
        MAIN_OBJECTS_IN_PARAMETER(0)

    DECLARE_END_ACTION()

    DECLARE_CONDITION("LayerVisible",
                   _T("Visibilit� d'un calque"),
                   _T("Teste si un calque est affich�."),
                   _T("Le calque _PARAM0_ est visible"),
                   _T("Calques et cam�ras"),
                   "res/conditions/layer24.png",
                   "res/conditions/layer.png",
                   &CondLayerVisible);

        DECLARE_PARAMETER("layer", _T("Calque ( Calque de base si vide )"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_EXPRESSION("CameraWidth", _T("Largeur de la cam�ra d'un calque"), _T("Largeur de la cam�ra d'un calque"), _T("Cam�ra"), "res/actions/camera.png", &ExpCameraWidth)
        DECLARE_PARAMETER("layer", _T("Calque"), false, "")
        DECLARE_PARAMETER("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraHeight", _T("Hauteur de la cam�ra d'un calque"), _T("Hauteur de la cam�ra d'un calque"), _T("Cam�ra"), "res/actions/camera.png", &ExpCameraHeight)
        DECLARE_PARAMETER("layer", _T("Calque"), false, "")
        DECLARE_PARAMETER("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraViewportLeft", _T("Position X du cot� haut-gauche de la zone de rendu d'une cam�ra"), _T("Position X du cot� haut-gauche de la zone de rendu d'une cam�ra"), _T("Cam�ra"), "res/actions/camera.png", &ExpCameraViewportLeft)
        DECLARE_PARAMETER("layer", _T("Calque"), false, "")
        DECLARE_PARAMETER("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraViewportTop", _T("Position Y du cot� haut-gauche de la zone de rendu d'une cam�ra"), _T("Position Y du cot� haut-gauche de la zone de rendu d'une cam�ra"), _T("Cam�ra"), "res/actions/camera.png", &ExpCameraViewportTop)
        DECLARE_PARAMETER("layer", _T("Calque"), false, "")
        DECLARE_PARAMETER("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraViewportRight", _T("Position X du cot� bas-droit de la zone de rendu d'une cam�ra"), _T("Position X du cot� bas-droit de la zone de rendu d'une cam�ra"), _T("Cam�ra"), "res/actions/camera.png", &ExpCameraViewportRight)
        DECLARE_PARAMETER("layer", _T("Calque"), false, "")
        DECLARE_PARAMETER("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraViewportBottom", _T("Position Y du cot� bas-droit de la zone de rendu d'une cam�ra"), _T("Position Y du cot� bas-droit de la zone de rendu d'une cam�ra"), _T("Cam�ra"), "res/actions/camera.png", &ExpCameraViewportBottom)
        DECLARE_PARAMETER("layer", _T("Calque"), false, "")
        DECLARE_PARAMETER("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraX", _T("Position X de la cam�ra d'un calque"), _T("Position X de la cam�ra d'un calque"), _T("Cam�ra"), "res/actions/camera.png", &ExpCameraX)
        DECLARE_PARAMETER_OPTIONAL("layer", _T("Calque"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_HIDDEN_EXPRESSION("VueX", _T("Position X de la cam�ra d'un calque"), _T("Position X de la cam�ra d'un calque"), _T("Cam�ra"), "res/actions/camera.png", &ExpCameraX)
        DECLARE_PARAMETER_OPTIONAL("layer", _T("Calque"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraY", _T("Position Y de la cam�ra d'un calque"), _T("Position Y de la cam�ra d'un calque"), _T("Cam�ra"), "res/actions/camera.png", &ExpCameraY)
        DECLARE_PARAMETER_OPTIONAL("layer", _T("Calque"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_HIDDEN_EXPRESSION("VueY", _T("Position Y de la cam�ra d'un calque"), _T("Position Y de la cam�ra d'un calque"), _T("Cam�ra"), "res/actions/camera.png", &ExpCameraY)
        DECLARE_PARAMETER_OPTIONAL("layer", _T("Calque"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraRotation", _T("Angle de la cam�ra d'un calque"), _T("Angle de la cam�ra d'un calque"), _T("Cam�ra"), "res/actions/camera.png", &ExpCameraRotation)
        DECLARE_PARAMETER_OPTIONAL("layer", _T("Calque"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()

    DECLARE_HIDDEN_EXPRESSION("VueRotation", _T("Angle de la cam�ra d'un calque"), _T("Angle de la cam�ra d'un calque"), _T("Cam�ra"), "res/actions/camera.png", &ExpCameraRotation)
        DECLARE_PARAMETER_OPTIONAL("layer", _T("Calque"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Num�ro de la cam�ra ( 0 par d�faut )"), false, "")
    DECLARE_END_EXPRESSION()
}

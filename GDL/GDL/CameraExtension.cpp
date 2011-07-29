/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/CameraExtension.h"
#include "GDL/ExtensionBase.h"

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
                   "res/conditions/camera.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("expression", _("Valeur � tester"), "",false);
        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",true).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",true).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraX").SetManipulatedType("number").SetIncludeFile("GDL/RuntimeSceneCameraTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraY",
                   _("Position Y de la cam�ra"),
                   _("Teste si la valeur de la position Y de la cam�ra\ncorrespond au test effectu�."),
                   _("La position Y de la cam�ra _PARAM3_ est _PARAM1_ � _PARAM0_ ( Calque : _PARAM2_ )"),
                   _("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("expression", _("Valeur � tester"), "",false);
        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",false).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",false).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraY").SetManipulatedType("number").SetIncludeFile("GDL/RuntimeSceneCameraTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraWidth",
                   _("Largeur d'une cam�ra"),
                   _("Teste la largeur d'une cam�ra d'un calque."),
                   _("La largeur de la cam�ra _PARAM1_ du calque _PARAM0_ est _PARAM2_ � _PARAM3_"),
                   _("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque"), "",false).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra"), "",false);
        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);
        instrInfo.AddParameter("expression", _("Valeur � tester"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraWidth").SetManipulatedType("number").SetIncludeFile("GDL/RuntimeSceneCameraTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraHeight",
                   _("Hauteur d'une cam�ra"),
                   _("Teste la hauteur d'une cam�ra d'un calque."),
                   _("La hauteur de la cam�ra _PARAM1_ du calque _PARAM0_ est _PARAM2_ � _PARAM3_"),
                   _("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",false).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra"), "",false);
        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);
        instrInfo.AddParameter("expression", _("Valeur � tester"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraHeight").SetManipulatedType("number").SetIncludeFile("GDL/RuntimeSceneCameraTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("CameraAngle",
                   _("Angle de la cam�ra d'un calque"),
                   _("Teste l'angle d'une cam�ra."),
                   _("L'angle de la cam�ra est _PARAM1_ � _PARAM0_� ( Calque : _PARAM2_, cam�ra : _PARAM3_  )"),
                   _("Calques et cam�ras"),
                   "res/conditions/camera24.png",
                   "res/conditions/camera.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("expression", _("Valeur � tester"), "",false);
        instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",true).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",true).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraAngle").SetManipulatedType("number").SetIncludeFile("GDL/RuntimeSceneCameraTools.h");

    DECLARE_END_CONDITION()

    DECLARE_ACTION("RotateCamera",
                   _("Modifier l'angle de la cam�ra"),
                   _("Cette action modifie l'angle de la cam�ra du calque indiqu�."),
                   _("Faire _PARAM1__PARAM0_ � l'angle de la cam�ra ( calque : _PARAM2_, cam�ra : _PARAM3_ )"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("expression", _("Valeur"), "",false);
        instrInfo.AddParameter("operator", _("Signe de la modification"), "",false);
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",true).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",true).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("SetCameraAngle").SetAssociatedGetter("GetCameraAngle").SetManipulatedType("number").SetIncludeFile("GDL/RuntimeSceneCameraTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("AddCamera",
                   _("Ajouter une cam�ra � un calque"),
                   _("Cette action ajoute une cam�ra � un calque."),
                   _("Ajouter une cam�ra au calque _PARAM0_"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",false).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Largeur"), "",true);
        instrInfo.AddParameter("expression", _("Hauteur"), "",true);
        instrInfo.AddParameter("expression", _("Position X du point haut gauche de la zone de rendu ( entre 0 et 1 )"), "",true);
        instrInfo.AddParameter("expression", _("Position Y du point haut gauche de la zone de rendu ( entre 0 et 1 )"), "",true);
        instrInfo.AddParameter("expression", _("Position X du point bas droit de la zone de rendu ( entre 0 et 1 )"), "",true);
        instrInfo.AddParameter("expression", _("Position Y du point bas droit de la zone de rendu ( entre 0 et 1 )"), "",true);

        instrInfo.cppCallingInformation.SetFunctionName("AddCamera").SetIncludeFile("GDL/RuntimeSceneCameraTools.h");
    DECLARE_END_ACTION()

    DECLARE_ACTION("DeleteCamera",
                   _("Supprimer une cam�ra d'un calque"),
                   _("Supprime la cam�ra indiqu�e d'un calque."),
                   _("Supprimer la cam�ra _PARAM1_ du calque _PARAM0_"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",false).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("DeleteCamera").SetIncludeFile("GDL/RuntimeSceneCameraTools.h");
    DECLARE_END_ACTION()

    DECLARE_ACTION("CameraSize",
                   _("Modifier la taille d'une cam�ra"),
                   _("Cette action modifie la taille d'une cam�ra. Remet le zoom � sa valeur initiale."),
                   _("Changer la taille de la cam�ra _PARAM1_ du calque _PARAM0_ en _PARAM2_*_PARAM3_"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",false).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra"), "",false);
        instrInfo.AddParameter("expression", _("Largeur"), "",false);
        instrInfo.AddParameter("expression", _("Hauteur"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("SetCameraSize").SetIncludeFile("GDL/RuntimeSceneCameraTools.h");
    DECLARE_END_ACTION()

    DECLARE_ACTION("CameraViewport",
                   _("Modifier la zone de rendu d'une cam�ra"),
                   _("Cette action modifie la zone de rendu d'une cam�ra, exprim�e en facteur de la fen�tre."),
                   _("Mettre la zone de rendu de la cam�ra _PARAM1_ du calque _PARAM0_ � _PARAM2_;_PARAM3_ _PARAM4_;_PARAM5_"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",false).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra"), "",false);
        instrInfo.AddParameter("expression", _("Position X du point haut gauche de la zone ( entre 0 et 1 )"), "",false);
        instrInfo.AddParameter("expression", _("Position Y du point haut gauche de la zone ( entre 0 et 1 )"), "",false);
        instrInfo.AddParameter("expression", _("Position X du point bas droit de la zone ( entre 0 et 1 )"), "",false);
        instrInfo.AddParameter("expression", _("Position Y du point bas droit de la zone ( entre 0 et 1 )"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("SetCameraViewport").SetIncludeFile("GDL/RuntimeSceneCameraTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("ZoomCamera",
                   _("Changer le niveau de zoom de la cam�ra"),
                   _("Modifie le niveau de zoom de la cam�ra."),
                   _("Mettre le niveau de zoom de la cam�ra � _PARAM0_ ( calque : _PARAM1_, cam�ra : _PARAM2_ )"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("expression", _("Valeur ( 1: Zoom initial, 2: Zoom avant x2, 0.5:Zoom arri�re x2... )"), "",false);
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",true).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",true).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("SetCameraZoom").SetAssociatedGetter("GetCameraZoom").SetManipulatedType("number").SetIncludeFile("GDL/RuntimeSceneCameraTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("FixCamera",
                   _("Centrer la cam�ra sur un objet ( Limites )"),
                   _("Centre la cam�ra sur l'objet, dans les limites d�finies.\nIl est pr�f�rable d'appeler cette action vers la fin des �v�nements, quand toutes les actions\nde positionnement et de d�placement de l'objet ont �t� effectu�es."),
                   _("Centrer la cam�ra sur _PARAM0_ ( limites : de _PARAM1_;_PARAM2_ � _PARAM3_;_PARAM4_ ) ( calque : _PARAM6_, cam�ra : _PARAM7_ )"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("object", _("Objet"), "", false);
        instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "1");
        instrInfo.AddParameter("expression", _("Cot� haut gauche de la limite : Position X"), "",false);
        instrInfo.AddParameter("expression", _("Cot� haut gauche de la limite : Position Y"), "",false);
        instrInfo.AddParameter("expression", _("Cot� bas droit de la limite : Position X"), "",false);
        instrInfo.AddParameter("expression", _("Cot� bas droit de la limite : Position Y"), "",false);
        instrInfo.AddParameter("yesorno", _("Anticiper le d�placement de l'objet ( oui par d�faut )"), "",true);
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",true).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",true).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("CenterCameraOnObjectWithLimits").SetIncludeFile("GDL/RuntimeSceneCameraTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("CentreCamera",
                   _("Centrer la cam�ra sur un objet"),
                   _("Centre la cam�ra sur l'objet indiqu�.\nIl est pr�f�rable d'appeler cette action vers la fin des �v�nements, quand toutes les actions\nde positionnement et de d�placement de l'objet ont �t� effectu�es."),
                   _("Centrer la cam�ra sur _PARAM0_ ( calque : _PARAM2_, cam�ra : _PARAM3_ )"),
                   _("Calques et cam�ras"),
                   "res/actions/camera24.png",
                   "res/actions/camera.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("object", _("Objet"), "", false);
        instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "1");
        instrInfo.AddParameter("yesorno", _("Anticiper le d�placement de l'objet ( oui par d�faut )"), "",true);
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",true).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",true).SetDefaultValue("0");


        instrInfo.cppCallingInformation.SetFunctionName("CenterCameraOnObject").SetIncludeFile("GDL/RuntimeSceneCameraTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("ShowLayer",
                   _("Afficher un calque"),
                   _("Rend visible un calque."),
                   _("Afficher le calque _PARAM0_"),
                   _("Calques et cam�ras"),
                   "res/actions/layer24.png",
                   "res/actions/layer.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",false).SetDefaultValue("\"\"");

        instrInfo.cppCallingInformation.SetFunctionName("ShowLayer").SetIncludeFile("GDL/RuntimeSceneTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("HideLayer",
                   _("Cacher un calque"),
                   _("Rend invisible un calque."),
                   _("Cacher le calque _PARAM0_"),
                   _("Calques et cam�ras"),
                   "res/actions/layer24.png",
                   "res/actions/layer.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",false).SetDefaultValue("\"\"");

        instrInfo.cppCallingInformation.SetFunctionName("HideLayer").SetIncludeFile("GDL/RuntimeSceneTools.h");;

    DECLARE_END_ACTION()

    DECLARE_CONDITION("LayerVisible",
                   _("Visibilit� d'un calque"),
                   _("Teste si un calque est affich�."),
                   _("Le calque _PARAM0_ est visible"),
                   _("Calques et cam�ras"),
                   "res/conditions/layer24.png",
                   "res/conditions/layer.png");

        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque ( Calque de base si vide )"), "",false).SetDefaultValue("\"\"");

        instrInfo.cppCallingInformation.SetFunctionName("IsLayerVisible").SetIncludeFile("GDL/RuntimeSceneTools.h");;

    DECLARE_END_CONDITION()

    DECLARE_EXPRESSION("CameraWidth", _("Largeur de la cam�ra d'un calque"), _("Largeur de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque"), "",false);
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",false).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraWidth");
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraHeight", _("Hauteur de la cam�ra d'un calque"), _("Hauteur de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque"), "",false);
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",false).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraHeight");
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraViewportLeft", _("Position X du cot� haut-gauche de la zone de rendu d'une cam�ra"), _("Position X du cot� haut-gauche de la zone de rendu d'une cam�ra"), _("Cam�ra"), "res/actions/camera.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque"), "",false);
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",false).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraViewportLeft");
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraViewportTop", _("Position Y du cot� haut-gauche de la zone de rendu d'une cam�ra"), _("Position Y du cot� haut-gauche de la zone de rendu d'une cam�ra"), _("Cam�ra"), "res/actions/camera.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque"), "",false);
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",false).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraViewportTop");
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraViewportRight", _("Position X du cot� bas-droit de la zone de rendu d'une cam�ra"), _("Position X du cot� bas-droit de la zone de rendu d'une cam�ra"), _("Cam�ra"), "res/actions/camera.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque"), "",false);
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",false).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraViewportRight");
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraViewportBottom", _("Position Y du cot� bas-droit de la zone de rendu d'une cam�ra"), _("Position Y du cot� bas-droit de la zone de rendu d'une cam�ra"), _("Cam�ra"), "res/actions/camera.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque"), "",false);
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",false).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraViewportBottom");
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraX", _("Position X de la cam�ra d'un calque"), _("Position X de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque"), "",true).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",true).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraX");
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("VueX", _("Position X de la cam�ra d'un calque"), _("Position X de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque"), "",true).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",true).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraX");
        instrInfo.SetHidden();
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraY", _("Position Y de la cam�ra d'un calque"), _("Position Y de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque"), "",true).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",true).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraY");
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("VueY", _("Position Y de la cam�ra d'un calque"), _("Position Y de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque"), "",true).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",true).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraY");
        instrInfo.SetHidden();
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("CameraRotation", _("Angle de la cam�ra d'un calque"), _("Angle de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque"), "",true).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",true).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraRotation");
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("VueRotation", _("Angle de la cam�ra d'un calque"), _("Angle de la cam�ra d'un calque"), _("Cam�ra"), "res/actions/camera.png")
        instrInfo.AddCodeOnlyParameter("currentScene", "");
        instrInfo.AddParameter("layer", _("Calque"), "",true).SetDefaultValue("\"\"");
        instrInfo.AddParameter("expression", _("Num�ro de la cam�ra ( 0 par d�faut )"), "",true).SetDefaultValue("0");

        instrInfo.cppCallingInformation.SetFunctionName("GetCameraRotation");
        instrInfo.SetHidden();
    DECLARE_END_EXPRESSION()
}

/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/SpriteExtension.h"
#include "GDL/SpriteObject.h"

SpriteExtension::SpriteExtension()
{
    DECLARE_THE_EXTENSION("Sprite",
                          _("Sprite ( image anim�e )"),
                          _("Extension permettant d'ajouter des objets anim�es � la sc�ne, qui peuvent contenir des animations avec des directions � l'int�rieur de chacune."),
                          "Compil Games",
                          "Freeware")

    //Declaration of all objects available
    DECLARE_OBJECT("Sprite",
                   _("Sprite ( image anim�e )"),
                   _("Objet anim�, compos� d'animations et directions contenant des images."),
                   "Extensions/spriteicon.png",
                   &CreateSpriteObject,
                   &DestroySpriteObject,
                   "SpriteObject");
        #if defined(GD_IDE_ONLY)

        objInfos.SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_OBJECT_ACTION("Opacity",
                       _("R�gler l'opacit� d'un objet"),
                       _("Modifie la transparence d'un objet."),
                       _("Faire _PARAM2__PARAM1_ � l'opacit� de _PARAM0_"),
                       _("Visibilit�"),
                       "res/actions/opacity24.png",
                       "res/actions/opacity.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Valeur"), "",false);
            instrInfo.AddParameter("operator", _("Signe de la modification"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("SetOpacity").SetAssociatedGetter("GetOpacity").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("ChangeAnimation",
                       _("Changer le num�ro de l'animation d'un objet"),
                       _("Modifie le num�ro de l'animation de l'objet."),
                       _("Faire _PARAM2__PARAM1_ au num�ro de l'animation de _PARAM0_"),
                       _("Animations et images"),
                       "res/actions/animation24.png",
                       "res/actions/animation.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Valeur"), "",false);
            instrInfo.AddParameter("operator", _("Signe de la modification"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("SetAnimation").SetAssociatedGetter("GetCurrentAnimation").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("ChangeDirection",
                       _("Changer le num�ro de la direction d'un objet"),
                       _("Modifie la direction de l'objet"),
                       _("Faire _PARAM2__PARAM1_ � la direction de _PARAM0_"),
                       _("Direction"),
                       "res/actions/direction24.png",
                       "res/actions/direction.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Valeur"), "",false);
            instrInfo.AddParameter("operator", _("Signe de la modification"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("SetDirection").SetAssociatedGetter("GetCurrentDirectionOrAngle").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("ChangeSprite",
                       _("Changer le num�ro de l'image d'un objet"),
                       _("Modifie le num�ro de l'image actuelle de l'objet"),
                       _("Faire _PARAM2__PARAM1_ au num�ro de l'image de _PARAM0_"),
                       _("Animations et images"),
                       "res/actions/sprite24.png",
                       "res/actions/sprite.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Valeur"), "",false);
            instrInfo.AddParameter("operator", _("Signe de la modification"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("SetSprite").SetAssociatedGetter("GetSpriteNb").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("PauseAnimation",
                       _("Mettre en pause l'animation de l'objet"),
                       _("Met en pause l'animation actuelle de l'objet"),
                       _("Mettre en pause l'animation actuelle de _PARAM0_"),
                       _("Animations et images"),
                       "res/actions/animation24.png",
                       "res/actions/animation.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);


            instrInfo.cppCallingInformation.SetFunctionName("StopAnimation").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("PlayAnimation",
                       _("Jouer l'animation de l'objet"),
                       _("Joue l'animation actuelle de l'objet"),
                       _("Jouer l'animation actuelle de _PARAM0_"),
                       _("Animations et images"),
                       "res/actions/animation24.png",
                       "res/actions/animation.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);


            instrInfo.cppCallingInformation.SetFunctionName("PlayAnimation").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("TourneVersPos",
                       _("Tourner un objet vers une position"),
                       _("Tourne un objet vers une position.\n( Si la direction est normale, l'objet prendra la direction la plus appropri�e.\nSi c'est une rotation automatique, il sera tourn� vers l'objet. )"),
                       _("Tourner _PARAM0_ vers _PARAM1_;_PARAM2_"),
                       _("Direction"),
                       "res/actions/direction24.png",
                       "res/actions/direction.png");

            instrInfo.AddParameter("object", _("Objet � tourner"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Position X"), "",false);
            instrInfo.AddParameter("expression", _("Position Y"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("TurnTowardPosition").SetIncludeFile("GDL/SpriteObject.h");


        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("ChangeScale",
                       _("Modifier l'�chelle d'un objet"),
                       _("Modifie l'�chelle de la taille de l'objet indiqu�."),
                       _("Faire _PARAM2__PARAM1_ � l'�chelle de la taille de _PARAM0_"),
                       _("Taille"),
                       "res/actions/scale24.png",
                       "res/actions/scale.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Valeur"), "",false);
            instrInfo.AddParameter("operator", _("Signe de la modification"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("ChangeScale").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("ChangeScaleWidth",
                       _("Modifier l'�chelle en largeur d'un objet"),
                       _("Modifie l'�chelle de la taille de l'objet indiqu� en largeur."),
                       _("Faire _PARAM2__PARAM1_ � l'�chelle de la taille de _PARAM0_ en largeur"),
                       _("Taille"),
                       "res/actions/scale24.png",
                       "res/actions/scale.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Valeur"), "",false);
            instrInfo.AddParameter("operator", _("Signe de la modification"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("SetScaleX").SetAssociatedGetter("GetScaleX").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("ChangeScaleHeight",
                       _("Modifier l'�chelle en hauteur d'un objet"),
                       _("Modifie l'�chelle de la taille de l'objet indiqu� en hauteur."),
                       _("Faire _PARAM2__PARAM1_ � l'�chelle de la taille de _PARAM0_ en hauteur"),
                       _("Taille"),
                       "res/actions/scale24.png",
                       "res/actions/scale.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Valeur"), "",false);
            instrInfo.AddParameter("operator", _("Signe de la modification"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("SetScaleY").SetAssociatedGetter("GetScaleY").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_CONDITION("Animation",
                       _("Num�ro de l'animation d'un objet"),
                       _("Teste si le num�ro de l'animation de l'objet correspond."),
                       _("Le num�ro de l'animation de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                       _("Animations et images"),
                       "res/conditions/animation24.png",
                       "res/conditions/animation.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Num�ro de l'animation � tester"), "",false);
            instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("GetCurrentAnimation").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_CONDITION()

        DECLARE_OBJECT_CONDITION("Direction",
                       _("Num�ro de la direction de l'objet"),
                       _("Teste si le num�ro de la direction de l'objet correspond au test effectu�."),
                       _("La direction de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                       _("Direction"),
                       "res/conditions/direction24.png",
                       "res/conditions/direction.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Num�ro de la direction � tester"), "",false);
            instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("GetCurrentDirectionOrAngle").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_CONDITION()

        DECLARE_OBJECT_CONDITION("Sprite",
                       _("Num�ro de l'image de l'objet"),
                       _("Teste si le num�ro de l'image de l'objet correspond."),
                       _("L'image de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                       _("Animations et images"),
                       "res/conditions/sprite24.png",
                       "res/conditions/sprite.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Num�ro de l'image � tester"), "",false);
            instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("GetSpriteNb").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_CONDITION()

        DECLARE_OBJECT_CONDITION("AnimStopped",
                       _("L'animation est en pause"),
                       _("Teste si l'animation de l'objet est en pause."),
                       _("L'animation de _PARAM0_ est en pause"),
                       _("Animations et images"),
                       "res/conditions/animation24.png",
                       "res/conditions/animation.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);


            instrInfo.cppCallingInformation.SetFunctionName("IsAnimationStopped").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_CONDITION()

        DECLARE_OBJECT_CONDITION("ScaleWidth",
                       _("Echelle de la taille d'un objet en largeur"),
                       _("Teste l'�chelle de la taille de l'objet en largeur."),
                       _("L'�chelle de la taille de l'objet _PARAM0_ en largeur est _PARAM2_ � _PARAM1_"),
                       _("Taille"),
                       "res/conditions/scaleWidth24.png",
                       "res/conditions/scaleWidth.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Valeur � tester"), "",false);
            instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("GetScaleX").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_CONDITION()

        DECLARE_OBJECT_CONDITION("ScaleHeight",
                       _("Echelle de la taille d'un objet en hauteur"),
                       _("Teste l'�chelle de la taille de l'objet en hauteur."),
                       _("L'�chelle de la taille de l'objet _PARAM0_ en hauteur est _PARAM2_ � _PARAM1_"),
                       _("Taille"),
                       "res/conditions/scaleHeight24.png",
                       "res/conditions/scaleHeight.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Valeur � tester"), "",false);
            instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("GetScaleY").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_CONDITION()

        DECLARE_OBJECT_CONDITION("Opacity",
                       _("Opacit� d'un objet"),
                       _("Teste la valeur de l'opacit� ( transparence ) d'un objet."),
                       _("L'opacit� de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                       _("Visibilit�"),
                       "res/conditions/opacity24.png",
                       "res/conditions/opacity.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Valeur � tester"), "",false);
            instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("GetOpacity").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_CONDITION()

        DECLARE_OBJECT_CONDITION("BlendMode",
                       _("Mode d'affichage"),
                       _("Teste le num�ro du mode d'affichage actuellement employ� par un objet"),
                       _("Le num�ro du mode d'affichage de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                       _("Effets"),
                       "res/conditions/opacity24.png",
                       "res/conditions/opacity.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Valeur � tester ( 0 : Alpha, 1 : Add, 2 : Multiply, 3 : None )"), "",false);
            instrInfo.AddParameter("relationalOperator", _("Signe du test"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("GetBlendMode").SetManipulatedType("number").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_CONDITION()

        DECLARE_OBJECT_ACTION("CopyImageOnImageOfSprite",
                       _("Copier une image sur celle d'un objet"),
                       _("Copie une image sur celle d'un objet.\nNotez qu'il est pr�f�rable que l'image source reste charg�e en m�moire."),
                       _("Copier l'image _PARAM2_ sur celle de _PARAM0_ � l'emplacement _PARAM3_;_PARAM4_"),
                       _("Effets"),
                       "res/actions/copy24.png",
                       "res/actions/copy.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddCodeOnlyParameter("currentScene", "");
            instrInfo.AddParameter("string", _("Nom de l'image source"), "",false);
            instrInfo.AddParameter("expression", _("Position X"), "",false);
            instrInfo.AddParameter("expression", _("Position Y"), "",false);
            instrInfo.AddParameter("yesorno", _("Utiliser la transparence de la source ( non si vide )"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("CopyImageOnImageOfCurrentSprite").SetIncludeFile("GDL/SpriteObject.h");


        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("CreateMaskFromColorOnActualImage", //Actual is indeed a mistake : Current should have been chosen.
                       _("Rendre une couleur de l'image d'un objet transparente"),
                       _("Rend une couleur de l'image d'un objet transparente."),
                       _("Rendre la couleur _PARAM1_ de l'image actuelle de _PARAM0_ transparente"),
                       _("Effets"),
                       "res/actions/opacity24.png",
                       "res/actions/opacity.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("color", _("Couleur � rendre transparente"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("MakeColorTransparent").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("ChangeColor",
                       _("Changer la couleur globale d'un objet"),
                       _("Change la couleur globale de l'objet. Par d�faut, la couleur est le blanc."),
                       _("Changer la couleur de _PARAM0_ en _PARAM1_"),
                       _("Effets"),
                       "res/actions/color24.png",
                       "res/actions/color.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("color", _("Couleur"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("SetColor").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("ChangeBlendMode",
                       _("Changer le mode d'affichage"),
                       _("Change le num�ro de mode d'affichage d'un objet.\nLe mode d'affichage par d�faut est 0 ( Alpha )."),
                       _("Changer le num�ro de mode d'affichage de _PARAM0_ en _PARAM1_"),
                       _("Effets"),
                       "res/actions/color24.png",
                       "res/actions/color.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("expression", _("Mode ( 0 : Alpha, 1 : Add, 2 : Multiply, 3 : None )"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("SetBlendMode").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("FlipX",
                       _("Inverser l'affichage horizontalement"),
                       _("Inverse l'affichage de l'objet horizontalement"),
                       _("Inverser l'affichage de _PARAM0_ horizontalement : _PARAM1_"),
                       _("Effets"),
                       "res/actions/flipX24.png",
                       "res/actions/flipX.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("yesorno", _("Activer l'inversion"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("FlipX").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("FlipY",
                       _("Inverser l'affichage verticalement"),
                       _("Inverse l'affichage de l'objet verticalement"),
                       _("Inverser l'affichage de _PARAM0_ verticalement : _PARAM1_"),
                       _("Effets"),
                       "res/actions/flipY24.png",
                       "res/actions/flipY.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("yesorno", _("Activer l'inversion"), "",false);


            instrInfo.cppCallingInformation.SetFunctionName("FlipY").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("TourneVers",
                       _("Tourner un objet vers un autre"),
                       _("Tourne un objet vers un autre.\n( Si la direction est normale, l'objet prendra la direction la plus appropri�e.\nSi c'est une rotation automatique, il sera tourn� vers l'objet. )"),
                       _("Tourner _PARAM0_ vers _PARAM1_"),
                       _("Direction"),
                       "res/actions/direction24.png",
                       "res/actions/direction.png");

            instrInfo.AddParameter("object", _("Objet � tourner"), "Sprite", false);
            instrInfo.AddParameter("object", _("Objet vers lequel se tourner"), "", false);
            instrInfo.AddCodeOnlyParameter("ptrToObjectOfParameter", "1");

            instrInfo.cppCallingInformation.SetFunctionName("TurnTowardObject").SetIncludeFile("GDL/SpriteTools.h");

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_CONDITION("SourisSurObjet",
                       _("Le curseur est sur un objet"),
                       _("Teste si le curseur survole un objet. Le test est pr�cis par d�faut ( v�rifie que le curseur n'est pas sur une zone transparente )."),
                       _("Le curseur est sur _PARAM0_"),
                       _("Souris"),
                       "res/conditions/surObjet24.png",
                       "res/conditions/surObjet.png");

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddCodeOnlyParameter("currentScene", "");
            instrInfo.AddParameter("yesorno", _("Test pr�cis ? ( oui par d�faut )"), "", true).SetDefaultValue("yes");

            instrInfo.cppCallingInformation.SetFunctionName("CursorOnObject").SetIncludeFile("GDL/SpriteTools.h");

        DECLARE_END_OBJECT_CONDITION()

        DECLARE_OBJECT_EXPRESSION("X", _("Position X d'un point"), _("Position X d'un point"), _("Position"), "res/actions/position.png")

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("", _("Nom du point"), "", true);

            instrInfo.cppCallingInformation.SetFunctionName("GetPointX").SetIncludeFile("GDL/SpriteObject.h");
            instrInfo.SetHidden();

        DECLARE_END_OBJECT_EXPRESSION()

        DECLARE_OBJECT_EXPRESSION("Y", _("Position Y d'un point"), _("Position Y d'un point"), _("Position"), "res/actions/position.png")

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("", _("Nom du point"), "", true);

            instrInfo.cppCallingInformation.SetFunctionName("GetPointY").SetIncludeFile("GDL/SpriteObject.h");
            instrInfo.SetHidden();

        DECLARE_END_OBJECT_EXPRESSION()

        DECLARE_OBJECT_EXPRESSION("PointX", _("Position X d'un point"), _("Position X d'un point"), _("Position"), "res/actions/position.png")

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("", _("Nom du point"), "",false);

            instrInfo.cppCallingInformation.SetFunctionName("GetPointX").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_EXPRESSION()

        DECLARE_OBJECT_EXPRESSION("PointY", _("Position Y d'un point"), _("Position Y d'un point"), _("Position"), "res/actions/position.png")

            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);
            instrInfo.AddParameter("", _("Nom du point"), "",false);

            instrInfo.cppCallingInformation.SetFunctionName("GetPointY").SetIncludeFile("GDL/SpriteObject.h");

        DECLARE_END_OBJECT_EXPRESSION()

        DECLARE_OBJECT_EXPRESSION("Direc", _("Direction"), _("Direction de l'objet"), _("Direction"), "res/actions/direction.png")
            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);

            instrInfo.cppCallingInformation.SetFunctionName("GetCurrentDirectionOrAngle").SetIncludeFile("GDL/SpriteObject.h");
            instrInfo.SetHidden();
        DECLARE_END_OBJECT_EXPRESSION()

        DECLARE_OBJECT_EXPRESSION("Direction", _("Direction"), _("Direction de l'objet"), _("Direction"), "res/actions/direction.png")
            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);

            instrInfo.cppCallingInformation.SetFunctionName("GetCurrentDirectionOrAngle").SetIncludeFile("GDL/SpriteObject.h");
        DECLARE_END_OBJECT_EXPRESSION()

        DECLARE_OBJECT_EXPRESSION("Anim", _("Animation"), _("Animation de l'objet"), _("Animations et images"), "res/actions/animation.png")
            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);

            instrInfo.cppCallingInformation.SetFunctionName("GetCurrentAnimation").SetIncludeFile("GDL/SpriteObject.h");
            instrInfo.SetHidden();
        DECLARE_END_OBJECT_EXPRESSION()

        DECLARE_OBJECT_EXPRESSION("Animation", _("Animation"), _("Animation de l'objet"), _("Animations et images"), "res/actions/animation.png")
            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);

            instrInfo.cppCallingInformation.SetFunctionName("GetCurrentAnimation").SetIncludeFile("GDL/SpriteObject.h");
        DECLARE_END_OBJECT_EXPRESSION()

        DECLARE_OBJECT_EXPRESSION("Sprite", _("Image"), _("Num�ro de l'image de l'objet"), _("Animations et images"), "res/actions/sprite.png")
            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);

            instrInfo.cppCallingInformation.SetFunctionName("GetSpriteNb").SetIncludeFile("GDL/SpriteObject.h");
        DECLARE_END_OBJECT_EXPRESSION()

        DECLARE_OBJECT_EXPRESSION("ScaleX", _("Echelle de la taille en largeur"), _("Echelle de la taille en largeur"), _("Taille"), "res/actions/scaleWidth.png")
            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);

            instrInfo.cppCallingInformation.SetFunctionName("GetScaleX").SetIncludeFile("GDL/SpriteObject.h");
        DECLARE_END_OBJECT_EXPRESSION()

        DECLARE_OBJECT_EXPRESSION("ScaleY", _("Echelle de la taille en hauteur"), _("Echelle de la taille en hauteur"), _("Taille"), "res/actions/scaleHeight.png")
            instrInfo.AddParameter("object", _("Objet"), "Sprite", false);

            instrInfo.cppCallingInformation.SetFunctionName("GetScaleY").SetIncludeFile("GDL/SpriteObject.h");
        DECLARE_END_OBJECT_EXPRESSION()
        #endif

    DECLARE_END_OBJECT()

    #if defined(GD_IDE_ONLY)

    //Declaration of all conditions available

    DECLARE_CONDITION("EstTourne", //CONVERT TO OBJECT INSTRUCTION //TODO Par ici
                      _("Un objet est tourn� vers un autre"),
                      _("Teste si un objet est tourn� vers un autre"),
                      _("L'objet _PARAM0_ est tourn� vers _PARAM1_"),
                      _("Direction"),
                      "res/conditions/estTourne24.png",
                      "res/conditions/estTourne.png");

        instrInfo.AddParameter("object", _("Nom de l'objet"), "Sprite", false);
        instrInfo.AddParameter("object", _("Nom du second objet"), "", false);
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "0");
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "1");
        instrInfo.AddParameter("expression", _("Angle de tol�rance ( 0 : tol�rance minimale )"), "",false);
        instrInfo.AddCodeOnlyParameter("conditionInverted", "");

        instrInfo.cppCallingInformation.SetFunctionName("SpriteTurnedToward").SetIncludeFile("GDL/SpriteTools.h");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("Collision",
                      _("Collision"),
                      _("La condition est vraie si il y a collision entre les deux objets donn�s.\nLa collision est faite au pixel pr�s.\nAttention ! Cette condition est couteuse pour l'ordinateur en terme de perfomance."),
                      _("_PARAM0_ est en collision avec _PARAM1_"),
                      _("Collision"),
                      "res/conditions/collision24.png",
                      "res/conditions/collision.png");

        instrInfo.AddParameter("object", _("Objet 1"), "Sprite", false);
        instrInfo.AddParameter("object", _("Objet 2"), "Sprite", false);
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "0");
        instrInfo.AddCodeOnlyParameter("mapOfObjectListsOfParameter", "1");
        instrInfo.AddCodeOnlyParameter("conditionInverted", "");

        instrInfo.cppCallingInformation.SetFunctionName("SpriteCollision").SetIncludeFile("GDL/SpriteTools.h");

    DECLARE_END_CONDITION()

    #endif
}

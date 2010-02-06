#include "GDL/TextExtension.h"
#include "GDL/TextObject.h"

TextExtension::TextExtension()
{
    DECLARE_THE_EXTENSION("TextObject",
                          _("Objet Texte"),
                          _("Extension permettant d'utiliser un objet affichant du texte."),
                          "Compil Games",
                          "Freeware")

    //Declaration of all objects available
    DECLARE_OBJECT("Text",
                   _("Texte"),
                   _("Objet affichant un texte"),
                   "Extensions/texticon.png",
                   &CreateTextObject,
                   &CreateTextObjectByCopy,
                   &DestroyTextObject);

        DECLARE_OBJECT_ACTION("String",
                       _("Modifier le texte"),
                       _("Modifier le texte d'un objet texte."),
                       _("Faire _PARAM2__PARAM1_ au texte de _PARAM0_"),
                       _("Texte"),
                       "res/actions/text24.png",
                       "res/actions/text.png",
                       &TextObject::ActString);

            DECLARE_PARAMETER("objet", _("Objet"), true, "Text")
            DECLARE_PARAMETER("texte", _("Texte"), false, "")
            DECLARE_PARAMETER("signe", _("Signe de la modification"), false, "")
            MAIN_OBJECTS_IN_PARAMETER(0)

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_CONDITION("String",
                       _("Tester le texte"),
                       _("Teste le texte d'un objet texte."),
                       _("Le texte de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                       _("Texte"),
                       "res/conditions/text24.png",
                       "res/conditions/text.png",
                       &TextObject::CondString);

            DECLARE_PARAMETER("objet", _("Objet"), true, "Text")
            DECLARE_PARAMETER("texte", _("Texte � tester"), false, "")
            DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
            MAIN_OBJECTS_IN_PARAMETER(0)

        DECLARE_END_OBJECT_CONDITION()

        DECLARE_OBJECT_ACTION("Font",
                       _("Changer la police"),
                       _("Modifie la police de caract�re du texte."),
                       _("Changer la police de _PARAM0_ en _PARAM1_"),
                       _("Police"),
                       "res/actions/font24.png",
                       "res/actions/font.png",
                       &TextObject::ActFont);

            DECLARE_PARAMETER("objet", _("Objet"), true, "Text")
            DECLARE_PARAMETER("police", _("Valeur"), false, "")
            MAIN_OBJECTS_IN_PARAMETER(0)

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("Size",
                       _("R�gler la taille du texte"),
                       _("Modifie la taille du texte."),
                       _("Faire _PARAM2__PARAM1_ � la taille du texte de _PARAM0_"),
                       _("Taille"),
                       "res/actions/characterSize24.png",
                       "res/actions/characterSize.png",
                       &TextObject::ActSize);

            DECLARE_PARAMETER("objet", _("Objet"), true, "Text")
            DECLARE_PARAMETER("expression", _("Valeur"), false, "")
            DECLARE_PARAMETER("signe", _("Signe de la modification"), false, "")
            MAIN_OBJECTS_IN_PARAMETER(0)

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_CONDITION("Size",
                       _("Taille du texte"),
                       _("Teste la taille du texte."),
                       _("La taille du texte de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                       _("Taille"),
                       "res/conditions/characterSize24.png",
                       "res/conditions/characterSize.png",
                       &TextObject::CondSize);

            DECLARE_PARAMETER("objet", _("Objet"), true, "Text")
            DECLARE_PARAMETER("expression", _("Taille � tester"), false, "")
            DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
            MAIN_OBJECTS_IN_PARAMETER(0)

        DECLARE_END_OBJECT_CONDITION()

        DECLARE_OBJECT_ACTION("ChangeColor",
                       _("Changer la couleur d'un objet texte"),
                       _("Change la couleur du texte. Par d�faut, la couleur est le blanc."),
                       _("Changer la couleur de _PARAM0_ en _PARAM1_"),
                       _("Effets"),
                       "res/actions/color24.png",
                       "res/actions/color.png",
                       &TextObject::ActChangeColor);

            DECLARE_PARAMETER("objet", _("Objet"), true, "Text")
            DECLARE_PARAMETER("color", _("Couleur"), false, "")
            MAIN_OBJECTS_IN_PARAMETER(0)

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_ACTION("Opacity",
                       _("R�gler l'opacit� d'un objet"),
                       _("Modifie la transparence d'un objet texte."),
                       _("Faire _PARAM2__PARAM1_ � l'opacit� de _PARAM0_"),
                       _("Visibilit�"),
                       "res/actions/opacity24.png",
                       "res/actions/opacity.png",
                       &TextObject::ActOpacity);

            DECLARE_PARAMETER("objet", _("Objet"), true, "Text")
            DECLARE_PARAMETER("expression", _("Valeur"), false, "")
            DECLARE_PARAMETER("signe", _("Signe de la modification"), false, "")
            MAIN_OBJECTS_IN_PARAMETER(0)

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_CONDITION("Opacity",
                       _("Opacit� d'un objet"),
                       _("Teste la valeur de l'opacit� ( transparence ) d'un objet texte."),
                       _("L'opacit� de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                       _("Visibilit�"),
                       "res/conditions/opacity24.png",
                       "res/conditions/opacity.png",
                       &TextObject::CondOpacity);

            DECLARE_PARAMETER("objet", _("Objet"), true, "Text")
            DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
            DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
            MAIN_OBJECTS_IN_PARAMETER(0)

        DECLARE_END_OBJECT_CONDITION()


        DECLARE_OBJECT_ACTION("Angle",
                       _("R�gler l'angle d'un objet texte"),
                       _("Modifie l'angle d'un objet texte."),
                       _("Faire _PARAM2__PARAM1_ � l'angle de _PARAM0_"),
                       _("Rotation"),
                       "res/actions/rotate24.png",
                       "res/actions/rotate.png",
                       &TextObject::ActAngle);

            DECLARE_PARAMETER("objet", _("Objet"), true, "Text")
            DECLARE_PARAMETER("expression", _("Valeur"), false, "")
            DECLARE_PARAMETER("signe", _("Signe de la modification"), false, "")
            MAIN_OBJECTS_IN_PARAMETER(0)

        DECLARE_END_OBJECT_ACTION()

        DECLARE_OBJECT_CONDITION("Angle",
                       _("Angle d'un objet texte"),
                       _("Teste la valeur de l'angle d'un objet texte."),
                       _("L'angle de _PARAM0_ est _PARAM2_ � _PARAM1_"),
                       _("Rotation"),
                       "res/conditions/rotate24.png",
                       "res/conditions/rotate.png",
                       &TextObject::CondAngle);

            DECLARE_PARAMETER("objet", _("Objet"), true, "Text")
            DECLARE_PARAMETER("expression", _("Valeur � tester"), false, "")
            DECLARE_PARAMETER("signe", _("Signe du test"), false, "")
            MAIN_OBJECTS_IN_PARAMETER(0)

        DECLARE_END_OBJECT_CONDITION()

        DECLARE_OBJECT_EXPRESSION("opacity", _("Opacit�"), _("Opacit�"), _("Opacit�"), "res/actions/opacity.png", &TextObject::GetOpacity)
            DECLARE_PARAMETER("object", _("Objet"), true, "Text")
        DECLARE_END_OBJECT_EXPRESSION()

        DECLARE_OBJECT_EXPRESSION("angle", _("Angle"), _("Angle"), _("Rotation"), "res/actions/rotate.png", &TextObject::GetAngle)
            DECLARE_PARAMETER("object", _("Objet"), true, "Text")
        DECLARE_END_OBJECT_EXPRESSION()

    DECLARE_END_OBJECT()
}

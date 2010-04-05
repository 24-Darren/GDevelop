#include "GDL/AdvancedExtension.h"
#include "GDL/ExtensionBase.h"
#include "GDL/cScene.h"

AdvancedExtension::AdvancedExtension()
{
    DECLARE_THE_EXTENSION("BuiltinAdvanced",
                          _("Fonctionnalit�s de contr�le avanc�"),
                          _("Extension offrant des fonctionnalit�s de contr�le avanc�, integr�e en standard"),
                          "Compil Games",
                          "Freeware")

    DECLARE_CONDITION("ForEach",
                   _("R�p�ter pour chaque objet"),
                   _("Condition sp�ciale qui r�p�te les conditions actions suivantes pour chaque objet concern�."),
                   _("Pour chaque _PARAM0_, r�p�ter les conditions et actions suivantes :"),
                   _("Avanc�"),
                   "res/conditions/foreach24.png",
                   "res/conditions/foreach.png",
                   NULL);

        DECLARE_PARAMETER("objet", _("Objet"), true, "")

    DECLARE_END_CONDITION()

    DECLARE_ACTION("ForEach",
                   _("R�p�ter pour chaque objet"),
                   _("Action sp�ciale qui r�p�te les actions suivantes pour chaque objet concern�."),
                   _("Pour chaque _PARAM0_, r�p�ter les actions suivantes :"),
                   _("Avanc�"),
                   "res/actions/foreach24.png",
                   "res/actions/foreach.png",
                   NULL);

        DECLARE_PARAMETER("objet", _("Objet"), true, "")

    DECLARE_END_ACTION()

    DECLARE_CONDITION("While",
                   _("Tant que"),
                   _("Condition sp�ciale qui r�p�te les conditions et actions suivantes tant que\nla condition qui la suit est remplie ou non."),
                   _("Tant que la condition suivante est _PARAM0_, r�p�ter les conditions et actions suivantes :"),
                   _("Avanc�"),
                   "res/conditions/while24.png",
                   "res/conditions/while.png",
                   NULL);

        DECLARE_PARAMETER("trueorfalse", _("La condition suivante doit �tre"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("Repeat",
                   _("R�p�ter"),
                   _("Condition sp�ciale qui r�p�te les conditions et actions suivantes un certain nombre de fois."),
                   _("R�p�ter _PARAM0_ fois les conditions et actions suivantes :"),
                   _("Avanc�"),
                   "res/conditions/repeat24.png",
                   "res/conditions/repeat.png",
                   NULL);

        DECLARE_PARAMETER("expression", _("Nombre de r�p�tition"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_ACTION("Repeat",
                   _("R�p�ter"),
                   _("Action sp�ciale qui r�p�te les actions suivantes un certain nombre de fois."),
                   _("R�p�ter _PARAM0_ fois les actions suivantes :"),
                   _("Avanc�"),
                   "res/actions/repeat24.png",
                   "res/actions/repeat.png",
                   NULL);

        DECLARE_PARAMETER("expression", _("Nombre de r�p�tition"), false, "")

    DECLARE_END_ACTION()

    DECLARE_CONDITION("Toujours",
                   _("Toujours"),
                   _("Cette condition renvoie toujours vrai."),
                   _("Toujours"),
                   _("Autre"),
                   "res/conditions/toujours24.png",
                   "res/conditions/toujours.png",
                   &CondAlways);

    DECLARE_END_CONDITION()
}

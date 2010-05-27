#include "GDL/CommonConversionsExtension.h"
#include "GDL/CommonConversions.h"

CommonConversionsExtension::CommonConversionsExtension()
{
    DECLARE_THE_EXTENSION("BuiltinCommonConversions",
                          _("Conversions standards"),
                          _("Extension apportant des expressions de conversion, int�gr�e en standard."),
                          "Compil Games",
                          "Freeware")


    DECLARE_EXPRESSION("ToNumber",
                       _("Convertir en un nombre"),
                       _("Converti le texte en un nombre"),
                       _("Conversion"),
                       "res/conditions/toujours24.png",
                       &ExpToNumber)

        DECLARE_PARAMETER("text", _("Texte � convertir en nombre"), false, "")

    DECLARE_END_EXPRESSION()

    DECLARE_STR_EXPRESSION("ToString",
                       _("Convertir en un texte"),
                       _("Converti le r�sultat de l'expression en un texte"),
                       _("Conversion"),
                       "res/conditions/toujours24.png",
                       &ExpToStr)

        DECLARE_PARAMETER("expression", _("Expression � convertir en texte"), false, "")

    DECLARE_END_STR_EXPRESSION()
}

#include "GDL/BuiltinExtensions/CommonConversionsExtension.h"

CommonConversionsExtension::CommonConversionsExtension()
{
    DECLARE_THE_EXTENSION("BuiltinCommonConversions",
                          _("Conversions standards"),
                          _("Extension apportant des expressions de conversion, int�gr�e en standard."),
                          "Compil Games",
                          "Freeware")
    #if defined(GD_IDE_ONLY)

    DECLARE_EXPRESSION("ToNumber",
                       _("Texte > Nombre"),
                       _("Convertit le texte en un nombre"),
                       _("Conversion"),
                       "res/conditions/toujours24.png")

        instrInfo.AddParameter("string", _("Texte � convertir en nombre"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GDpriv::CommonInstructions::ToDouble").SetIncludeFile("GDL/BuiltinExtensions/CommonInstructionsTools.h");

    DECLARE_END_EXPRESSION()

    DECLARE_STR_EXPRESSION("ToString",
                       _("Nombre > Texte"),
                       _("Convertit le r�sultat de l'expression en un texte"),
                       _("Conversion"),
                       "res/conditions/toujours24.png")

        instrInfo.AddParameter("expression", _("Expression � convertir en texte"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GDpriv::CommonInstructions::ToString").SetIncludeFile("GDL/BuiltinExtensions/CommonInstructionsTools.h");

    DECLARE_END_STR_EXPRESSION()

    DECLARE_STR_EXPRESSION("LargeNumberToString",
                       _("Nombre > Texte ( sans notation scientifique )"),
                       _("Convertit le r�sultat de l'expression en un texte, sans utiliser la notation scientifique"),
                       _("Conversion"),
                       "res/conditions/toujours24.png")

        instrInfo.AddParameter("expression", _("Expression � convertir en texte"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GDpriv::CommonInstructions::LargeNumberToString").SetIncludeFile("GDL/BuiltinExtensions/CommonInstructionsTools.h");

    DECLARE_END_STR_EXPRESSION()

    DECLARE_EXPRESSION("ToRad",
                       _("Degr�s > Radians"),
                       _("Convertit l'angle, exprim� en degr�s, en radians"),
                       _("Conversion"),
                       "res/conditions/toujours24.png")

        instrInfo.AddParameter("expression", _("Angle en degr�s"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GDpriv::CommonInstructions::ToRad").SetIncludeFile("GDL/BuiltinExtensions/CommonInstructionsTools.h");

    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("ToDeg",
                       _("Radians > Degr�s"),
                       _("Convertit l'angle, exprim� en radians, en degr�s"),
                       _("Conversion"),
                       "res/conditions/toujours24.png")

        instrInfo.AddParameter("expression", _("Angle en radians"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GDpriv::CommonInstructions::ToDeg").SetIncludeFile("GDL/BuiltinExtensions/CommonInstructionsTools.h");

    DECLARE_END_EXPRESSION()
    #endif
}

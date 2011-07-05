#include "MathematicalToolsExtension.h"

MathematicalToolsExtension::MathematicalToolsExtension()
{
    DECLARE_THE_EXTENSION("BuiltinMathematicalTools",
                          _("Outils math�matiques"),
                          _("Extension proposant des outils math�matiques, integr�e en standard"),
                          "Compil Games",
                          "Freeware")

    DECLARE_EXPRESSION("min", _("Minimum de deux nombres"), _("Minimum de deux nombres"), _("Outils math�matiques"), "res/actions/time.png")
        DECLARE_PARAMETER("expression", _("Premi�re expression"), "", false);
        DECLARE_PARAMETER("expression", _("Deuxi�me expression"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("Minimal").SetIncludeFile("GDL/MathematicalTools.h");
    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("max", _("Maximum de deux nombres"), _("Maximum de deux nombres"), _("Outils math�matiques"), "res/actions/time.png")
        DECLARE_PARAMETER("expression", _("Premi�re expression"), "", false);
        DECLARE_PARAMETER("expression", _("Deuxi�me expression"), "", false);

        instrInfo.cppCallingInformation.SetFunctionName("Maximal").SetIncludeFile("GDL/MathematicalTools.h");
    DECLARE_END_EXPRESSION()
}

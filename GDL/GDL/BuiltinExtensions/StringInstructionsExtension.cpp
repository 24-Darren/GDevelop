/** \file
 *  Game Develop
 *  2008-2012 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/BuiltinExtensions/StringInstructionsExtension.h"
#include "GDL/ExtensionBase.h"

StringInstructionsExtension::StringInstructionsExtension()
{
    DECLARE_THE_EXTENSION("BuiltinStringInstructions",
                          _("Manipulation de texte"),
                          _("Extension apportant des expressions de manipulation de texte, int�gr�e en standard."),
                          "Compil Games",
                          "Freeware")

    #if defined(GD_IDE_ONLY)

    DECLARE_STR_EXPRESSION("SubStr",
                   _("Obtenir une portion de texte depuis un texte"),
                   _("Obtenir une portion de texte depuis un texte"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png")

        instrInfo.AddParameter("string", _("Texte"), "",false);
        instrInfo.AddParameter("expression", _("Position de d�part de la portion ( La premi�re lettre est � la position 0 )"), "",false);
        instrInfo.AddParameter("expression", _("Longueur de la portion"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GDpriv::StringTools::SubStr").SetIncludeFile("GDL/BuiltinExtensions/StringTools.h");

    DECLARE_END_STR_EXPRESSION()

    DECLARE_STR_EXPRESSION("StrAt",
                   _("Obtenir un caract�re depuis un texte"),
                   _("Obtenir un caract�re depuis un texte"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png")

        instrInfo.AddParameter("string", _("Texte"), "",false);
        instrInfo.AddParameter("expression", _("Position du caract�re � pr�lever ( Premier caract�re : 0 )"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GDpriv::StringTools::StrAt").SetIncludeFile("GDL/BuiltinExtensions/StringTools.h");

    DECLARE_END_STR_EXPRESSION()

    DECLARE_EXPRESSION("StrLength",
                   _("Longueur d'un texte"),
                   _("Longueur d'un texte"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png")

        instrInfo.AddParameter("string", _("Texte"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GDpriv::StringTools::StrLen").SetIncludeFile("GDL/BuiltinExtensions/StringTools.h");

    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("StrFind",
                   _("Chercher dans un texte"),
                   _("Chercher dans un texte ( Retourne la position du r�sultat ou -1 si non trouv� )"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png")

        instrInfo.AddParameter("string", _("Texte"), "",false);
        instrInfo.AddParameter("string", _("Texte � chercher"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GDpriv::StringTools::StrFind").SetIncludeFile("GDL/BuiltinExtensions/StringTools.h");

    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("StrRFind",
                   _("Chercher dans un texte depuis la fin"),
                   _("Chercher dans un texte depuis la fin ( Retourne la position du r�sultat ou -1 si non trouv� )"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png")

        instrInfo.AddParameter("string", _("Texte"), "",false);
        instrInfo.AddParameter("string", _("Texte � chercher"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GDpriv::StringTools::StrRFind").SetIncludeFile("GDL/BuiltinExtensions/StringTools.h");

    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("StrFindFrom",
                   _("Chercher dans un texte � partir d'une position"),
                   _("Chercher dans un texte � partir d'une position ( Retourne la position du r�sultat ou -1 si non trouv� )"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png")

        instrInfo.AddParameter("string", _("Texte"), "",false);
        instrInfo.AddParameter("string", _("Texte � chercher"), "",false);
        instrInfo.AddParameter("expression", _("Position � partir de laquelle chercher le texte"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GDpriv::StringTools::StrFindFrom").SetIncludeFile("GDL/BuiltinExtensions/StringTools.h");

    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("StrRFindFrom",
                   _("Chercher dans un texte depuis la fin � partir d'une position"),
                   _("Chercher dans un texte depuis la fin � partir d'une position ( Retourne la position du r�sultat ou -1 si non trouv� )"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png")

        instrInfo.AddParameter("string", _("Texte"), "",false);
        instrInfo.AddParameter("string", _("Texte � chercher"), "",false);
        instrInfo.AddParameter("expression", _("Position � partir de laquelle chercher le texte"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("GDpriv::StringTools::StrRFindFrom").SetIncludeFile("GDL/BuiltinExtensions/StringTools.h");

    DECLARE_END_EXPRESSION()
    #endif
}

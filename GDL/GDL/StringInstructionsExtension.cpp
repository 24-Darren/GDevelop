/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/StringInstructionsExtension.h"
#include "GDL/StringExpressions.h"
#include "GDL/CommentEvent.h"
#include "GDL/StandardEvent.h"
#include "GDL/LinkEvent.h"
#include "GDL/WhileEvent.h"
#include "GDL/RepeatEvent.h"
#include "GDL/ForEachEvent.h"
#include "GDL/Event.h"

#include "GDL/ExtensionBase.h"

StringInstructionsExtension::StringInstructionsExtension()
{
    DECLARE_THE_EXTENSION("BuiltinStringInstructions",
                          _T("Manipulation de texte"),
                          _T("Extension apportant des expressions de manipulation de texte, int�gr�e en standard."),
                          "Compil Games",
                          "Freeware")

    DECLARE_STR_EXPRESSION("SubStr",
                   _T("Obtenir une portion de texte depuis un texte"),
                   _T("Obtenir une portion de texte depuis un texte"),
                   _T("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpSubStr)

        DECLARE_PARAMETER("text", _T("Texte"), false, "")
        DECLARE_PARAMETER("expression", _T("Position de d�part de la portion ( La premi�re lettre est � la position 0 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Longueur de la portion"), false, "")

    DECLARE_END_STR_EXPRESSION()

    DECLARE_STR_EXPRESSION("StrAt",
                   _T("Obtenir un caract�re depuis un texte"),
                   _T("Obtenir un caract�re depuis un texte"),
                   _T("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpStrAt)

        DECLARE_PARAMETER("text", _T("Texte"), false, "")
        DECLARE_PARAMETER("expression", _T("Position du caract�re � pr�lever ( Premier caract�re : 0 )"), false, "")

    DECLARE_END_STR_EXPRESSION()

    DECLARE_EXPRESSION("StrLength",
                   _T("Longueur d'un texte"),
                   _T("Longueur d'un texte"),
                   _T("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpStrLen)

        DECLARE_PARAMETER("text", _T("Texte"), false, "")

    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("StrFind",
                   _T("Chercher dans un texte"),
                   _T("Chercher dans un texte ( Retourne la position du r�sultat ou -1 si non trouv� )"),
                   _T("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpStrFind)

        DECLARE_PARAMETER("text", _T("Texte"), false, "")
        DECLARE_PARAMETER("text", _T("Texte � chercher"), false, "")

    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("StrRFind",
                   _T("Chercher dans un texte depuis la fin"),
                   _T("Chercher dans un texte depuis la fin ( Retourne la position du r�sultat ou -1 si non trouv� )"),
                   _T("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpStrRFind)

        DECLARE_PARAMETER("text", _T("Texte"), false, "")
        DECLARE_PARAMETER("text", _T("Texte � chercher"), false, "")

    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("StrFindFrom",
                   _T("Chercher dans un texte � partir d'une position"),
                   _T("Chercher dans un texte � partir d'une position ( Retourne la position du r�sultat ou -1 si non trouv� )"),
                   _T("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpStrFindFrom)

        DECLARE_PARAMETER("text", _T("Texte"), false, "")
        DECLARE_PARAMETER("text", _T("Texte � chercher"), false, "")
        DECLARE_PARAMETER("expression", _T("Position � partir de laquelle chercher le texte"), false, "")

    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("StrRFindFrom",
                   _T("Chercher dans un texte depuis la fin � partir d'une position"),
                   _T("Chercher dans un texte depuis la fin � partir d'une position ( Retourne la position du r�sultat ou -1 si non trouv� )"),
                   _T("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpStrRFindFrom)

        DECLARE_PARAMETER("text", _T("Texte"), false, "")
        DECLARE_PARAMETER("text", _T("Texte � chercher"), false, "")
        DECLARE_PARAMETER("expression", _T("Position � partir de laquelle chercher le texte"), false, "")

    DECLARE_END_EXPRESSION()
}

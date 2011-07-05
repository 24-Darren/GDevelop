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
                          _("Manipulation de texte"),
                          _("Extension apportant des expressions de manipulation de texte, int�gr�e en standard."),
                          "Compil Games",
                          "Freeware")

    DECLARE_STR_EXPRESSION("SubStr",
                   _("Obtenir une portion de texte depuis un texte"),
                   _("Obtenir une portion de texte depuis un texte"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpSubStr)

        DECLARE_PARAMETER("string", _("Texte"), "",false)
        DECLARE_PARAMETER("expression", _("Position de d�part de la portion ( La premi�re lettre est � la position 0 )"), "",false)
        DECLARE_PARAMETER("expression", _("Longueur de la portion"), "",false)

    DECLARE_END_STR_EXPRESSION()

    DECLARE_STR_EXPRESSION("StrAt",
                   _("Obtenir un caract�re depuis un texte"),
                   _("Obtenir un caract�re depuis un texte"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpStrAt)

        DECLARE_PARAMETER("string", _("Texte"), "",false)
        DECLARE_PARAMETER("expression", _("Position du caract�re � pr�lever ( Premier caract�re : 0 )"), "",false)

    DECLARE_END_STR_EXPRESSION()

    DECLARE_EXPRESSION("StrLength",
                   _("Longueur d'un texte"),
                   _("Longueur d'un texte"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpStrLen)

        DECLARE_PARAMETER("string", _("Texte"), "",false)

    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("StrFind",
                   _("Chercher dans un texte"),
                   _("Chercher dans un texte ( Retourne la position du r�sultat ou -1 si non trouv� )"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpStrFind)

        DECLARE_PARAMETER("string", _("Texte"), "",false)
        DECLARE_PARAMETER("string", _("Texte � chercher"), "",false)

    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("StrRFind",
                   _("Chercher dans un texte depuis la fin"),
                   _("Chercher dans un texte depuis la fin ( Retourne la position du r�sultat ou -1 si non trouv� )"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpStrRFind)

        DECLARE_PARAMETER("string", _("Texte"), "",false)
        DECLARE_PARAMETER("string", _("Texte � chercher"), "",false)

    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("StrFindFrom",
                   _("Chercher dans un texte � partir d'une position"),
                   _("Chercher dans un texte � partir d'une position ( Retourne la position du r�sultat ou -1 si non trouv� )"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpStrFindFrom)

        DECLARE_PARAMETER("string", _("Texte"), "",false)
        DECLARE_PARAMETER("string", _("Texte � chercher"), "",false)
        DECLARE_PARAMETER("expression", _("Position � partir de laquelle chercher le texte"), "",false)

    DECLARE_END_EXPRESSION()

    DECLARE_EXPRESSION("StrRFindFrom",
                   _("Chercher dans un texte depuis la fin � partir d'une position"),
                   _("Chercher dans un texte depuis la fin � partir d'une position ( Retourne la position du r�sultat ou -1 si non trouv� )"),
                   _("Manipulation sur le texte"),
                   "res/conditions/toujours24.png",
                   &ExpStrRFindFrom)

        DECLARE_PARAMETER("string", _("Texte"), "",false)
        DECLARE_PARAMETER("string", _("Texte � chercher"), "",false)
        DECLARE_PARAMETER("expression", _("Position � partir de laquelle chercher le texte"), "",false)

    DECLARE_END_EXPRESSION()
}

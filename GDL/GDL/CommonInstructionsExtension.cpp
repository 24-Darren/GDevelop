/**
 *  Game Develop
 *  2008-2010 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/CommonInstructionsExtension.h"
#include "GDL/CommonInstructions.h"
#include "GDL/CommentEvent.h"
#include "GDL/StandardEvent.h"
#include "GDL/LinkEvent.h"
#include "GDL/WhileEvent.h"
#include "GDL/RepeatEvent.h"
#include "GDL/ForEachEvent.h"
#include "GDL/Event.h"

#include "GDL/ExtensionBase.h"

CommonInstructionsExtension::CommonInstructionsExtension()
{
    DECLARE_THE_EXTENSION("BuiltinCommonInstructions",
                          _("�v�nements standards"),
                          _("Extension apportant des types d'�v�nements de base, int�gr�e en standard."),
                          "Compil Games",
                          "Freeware")

    DECLARE_CONDITION("Or",
                   _("Ou"),
                   _("Renvoie vraie si une seule des sous conditions est vraie"),
                   _("Si une de ces condition est vraie :"),
                   _("Avanc�"),
                   "res/conditions/or24.png",
                   "res/conditions/or.png",
                   &ConditionOr);

        DECLARE_CAN_HAVE_SUB_CONDITION();

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("And",
                   _("Et"),
                   _("Renvoie vraie si toutes les sous conditions sont vraies"),
                   _("Si toutes ces conditions sont vraies :"),
                   _("Avanc�"),
                   "res/conditions/and24.png",
                   "res/conditions/and.png",
                   &ConditionAnd);

        DECLARE_CAN_HAVE_SUB_CONDITION();

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("Not",
                   _("Non"),
                   _("Renvoie l'inverse du r�sultat des sous conditions"),
                   _("Inverser le r�sultat logique de ces conditions :"),
                   _("Avanc�"),
                   "res/conditions/not24.png",
                   "res/conditions/not.png",
                   &ConditionNot);

        DECLARE_CAN_HAVE_SUB_CONDITION();

    DECLARE_END_CONDITION()

    DECLARE_EVENT("Standard",
                  _("�v�nement standard"),
                  "�v�nement standard : Actions qui sont lanc�es si des conditions sont v�rifi�es",
                  "",
                  "res/eventaddicon.png",
                  StandardEvent)

    DECLARE_END_EVENT()

    DECLARE_EVENT("Link",
                  _("Lien"),
                  "Lien vers des �v�nements d'une autre sc�ne",
                  "",
                  "res/lienaddicon.png",
                  LinkEvent)

    DECLARE_END_EVENT()

    DECLARE_EVENT("Comment",
                  _("Commentaire"),
                  "Un �v�nement permettant d'ajouter un commentaire dans la liste des �v�nements",
                  "",
                  "res/comment.png",
                  CommentEvent)

    DECLARE_END_EVENT()

    DECLARE_EVENT("While",
                  _("Tant que"),
                  "R�p�te des conditions et actions tant que certaines conditions ne sont pas v�rifi�es",
                  "",
                  "res/while.png",
                  WhileEvent)

    DECLARE_END_EVENT()

    DECLARE_EVENT("Repeat",
                  _("R�p�ter"),
                  "R�p�te un certain nombre de fois des conditions et actions",
                  "",
                  "res/repeat.png",
                  RepeatEvent)

    DECLARE_END_EVENT()

    DECLARE_EVENT("ForEach",
                  _("Pour chaque objet"),
                  "R�p�te des conditions et actions en prenant � chaque fois un objet ayant le nom indiqu�",
                  "",
                  "res/foreach.png",
                  ForEachEvent)

    DECLARE_END_EVENT()

}

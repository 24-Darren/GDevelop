#include "GDL/SceneExtension.h"
#include "GDL/aWindow.h"
#include "GDL/actions.h"
#include "GDL/conditions.h"

#include "GDL/ExtensionBase.h"

SceneExtension::SceneExtension()
{
    DECLARE_THE_EXTENSION("BuiltinScene",
                          _("Fonctionnalit�s de manipulation des sc�nes"),
                          _("Extension permettant de manipuler les sc�nes, integr�e en standard"),
                          "Compil Games",
                          "Freeware")

    DECLARE_CONDITION("DepartScene",
                   _("Au lancement de la sc�ne"),
                   _("Est vrai uniquement quand la sc�ne vient juste d'�tre lanc�e."),
                   _("Au lancement de la sc�ne"),
                   _("Sc�ne"),
                   "res/conditions/depart24.png",
                   "res/conditions/depart.png",
                   &CondSceneBegins);

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("Egal",
                   _("Comparaisons d'expressions"),
                   _("Teste les deux expressions"),
                   _("_PARAM0_ _PARAM2_ _PARAM1_"),
                   _("Autre"),
                   "res/conditions/egal24.png",
                   "res/conditions/egal.png",
                   &CondEgal);

        DECLARE_PARAMETER("expression", _("Expression 1"), false, "")
        DECLARE_PARAMETER("expression", _("Expression 2"), false, "")
        DECLARE_PARAMETER("signe", _("Signe du test"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_ACTION("Scene",
                   _("Aller � une sc�ne"),
                   _("Change et d�marre la sc�ne sp�cifi�e."),
                   _("Aller � la sc�ne _PARAM0_"),
                   _("Sc�ne"),
                   "res/actions/goscene24.png",
                   "res/actions/goscene.png",
                   NULL);

        DECLARE_PARAMETER("", _("Nom de la sc�ne"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("Quit",
                   _("Quitter le jeu"),
                   _("Quitte le jeu."),
                   _("Quitter le jeu"),
                   _("Sc�ne"),
                   "res/actions/quit24.png",
                   "res/actions/quit.png",
                   NULL);

    DECLARE_END_ACTION()

    DECLARE_ACTION("SceneBackground",
                   _("Changer la couleur d'arri�re plan"),
                   _("Remplace la couleur d'arri�re plan de la sc�ne par celle indiqu�e."),
                   _("Remplacer la couleur d'arri�re plan par _PARAM0_"),
                   _("Sc�ne"),
                   "res/actions/background24.png",
                   "res/actions/background.png",
                   &ActSceneBackground);

        DECLARE_PARAMETER("color", _("Couleur"), false, "")

    DECLARE_END_ACTION()
}

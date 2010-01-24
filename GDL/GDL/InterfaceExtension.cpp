#include "GDL/InterfaceExtension.h"
#include "GDL/aGUI.h"

InterfaceExtension::InterfaceExtension()
{
    DECLARE_THE_EXTENSION("BuiltinInterface",
                          _("Fonctionnalit�s d'interface"),
                          _("Extension permettant d'afficher des interfaces, integr�e en standard"),
                          "Compil Games",
                          "Freeware")

    DECLARE_ACTION("ShowMsgBox",
                   _("Afficher une boite de message"),
                   _("Affiche une boite de message avec le texte indiqu�, et un bouton ok."),
                   _("Afficher le message \"_PARAM0_\" avec le titre \"_PARAM1_\""),
                   _("Interfaces"),
                   "res/actions/msgbox24.png",
                   "res/actions/msgbox.png",
                   &ActShowMsgBox);

        DECLARE_PARAMETER("texte", _("Message"), false, "")
        DECLARE_PARAMETER("texte", _("Titre"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("ShowOpenFile",
                   _("Afficher une fen�tre d'ouverture de fichier"),
                   _("Affiche une fen�tre permettant de choisir un fichier.\nLe nom et r�pertoire du fichier est enregistr� dans la variable de la sc�ne indiqu�e."),
                   _("Ouvrir une fen�tre de choix de fichier, et enregistrer le r�sultat dans _PARAM0_"),
                   _("Interfaces"),
                   "res/actions/openfile24.png",
                   "res/actions/openfile.png",
                   &ActShowOpenFile);

        DECLARE_PARAMETER("scenevar", _("Variable de la sc�ne o� enregistrer le r�sultat"), false, "")
        DECLARE_PARAMETER("texte", _("Titre"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("ShowTextInput",
                   _("Afficher une fen�tre d'entr�e de texte"),
                   _("Affiche une fen�tre permettant d'entrer un texte.\nLe texte sera enregistr� dans la variable de la sc�ne indiqu�e."),
                   _("Ouvrir une fen�tre d'entr�e de texte, et enregistrer le r�sultat dans _PARAM0_"),
                   _("Interfaces"),
                   "res/actions/textenter24.png",
                   "res/actions/textenter.png",
                   &ActShowTextInput);

        DECLARE_PARAMETER("scenevar", _("Variable de la sc�ne o� enregistrer le r�sultat"), false, "")
        DECLARE_PARAMETER("texte", _("Message"), false, "")
        DECLARE_PARAMETER("texte", _("Titre"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("ShowYesNoMsgBox",
                   _("Afficher une boite de message Oui/Non"),
                   _("Affiche une fen�tre permettant de choisir entre oui ou non.\nLa r�ponse sera enregistr�e dans la variable de la sc�ne indiqu�e."),
                   _("Ouvrir une fen�tre Oui/Non, et enregistrer le r�sultat dans _PARAM0_"),
                   _("Interfaces"),
                   "res/actions/msgbox24.png",
                   "res/actions/msgbox.png",
                   &ActShowYesNoMsgBox);

        DECLARE_PARAMETER("scenevar", _("Variable de la sc�ne o� enregistrer le r�sultat"), false, "")
        DECLARE_PARAMETER("texte", _("Message"), false, "")
        DECLARE_PARAMETER("texte", _("Titre"), false, "")

    DECLARE_END_ACTION()

}

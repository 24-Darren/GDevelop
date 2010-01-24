#include "GDL/NetworkExtension.h"
#include "GDL/aNet.h"

NetworkExtension::NetworkExtension()
{
    DECLARE_THE_EXTENSION("BuiltinNetwork",
                          _("Fonctionnalit�s r�seau"),
                          _("Extension pour utiliser internet, integr�e en standard"),
                          "Compil Games",
                          "Freeware")

    DECLARE_ACTION("EnvoiDataNet",
                   _("Envoyer des donn�es sur internet"),
                   _("Envoie les donn�es sp�cifi� � un site web.\nVous avez besoin de mettre en place une page php sur votre site web permettant de r�colter ces donn�es.\nEntrez un mot de passe, et appliquez le m�me � la configuration de votre page php.\nPour plus d'informations sur la mise en place de votre site, consultez l'aide."),
                   _("Envoyer � _PARAM0_ les donn�es : _PARAM2_, _PARAM3_,_PARAM4_,_PARAM5_,_PARAM6_,_PARAM7_"),
                   _("R�seau"),
                   "res/actions/net24.png",
                   "res/actions/net.png",
                   &ActEnvoiDataNet);

        DECLARE_PARAMETER("", _("Adresse de la page .php"), false, "")
        DECLARE_PARAMETER("password", _("Mot de passe de s�curit�"), false, "")
        DECLARE_PARAMETER("texte", _("Donn�e 1"), false, "")
        DECLARE_PARAMETER_OPTIONAL("texte", _("Donn�e 2"), false, "")
        DECLARE_PARAMETER_OPTIONAL("texte", _("Donn�e 3"), false, "")
        DECLARE_PARAMETER_OPTIONAL("texte", _("Donn�e 4"), false, "")
        DECLARE_PARAMETER_OPTIONAL("texte", _("Donn�e 5"), false, "")
        DECLARE_PARAMETER_OPTIONAL("texte", _("Donn�e 6"), false, "")

    DECLARE_END_ACTION()
}

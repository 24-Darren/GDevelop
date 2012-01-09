/** \file
 *  Game Develop
 *  2008-2012 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/BuiltinExtensions/NetworkExtension.h"

NetworkExtension::NetworkExtension()
{
    DECLARE_THE_EXTENSION("BuiltinNetwork",
                          _("Fonctionnalit�s internet basiques"),
                          _("Extension pour utiliser internet, integr�e en standard"),
                          "Compil Games",
                          "Freeware")
    #if defined(GD_IDE_ONLY)

    DECLARE_ACTION("EnvoiDataNet",
                   _("Envoyer des donn�es sur internet"),
                   _("Envoie les donn�es sp�cifi� � un site web.\nVous avez besoin de mettre en place une page php sur votre site web permettant de r�colter ces donn�es.\nEntrez un mot de passe, et appliquez le m�me � la configuration de votre page php.\nPour plus d'informations sur la mise en place de votre site, consultez l'aide."),
                   _("Envoyer � _PARAM0_ les donn�es : _PARAM2_, _PARAM3_,_PARAM4_,_PARAM5_,_PARAM6_,_PARAM7_"),
                   _("R�seau"),
                   "res/actions/net24.png",
                   "res/actions/net.png");

        instrInfo.AddParameter("string", _("Adresse de la page .php ( N'oubliez pas le protocole http:// )"), "",false);
        instrInfo.AddParameter("password", _("Mot de passe de s�curit�"), "",false);
        instrInfo.AddParameter("string", _("Donn�e 1"), "",false);
        instrInfo.AddParameter("string", _("Donn�e 2"), "",true);
        instrInfo.AddParameter("string", _("Donn�e 3"), "",true);
        instrInfo.AddParameter("string", _("Donn�e 4"), "",true);
        instrInfo.AddParameter("string", _("Donn�e 5"), "",true);
        instrInfo.AddParameter("string", _("Donn�e 6"), "",true);

        instrInfo.cppCallingInformation.SetFunctionName("SendDataToPhpWebPage").SetIncludeFile("GDL/BuiltinExtensions/NetworkTools.h");

    DECLARE_END_ACTION()

    DECLARE_ACTION("DownloadFile",
                   _("T�l�charger un fichier"),
                   _("T�l�charge un fichier depuis un site web."),
                   _("T�l�charger le fichier _PARAM1_ depuis _PARAM0_ sous le nom de _PARAM2_"),
                   _("R�seau"),
                   "res/actions/net24.png",
                   "res/actions/net.png");

        instrInfo.AddParameter("string", _("Site web ( Par exemple : http://www.monsite.com )"), "",false);
        instrInfo.AddParameter("string", _("Chemin du fichier ( Par exemple : /dossier/fichier.txt )"), "",false);
        instrInfo.AddParameter("string", _("Enregistrer le fichier sous le nom"), "",false);

        instrInfo.cppCallingInformation.SetFunctionName("DownloadFile").SetIncludeFile("GDL/BuiltinExtensions/NetworkTools.h");

    DECLARE_END_ACTION()
    #endif
}

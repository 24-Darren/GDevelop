#include "GDL/FileExtension.h"
#include "GDL/cFichier.h"
#include "GDL/aFichier.h"
#include "GDL/XmlFilesHelper.h"

FileExtension::FileExtension()
{
    DECLARE_THE_EXTENSION("BuiltinFile",
                          _("Fichiers"),
                          _("Extension offrant des actions et conditions sur les fichiers, integr�e en standard."),
                          "Compil Games",
                          "Freeware")

    DECLARE_CONDITION("FileExists",
                   _("Le fichier existe"),
                   _("Teste si le fichier existe."),
                   _("Le fichier _PARAM0_ existe"),
                   _("Fichiers"),
                   "res/conditions/fichier24.png",
                   "res/conditions/fichier.png",
                   &CondFileExists);

        DECLARE_PARAMETER("file", _("Nom du fichier"), false, "");

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("GroupExists",
                   _("Existence d'un groupe"),
                   _("Teste si le groupe ( de la forme /Racine/Exemple/1 ) existe dans le fichier.\nAttention ! Les espaces sont interdits dans le nom des groupes."),
                   _("Le groupe _PARAM1_ existe dans le fichier _PARAM0_"),
                   _("Fichiers XML"),
                   "res/conditions/fichier24.png",
                   "res/conditions/fichier.png",
                   &CondGroupExists);

        DECLARE_PARAMETER("file", _("Nom du fichier"), false, "");
        DECLARE_PARAMETER("text", _("Groupe"), false, "");

    DECLARE_END_CONDITION()

    DECLARE_ACTION("LoadFile",
                   _("Charger un fichier en m�moire"),
                   _("Cette action charge le fichier XML en m�moire, pour permettre de lire et �crire dedans.\nIl est possible de lire et d'�crire dans un fichier XML sans passer par cette action, mais les performances seront moindres.\nN'oubliez surtout pas de d�charger le fichier de la m�moire une fois les op�rations termin�es."),
                   _("Charger le fichier XML _PARAM0_ en m�moire"),
                   _("Fichiers XML"),
                   "res/actions/fichier24.png",
                   "res/actions/fichier.png",
                   &ActLoadFile);

        DECLARE_PARAMETER("file", _("Fichier"), false, "");

    DECLARE_END_ACTION()

    DECLARE_ACTION("UnloadFile",
                   _("Fermer un fichier charg� en m�moire"),
                   _("Cette action ferme le fichier XML charg� pr�c�demment en m�moire, en enregistrant les modifications apport�es � celui ci."),
                   _("Fermer le fichier XML _PARAM0_ charg� en m�moire"),
                   _("Fichiers XML"),
                   "res/actions/fichier24.png",
                   "res/actions/fichier.png",
                   &ActUnloadFile);

        DECLARE_PARAMETER("file", _("Fichier"), false, "");

    DECLARE_END_ACTION()

    DECLARE_ACTION("EcrireFichierExp",
                   _("Ecrire une valeur"),
                   _("Cette action �crit le r�sultat de l'expression dans le fichier, dans le groupe indiqu�.\nIndiquez la structure du groupe en s�parant les �l�ments par des /. (Exemple : Racine/MonPersonnage/X)\nAttention ! Les espaces sont interdits dans le nom des groupes."),
                   _("Ecrire _PARAM2_ dans _PARAM1_ du fichier _PARAM0_"),
                   _("Fichiers XML"),
                   "res/actions/fichier24.png",
                   "res/actions/fichier.png",
                   &ActEcrireFichierExp);

        DECLARE_PARAMETER("file", _("Fichier"), false, "");
        DECLARE_PARAMETER("text", _("Groupe"), false, "");
        DECLARE_PARAMETER("expression", _("Expression"), false, "");

    DECLARE_END_ACTION()

    DECLARE_ACTION("EcrireFichierTxt",
                   _("Ecrire un texte"),
                   _("Cette action �crit le texte dans le fichier, dans le groupe indiqu�.\nIndiquez la structure du groupe en s�parant les �l�ments par des /. (Exemple : Racine/MonPersonnage/X)\nAttention ! Les espaces sont interdits dans le nom des groupes."),
                   _("Ecrire _PARAM2_ dans _PARAM1_ du fichier _PARAM0_"),
                   _("Fichiers XML"),
                   "res/actions/fichier24.png",
                   "res/actions/fichier.png",
                   &ActEcrireFichierTxt);

        DECLARE_PARAMETER("file", _("Fichier"), false, "");
        DECLARE_PARAMETER("text", _("Groupe"), false, "");
        DECLARE_PARAMETER("text", _("Texte"), false, "");

    DECLARE_END_ACTION()

    DECLARE_ACTION("LireFichierExp",
                   _("Lire une valeur"),
                   _("Cette action lit la valeur du groupe indiqu� et\nla stocke dans une variable de la sc�ne.\nIndiquez la structure du groupe en s�parant les �l�ments par des /. (Exemple : Racine/Niveau/Actuel)\nAttention ! Les espaces sont interdits dans le nom des groupes."),
                   _("Lire le groupe _PARAM1_ du fichier _PARAM0_ et stocker la valeur dans _PARAM2_"),
                   _("Fichiers XML"),
                   "res/actions/fichier24.png",
                   "res/actions/fichier.png",
                   &ActLireFichierExp);

        DECLARE_PARAMETER("file", _("Fichier"), false, "");
        DECLARE_PARAMETER("text", _("Groupe"), false, "");
        DECLARE_PARAMETER("scenevar", _("Variable de la sc�ne"), false, "");

    DECLARE_END_ACTION()

    DECLARE_ACTION("LireFichierTxt",
                   _("Lire un texte"),
                   _("Cette action lit le texte du groupe indiqu� et\nle stocke dans une variable de la sc�ne.\nIndiquez la structure du groupe en s�parant les �l�ments par des /. (Exemple : Racine/Niveau/Actuel)\nAttention ! Les espaces sont interdits dans le nom des groupes."),
                   _("Lire le groupe _PARAM1_ du fichier _PARAM0_ et stocker le texte dans _PARAM2_"),
                   _("Fichiers XML"),
                   "res/actions/fichier24.png",
                   "res/actions/fichier.png",
                   &ActLireFichierTxt);

        DECLARE_PARAMETER("file", _("Fichier"), false, "");
        DECLARE_PARAMETER("text", _("Groupe"), false, "");
        DECLARE_PARAMETER("scenevar", _("Variable de la sc�ne"), false, "");

    DECLARE_END_ACTION()

    DECLARE_ACTION("DeleteFichier",
                   _("Supprimer un fichier"),
                   _("Supprime le fichier de fa�on d�finitive."),
                   _("Supprimer le fichier _PARAM0_"),
                   _("Fichiers"),
                   "res/actions/delete24.png",
                   "res/actions/delete.png",
                   &ActDeleteFichier);

        DECLARE_PARAMETER("file", _("Nom du fichier"), false, "");

    DECLARE_END_ACTION()

    DECLARE_ACTION("DeleteGroupFichier",
                   _("Supprimer un groupe"),
                   _("Cette action supprime le groupe indiqu� du fichier XML.\nIndiquez la structure du groupe en s�parant les �l�ments par des /. (Exemple : Racine/Niveau/Actuel)"),
                   _("Supprimer le groupe _PARAM1_ du fichier _PARAM0_"),
                   _("Fichiers XML"),
                   "res/actions/delete24.png",
                   "res/actions/delete.png",
                   &ActDeleteGroupFichier);

        DECLARE_PARAMETER("file", _("Nom du fichier"), false, "");
        DECLARE_PARAMETER("text", _("Groupe"), false, "");

    DECLARE_END_ACTION()

    DECLARE_ACTION("LaunchFile",
                   _("Lancer un fichier"),
                   _("Cette action lance le fichier indiqu�."),
                   _("Lancer le fichier _PARAM0_"),
                   _("Fichiers"),
                   "res/actions/launchFile24.png",
                   "res/actions/launchFile.png",
                   &ActLaunchFile);

        DECLARE_PARAMETER("file", _("Nom du fichier"), false, "");

    DECLARE_END_ACTION()

    DECLARE_ACTION("ExecuteCmd",
                   _("Executer une commande"),
                   _("Cette action execute la commande indiqu�."),
                   _("Executer _PARAM0_"),
                   _("Fichiers"),
                   "res/actions/launchFile24.png",
                   "res/actions/launchFile.png",
                   &ActExecuteCmd);

        DECLARE_PARAMETER("text", _("Commande"), false, "");

    DECLARE_END_ACTION()
}

#if defined(GD_IDE_ONLY)
void FileExtension::GetPropertyForDebugger(RuntimeScene & scene, unsigned int propertyNb, std::string & name, std::string & value) const
{
    const std::map < std::string, boost::shared_ptr<XmlFile> > & openedFiles = XmlFilesManager::GetOpenedFilesList();

    unsigned int i = 0;
    std::map < std::string, boost::shared_ptr<XmlFile> >::const_iterator end = openedFiles.end();
    for (std::map < std::string, boost::shared_ptr<XmlFile> >::const_iterator iter = openedFiles.begin();iter != end;++iter)
    {
        if ( propertyNb == i )
        {
            name = _("Fichier ouvert :");
            value = iter->first;

            return;
        }

        ++i;
    }
}

bool FileExtension::ChangeProperty(RuntimeScene & scene, unsigned int propertyNb, std::string newValue)
{
    return false;
}

unsigned int FileExtension::GetNumberOfProperties(RuntimeScene & scene) const
{
    return XmlFilesManager::GetOpenedFilesList().size();
}
#endif

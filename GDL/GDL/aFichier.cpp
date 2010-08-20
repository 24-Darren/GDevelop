/**
 *  Game Develop
 *  2008-2010 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/tinyxml.h"
#include "GDL/RuntimeScene.h"
#include "GDL/ObjectsConcerned.h"
#include <vector>
#include <string>
#include "GDL/CommonTools.h"
#include <stdio.h>

using namespace std;

/**
 * Launch a file
 */
bool ActLaunchFile( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
#ifdef WINDOWS
    //Cr�ation de l'adresse internet � lancer
    string appel = "start \"\" \""+action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned)+"\""; //quotes are important

    system(appel.c_str());
#endif
#ifdef LINUX
    //N�cessite le paquet xdg-utils
    string appel = "xdg-open \""+action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned)+"\"";

    system(appel.c_str());
#endif

    return true;
}

/**
 * Execute a system-specific command
 */
bool ActExecuteCmd( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    system(action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned).c_str());

    return true;
}

/**
 * Delete a file
 */
bool ActDeleteFichier( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    remove(action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned).c_str());

    return true;
}

/**
 * Helper class wrapping a tinyxml document in RAII fashion
 */
class XmlFile
{
    public :
        XmlFile(std::string filename) : doc(filename.c_str()), modified(false) { doc.LoadFile(); };
        ~XmlFile() { if (modified) doc.SaveFile(); }

        void MarkAsModified() { modified = true; }
        TiXmlDocument & GetTinyXmlDocument() { return doc; };
        const TiXmlDocument & GetTinyXmlDocument() const { return doc; };

    private :
        TiXmlDocument doc;
        bool modified;
};

/**
 * Helper class for opening files.
 */
class XmlFilesManager
{
    static std::map<string, boost::shared_ptr<XmlFile> > openedFiles;

    public:

    /**
     * Load a file
     */
    static void LoadFile(std::string filename)
    {
        if ( openedFiles.find(filename) == openedFiles.end() )
            openedFiles[filename] = boost::shared_ptr<XmlFile>(new XmlFile(filename));
    }

    /**
     * Unload a file
     */
    static void UnloadFile(std::string filename)
    {
        if ( openedFiles.find(filename) != openedFiles.end() )
            openedFiles.erase(filename);
    }

    /**
     * Get access to a file. If the file has not been loaded with LoadFile,
     * it will be loaded now.
     */
    static boost::shared_ptr<XmlFile> GetFile(std::string filename, bool isGoingToModifyFile = true)
    {
        boost::shared_ptr<XmlFile> file = openedFiles.find(filename) != openedFiles.end() ? openedFiles[filename] : boost::shared_ptr<XmlFile>(new XmlFile(filename));
        if ( isGoingToModifyFile ) file->MarkAsModified();

        return file;
    }
};
std::map<string, boost::shared_ptr<XmlFile> > XmlFilesManager::openedFiles;

bool ActLoadFile( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    XmlFilesManager::LoadFile(action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned));

    return true;
}

bool ActUnloadFile( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    XmlFilesManager::UnloadFile(action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned));

    return true;
}

////////////////////////////////////////////////////////////
/// Supprimer un groupe d'un fichier
///
/// Type : EcrireFichierExp
/// Param�tre 1 : Nom du fichier
/// Param�tre 2 : Groupe
////////////////////////////////////////////////////////////
bool ActDeleteGroupFichier( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    boost::shared_ptr<XmlFile> file = XmlFilesManager::GetFile(action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned));
    TiXmlHandle hdl( &file->GetTinyXmlDocument() );

    //D�coupage des groupes
    istringstream groupsStr( action.GetParameter(1).GetAsTextExpressionResult(scene, objectsConcerned) );
    string Str;
    vector < string > groups;
    while ( std::getline( groupsStr, Str, '/' ) )
    {
        groups.push_back(Str);
    }
    groups.erase(std::remove_if(groups.begin(), groups.end(), StringEmpty()), groups.end());

    if ( groups.empty() )
    {
        scene.errors.Add("Aucun groupe disponible � supprimer", "", "", -1, 2);
        return false;
    }
    groups.push_back("");

    //Cr�ation si besoin est de la racine
    if ( hdl.FirstChildElement(groups.at(0).c_str()).Element() == NULL )
    {
        scene.errors.Add("Impossible d'acc�der au groupe � supprimer", "", "", -1, 2);
    }


    //A chaque fois, on v�rifie si le groupe voulu existe
    for (unsigned int i =0;i<groups.size();i++)
    {
        if ( hdl.FirstChildElement(groups.at(i).c_str()).Element() == NULL )
            return false;

        //Si on arrive au groupe parent du groupe
        //� supprimer
        if ( i >= (groups.size()-1)-1 )
        {
            hdl.ToNode()->RemoveChild(hdl.FirstChildElement(groups.at(i).c_str()).ToNode());
            return true;
        }

        hdl = hdl.FirstChildElement(groups.at(i).c_str());
    }

    scene.errors.Add("Aucun groupe du nom indiqu� � supprimer", "", "", -1, 2);
    return false;
}

////////////////////////////////////////////////////////////
/// Ecrit une expression dans un fichier
///
/// Type : EcrireFichierExp
/// Param�tre 1 : Nom du fichier
/// Param�tre 2 : Groupe
/// Param�tre 3 : Expression � �crire
////////////////////////////////////////////////////////////
bool ActEcrireFichierExp( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    boost::shared_ptr<XmlFile> file = XmlFilesManager::GetFile(action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned));
    TiXmlHandle hdl( &file->GetTinyXmlDocument() );

    //D�coupage des groupes
    istringstream groupsStr( action.GetParameter(1).GetAsTextExpressionResult(scene, objectsConcerned) );
    string Str;
    vector < string > groups;
    while ( std::getline( groupsStr, Str, '/' ) )
    {
        groups.push_back(Str);
    }
    groups.erase(std::remove_if(groups.begin(), groups.end(), StringEmpty()), groups.end());

    if ( groups.empty() )
    {
        scene.errors.Add("Aucun groupe dans lequel enregistrer la valeur.", "", "", -1, 2);
        return false;
    }

    //Insertion de la d�claration
    TiXmlDeclaration decl( "1.0", "ISO-8859-1", "" );
    if ( hdl.FirstChildElement().Element() != NULL )
    {
        //Il y a d�j� un noeud, on v�rifie que c'est pas une d�claration
        if ( hdl.FirstChild().ToNode()->ToDeclaration() == NULL )
            file->GetTinyXmlDocument().InsertBeforeChild(hdl.FirstChildElement().Element(), decl);
    }
    else
        file->GetTinyXmlDocument().InsertEndChild(decl); //Il n'y a rien, on peut ins�rer notre d�claration

    //Cr�ation si besoin est de la racine
    if ( hdl.FirstChildElement(groups.at(0).c_str()).Element() == NULL )
    {
        TiXmlElement root(groups.at(0).c_str());
        file->GetTinyXmlDocument().InsertEndChild(root);
    }

    //A chaque fois, on v�rifie si le groupe voulu existe, si non on le cr��,
    //et on se d�place dedans.
    for (unsigned int i =0;i<groups.size();i++)
    {
        if ( hdl.FirstChildElement(groups.at(i).c_str()).Element() == NULL )
        {
            TiXmlElement le_nouveau (groups.at(i).c_str());
            hdl.Element()->InsertEndChild(le_nouveau);
        }

        hdl = hdl.FirstChildElement(groups.at(i).c_str());
    }

    //Ecriture dans le groupe
    if ( hdl.Element() != NULL )
    {
        hdl.Element()->SetDoubleAttribute("value", action.GetParameter( 2 ).GetAsMathExpressionResult(scene, objectsConcerned));
    }
    else { scene.errors.Add("Erreur interne : Le groupe finale aurait d� �tre valide.", "", "", -1, 2); }

    return true;
}

////////////////////////////////////////////////////////////
/// Ecrit une expression dans un fichier
///
/// Type : EcrireFichierTxt
/// Param�tre 1 : Nom du fichier
/// Param�tre 2 : Groupe
/// Param�tre 3 : Expression texte � �crire
////////////////////////////////////////////////////////////
bool ActEcrireFichierTxt( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    boost::shared_ptr<XmlFile> file = XmlFilesManager::GetFile(action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned));
    TiXmlHandle hdl( &file->GetTinyXmlDocument() );

    //D�coupage des groupes
    istringstream groupsStr( action.GetParameter(1).GetAsTextExpressionResult(scene, objectsConcerned) );
    string Str;
    vector < string > groups;
    while ( std::getline( groupsStr, Str, '/' ) )
    {
        groups.push_back(Str);
    }
    groups.erase(std::remove_if(groups.begin(), groups.end(), StringEmpty()), groups.end());

    if ( groups.empty() )
    {
        scene.errors.Add("Aucun groupe dans lequel enregistrer la valeur.", "", "", -1, 2);
        return false;
    }

    //Insertion de la d�claration
    TiXmlDeclaration decl( "1.0", "ISO-8859-1", "" );
    if ( hdl.FirstChildElement().Element() != NULL )
    {
        //Il y a d�j� un noeud, on v�rifie que c'est pas une d�claration
        if ( hdl.FirstChild().ToNode()->ToDeclaration() == NULL )
            file->GetTinyXmlDocument().InsertBeforeChild(hdl.FirstChildElement().Element(), decl);
    }
    else
        file->GetTinyXmlDocument().InsertEndChild(decl); //Il n'y a rien, on peut ins�rer notre d�claration

    //Cr�ation si besoin est de la racine
    if ( hdl.FirstChildElement(groups.at(0).c_str()).Element() == NULL )
    {
        TiXmlElement root(groups.at(0).c_str());
        file->GetTinyXmlDocument().InsertEndChild(root);
    }

    //A chaque fois, on v�rifie si le groupe voulu existe, si non on le cr��,
    //et on se d�place dedans.
    for (unsigned int i =0;i<groups.size();i++)
    {
        if ( hdl.FirstChildElement(groups.at(i).c_str()).Element() == NULL )
        {
            TiXmlElement le_nouveau (groups.at(i).c_str());
            hdl.Element()->InsertEndChild(le_nouveau);
        }

        hdl = hdl.FirstChildElement(groups.at(i).c_str());
    }

    //Ecriture dans le groupe
    if ( hdl.Element() != NULL )
    {
        hdl.Element()->SetAttribute("texte", action.GetParameter(2).GetAsTextExpressionResult(scene, objectsConcerned).c_str());
    }
    else { scene.errors.Add("Erreur interne : Le groupe final aurait d� �tre valide.", "", "", -1, 2); }

    return true;
}

////////////////////////////////////////////////////////////
/// Charger une expression depuis un fichier
///
/// Type : LireFichierExp
/// Param�tre 1 : Nom du fichier
/// Param�tre 2 : Groupe
/// Param�tre 3 : Variable ( de la sc�ne ) dans laquelle stocker la valeur
////////////////////////////////////////////////////////////
bool ActLireFichierExp( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    boost::shared_ptr<XmlFile> file = XmlFilesManager::GetFile(action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned));
    TiXmlHandle hdl( &file->GetTinyXmlDocument() );

    //D�coupage des groupes
    istringstream groupsStr( action.GetParameter(1).GetAsTextExpressionResult(scene, objectsConcerned) );
    string Str;
    vector < string > groups;
    while ( std::getline( groupsStr, Str, '/' ) )
    {
        groups.push_back(Str);
    }
    groups.erase(std::remove_if(groups.begin(), groups.end(), StringEmpty()), groups.end());

    //On avance petit � petit dans le fichier
    for (unsigned int i =0;i<groups.size();i++)
    {
        if ( !hdl.FirstChildElement(groups.at(i).c_str()).ToElement())
        {
            scene.errors.Add("Impossible d'acc�der � "+action.GetParameter(1).GetPlainString()+" dans le fichier "+action.GetParameter(0).GetPlainString(), "", "", -1, 2);
            return false;
        }
        hdl = hdl.FirstChildElement(groups.at(i).c_str());
    }

    //On stocke la valeur
    if ( hdl.ToElement()->Attribute("value") == NULL ) return false;
    double value;
    hdl.ToElement()->Attribute("value", &value);

    //Update variable value
    scene.variables.ObtainVariable(action.GetParameter( 2 ).GetPlainString()) = value;

    return true;
}


////////////////////////////////////////////////////////////
/// Charger une expression depuis un fichier
///
/// Type : LireFichierTxt
/// Param�tre 1 : Nom du fichier
/// Param�tre 2 : Groupe
/// Param�tre 3 : Variable ( de la sc�ne ) dans laquelle stocker la valeur
////////////////////////////////////////////////////////////
bool ActLireFichierTxt( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    boost::shared_ptr<XmlFile> file = XmlFilesManager::GetFile(action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned));
    TiXmlHandle hdl( &file->GetTinyXmlDocument() );

    //D�coupage des groupes
    istringstream groupsStr( action.GetParameter(1).GetAsTextExpressionResult(scene, objectsConcerned) );
    string Str;
    vector < string > groups;
    while ( std::getline( groupsStr, Str, '/' ) )
    {
        groups.push_back(Str);
    }
    groups.erase(std::remove_if(groups.begin(), groups.end(), StringEmpty()), groups.end());

    //On avance petit � petit dans le fichier
    for (unsigned int i =0;i<groups.size();i++)
    {
        if ( !hdl.FirstChildElement(groups.at(i).c_str()).ToElement())
        {
            scene.errors.Add("Impossible d'acc�der � "+action.GetParameter(1).GetPlainString()+" dans le fichier "+action.GetParameter(0).GetPlainString(), "", "", -1, 2);
            return false;
        }
        hdl = hdl.FirstChildElement(groups.at(i).c_str());
    }

    //On stocke la valeur
    if ( hdl.ToElement()->Attribute("texte") == NULL ) return false;

    //Update variable texte
    scene.variables.ObtainVariable( action.GetParameter( 2 ).GetPlainString() ) = hdl.ToElement()->Attribute("texte");

    return true;
}

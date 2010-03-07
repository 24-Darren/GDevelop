/**
 *  Game Develop
 *  2008-2010 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/tinyxml.h"
#include "GDL/RuntimeScene.h"
#include "GDL/Access.h"
#include "GDL/ObjectsConcerned.h"
#include <vector>
#include <string>
#include "GDL/algo.h"
#include <stdio.h>

using namespace std;

/**
 * Launch a file
 */
bool ActLaunchFile( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
#ifdef WINDOWS
    //Cr�ation de l'adresse internet � lancer
    string appel = "start \"\" \""+eval.EvalTxt(action.GetParameter(0))+"\""; //quotes are important

    system(appel.c_str());
#endif
#ifdef LINUX
    //N�cessite le paquet xdg-utils
    string appel = "xdg-open \""+eval.EvalTxt(action.GetParameter(0))+"\"";

    system(appel.c_str());
#endif

    return true;
}

/**
 * Execute a command
 */
bool ActExecuteCmd( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    system(eval.EvalTxt(action.GetParameter(0)).c_str());

    return true;
}

////////////////////////////////////////////////////////////
/// Supprimer un fichier
///
/// Type : EcrireFichierExp
/// Param�tre 1 : Nom du fichier
////////////////////////////////////////////////////////////
bool ActDeleteFichier( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    remove(eval.EvalTxt(action.GetParameter(0)).c_str());

    return true;
}

////////////////////////////////////////////////////////////
/// Supprimer un groupe d'un fichier
///
/// Type : EcrireFichierExp
/// Param�tre 1 : Nom du fichier
/// Param�tre 2 : Groupe
////////////////////////////////////////////////////////////
bool ActDeleteGroupFichier( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    TiXmlDocument doc(eval.EvalTxt(action.GetParameter(0)).c_str()); //On tente de charger le fichier, pour garder la structure.
    doc.LoadFile(); //On ne se pr�occupe pas du retour.

    TiXmlHandle hdl( &doc );

    //D�coupage des groupes
    istringstream groupsStr( eval.EvalTxt(action.GetParameter(1)) );
    string Str;
    vector < string > groups;
    while ( std::getline( groupsStr, Str, '/' ) )
    {
        groups.push_back(Str);
    }
    groups.erase(std::remove_if(groups.begin(), groups.end(), StringEmpty()), groups.end());

    if ( groups.empty() )
    {
        scene->errors.Add("Aucun groupe disponible � supprimer", "", "", -1, 2);
        return false;
    }
    groups.push_back("");

    //Cr�ation si besoin est de la racine
    if ( hdl.FirstChildElement(groups.at(0).c_str()).Element() == NULL )
    {
        scene->errors.Add("Impossible d'acc�der au groupe � supprimer", "", "", -1, 2);
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
            if ( !doc.SaveFile( eval.EvalTxt(action.GetParameter(0)).c_str() ) )
            {
                scene->errors.Add("Impossible d'enregistrer dans le fichier "+action.GetParameter(0).GetPlainString(), "", "", -1, 2);
                return false;
            }
            return true;
        }

        hdl = hdl.FirstChildElement(groups.at(i).c_str());
    }

    scene->errors.Add("Aucun groupe du nom indiqu� � supprimer", "", "", -1, 2);
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
bool ActEcrireFichierExp( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    TiXmlDocument doc(eval.EvalTxt(action.GetParameter(0)).c_str()); //On tente de charger le fichier, pour garder la structure.
    doc.LoadFile(); //On ne se pr�occupe pas du retour.

    TiXmlHandle hdl( &doc );

    //D�coupage des groupes
    istringstream groupsStr( eval.EvalTxt(action.GetParameter(1)) );
    string Str;
    vector < string > groups;
    while ( std::getline( groupsStr, Str, '/' ) )
    {
        groups.push_back(Str);
    }
    groups.erase(std::remove_if(groups.begin(), groups.end(), StringEmpty()), groups.end());

    if ( groups.empty() )
    {
        scene->errors.Add("Aucun groupe dans lequel enregistrer la valeur.", "", "", -1, 2);
        return false;
    }

    //Insertion de la d�claration
    TiXmlDeclaration decl( "1.0", "ISO-8859-1", "" );
    if ( hdl.FirstChildElement().Element() != NULL )
    {
        //Il y a d�j� un noeud, on v�rifie que c'est pas une d�claration
        if ( hdl.FirstChild().ToNode()->ToDeclaration() == NULL )
            doc.InsertBeforeChild(hdl.FirstChildElement().Element(), decl);
    }
    else
        doc.InsertEndChild(decl); //Il n'y a rien, on peut ins�rer notre d�claration

    //Cr�ation si besoin est de la racine
    if ( hdl.FirstChildElement(groups.at(0).c_str()).Element() == NULL )
    {
        TiXmlElement root(groups.at(0).c_str());
        doc.InsertEndChild(root);
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
        hdl.Element()->SetDoubleAttribute("value", eval.EvalExp(action.GetParameter(2)));
    }
    else { scene->errors.Add("Erreur interne : Le groupe finale aurait d� �tre valide.", "", "", -1, 2); }

    if ( !doc.SaveFile( eval.EvalTxt(action.GetParameter(0)).c_str() ) )
    {
        scene->errors.Add("Impossible d'enregistrer dans le fichier "+action.GetParameter(0).GetPlainString(), "", "", -1, 2);
        return false;
    }

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
bool ActEcrireFichierTxt( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    TiXmlDocument doc(eval.EvalTxt(action.GetParameter(0)).c_str()); //On tente de charger le fichier, pour garder la structure.
    doc.LoadFile(); //On ne se pr�occupe pas du retour.

    TiXmlHandle hdl( &doc );

    //D�coupage des groupes
    istringstream groupsStr( eval.EvalTxt(action.GetParameter(1)) );
    string Str;
    vector < string > groups;
    while ( std::getline( groupsStr, Str, '/' ) )
    {
        groups.push_back(Str);
    }
    groups.erase(std::remove_if(groups.begin(), groups.end(), StringEmpty()), groups.end());

    if ( groups.empty() )
    {
        scene->errors.Add("Aucun groupe dans lequel enregistrer la valeur.", "", "", -1, 2);
        return false;
    }

    //Insertion de la d�claration
    TiXmlDeclaration decl( "1.0", "ISO-8859-1", "" );
    if ( hdl.FirstChildElement().Element() != NULL )
    {
        //Il y a d�j� un noeud, on v�rifie que c'est pas une d�claration
        if ( hdl.FirstChild().ToNode()->ToDeclaration() == NULL )
            doc.InsertBeforeChild(hdl.FirstChildElement().Element(), decl);
    }
    else
        doc.InsertEndChild(decl); //Il n'y a rien, on peut ins�rer notre d�claration

    //Cr�ation si besoin est de la racine
    if ( hdl.FirstChildElement(groups.at(0).c_str()).Element() == NULL )
    {
        TiXmlElement root(groups.at(0).c_str());
        doc.InsertEndChild(root);
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
        hdl.Element()->SetAttribute("texte", eval.EvalTxt(action.GetParameter(2)).c_str());
    }
    else { scene->errors.Add("Erreur interne : Le groupe final aurait d� �tre valide.", "", "", -1, 2); }

    if ( !doc.SaveFile( eval.EvalTxt(action.GetParameter(0)).c_str() ) )
    {
        scene->errors.Add("Impossible d'enregistrer dans le fichier "+action.GetParameter(0).GetPlainString(), "", "", -1, 2);
        return false;
    }

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
bool ActLireFichierExp( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    TiXmlDocument doc;
    if ( !doc.LoadFile(eval.EvalTxt(action.GetParameter(0)).c_str() ) && doc.ErrorId() == 2) //Tente de charger le fichier en tant que fichier xml pour pr�server sa structure
    {
        scene->errors.Add("Impossible d'ouvrir le fichier "+action.GetParameter(0).GetPlainString()+" : "+string(doc.ErrorDesc()), "", "", -1, 2);
        return false;
    }

    TiXmlHandle hdl( &doc );

    //D�coupage des groupes
    istringstream groupsStr( eval.EvalTxt(action.GetParameter(1)) );
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
            scene->errors.Add("Impossible d'acc�der � "+action.GetParameter(1).GetPlainString()+" dans le fichier "+action.GetParameter(0).GetPlainString(), "", "", -1, 2);
            return false;
        }
        hdl = hdl.FirstChildElement(groups.at(i).c_str());
    }

    //On stocke la valeur
    if ( hdl.ToElement()->Attribute("value") == NULL ) return false;
    double value;
    hdl.ToElement()->Attribute("value", &value);

    //On cherche la variable
    int ID = scene->variables.FindVariable( action.GetParameter( 2 ).GetPlainString() );
    if ( ID == -1 )
    {
        //Si elle n'existe pas, on la cr�er
        scene->variables.variables.push_back( Variable(action.GetParameter( 2 ).GetPlainString()) );
        //On reprend l'identifiant
        ID = scene->variables.variables.size() - 1;
    }

    scene->variables.variables.at( ID ) = value;

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
bool ActLireFichierTxt( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    TiXmlDocument doc;
    if ( !doc.LoadFile(eval.EvalTxt(action.GetParameter(0)).c_str() ) && doc.ErrorId() == 2) //Tente de charger le fichier en tant que fichier xml pour pr�server sa structure
    {
        scene->errors.Add("Impossible d'ouvrir le fichier "+action.GetParameter(0).GetPlainString()+" : "+string(doc.ErrorDesc()), "", "", -1, 2);
        return false;
    }

    TiXmlHandle hdl( &doc );

    //D�coupage des groupes
    istringstream groupsStr( eval.EvalTxt(action.GetParameter(1)) );
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
            scene->errors.Add("Impossible d'acc�der � "+action.GetParameter(1).GetPlainString()+" dans le fichier "+action.GetParameter(0).GetPlainString(), "", "", -1, 2);
            return false;
        }
        hdl = hdl.FirstChildElement(groups.at(i).c_str());
    }

    //On stocke la valeur
    if ( hdl.ToElement()->Attribute("texte") == NULL ) return false;

    string texte = hdl.ToElement()->Attribute("texte");

    //On cherche la variable
    int ID = scene->variables.FindVariable( action.GetParameter( 2 ).GetPlainString() );
    if ( ID == -1 )
    {
        //Si elle n'existe pas, on la cr�er
        scene->variables.variables.push_back( Variable(action.GetParameter( 2 ).GetPlainString()) );
        //On reprend l'identifiant
        ID = scene->variables.variables.size() - 1;
    }

    scene->variables.variables.at( ID ) = texte;

    return true;
}

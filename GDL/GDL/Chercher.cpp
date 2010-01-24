/**
 *  Game Develop
 *      Player
 *
 *  Par Florian "4ian" Rival
 *
 */
/**
 *  Chercher.cpp
 *
 *  Les algorithmes de recherche d'objets.
 *  Consistent souvent � passer en revue les objets
 *  et renvoyer ceux qui ont un nom pr�cis.
 */

#include <SFML/System.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include "GDL/Log.h"
#include "GDL/Object.h"
#include "GDL/Image.h"
#include "GDL/ObjectGroup.h"
#include <algorithm>
#include "GDL/Chercher.h"

using namespace std;

////////////////////////////////////////////////////////////
/// Cherche et renvoie le num�ro de l'image ayant le nom indiqu�
////////////////////////////////////////////////////////////
int ChercherImage(const vector < string > *nomImages, const string nom)
{
    for ( unsigned int i =0;i<nomImages->size();i++)
    {
        if (nomImages->at(i)==nom)
        {
            return i;
        }
    }

    string error = "L'image nomm�e \"";
    string error3 = "\" n'a pas pu �tre trouv�e.";
    EcrireLog("Chercher Image", error+nom+error3);

    return -1;
}

////////////////////////////////////////////////////////////
/// Cherche et renvoie le num�ro de l'image ayant le nom indiqu�
////////////////////////////////////////////////////////////
int ChercherImage(const vector < Image > & images, const string nom)
{
    for ( unsigned int i =0;i<images.size();i++)
    {
        if (images.at(i).nom==nom)
        {
            return i;
        }
    }

    string error = "L'image nomm�e \"";
    string error3 = "\" n'a pas pu �tre trouv�e.";
    EcrireLog("Chercher Image", error+nom+error3);

    return -1;
}
////////////////////////////////////////////////////////////
/// Cherche et renvoie le premier objet ayant le nom sp�cifi�
////////////////////////////////////////////////////////////
int Picker::PickOneObject(const vector < boost::shared_ptr<Object> > *objets, const string nom, const vector < int > *ObjConcern)
{
    //Syntaxe avec l'op�rateur [] peu agr�able mais
    //n�cessaire pour ne pas utiliser at
    const size_t size = ObjConcern->size();
    for ( unsigned int i =0;i<size;++i)
    {
        if ((*objets)[(*ObjConcern)[i]]->GetName() ==nom)
        {
            return (*ObjConcern)[i];
        }
    }

    return -1;
}

////////////////////////////////////////////////////////////
/// Cherche et renvoie le premier objet ayant le nom sp�cifi�
////////////////////////////////////////////////////////////
int Picker::PickOneObject(const vector < boost::shared_ptr<Object> > *objets, const string nom)
{
    //Syntaxe avec l'op�rateur [] peu agr�able mais
    //n�cessaire pour ne pas utiliser at
    const size_t size = objets->size();
    for ( unsigned int i =0;i<size;i++)
    {
        if (objets->at(i)->GetName() == nom)
        {
            return i;
        }
    }

    return -1;
}

////////////////////////////////////////////////////////////
/// Cherche et renvoie une liste d'objet ayant le nom sp�cifi�
////////////////////////////////////////////////////////////
vector < int > Picker::PickObjects(const vector < boost::shared_ptr<Object> > *objets, const string nom)
{
    vector <int> List1;
    const size_t size = objets->size();
    for ( unsigned int objList1 = 0; objList1 < size;objList1++)
    {
        if ( objets->at(objList1)->GetName() == nom )
        {
            List1.push_back(objList1);
        }
    }

    return List1;
}
vector < int > Picker::PickObjects(const vector < boost::shared_ptr<Object> > *objets, const string nom, const vector < int > *ObjConcern)
{
    vector <int> List1;

    const size_t size = ObjConcern->size();
    for ( unsigned int objList1 = 0; objList1 < size;objList1++)
    {
        if ( objets->at(ObjConcern->at(objList1))->GetName() == nom )
        {
            List1.push_back(ObjConcern->at(objList1));
        }
    }

    return List1;
}

////////////////////////////////////////////////////////////
/// Cherche et renvoie une liste d'objet appartenant au grouep sp�cifi�
////////////////////////////////////////////////////////////
vector < int > Picker::PickGroups(const vector < boost::shared_ptr<Object> > *objets, const vector < ObjectGroup > *groups, const string nom)
{
    vector <int> List1;
    const size_t size = groups->size();
    for ( unsigned int i = 0; i < size;++i)
    {
        if ( groups->at(i).GetName() == nom )
        {
            for (unsigned int j = 0;j < groups->at(i).Getobjets().size();++j)
            {
                vector <int> List2 = Picker::PickObjects(objets, groups->at(i).Getobjets().at(j));

                copy(List2.begin(), List2.end(), back_inserter(List1));
            }
        }
    }

    return List1;
}
vector < int > Picker::PickGroups(const vector < boost::shared_ptr<Object> > *objets, const vector < ObjectGroup > *groups, const string nom, const vector < int > *ObjConcern)
{
    vector <int> List1;
    const size_t size = groups->size();
    for ( unsigned int i = 0; i < size;++i)
    {
        if ( groups->at(i).GetName() == nom )
        {
            for (unsigned int j = 0;j < groups->at(i).Getobjets().size();++j)
            {
                vector <int> List2 = Picker::PickObjects(objets, groups->at(i).Getobjets().at(j), ObjConcern);

                copy(List2.begin(), List2.end(), back_inserter(List1));
            }
        }
    }

    return List1;
}


////////////////////////////////////////////////////////////
/// Cherche et renvoie une liste d'objets ayant le nom sp�cifi� en utilisant les groupes d'objets
////////////////////////////////////////////////////////////
vector < int > Picker::Pick(const vector < boost::shared_ptr<Object> > *objets, const vector < ObjectGroup > *groups, const string nom)
{
    vector <int> ObjConcern = Picker::PickObjects(objets, nom);
    vector <int> ObjConcernGroups = Picker::PickGroups(objets, groups, nom);

    copy(ObjConcernGroups.begin(), ObjConcernGroups.end(), back_inserter(ObjConcern));

    return ObjConcern;
}

////////////////////////////////////////////////////////////
/// Cherche et renvoie une liste d'objets ayant le nom sp�cifi� ( dans
/// la liste des objets concern�s )
////////////////////////////////////////////////////////////
vector < int > Picker::Pick(const vector < boost::shared_ptr<Object> > *objets, const vector < ObjectGroup > *groups, const string nom, const vector < int > *ObjConcern)
{
    vector <int> List1 = Picker::PickObjects(objets, nom, ObjConcern);
    vector <int> List2 = Picker::PickGroups(objets, groups, nom, ObjConcern);

    copy(List2.begin(), List2.end(), back_inserter(List1));

    return List1;
}

////////////////////////////////////////////////////////////
/// Cherche et renvoie une liste d'objets ayant le nom sp�cifi� ( dans
/// la liste des objets concern�s )
////////////////////////////////////////////////////////////
vector < int > Picker::PickAndRemove(const vector < boost::shared_ptr<Object> > *objets, const vector < ObjectGroup > *groups, const string nom, vector < int > *ObjConcern)
{
    vector <int> AncienObjConcern = *ObjConcern;
    vector <int> List2 = Picker::Pick(objets, groups, nom, ObjConcern);
    ObjConcern->clear(); //On efface la liste des objets concern�s pour la r�cr�er ensuite

    //On enl�ve de la liste des objets concern�s, les objets concern�s par l'instruction
    //il seront r�int�gr�s par l'instruction si ils remplissent les conditions.
    const size_t size = AncienObjConcern.size();
    for (unsigned int i = 0;i<size;++i)
    {
        //Si l'objet de la liste des objets concern�s n'est PAS concern� pas cette condition...
        if ( find(List2.begin(), List2.end(), AncienObjConcern[i]) == List2.end() )
    	{
    	    //On le laisse
    	    ObjConcern->push_back(AncienObjConcern[i]);
    	}
    }

    return List2;
}

////////////////////////////////////////////////////////////
/// Cherche et renvoie une liste d'objets ayant le nom sp�cifi�
////////////////////////////////////////////////////////////
vector < int > Picker::PickAndRemove(const vector < boost::shared_ptr<Object> > *objets, const vector < ObjectGroup > *groups, const string nom)
{
    vector <int> List1;

    const size_t size = objets->size();
    for ( unsigned int objList1 = 0; objList1 < size;++objList1)
    {
        if ( (*objets)[objList1]->GetName() == nom )
        {
            List1.push_back(objList1); //On a un objet qui a le nom recherch�
        }
    }

    vector <int> List2 = PickGroups(objets, groups, nom);

    copy(List2.begin(), List2.end(), back_inserter(List1));

    return List1;
}

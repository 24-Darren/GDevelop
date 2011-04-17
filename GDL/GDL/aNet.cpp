#include <vector>
#include "GDL/RuntimeScene.h"
#include "GDL/ObjectsConcerned.h"
#include "GDL/md5.h"
#include <SFML/Network.hpp>
#include <fstream>


////////////////////////////////////////////////////////////
/// Envoyer des donn�es ( score, niveau... ) � une page php
/// qui receptionnera ces donn�es.
/// Pour �viter l'envoi de donn�es pirat�es ( hausse de scores... )
/// une somme MD5 sera appliqu�e � chaque donn�es, auquelle on
/// aura rajout� le mot de passe d�finie par le cr�ateur du jeu.
/// La page php devra connaitre aussi ce mot de passe, et l'ajoutera
/// � la donn�e puis fera la somme md5 du tout. Si les sommes se
/// correspondent, alors les donn�es seront accept�es.
///
/// Type : EnvoiDataNet
/// Param�tre 1 : Adresse de la page php
/// Param�tre 2 : Mot de passe de s�curit�
/// Param�tre 3 : Donn�e 1 ( texte )
/// Param�tre 4 : Donn�e 2 ( texte )
/// Param�tre 5 : Donn�e 3 ( texte )
/// Param�tre 6 : Donn�e 4 ( texte )
/// Param�tre 7 : Donn�e 5 ( texte )
/// Param�tre 8 : Donn�e 6 ( texte )
////////////////////////////////////////////////////////////
bool ActEnvoiDataNet( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    string data1 = action.GetParameter(2).GetAsTextExpressionResult(scene, objectsConcerned); //On r�cup�re les donn�es
    string data2 = action.GetParameter(3).GetAsTextExpressionResult(scene, objectsConcerned);
    string data3 = action.GetParameter(4).GetAsTextExpressionResult(scene, objectsConcerned);
    string data4 = action.GetParameter(5).GetAsTextExpressionResult(scene, objectsConcerned);
    string data5 = action.GetParameter(6).GetAsTextExpressionResult(scene, objectsConcerned);
    string data6 = action.GetParameter(7).GetAsTextExpressionResult(scene, objectsConcerned);

    string data1md5 = md5(data1+action.GetParameter(1).GetPlainString()); //On leur ajoute le mot de passe
    string data2md5 = md5(data2+action.GetParameter(1).GetPlainString()); //Et on effectue la somme de contr�le
    string data3md5 = md5(data3+action.GetParameter(1).GetPlainString());
    string data4md5 = md5(data4+action.GetParameter(1).GetPlainString());
    string data5md5 = md5(data5+action.GetParameter(1).GetPlainString());
    string data6md5 = md5(data6+action.GetParameter(1).GetPlainString());

#ifdef WINDOWS
    //Cr�ation de l'adresse internet � lancer
    string call = "start \"\" \""+action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned)+
                   "?data1="+data1+"&check1="+data1md5+
                   "&data2="+data2+"&check2="+data2md5+
                   "&data3="+data3+"&check3="+data3md5+
                   "&data4="+data4+"&check4="+data4md5+
                   "&data5="+data5+"&check5="+data5md5+
                   "&data6="+data6+"&check6="+data6md5+"\"";

    system(call.c_str());
#elif defined(LINUX)
    //N�cessite le paquet xdg-utils
    string call = "xdg-open \""+action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned)+
                   "?data1="+data1+"&check1="+data1md5+
                   "&data2="+data2+"&check2="+data2md5+
                   "&data3="+data3+"&check3="+data3md5+
                   "&data4="+data4+"&check4="+data4md5+
                   "&data5="+data5+"&check5="+data5md5+
                   "&data6="+data6+"&check6="+data6md5+"\"";

    system(call.c_str());
#elif defined(MAC)
    //N�cessite le paquet xdg-utils
    string call = "open \""+action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned)+
                   "?data1="+data1+"&check1="+data1md5+
                   "&data2="+data2+"&check2="+data2md5+
                   "&data3="+data3+"&check3="+data3md5+
                   "&data4="+data4+"&check4="+data4md5+
                   "&data5="+data5+"&check5="+data5md5+
                   "&data6="+data6+"&check6="+data6md5+"\"";

    system(call.c_str());
#endif

    return true;
}

bool ActDownloadFile( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    // Create Http
    sf::Http Http;
    Http.SetHost(action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned));

    // Create request
    sf::Http::Request Request;
    Request.SetMethod(sf::Http::Request::Get);
    Request.SetUri(action.GetParameter(1).GetAsTextExpressionResult(scene, objectsConcerned));

    // Send request & Get response
    sf::Http::Response datas = Http.SendRequest(Request);

    string ofilename = action.GetParameter(2).GetAsTextExpressionResult(scene, objectsConcerned);
    ofstream ofile(ofilename.c_str(), ios_base::binary);
    if ( ofile.is_open() )
    {
        ofile.write(datas.GetBody().c_str(),datas.GetBody().size());
        ofile.close();

        return true;
    }

    cout << "Downloading file : Unable to open output file " << ofilename;
    return false;
}

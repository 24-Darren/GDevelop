/** \file
 *  Game Develop
 *  2008-2012 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/BuiltinExtensions/NetworkTools.h"
#include <fstream>
#include <SFML/Network.hpp>
#include "GDL/RuntimeScene.h"
#include "GDL/Tools/md5.h"

/**
 * Send data to a php web page.
 * To prevent sending hacked data ( like a modified hi score )
 * a md5 checksum is applied on the data+a password defined by the developer
 * Php web page has to known the same password, and will applied md5 ont on the data+the password to
 * be sure data were not modified.
*/
void GD_API SendDataToPhpWebPage(const std::string & webpageurl,
                     const std::string & password,
                     const std::string & data1,
                     const std::string & data2,
                     const std::string & data3,
                     const std::string & data4,
                     const std::string & data5,
                     const std::string & data6)
{
    string data1md5 = md5(data1+password); //On leur ajoute le mot de passe
    string data2md5 = md5(data2+password); //Et on effectue la somme de contr�le
    string data3md5 = md5(data3+password);
    string data4md5 = md5(data4+password);
    string data5md5 = md5(data5+password);
    string data6md5 = md5(data6+password);

#ifdef WINDOWS
    //Cr�ation de l'adresse internet � lancer
    string call = "start \"\" \""+webpageurl+
                   "?data1="+data1+"&check1="+data1md5+
                   "&data2="+data2+"&check2="+data2md5+
                   "&data3="+data3+"&check3="+data3md5+
                   "&data4="+data4+"&check4="+data4md5+
                   "&data5="+data5+"&check5="+data5md5+
                   "&data6="+data6+"&check6="+data6md5+"\"";

    system(call.c_str());
#elif defined(LINUX)
    //N�cessite le paquet xdg-utils
    string call = "xdg-open \""+webpageurl+
                   "?data1="+data1+"&check1="+data1md5+
                   "&data2="+data2+"&check2="+data2md5+
                   "&data3="+data3+"&check3="+data3md5+
                   "&data4="+data4+"&check4="+data4md5+
                   "&data5="+data5+"&check5="+data5md5+
                   "&data6="+data6+"&check6="+data6md5+"\"";

    system(call.c_str());
#elif defined(MAC)
    string call = "open \""+webpageurl+
                   "?data1="+data1+"&check1="+data1md5+
                   "&data2="+data2+"&check2="+data2md5+
                   "&data3="+data3+"&check3="+data3md5+
                   "&data4="+data4+"&check4="+data4md5+
                   "&data5="+data5+"&check5="+data5md5+
                   "&data6="+data6+"&check6="+data6md5+"\"";

    system(call.c_str());
#endif

    return;
}

void GD_API DownloadFile( const std::string & host, const std::string & uri, const std::string & outputfilename )
{
    // Create Http
    sf::Http Http;
    Http.SetHost(host);

    // Create request
    sf::Http::Request Request;
    Request.SetMethod(sf::Http::Request::Get);
    Request.SetUri(uri);

    // Send request & Get response
    sf::Http::Response datas = Http.SendRequest(Request);

    ofstream ofile(outputfilename.c_str(), ios_base::binary);
    if ( ofile.is_open() )
    {
        ofile.write(datas.GetBody().c_str(),datas.GetBody().size());
        ofile.close();

        return;
    }

    cout << "Downloading file : Unable to open output file " << outputfilename;
    return;
}

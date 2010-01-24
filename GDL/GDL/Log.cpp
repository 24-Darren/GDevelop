/**
 *  Game Develop
 *      Player
 *
 *  Par Florian "4ian" Rival
 *
 */
/**
 *  Log.cpp
 *
 *  Gestion des erreurs et du suivi du d�roulement du programme
 */

#include <string>
#include <vector>
#include "GDL/Version.h"

using namespace std;
using namespace AutoVersion;

bool GD_API EcrireLog(string localisation, string texte)
{
    string txt = localisation +" : "+ texte + "\n";

    printf(txt.c_str());

    return true;
}

bool GD_API InitLog()
{
    string nbversion = FULLVERSION_STRING;
    string status = STATUS;
    string version ="Game Develop - "+nbversion+" "+status+"\n";

    string date = DATE;
    string month = MONTH;
    string year = YEAR;
    string fulldate = "Build du "+date+"/"+month+"/"+year+"\n";

    #ifdef LINUX
        string sys = "Systeme cible : Linux\n";
    #endif
    #ifdef WINDOWS
        string sys = "Systeme cible : Windows\n";
    #endif

    printf(version.c_str());
    printf(fulldate.c_str());
    printf(sys.c_str());
    printf("\n");

    return true;
}

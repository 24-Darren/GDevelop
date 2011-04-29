#ifdef DEBUG
#include "nommgr.h"
#endif

#include <wx/log.h>
#include <wx/wx.h>
#include "wx/msgdlg.h"
#include <wx/protocol/http.h>
#include <wx/url.h>
#include <wx/wfstream.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "SFML/Network.hpp"
#include "GDL/tinyxml.h"
#include "GDL/VersionWrapper.h"

#ifdef DEBUG

#endif

#include "CheckMAJ.h"
#include "MAJ.h"

using namespace std;


////////////////////////////////////////////////////////////
/// T�l�chargement de news.txt
///
/// T�l�charge news.txt depuis compilgames.net.
/// Il faut ensuite proc�der � l'analyse de news.txt
////////////////////////////////////////////////////////////
void CheckMAJ::DownloadInformation()
{
    wxHTTP http;

    wxURL *url = new wxURL(_T("http://www.compilgames.net/news.txt"));
    wxInputStream * input;

    input = url->GetInputStream();

    if (input!=NULL) {
        wxFileOutputStream out("news.txt");

        if (out.Ok()) {
            input->Read(out);
        }
        else
        {
            wxLogWarning( _( "Impossible d'�crire le fichier de mise � jour.\nV�rifiez que vous poss�dez les droits requis pour �crire dans le dossier de Game Develop ou d�sactivez la v�rification des mises � jour dans les pr�f�rences.\n\nVous pouvez d�sactiver la v�rification des mises � jour dans les pr�f�rences." ) );
        }

        delete input;
    } else {
        wxLogWarning( _( "Impossible de se connecter au serveur de v�rification des mises � jour de Compil Games.\nV�rifiez :\n-Votre connexion internet\n-Votre pare-feu\n-Si il vous est possible d'acc�der � notre site.\n\nVous pouvez d�sactiver la v�rification des mises � jour dans les pr�f�rences." ) );
        return;
    }

    TiXmlDocument doc( "news.txt" );
    if ( !doc.LoadFile() )
    {
        wxLogWarning( _( "Erreur lors du chargement du fichier de mise � jour.\nV�rifiez :\n-Votre connexion internet\n-Votre pare-feu\n-Si il vous est possible d'acc�der � notre site.\n\nVous pouvez d�sactiver la v�rification des mises � jour dans les pr�f�rences.") );
        return;
    }

    TiXmlHandle hdl( &doc );
    TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();

    //Comparaison de versions
    newMajor = 0;
    elem->QueryIntAttribute( "Major", &newMajor );
    newMinor = 0;
    elem->QueryIntAttribute( "Minor", &newMinor );
    newBuild = 0;
    elem->QueryIntAttribute( "Build", &newBuild );
    newRevision = 0;
    elem->QueryIntAttribute( "Revision", &newRevision );

    if ( newMajor > GDLVersionWrapper::Major() ||
         (newMajor == GDLVersionWrapper::Major() && newMinor > GDLVersionWrapper::Minor()) ||
         (newMajor == GDLVersionWrapper::Major() && newMinor == GDLVersionWrapper::Minor() && newBuild > GDLVersionWrapper::Build()) ||
         (newMajor == GDLVersionWrapper::Major() && newMinor == GDLVersionWrapper::Minor() && newBuild == GDLVersionWrapper::Build() && newRevision > GDLVersionWrapper::Revision() ) )
    {
        newVersionAvailable = true;
    }
    else
        newVersionAvailable = false;

    elem = hdl.FirstChildElement().FirstChildElement("Info").Element();

    if ( elem->Attribute( "Info") != NULL )
         info = elem->Attribute( "Info");

    if ( elem->Attribute( "Lien") != NULL )
         link = elem->Attribute( "Lien");

    return;
}

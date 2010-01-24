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
#include "tinyxml.h"
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
CheckMAJ::CheckMAJ()
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
            wxLogWarning( _( "Impossible d'�crire le fichier de mise � jour.\nV�rifiez que vous poss�dez les droits requis pour �crire dans le dossier de Game Develop ou d�sactivez la v�rification des mises � jour dans les pr�f�rences." ) );

        delete input;
    } else {
        wxLogWarning( _( "Impossible de se connecter au serveur de v�rification des mises � jour de Compil Games.\nV�rifiez :\n-Votre connexion internet\n-Votre pare-feu\n-Si il vous est possible d'acc�der � notre site.\n\nVous pouvez d�sactiver la v�rification des mises � jour dans les pr�f�rences." ) );
    }



}

CheckMAJ::~CheckMAJ()
{
    //dtor
}


////////////////////////////////////////////////////////////
/// Controle de la version
///
/// Utilise le fichier news.txt pour controler la version
////////////////////////////////////////////////////////////
void CheckMAJ::Check()
{
    TiXmlDocument doc( "news.txt" );
    if ( !doc.LoadFile() )
    {
        wxString ErrorDescription = doc.ErrorDesc();
        wxString Error = _( "Erreur lors du chargement du fichier de mise � jour ( " ) + ErrorDescription + _(" )\nV�rifiez :\n-Votre connexion internet\n-Votre pare-feu\n-Si il vous est possible d'acc�der � notre site.\n\nVous pouvez d�sactiver la v�rification des mises � jour dans les pr�f�rences.");
        wxLogWarning( Error );
        return;
    }

    TiXmlHandle hdl( &doc );
    TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();

    //Comparaison de versions
    int Major = 0;
    elem->QueryIntAttribute( "Major", &Major );
    if ( Major > GDLVersionWrapper::Major() )
    {
        if ( wxMessageBox( "Une nouvelle version de Game Develop est disponible !\nVoulez vous ouvrir la fen�tre de mise � jour ?\n\nVous pouvez d�sactiver la v�rification automatique dans les pr�f�rences.", "Nouvelle version", wxYES_NO ) == wxYES )
        {
            MAJ dialog( NULL );
            dialog.ShowModal();
        }

    }
    else
    {
        int Minor = 0;
        elem->QueryIntAttribute( "Minor", &Minor );
        int Build = 0;
        elem->QueryIntAttribute( "Build", &Build );
        int Revision = 0;
        elem->QueryIntAttribute( "Revision", &Revision );

        if ( Build > GDLVersionWrapper::Build() || Minor > GDLVersionWrapper::Minor() || Revision > GDLVersionWrapper::Revision() )
        {
            if ( wxMessageBox( "Une nouvelle version de Game Develop est disponible !\nVoulez vous ouvrir la fen�tre de mise � jour ?\n\nVous pouvez d�sactiver la v�rification automatique dans les pr�f�rences.", "Nouvelle version", wxYES_NO ) == wxYES )
            {
                MAJ dialog( NULL );
                dialog.ShowModal();
            }
        }
    }

    return;
}

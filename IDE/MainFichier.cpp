#include <boost/shared_ptr.hpp>
#include "GDL/OpenSaveGame.h"
#include "GDL/ExtensionsManager.h"
#include "GDL/Game.h"

#include "Game_Develop_EditorMain.h"
#include "Compilation.h"
#include "Portable.h"
#include "Fusion.h"
#include "MessagePlus.h"

////////////////////////////////////////////////////////////
/// Fermeture avec le menu quitter
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnQuit( wxCommandEvent& event )
{
    Close();
}

////////////////////////////////////////////////////////////
/// Cr�er un nouveau jeu vierge
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnMenuNewSelected( wxCommandEvent& event )
{
    if ( wxMessageBox( _( "Attention !\nToute modification non enregistr�e sera perdue.\n\nCr�er un nouveau jeu ?" ), _( "Cr�ation d'un nouveau jeu" ), wxYES_NO, this ) == wxNO )
        return;

    CloseAllSceneEditors();

    Game blankGame;

    game = blankGame;
    wxString GD = _( "Game Develop - Nouveau jeu" );
    SetTitle( GD );

    m_fichierJeu = "";


    //Mise � jour des �diteurs
    ReloadEditors();
    RefreshListScene();

}

/**
 * Adapter for the ribbon
 */
void Game_Develop_EditorFrame::OnRibbonNewClicked(wxRibbonButtonBarEvent& evt)
{
    wxCommandEvent uselessEvent;
    OnMenuNewSelected(uselessEvent);
}

////////////////////////////////////////////////////////////
/// Ouvrir un jeu
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnMenuOpenSelected( wxCommandEvent& event )
{
    //Affichage de la boite de dialogue
    wxFileDialog FileDialog( this, _( "Choisissez le jeu � ouvrir" ), "", "", "*.jgd" );
    FileDialog.ShowModal();

    //A t on  un fichier � ouvrir ?
    if ( FileDialog.GetPath() != "" )
    {
        Open( static_cast<string>( FileDialog.GetPath() ) );

    }

}
/**
 * Adapter for the ribbon
 */
void Game_Develop_EditorFrame::OnRibbonOpenClicked(wxRibbonButtonBarEvent& evt)
{
    wxCommandEvent uselessEvent;
    OnMenuOpenSelected(uselessEvent);
}
void Game_Develop_EditorFrame::OnRibbonOpenDropDownClicked(wxRibbonButtonBarEvent& evt)
{
    evt.PopupMenu(&openContextMenu);
}


////////////////////////////////////////////////////////////
/// Ouverture du fichier, puis ajout � la RecentList et rafraichissement des �diteurs
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::Open( string file )
{
    CloseAllSceneEditors();

    Game blankGame;
    game = blankGame;

    m_fichierJeu = file;

    OpenSaveGame openGame( game );
    openGame.OpenFromFile(m_fichierJeu);

    wxString GD = "Game Develop";
    wxString Fichier = m_fichierJeu;
    SetTitle( GD + " - " + Fichier );

    //Sauvegarde fichiers r�cents
    m_recentlist.SetLastUsed( m_fichierJeu );
    for ( int i = 0;i < 9;i++ )
    {
        wxConfigBase *pConfig = wxConfigBase::Get();
        pConfig->Write( wxString::Format( _T( "/Recent/%d" ), i ), m_recentlist.GetEntry( i ) );
    }

    //Mise � jour des �diteurs
    ReloadEditors();
    RefreshListScene();

    string unknownExtensions = "";
    gdp::ExtensionsManager * extensionsManager = gdp::ExtensionsManager::getInstance();
    for (unsigned int i = 0;i<game.extensionsUsed.size();++i)
    {
    	if ( extensionsManager->GetExtension(game.extensionsUsed[i]) == boost::shared_ptr<ExtensionBase> () )
    	{
    	    unknownExtensions += game.extensionsUsed[i]+"\n";
    	}
    }

    if (unknownExtensions != "")
    {
        wxString errorMsg = _("Une ou plusieurs extensions sont utilis�es par le jeu mais ne sont pas install�es :\n")
                            + unknownExtensions
                            + _("\nCertains objets, actions, conditions ou expressions peuvent manquer ou �tre inconnues.");
        wxLogWarning(errorMsg);
    }
}

////////////////////////////////////////////////////////////
/// Enregistrement du jeu
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnMenuSaveSelected( wxCommandEvent& event )
{
    if ( m_fichierJeu == "" )
    {
        SaveAs();
    }
    else
    {
        OpenSaveGame saveGame( game );
        if ( !saveGame.SaveToFile(m_fichierJeu) )
        {
            wxLogError( "L'enregistrement a �chou�" );
        }

        wxLogStatus(_("Enregistrement du fichier termin�."));
        return;
    }
}
/**
 * Adapter for the ribbon
 */
void Game_Develop_EditorFrame::OnRibbonSaveClicked(wxRibbonButtonBarEvent& evt)
{
    wxCommandEvent uselessEvent;
    OnMenuSaveSelected(uselessEvent);
}
void Game_Develop_EditorFrame::OnRibbonSaveDropDownClicked(wxRibbonButtonBarEvent& evt)
{
    evt.PopupMenu(&saveContextMenu);
}

////////////////////////////////////////////////////////////
/// Enregistrer sous
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnMenuSaveAsSelected( wxCommandEvent& event )
{
    SaveAs();
}

////////////////////////////////////////////////////////////
/// La v�ritable fonction Enregistrer sous
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::SaveAs()
{
    //Affichage de la boite de dialogue
    wxFileDialog FileDialog( this, _( "Choisissez le nom et le r�pertoire du jeu � enregistrer" ), "", "", "*.jgd", wxFD_SAVE );
    FileDialog.ShowModal();

    //A t on  un fichier � enregistrer ?
    if ( FileDialog.GetPath() != "" )
    {
        //oui, donc on l'enregistre
        m_fichierJeu = FileDialog.GetPath();
        OpenSaveGame saveGame( game );

        if ( !saveGame.SaveToFile(m_fichierJeu) )
        {
            wxLogError( "L'enregistrement a �chou�" );
        }

        wxString GD = "Game Develop";
        wxString Fichier = m_fichierJeu;
        SetTitle( GD + " - " + Fichier );

        return;
    }
}


////////////////////////////////////////////////////////////
/// Ouverture de la fen�tre de compilation
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnMenuCompilationSelected( wxCommandEvent& event )
{
    Compilation Dialog( this, &game );
    Dialog.ShowModal();
}

////////////////////////////////////////////////////////////
/// Ouverture de la fen�tre d'enregistrement en version portable
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnMenuPortableSelected( wxCommandEvent& event )
{
    Portable dialog( this, &game );
    dialog.ShowModal();
}

////////////////////////////////////////////////////////////
/// Fichier r�cemment ouverts
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnRecentClicked( wxCommandEvent& event )
{
    wxString Last;

    switch ( event.GetId() )
    {
    case wxID_FILE1:
        Last = m_recentlist.GetEntry( 0 );
        break;
    case wxID_FILE2:
        Last = m_recentlist.GetEntry( 1 );
        break;
    case wxID_FILE3:
        Last = m_recentlist.GetEntry( 2 );
        break;
    case wxID_FILE4:
        Last = m_recentlist.GetEntry( 3 );
        break;
    case wxID_FILE5:
        Last = m_recentlist.GetEntry( 4 );
        break;
    case wxID_FILE6:
        Last = m_recentlist.GetEntry( 5 );
        break;
    case wxID_FILE7:
        Last = m_recentlist.GetEntry( 6 );
        break;
    case wxID_FILE8:
        Last = m_recentlist.GetEntry( 7 );
        break;
    case wxID_FILE9:
        Last = m_recentlist.GetEntry( 8 );
        break;

    default:
        break;
    }

    Open( static_cast<string>( Last ) );

}


////////////////////////////////////////////////////////////
/// Ouvrir la fen�tre de fusion de jeux
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnMenuFusionSelected(wxCommandEvent& event)
{
    Fusion dialog(this, &game);
    dialog.ShowModal();

    ReloadEditors();
    RefreshListScene();
}

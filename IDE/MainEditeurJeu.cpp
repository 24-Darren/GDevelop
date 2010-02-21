#ifdef DEBUG
#define _MEMORY_TRACKER
#include "debugMem.h" //suivi m�moire
#endif

#include "MemTrace.h"
extern MemTrace MemTracer;

#include <algorithm>
#include <wx/dcclient.h>
#include "Game_Develop_EditorMain.h"
#include "EditPropJeu.h"
#include "EditPropScene.h"
#include "GDL/BitmapGUIManager.h"
#include "GDL/Game.h"
#include "GDL/ChercherScene.h"
#include "MessagePlus.h"
#include "Extensions.h"
#include "Clipboard.h"
#include "InitialVariablesDialog.h"

using namespace std;



////////////////////////////////////////////////////////////
/// Mise � jour de la liste des sc�nes
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::RefreshListScene()
{
    SceneTree->DeleteAllItems();
    SceneTree->AddRoot( _( "Toutes les sc�nes du jeu" ), 0 );

    /*if ( gameCurrentlyEdited >= games.size() ) return;

    if ( !games[gameCurrentlyEdited]->m_scenes.empty() )
    {
        StaticText2->SetLabel( "" );
        for ( unsigned int i = 0;i < games[gameCurrentlyEdited]->m_scenes.size();i++ )
        {
            SceneTree->AppendItem( SceneTree->GetRootItem(), games[gameCurrentlyEdited]->m_scenes.at( i ).name, 1 );
        }
    }
    else
    {
        StaticText2->SetLabel( _( "Le jeu ne contient aucune sc�ne,\nil vous faut en ajouter une. Faites un\nclic droit sur \"Toutes les sc�nes\" et\nchoisissez \"Ajouter une sc�ne\"." ) );
    }

    SceneTree->Expand( SceneTree->GetRootItem() );*/
}

////////////////////////////////////////////////////////////
/// Met � jour les controles en fonction du jeu
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::RefreshParaJeu()
{
    /*NomJeuTxt->SetLabel( games[gameCurrentlyEdited]->name );
    AuteurTxt->SetLabel( games[gameCurrentlyEdited]->author );

    TailleJeuTxt->SetLabel( wxString::Format(_("Taille fen�tre du jeu : %i x %i"), games[gameCurrentlyEdited]->windowWidth, games[gameCurrentlyEdited]->windowHeight));*/
}

////////////////////////////////////////////////////////////
/// Affichage du menu contextuel de la liste des sc�nes
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnSceneTreeItemMenu( wxTreeEvent& event )
{
    PopupMenu( &ContextMenu );
}

////////////////////////////////////////////////////////////
/// Selectionner la sc�ne pour l'�diter
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnEditSceneBtClick( wxCommandEvent& event )
{
/*
    if ( games[gameCurrentlyEdited]->m_scenes.empty() )
        return;

    //On cherche l'ID de la sc�ne voulue
    int sceneId = ChercherScene( games[gameCurrentlyEdited]->m_scenes, static_cast<string>( SceneTree->GetItemText( item ) ) );

    if ( sceneId == -1 )
    {
        return;
    }

    //On v�rifie si un �diteur de sc�ne �dite actuellement cette sc�ne
    bool sceneEditorAlreadyOpened = false;
    for (unsigned int j =0;j<editorsNotebook->GetPageCount() ;j++ )
    {
        EditorScene * sceneEditorPtr = dynamic_cast<EditorScene*>(editorsNotebook->GetPage(j));

        if ( sceneEditorPtr != NULL && sceneEditorPtr->scene->name == games[gameCurrentlyEdited]->m_scenes.at(sceneId).name )
        {
            //Si oui, on l'ouvre
            editorsNotebook->SetSelection(j);
            sceneEditorAlreadyOpened = true;
        }
    }

    //Sinon, on en ouvre un autre
    if ( !sceneEditorAlreadyOpened )
    {
        //Class to transmit informations between editors and main editor
        MainEditorCommand mainEditorCommand(games[gameCurrentlyEdited]->nr, sceneId);
        mainEditorCommand.SetRibbon(m_ribbon); //Need link to the ribbon
        mainEditorCommand.SetRibbonSceneEditorButtonBar(ribbonSceneEditorButtonBar); //Need link to the scene editor wxRibbonButtonBar
        mainEditorCommand.SetMainEditor(this);

        EditorScene * editorScene = new EditorScene( editorsNotebook,
                                                    *games[gameCurrentlyEdited],
                                                    &games[gameCurrentlyEdited]->m_scenes.at(sceneId),
                                                    mainEditorCommand);

        BitmapGUIManager * bitmapGUIManager = BitmapGUIManager::getInstance();

        editorsNotebook->AddPage(editorScene, games[gameCurrentlyEdited]->m_scenes.at(sceneId).name, true, bitmapGUIManager->scene);
        editorsNotebook->SetSelection(editorsNotebook->GetPageCount()-1);
    }*/

}


void Game_Develop_EditorFrame::OnSceneTreeItemActivated(wxTreeEvent& event)
{
    item = event.GetItem();
    wxCommandEvent uselessEvent;
    OnEditSceneBtClick(uselessEvent);
}

////////////////////////////////////////////////////////////
/// Affiche puis rafraichit les controles en fonction des param�tres du jeu
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnModParaBtClick( wxCommandEvent& event )
{
    /*EditPropJeu Dialog( this, games[gameCurrentlyEdited].get() );
    Dialog.ShowModal();

    MessagePlus Confirm( this, _( "Voulez vous mettre � jour les �diteurs de sc�nes\navec la taille de la fen�tre de jeu ?" ), 0, "/Auto/TailleEditeurScene" );
    if ( Confirm.Check() != wxID_NO && ( Confirm.Check() == wxID_YES || Confirm.ShowModal() == wxID_YES ) )
    {
        //Redimensionnement des �diteurs de sc�ne
        for (unsigned int j =0;j<editorsNotebook->GetPageCount() ;j++ )
        {
            EditorScene * sceneEditorPtr = dynamic_cast<EditorScene*>(editorsNotebook->GetPage(j));

            if ( sceneEditorPtr != NULL )
                sceneEditorPtr->Resize(games[gameCurrentlyEdited]->windowWidth, games[gameCurrentlyEdited]->windowHeight);
        }
    }

    RefreshParaJeu();*/
}

/**
 * Modify initial global variables
 */
void Game_Develop_EditorFrame::OnglobalVarBtClick(wxCommandEvent& event)
{
    /*InitialVariablesDialog dialog(this, games[gameCurrentlyEdited]->variables);
    if ( dialog.ShowModal() == 1 )
    {
        games[gameCurrentlyEdited]->variables = dialog.variables;
        games[gameCurrentlyEdited]->nr.SetAllScenesMustBeReloaded();
    }*/
}



////////////////////////////////////////////////////////////
/// Fonctions de copie/couper/coller des sc�nes
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnMenuCopySceneSelected( wxCommandEvent& event )
{
    //1) On cherche la sc�ne
    /*int IDscene = ChercherScene( games[gameCurrentlyEdited]->m_scenes, static_cast<string>( SceneTree->GetItemText( item ) ) );

    if ( IDscene != -1 )
    {
        Clipboard * clipboard = Clipboard::getInstance();
        clipboard->SetScene(games[gameCurrentlyEdited]->m_scenes.at( IDscene ));
        return;
    }
    else { wxLogStatus( _( "La sc�ne � copier n'a pas pu �tre trouv�e !" ) ); }*/
}

void Game_Develop_EditorFrame::OnMenuCutSceneSelected( wxCommandEvent& event )
{
    //1) On cherche la sc�ne
   /* int IDscene = ChercherScene( games[gameCurrentlyEdited]->m_scenes, static_cast<string>( SceneTree->GetItemText( item ) ) );

    if ( IDscene != -1 )
    {
        Clipboard * clipboard = Clipboard::getInstance();
        clipboard->SetScene(games[gameCurrentlyEdited]->m_scenes.at( IDscene ));

        CloseScene(IDscene);
        games[gameCurrentlyEdited]->m_scenes.erase( games[gameCurrentlyEdited]->m_scenes.begin() + IDscene );
    }
    else { wxLogStatus( _( "La sc�ne � couper n'a pas pu �tre trouv�e !" ) ); }

    UpdateEditorsSceneID();
    RefreshListScene();*/
}

void Game_Develop_EditorFrame::OnMenuPasteSceneSelected( wxCommandEvent& event )
{
    /*cout << "OnMenuPasteSceneSelected";
    Clipboard * clipboard = Clipboard::getInstance();
    if ( !clipboard->HasScene() )
    {
        wxLogMessage(_("Aucune sc�ne � coller."));
        return;
    }

    int IDscene = ChercherScene( games[gameCurrentlyEdited]->m_scenes, static_cast<string>( SceneTree->GetItemText( item ) ) );
    if ( IDscene == -1 )
    {
        wxLogMessage(_("Sc�ne introuvable."));
        return;
    }

    wxString name =  wxString::Format(_("Copie de %s"), clipboard->GetScene().name);
    unsigned int i = 0;
    bool ok = false;

    //Tant qu'une sc�ne avec le m�me nom existe, on ajoute un chiffre
    while ( !ok )
    {
        ok = true;
        //On v�rifie le nom de chaque sc�ne
        for ( unsigned int j = 0;j < games[gameCurrentlyEdited]->m_scenes.size();j++ )
        {
            if ( games[gameCurrentlyEdited]->m_scenes.at( j ).name == name )
            {
                i++;
                name =  wxString::Format(_("Copie de %s (%i)"), clipboard->GetScene().name, i);
                ok = false;
            }
        }
    }

    //On donne un nom � l'objet
    Scene scenePasted = clipboard->GetScene();
    scenePasted.name = static_cast<string>(name);

    games[gameCurrentlyEdited]->m_scenes.insert( games[gameCurrentlyEdited]->m_scenes.begin() + IDscene, scenePasted );
    cout << "UpdateEditorsSceneID";
    UpdateEditorsSceneID();
    cout << "UpdateEditorsSceneIDEND";
    RefreshListScene();
    cout << "OnMenuPasteSceneSelected END";*/
}

////////////////////////////////////////////////////////////
/// Changement de sc�nes s�lectionn�e
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnSceneTreeSelectionChanged( wxTreeEvent& event )
{
    item = event.GetItem();
}

////////////////////////////////////////////////////////////
/// Ajout d'une sc�ne
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnAddScene( wxCommandEvent& event )
{
    //La sc�ne � ajouter
    /*Scene NewScene;

    //Le treeCtrl
    wxTreeItemId rootId = SceneTree->GetRootItem();

    wxString Name =  _( "Nouvelle sc�ne" );
    int i = 0;
    bool ok = false;


    //Tant qu'une sc�ne avec le m�me nom existe, on ajoute un chiffre
    while ( !ok )
    {
        i++;
        Name =  _( "Nouvelle sc�ne " );
        wxString Num = st( i );

        Name += Num;

        ok = true;
        //On v�rifie le nom de chaque sc�ne
        for ( unsigned int j = 0;j < games[gameCurrentlyEdited]->m_scenes.size();j++ )
        {
            if ( games[gameCurrentlyEdited]->m_scenes.at( j ).name == Name )
            {
                ok = false;
            }
        }

    }

    //On donne un nom � la sc�ne
    NewScene.name = ( string ) Name;

    //On l'ajoute
    games[gameCurrentlyEdited]->m_scenes.push_back( NewScene );
    SceneTree->AppendItem( rootId, Name, 1 );

    StaticText2->SetLabel( "" );
    UpdateEditorsSceneID();*/
}

////////////////////////////////////////////////////////////
/// Suppression de la sc�ne s�lectionn�e
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnDelScene( wxCommandEvent& event )
{
    /*wxTreeItemId ItemNul = NULL;
    if ( item != ItemNul && item != SceneTree->GetRootItem() )
    {
        int i = ChercherScene( games[gameCurrentlyEdited]->m_scenes, ( string ) SceneTree->GetItemText( item ) );
        if ( i != -1 )
        {
            CloseScene(i);
            games[gameCurrentlyEdited]->m_scenes.erase( games[gameCurrentlyEdited]->m_scenes.begin() + i );
        }

        SceneTree->Delete( item );

        //Reaffichage si besoin du message "d'aucune sc�ne pr�sente".
        if ( games[gameCurrentlyEdited]->m_scenes.empty() )
        {
            StaticText2->SetLabel( _( "Le jeu ne contient aucune sc�ne,\nil vous faut en ajouter une. Faites un\nclic droit sur \"Toutes les sc�nes\" et\nchoisissez \"Ajouter une sc�ne\"." ) );
        }
        UpdateEditorsSceneID();
        return;

    }
    else
    {
        wxLogStatus( _( "Aucun objet s�lectionn�e" ) );
    }*/
}

////////////////////////////////////////////////////////////
/// Modifier le nom d'une sc�ne
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnModNameScene( wxCommandEvent& event )
{
    /*wxTreeItemId ItemNul = NULL;
    if ( item != ItemNul && SceneTree->GetItemText( item ) != _( "Toutes les sc�nes du jeu" ) )
    {
        SceneTree->EditLabel( item );
    }
    else
    {
        wxLogStatus( _( "Aucune sc�ne s�lectionn�e" ) );
    }*/
}

/**
 * Modify the initial variables of a scene
 */
void Game_Develop_EditorFrame::OnmodVarSceneMenuISelected(wxCommandEvent& event)
{
    /*int IDscene = ChercherScene( games[gameCurrentlyEdited]->m_scenes, static_cast<string>( SceneTree->GetItemText( item ) ) );
    if ( IDscene == -1 )
    {
        wxLogMessage(_("Sc�ne introuvable."));
        return;
    }

    InitialVariablesDialog dialog(this, games[gameCurrentlyEdited]->m_scenes[IDscene].variables);
    if ( dialog.ShowModal() == 1 )
    {
        games[gameCurrentlyEdited]->m_scenes[IDscene].variables = dialog.variables;
        games[gameCurrentlyEdited]->nr.SetASceneMustBeReloaded(IDscene);
    }*/
}

////////////////////////////////////////////////////////////
/// D�but de l'�dition du nom d'une sc�ne
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnSceneTreeBeginLabelEdit( wxTreeEvent& event )
{
    /*if ( SceneTree->GetItemText( event.GetItem() ) != _( "Toutes les sc�nes du jeu" ) )
    {
        ancienNom = SceneTree->GetItemText( event.GetItem() );
    }
    else
    {
        SceneTree->EndEditLabel( event.GetItem(), true );
    }*/
}

////////////////////////////////////////////////////////////
/// Fin de l'�dition du nom d'une sc�ne
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnSceneTreeEndLabelEdit( wxTreeEvent& event )
{
    /*if ( !event.IsEditCancelled() )
    {
        //1) On cherche l'ancienne sc�ne
        int IDscene = ChercherScene( games[gameCurrentlyEdited]->m_scenes, ancienNom );

        //2) On v�rifie si aucune autre sc�ne a le m�me nom
        bool nomExist = SceneExist( games[gameCurrentlyEdited]->m_scenes, ( string ) event.GetLabel(), IDscene );;

        if ( nomExist )
        {
            wxLogWarning( _( "Impossible de renommer : une sc�ne porte d�j� ce nom !" ) );
            RefreshListScene(); //Mise � jour
            return;
        }
        if ( IDscene != -1 )
        {
            //On v�rifie si un �diteur de cette sc�ne n'est pas ouvert
            for (unsigned int k =0;k<static_cast<unsigned>(editorsNotebook->GetPageCount()) ;k++ )
            {
                EditorScene * sceneEditorPtr = dynamic_cast<EditorScene*>(editorsNotebook->GetPage(k));

                //Si il s'agit d'un �diteur de sc�ne avec ce nom, on le renomme
                if ( sceneEditorPtr != NULL &&
                     editorsNotebook->GetPageText(k) == games[gameCurrentlyEdited]->m_scenes.at(IDscene).name)
                    editorsNotebook->SetPageText(k, event.GetLabel());
            }
            games[gameCurrentlyEdited]->m_scenes.at( IDscene ).name = event.GetLabel(); //Mise � jour
            SceneTree->SetItemText( event.GetItem(), event.GetLabel() );
            return;
        }
        else { wxLogError( _( "La sc�ne � renommer n'a pas pu �tre trouv�e !" ) ); }
    }*/
}

////////////////////////////////////////////////////////////
/// Edition des propri�t�s
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnMenuEditPropSceneSelected( wxCommandEvent& event )
{
    /*if ( !item.IsOk() || item == SceneTree->GetRootItem() )
        return;

    int IDscene = ChercherScene( games[gameCurrentlyEdited]->m_scenes, static_cast<string>( SceneTree->GetItemText( item ) ) );

    if ( IDscene != -1 )
    {
        EditPropScene Dialog( this, &games[gameCurrentlyEdited]->m_scenes.at( IDscene ) );

        Dialog.ShowModal();

        games[gameCurrentlyEdited]->nr.SetASceneMustBeReloaded(IDscene);
        return;
    }
    else { wxLogStatus( _( "La sc�ne n'a pas pu �tre trouv�e !" ) ); }*/
}

////////////////////////////////////////////////////////////
/// Fermeture d'un �diteur de sc�ne via le num�ro de sc�ne
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::CloseScene( int IDscene )
{
    /*for (unsigned int k =1;k<static_cast<unsigned>(editorsNotebook->GetPageCount()) ;k++ )
    {
        if ( editorsNotebook->GetPageText(k) == games[gameCurrentlyEdited]->m_scenes.at(IDscene).name)
            editorsNotebook->DeletePage(k);
    }*/
}

////////////////////////////////////////////////////////////
/// Mise � jour de l'identifier de sc�nes des �diteurs de sc�nes
/// � partir de leur nom ( si l'ordre de sc�nes a chang� )
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::UpdateEditorsSceneID()
{
    //On repasse tous les �diteurs de sc�nes ouverts
    /*for (unsigned int j =0;j<editorsNotebook->GetPageCount() ;j++ )
    {
        wxLogStatus(_("Mise � jour des sc�nes actuellement ouvertes..."));
        cout << "j" << j;
        EditorScene * sceneEditorPtr = dynamic_cast<EditorScene*>(editorsNotebook->GetPage(j));
        if ( sceneEditorPtr != NULL )
        {
            for (unsigned int k =0;k<games[gameCurrentlyEdited]->m_scenes.size() ;k++ )
            {
                //On v�rifie avec quelle sc�ne ils vont
                if ( editorsNotebook->GetPageText(j) == games[gameCurrentlyEdited]->m_scenes.at(k).name)
                {
                    cout << "majStart";
                    sceneEditorPtr->ChangeScenePtr(&games[gameCurrentlyEdited]->m_scenes.at(k), false);

                    //On met alors � jour le num�ro de la sc�ne
                    cout << "majEnd";
                }
            }
        }
    }
    wxLogStatus(_("Mise � jour termin�e."));*/
}

////////////////////////////////////////////////////////////
/// Modification de la sc�ne actuelle avec le nouvel �diteur
/// choisi, ou disparition de la croix de fermeture si on
/// a choisi l'�diteur du jeu
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnNotebook1PageChanged(wxAuiNotebookEvent& event)
{
    if ( dynamic_cast<EditorScene*>(editorsNotebook->GetPage(editorsNotebook->GetSelection())) == NULL &&
         dynamic_cast<EditorImages*>(editorsNotebook->GetPage(editorsNotebook->GetSelection())) == NULL )
    {
        long style = editorsNotebook->GetWindowStyleFlag();
        style &= ~wxAUI_NB_CLOSE_ON_ACTIVE_TAB;
        editorsNotebook->SetWindowStyleFlag(style);
    }
    else
    {
        long style = editorsNotebook->GetWindowStyleFlag();
        style |= wxAUI_NB_CLOSE_ON_ACTIVE_TAB;
        editorsNotebook->SetWindowStyleFlag(style);
    }
}

////////////////////////////////////////////////////////////
/// Choisir les modules d'extensions � utiliser
////////////////////////////////////////////////////////////
void Game_Develop_EditorFrame::OnextensionsEditBtClick(wxCommandEvent& event)
{
    /*Extensions dialog(this, *games[gameCurrentlyEdited]);
    dialog.ShowModal();*/
}


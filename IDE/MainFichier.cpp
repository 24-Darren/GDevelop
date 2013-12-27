/** \file
 *  Game Develop
 *  2008-2013 Florian Rival (Florian.Rival@gmail.com)
 */

#include <wx/progdlg.h>
#include <wx/richmsgdlg.h>
#include <wx/filedlg.h>
#include <boost/shared_ptr.hpp>
#include <SFML/System.hpp>
#include "GDCore/PlatformDefinition/Project.h"
#include "GDCore/PlatformDefinition/Platform.h"
#include "GDCore/PlatformDefinition/PlatformExtension.h"
#include "GDCore/IDE/ProjectResourcesCopier.h"
#include "GDCore/IDE/ProjectExporter.h"
#include "GDCore/IDE/wxTools/RecursiveMkDir.h"
#include "GDCore/IDE/PlatformManager.h"
#include "GDCore/CommonTools.h"
#include "Dialogs/NewProjectDialog.h"
#include "BuildMessagesPnl.h"
#include "MainFrame.h"
#include "BuildToolsPnl.h"
#include "BuildProgressPnl.h"
#include "Fusion.h"
#include "ProjectManager.h"
#include "StartHerePage.h"
#include "GDCpp/IDE/CodeCompiler.h"

using namespace gd;

/**
 * Request close
 */
void MainFrame::OnQuit( wxCommandEvent& event )
{
    Close();
}

void MainFrame::OnCloseCurrentProjectSelected(wxCommandEvent& event)
{
    wxRibbonButtonBarEvent uselessEvent;
    if ( projectManager ) projectManager->OnRibbonCloseSelected(uselessEvent);
}

void MainFrame::CreateNewProject()
{
    NewProjectDialog dialog(this);
    if ( dialog.ShowModal() == 1 )
    {
        gd::Platform* associatedPlatform = gd::PlatformManager::GetInstance()->GetPlatform(dialog.GetChosenTemplatePlatform());
        if ( associatedPlatform != NULL )
        {
            boost::shared_ptr<gd::Project> newProject(new gd::Project);

            //Be sure that the directory of the target exists
            wxString targetDirectory = wxFileName::FileName(dialog.GetChosenFilename()).GetPath();
            if ( !wxDirExists(targetDirectory) ) gd::RecursiveMkDir::MkDir(targetDirectory);

            if ( !dialog.GetChosenTemplateFile().empty() )
            {
                newProject->SetProjectFile(dialog.GetChosenTemplateFile());
                newProject->LoadFromFile(newProject->GetProjectFile());
                gd::ProjectResourcesCopier::CopyAllResourcesTo(*newProject, gd::ToString(targetDirectory), false);
            }
            else
                newProject->InsertNewLayout(gd::ToString(_("New scene")), 0);

            newProject->SetProjectFile(dialog.GetChosenFilename());
            newProject->AddPlatform(associatedPlatform);
            newProject->SaveToFile(newProject->GetProjectFile());

            games.push_back(newProject);
            SetCurrentGame(games.size()-1);
            UpdateOpenedProjectsLogFile();
            if ( startPage ) startPage->Refresh();

            //Ensure working directory is set to the IDE one.
            wxSetWorkingDirectory(mainFrameWrapper.GetIDEWorkingDirectory());
            if ( newProject->GetLayoutCount() > 0 ) projectManager->EditLayout(*newProject, newProject->GetLayout(0));
        }
        else wxLogError(_("Unable to find the platform associated with the template.\n\nPlease report this error to Game Develop developer."));
    }
    else if ( dialog.UserWantToBrowseExamples() )
    {
        wxCommandEvent uselessEvent;
        OnOpenExampleSelected(uselessEvent);
    }

    //Ensure working directory is set to the IDE one.
    wxSetWorkingDirectory(mainFrameWrapper.GetIDEWorkingDirectory());
}

void MainFrame::OnMenuNewSelected( wxCommandEvent& event )
{
    CreateNewProject();
}
void MainFrame::OnRibbonNewClicked(wxRibbonButtonBarEvent& evt)
{
    CreateNewProject();
}

/**
 * Open a file
 */
void MainFrame::OnMenuOpenSelected( wxCommandEvent& event )
{
    sf::Lock lock(CodeCompiler::openSaveDialogMutex);

    wxString oldWorkingDir = wxGetCwd();
    wxFileDialog openFileDialog( this, _( "Choose the project to open" ), "", "", "\"Game Develop\" Project(*.gdg)|*.gdg|\"Game Develop\" Project Autosave (*.gdg.autosave)|*.gdg.autosave" );
    wxSetWorkingDirectory(oldWorkingDir); //Ensure Windows does not mess up with the working directory.

    if (openFileDialog.ShowModal() != wxID_CANCEL && !openFileDialog.GetPath().empty() )
        Open( gd::ToString(openFileDialog.GetPath()) );
}

/**
 * Open an example file
 */
void MainFrame::OnOpenExampleSelected(wxCommandEvent& event)
{
    sf::Lock lock(CodeCompiler::openSaveDialogMutex);

    #if defined(WINDOWS)
    wxString examplesDir = wxGetCwd()+"\\Examples";
    std::cout << examplesDir;
    #else
    wxString examplesDir = wxGetCwd()+"/Examples/";
    #endif

    wxString oldWorkingDir = wxGetCwd();
    wxFileDialog open( NULL, _( "Open an example" ), examplesDir, "", "\"Game Develop\" Project (*.gdg)|*.gdg" );
    wxSetWorkingDirectory(oldWorkingDir); //Ensure Windows does not mess up with the working directory.

    if ( open.ShowModal() != wxID_CANCEL && !open.GetPath().empty() )
        Open(ToString(open.GetPath()));
}
/**
 * Adapter for the ribbon
 */
void MainFrame::OnRibbonOpenClicked(wxRibbonButtonBarEvent& evt)
{
    wxCommandEvent uselessEvent;
    OnMenuOpenSelected(uselessEvent);
}
void MainFrame::OnRibbonOpenDropDownClicked(wxRibbonButtonBarEvent& evt)
{
    evt.PopupMenu(&openContextMenu);
}

void MainFrame::SetLastUsedFile(wxString file)
{
    if ( file.EndsWith(".autosave") ) return;
    
    m_recentlist.SetLastUsed( file );
    for ( unsigned int i = 0;i < 9;i++ )
        wxConfigBase::Get()->Write( wxString::Format( _T( "/Recent/%d" ), i ), m_recentlist.GetEntry( i ) );
}

/**
 * Open a file
 */
void MainFrame::Open( string file )
{
    sf::Lock lock(CodeCompiler::openSaveDialogMutex);

    boost::shared_ptr<gd::Project> newProject(new gd::Project);
    if ( newProject->LoadFromFile(file) )
    {
        //Ensure working directory is set to the IDE one.
        wxSetWorkingDirectory(mainFrameWrapper.GetIDEWorkingDirectory());

        games.push_back(newProject);

        //Sauvegarde fichiers r�cents
        SetLastUsedFile( file );

        //Mise � jour des �diteurs
        SetCurrentGame(games.size()-1);
        if ( startPage ) startPage->Refresh();

        //Update the file logging the opened project
        UpdateOpenedProjectsLogFile();

        string unknownExtensions = "";
        for (unsigned int i = 0;i<newProject->GetUsedExtensions().size();++i)
        {
            bool extensionFound = false;

            for(unsigned int p = 0;p<newProject->GetUsedPlatforms().size();++p)
            {
                gd::Platform & platform = *newProject->GetUsedPlatforms()[p];
                std::vector < boost::shared_ptr<gd::PlatformExtension> > allExtensions = platform.GetAllPlatformExtensions();
                for (unsigned int e = 0;e<allExtensions.size();++e)
                {
                    if ( allExtensions[e]->GetName() == newProject->GetUsedExtensions()[i])
                    {
                        extensionFound = true;
                        break;
                    }
                }
                if ( extensionFound ) break;
            }

            if ( !extensionFound )
                unknownExtensions += newProject->GetUsedExtensions()[i]+"\n";
        }

        if (unknownExtensions != "")
        {
            wxString errorMsg = _("One or ore extensions are used by the project but are not installed for the platform used by the project :\n")
                                + unknownExtensions
                                + _("\nSome objects, actions, conditions or expressions can be unavailable or not working.");
            wxLogWarning(errorMsg);
        }
    }
    //Ensure working directory is set to the IDE one.
    wxSetWorkingDirectory(mainFrameWrapper.GetIDEWorkingDirectory());
    m_mgr.GetPane("PM").Show();
    m_mgr.Update();
}

void MainFrame::OnMenuSaveSelected( wxCommandEvent& event )
{
    if ( !CurrentGameIsValid() ) return;

    if ( GetCurrentGame()->GetProjectFile().empty() || wxString(GetCurrentGame()->GetProjectFile()).EndsWith(".autosave") )
        SaveAs();
    else
    {
        if ( !GetCurrentGame()->SaveToFile(GetCurrentGame()->GetProjectFile()) )
            wxLogError( _("Save failed!") );
        else
            wxLogStatus(_("Save ended."));

        SetLastUsedFile( GetCurrentGame()->GetProjectFile() );

        return;
    }
}
/**
 * Adapter for the ribbon
 */
void MainFrame::OnRibbonSaveClicked(wxRibbonButtonBarEvent& evt)
{
    wxCommandEvent uselessEvent;
    OnMenuSaveSelected(uselessEvent);
}
void MainFrame::OnRibbonSaveDropDownClicked(wxRibbonButtonBarEvent& evt)
{
    evt.PopupMenu(&saveContextMenu);
}

/**
 * Save all
 */
void MainFrame::OnRibbonSaveAllClicked(wxRibbonButtonBarEvent& evt)
{
    for (unsigned int i = 0;i<games.size();++i)
    {
        if ( games[i]->GetProjectFile().empty() || wxString(games[i]->GetProjectFile()).EndsWith(".autosave") )
        {
            sf::Lock lock(CodeCompiler::openSaveDialogMutex);

            wxFileDialog fileDialog( this, _( "Choose where to save the project" ), "", "", "\"Game Develop\" Project (*.gdg)|*.gdg", wxFD_SAVE );
            fileDialog.ShowModal();

            std::string path = gd::ToString(fileDialog.GetPath());

            #if defined(LINUX) //Extension seems not be added with wxGTK?
            if ( fileDialog.GetFilterIndex() == 0 && !path.empty() )
                path += ".gdg";
            #endif

            //A t on  un fichier � enregistrer ?
            if ( !path.empty() )
            {
                //oui, donc on l'enregistre
                games[i]->SetProjectFile(path);

                if ( !games[i]->SaveToFile(games[i]->GetProjectFile()) ) {wxLogError( _("Save failed!") );}
                SetLastUsedFile( games[i]->GetProjectFile() );

                if ( games[i] == GetCurrentGame() )
                    SetCurrentGame(i);
                UpdateOpenedProjectsLogFile();
            }
        }
        else
        {
            if ( !games[i]->SaveToFile(games[i]->GetProjectFile()) ) {wxLogError( _("Save failed!") );}
        }
    }

    wxLogStatus(_("Saves ended."));
}
void MainFrame::OnMenuSaveAllSelected(wxCommandEvent& event)
{
    wxRibbonButtonBarEvent uselessEvent;
    OnRibbonSaveAllClicked(uselessEvent);
}

void MainFrame::OnMenuSaveAsSelected( wxCommandEvent& event )
{
    SaveAs();
}

void MainFrame::SaveAs()
{
    sf::Lock lock(CodeCompiler::openSaveDialogMutex);

    if ( !CurrentGameIsValid() ) return;

    //Affichage de la boite de dialogue
    wxFileDialog fileDialog( this, _( "Choose where save the project" ), "", "", "\"Game Develop\" Project (*.gdg)|*.gdg", wxFD_SAVE );
    fileDialog.ShowModal();

    std::string file = gd::ToString(fileDialog.GetPath());
    #if defined(LINUX) //Extension seems not be added with wxGTK?
    if ( fileDialog.GetFilterIndex() == 0 && !file.empty() )
        file += ".gdg";
    #endif

    //A t on  un fichier � enregistrer ?
    if ( !file.empty() )
    {
        wxString oldPath = !GetCurrentGame()->GetProjectFile().empty() ? wxFileName::FileName(GetCurrentGame()->GetProjectFile()).GetPath() : "";

        //Warn the user that resources should maybe be also moved.
        bool avertOnSaveCheck;
        wxConfigBase::Get()->Read("/Save/AvertOnSaveAs", &avertOnSaveCheck, true);
        wxString newPath = wxFileName::FileName(file).GetPath();
        if ( avertOnSaveCheck && newPath != oldPath && oldPath != "" )
        {
            wxRichMessageDialog dlg(this, _("Project has been saved in a new folder.\nDo you want to also copy its resources into this new folder?"), _("Saving in a new directory"), wxYES_NO|wxICON_INFORMATION );
            dlg.ShowCheckBox(_("Do not show again"));
            //dlg.ShowDetailedText(_("Since the last versions of Game Develop, resources filenames are relative\nto the project folder, allowing to copy or move a project simply by moving the directory\nof the project, provided that resources are also in this directory."));

            if ( dlg.ShowModal() == wxID_YES )
            {
                wxProgressDialog progressDialog(_("Save progress"), _("Exporting resources..."));
                gd::ProjectResourcesCopier::CopyAllResourcesTo(*GetCurrentGame(), gd::ToString(newPath), true, &progressDialog);
            }

            if ( dlg.IsCheckBoxChecked() )
                wxConfigBase::Get()->Write("/Save/AvertOnSaveAs", "false");
        }

        GetCurrentGame()->SetProjectFile(file);

        if ( !GetCurrentGame()->SaveToFile(GetCurrentGame()->GetProjectFile()) )
        {
            wxLogError( _("The project could not be saved properly!") );
        }

        SetLastUsedFile( GetCurrentGame()->GetProjectFile() );
        SetCurrentGame(projectCurrentlyEdited, false);
        UpdateOpenedProjectsLogFile();

        return;
    }
}

void MainFrame::OnMenuCompilationSelected( wxCommandEvent& event )
{
    if ( !CurrentGameIsValid() ) return;

    long id =event.GetId();
    if ( idToPlatformExportMenuMap.find(id) == idToPlatformExportMenuMap.end() )
        return;

    boost::shared_ptr<gd::ProjectExporter> exporter = idToPlatformExportMenuMap[id]->GetProjectExporter();
    if ( !exporter ) return;

    exporter->ShowProjectExportDialog(*GetCurrentGame());
}

void MainFrame::OnRecentClicked( wxCommandEvent& event )
{
    wxString last;

    switch ( event.GetId() )
    {
    case wxID_FILE1:
        last = m_recentlist.GetEntry( 0 );
        break;
    case wxID_FILE2:
        last = m_recentlist.GetEntry( 1 );
        break;
    case wxID_FILE3:
        last = m_recentlist.GetEntry( 2 );
        break;
    case wxID_FILE4:
        last = m_recentlist.GetEntry( 3 );
        break;
    case wxID_FILE5:
        last = m_recentlist.GetEntry( 4 );
        break;
    case wxID_FILE6:
        last = m_recentlist.GetEntry( 5 );
        break;
    case wxID_FILE7:
        last = m_recentlist.GetEntry( 6 );
        break;
    case wxID_FILE8:
        last = m_recentlist.GetEntry( 7 );
        break;
    case wxID_FILE9:
        last = m_recentlist.GetEntry( 8 );
        break;

    default:
        break;
    }

    Open( gd::ToString(last) );
}

/**
 * Open import file dialog
 */
void MainFrame::OnMenuFusionSelected(wxCommandEvent& event)
{
    if ( !CurrentGameIsValid() ) return;

    Fusion dialog(this, *GetCurrentGame());
    dialog.ShowModal();

    projectManager->Refresh();
    if ( startPage ) startPage->Refresh();
}


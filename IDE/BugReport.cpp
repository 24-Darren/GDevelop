/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

#include "BugReport.h"

//(*InternalHeaders(BugReport)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)
#include <wx/textfile.h>
#include "GDL/VersionWrapper.h"
#include <string>
#include <vector>
#include <iostream>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>

using namespace std;

//(*IdInit(BugReport)
const long BugReport::ID_STATICBITMAP1 = wxNewId();
const long BugReport::ID_STATICTEXT1 = wxNewId();
const long BugReport::ID_PANEL1 = wxNewId();
const long BugReport::ID_STATICLINE1 = wxNewId();
const long BugReport::ID_STATICBITMAP3 = wxNewId();
const long BugReport::ID_STATICTEXT2 = wxNewId();
const long BugReport::ID_BUTTON4 = wxNewId();
const long BugReport::ID_PANEL2 = wxNewId();
const long BugReport::ID_STATICTEXT3 = wxNewId();
const long BugReport::ID_TEXTCTRL1 = wxNewId();
const long BugReport::ID_STATICTEXT6 = wxNewId();
const long BugReport::ID_BUTTON1 = wxNewId();
const long BugReport::ID_BUTTON5 = wxNewId();
const long BugReport::ID_PANEL3 = wxNewId();
const long BugReport::ID_STATICTEXT7 = wxNewId();
const long BugReport::ID_STATICBITMAP2 = wxNewId();
const long BugReport::ID_STATICTEXT5 = wxNewId();
const long BugReport::ID_BUTTON2 = wxNewId();
const long BugReport::ID_BUTTON3 = wxNewId();
const long BugReport::ID_PANEL4 = wxNewId();
const long BugReport::ID_NOTEBOOK1 = wxNewId();
//*)

BEGIN_EVENT_TABLE( BugReport, wxDialog )
    //(*EventTable(BugReport)
    //*)
END_EVENT_TABLE()

BugReport::BugReport( wxWindow* parent )
{
    //(*Initialize(BugReport)
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer7;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer6;
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, wxID_ANY, _("Rapport de bug"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticBitmap1 = new wxStaticBitmap(Panel1, ID_STATICBITMAP1, wxBitmap(wxImage(_T("res/bigbug.png"))), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP1"));
    FlexGridSizer2->Add(StaticBitmap1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Game Develop semble avoir rencontr�\nune erreur lors de sa derni�re utilisation."), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(11,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel1);
    FlexGridSizer2->SetSizeHints(Panel1);
    FlexGridSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    FlexGridSizer1->Add(StaticLine1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    FlexGridSizer3->AddGrowableRow(0);
    FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticBitmap3 = new wxStaticBitmap(Panel2, ID_STATICBITMAP3, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_INFORMATION")),wxART_OTHER), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP3"));
    FlexGridSizer9->Add(StaticBitmap3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel2, ID_STATICTEXT2, _("Il semble que Game Develop se soit ferm� brusquement suite � une\nerreur. Si ceci s\'av�re vrai, nous nous excusons pour le d�rangement\nencouru. Il ne s\'agit pas de votre faute, mais d\'un probl�me interne\nau programme.\nVous pouvez n�anmoins nous aider � corriger le probl�me en\ncompl�tant le rapport d\'erreur."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer9->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Button1 = new wxButton(Panel2, ID_BUTTON4, _("Suivant"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FlexGridSizer3->Add(Button1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_BOTTOM, 5);
    Panel2->SetSizer(FlexGridSizer3);
    FlexGridSizer3->Fit(Panel2);
    FlexGridSizer3->SetSizeHints(Panel2);
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    FlexGridSizer4->AddGrowableRow(3);
    StaticText3 = new wxStaticText(Panel3, ID_STATICTEXT3, _("Afin de nous aider � r�soudre le probl�me, essayez de d�crire comment est survenue\nl\'erreur. Indiquez, dans la mesure du possible :\n-Comment le bug s\'est d�clench� ( clic sur un bouton... )\n-O� s\'est il d�clench� ( �diteur de sc�nes, choix actions... )"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer4->Add(StaticText3, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    UserReportEdit = new wxTextCtrl(Panel3, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(408,71), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer4->Add(UserReportEdit, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer7->AddGrowableCol(1);
    FlexGridSizer7->AddGrowableRow(0);
    StaticText6 = new wxStaticText(Panel3, ID_STATICTEXT6, _("Une fois que vous aurez compl�t� le rapport d\'erreur,\ncliquez sur le bouton  \"Cr�er le rapport\". Envoyez\nensuite le fichier � notre adresse mail.\n\nMerci !"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer7->Add(StaticText6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CreateRapportBt = new wxButton(Panel3, ID_BUTTON1, _("Cr�er le rapport d\'erreur"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer7->Add(CreateRapportBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(FlexGridSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Button2 = new wxButton(Panel3, ID_BUTTON5, _("Suivant"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    FlexGridSizer4->Add(Button2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_BOTTOM, 5);
    Panel3->SetSizer(FlexGridSizer4);
    FlexGridSizer4->Fit(Panel3);
    FlexGridSizer4->SetSizeHints(Panel3);
    Panel4 = new wxPanel(Notebook1, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer5->AddGrowableCol(0);
    FlexGridSizer5->AddGrowableRow(1);
    FlexGridSizer10 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer10->AddGrowableCol(0);
    FlexGridSizer10->AddGrowableRow(0);
    StaticText7 = new wxStaticText(Panel4, ID_STATICTEXT7, _("Les jeux en cours d\'�dition on peut �tre p� etre sauvegard�s, sous le nom de gameDumpX.gdg ( o� X repr�sente un num�ro ).\n\nGame Develop peut les r�ouvrir automatiquement une fois la fen�tre ferm�e."), wxDefaultPosition, wxSize(407,117), 0, _T("ID_STATICTEXT7"));
    FlexGridSizer10->Add(StaticText7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(FlexGridSizer10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer6->AddGrowableCol(1);
    FlexGridSizer6->AddGrowableRow(0);
    StaticBitmap2 = new wxStaticBitmap(Panel4, ID_STATICBITMAP2, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_WARNING")),wxART_OTHER), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP2"));
    FlexGridSizer6->Add(StaticBitmap2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(Panel4, ID_STATICTEXT5, _("V�rifiez bien qu\'il s\'agit du jeu souhait�, et qu\'il soit au complet. \nIl n\'est pas garanti  que le jeu ait �t� enregistr� compl�tement,\net il est possible qu\'il s\'agisse d\'une sauvegarde ayant eu lieu\nlors d\'une ancienne erreur.\n\nSi il s\'agit bien de votre jeu au complet, vous pourrez le\nr�-enregistrer normalement."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    wxFont StaticText5Font(wxDEFAULT,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText5->SetFont(StaticText5Font);
    FlexGridSizer6->Add(StaticText5, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(FlexGridSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer8 = new wxFlexGridSizer(0, 3, 0, 0);
    CloseBt = new wxButton(Panel4, ID_BUTTON2, _("Fermer et ouvrir le(s) jeu(x)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer8->Add(CloseBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CloseNoOpenBt = new wxButton(Panel4, ID_BUTTON3, _("Fermer sans ouvrir le(s) jeu(x)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    FlexGridSizer8->Add(CloseNoOpenBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(FlexGridSizer8, 1, wxALL|wxALIGN_RIGHT|wxALIGN_BOTTOM, 0);
    Panel4->SetSizer(FlexGridSizer5);
    FlexGridSizer5->Fit(Panel4);
    FlexGridSizer5->SetSizeHints(Panel4);
    Notebook1->AddPage(Panel2, _("Explication"), false);
    Notebook1->AddPage(Panel3, _("Rapport d\'erreur"), false);
    Notebook1->AddPage(Panel4, _("Votre jeu"), false);
    FlexGridSizer1->Add(Notebook1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);
    Center();

    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BugReport::OnButton1Click);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BugReport::OnCreateRapportBtClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BugReport::OnButton2Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BugReport::OnCloseBtClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BugReport::OnCloseNoOpenBtClick);
    //*)
}

BugReport::~BugReport()
{
    //(*Destroy(BugReport)
    //*)
}


void BugReport::OnCreateRapportBtClick( wxCommandEvent& event )
{
    //On recherche le rapport d'erreur de Game Develop
    string rapport;
    if ( wxFileExists( "errordata.txt" ) )
    {
        wxFileInputStream input( "errordata.txt" );
        if ( input.Ok() )
        {
            wxTextInputStream text( input );
            while ( !input.Eof() )
            {
                rapport += text.ReadLine()+"\n";
            }
        }
    }
    if ( rapport == "" )
        rapport = "Pas de rapport d'erreur de Game Develop";

    wxTextFile ReportFile( "report.txt" );
    ReportFile.AddLine( "Game Develop - Rapport de bug" );
    ReportFile.AddLine( "Merci d'envoyer ce fichier � CompilGames@gmail.com" );
    ReportFile.AddLine( "Please, send this file to CompilGames@gmail.com" );
    ReportFile.AddLine( "" );

    ReportFile.AddLine( "Donn�es de Game Develop  :" );
    ReportFile.AddLine( "--------------------------" );
    wxString version = GDLVersionWrapper::FullString();
    ReportFile.AddLine( "Version " + version );
    ReportFile.AddLine( "Syst�me d'exploitation : " + wxGetOsDescription() );
    ReportFile.AddLine( "" );
    ReportFile.AddLine( "" );

    ReportFile.AddLine( "Rapport de Game Develop  :" );
    ReportFile.AddLine( "--------------------------" );
    ReportFile.AddLine( rapport );
    ReportFile.AddLine( "" );
    ReportFile.AddLine( "" );

    ReportFile.AddLine( "Rapport de l'utilisateur :\n" );
    ReportFile.AddLine( "--------------------------\n" );
    ReportFile.AddLine( UserReportEdit->GetValue() );
    ReportFile.AddLine( "" );
    ReportFile.AddLine( "" );

    ReportFile.Write();
    ReportFile.Close();

    wxExecute("notepad.exe "+wxGetCwd()+"/report.txt");
}


////////////////////////////////////////////////////////////
/// Fermeture sans ouvrir le jeu
////////////////////////////////////////////////////////////
void BugReport::OnCloseNoOpenBtClick(wxCommandEvent& event)
{
    EndModal(0);
}

void BugReport::OnCloseBtClick(wxCommandEvent& event)
{
    EndModal(1);
}

void BugReport::OnButton1Click(wxCommandEvent& event)
{
    Notebook1->SetSelection(1);
}

void BugReport::OnButton2Click(wxCommandEvent& event)
{
    Notebook1->SetSelection(2);
}

#include "EditorScene.h"

//(*InternalHeaders(EditorScene)
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/aui/aui.h>
#include <wx/toolbar.h>
#include <wx/config.h>
#include <wx/brush.h>
#include <wx/log.h>
#include <wx/dcclient.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/buttonbar.h>
#include <wx/ribbon/toolbar.h>

#include "GDL/Game.h"
#include "GDL/RuntimeGame.h"
#include "Game_Develop_EditorMain.h"
#include "GDL/MainEditorCommand.h"
#include "SceneCanvas.h"
#include "DebuggerGUI.h"
#include "EditorObjets.h"
#include "EditorLayers.h"
#include "InitialPositionBrowserDlg.h"
#include "GDL/ChooseLayer.h"
#include "GDL/ChooseObject.h"
#include "GDL/HelpFileAccess.h"
#include "EditorEvents.h"
#include "GridSetup.h"
#include "GDAuiTabArt.h"

#ifdef __WXGTK__
#include <gtk/gtk.h>
#endif

//(*IdInit(EditorScene)
const long EditorScene::ID_SCROLLBAR2 = wxNewId();
const long EditorScene::ID_SCROLLBAR1 = wxNewId();
const long EditorScene::ID_CUSTOM1 = wxNewId();
const long EditorScene::ID_PANEL4 = wxNewId();
const long EditorScene::ID_PANEL5 = wxNewId();
const long EditorScene::ID_PANEL1 = wxNewId();
const long EditorScene::ID_CUSTOM2 = wxNewId();
const long EditorScene::ID_PANEL6 = wxNewId();
const long EditorScene::ID_AUINOTEBOOK1 = wxNewId();
const long EditorScene::ID_MENUITEM8 = wxNewId();
const long EditorScene::ID_MENUITEM1 = wxNewId();
const long EditorScene::ID_MENUITEM2 = wxNewId();
const long EditorScene::ID_MENUITEM3 = wxNewId();
const long EditorScene::ID_MENUITEM4 = wxNewId();
const long EditorScene::ID_MENUITEM5 = wxNewId();
const long EditorScene::ID_MENUITEM6 = wxNewId();
const long EditorScene::ID_MENUITEM7 = wxNewId();
//*)


BEGIN_EVENT_TABLE(EditorScene,wxPanel)
	//(*EventTable(EditorScene)
	//*)
END_EVENT_TABLE()

EditorScene::EditorScene(wxWindow* parent, RuntimeGame & game_, Scene & scene_, const MainEditorCommand & mainEditorCommand_) :
scene(scene_),
game(game_),
mainEditorCommand(mainEditorCommand_),
externalWindow(this)
{
	//(*Initialize(EditorScene)
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	notebook = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_SPLIT|wxAUI_NB_TAB_MOVE|wxAUI_NB_SCROLL_BUTTONS|wxAUI_NB_BOTTOM|wxNO_BORDER);
	scenePanel = new wxPanel(notebook, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	scenePanel->SetBackgroundColour(wxColour(255,255,255));
	scenePanel->SetToolTip(_("Editer l\'aspect initial de la sc�ne"));
	Core = new wxPanel(scenePanel, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	ScrollBar2 = new wxScrollBar(Core, ID_SCROLLBAR2, wxDefaultPosition, wxDefaultSize, wxSB_VERTICAL, wxDefaultValidator, _T("ID_SCROLLBAR2"));
	ScrollBar2->SetScrollbar(2500, 10, 5000, 10);
	ScrollBar1 = new wxScrollBar(Core, ID_SCROLLBAR1, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL, wxDefaultValidator, _T("ID_SCROLLBAR1"));
	ScrollBar1->SetScrollbar(2500, 10, 5000, 10);
	Panel4 = new wxPanel(Core, ID_PANEL4, wxDefaultPosition, wxSize(1,1), 0, _T("ID_PANEL4"));
	sceneCanvas = new SceneCanvas(Panel4, game, scene, mainEditorCommand, ID_CUSTOM1,wxPoint(0,0),wxSize(800,600), wxWANTS_CHARS | wxBORDER_SIMPLE);
	Panel5 = new wxPanel(notebook, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL6"));
	Panel5->SetBackgroundColour(wxColour(255,255,255));
	Panel5->SetToolTip(_("Editer les �v�nements de la sc�ne."));
	FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	FlexGridSizer3->AddGrowableRow(0);
	eventsEditor = new EditorEvents(Panel5, game, scene, &scene.events, mainEditorCommand);
	FlexGridSizer3->Add(eventsEditor, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Panel5->SetSizer(FlexGridSizer3);
	FlexGridSizer3->Fit(Panel5);
	FlexGridSizer3->SetSizeHints(Panel5);
	notebook->AddPage(scenePanel, _("Sc�ne"));
	notebook->AddPage(Panel5, _("Ev�nements"));
	FlexGridSizer1->Add(notebook, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer1);
	zoom5 = new wxMenuItem((&zoomMenu), ID_MENUITEM8, _("5%"), wxEmptyString, wxITEM_NORMAL);
	zoomMenu.Append(zoom5);
	zoom10 = new wxMenuItem((&zoomMenu), ID_MENUITEM1, _("10%"), wxEmptyString, wxITEM_NORMAL);
	zoomMenu.Append(zoom10);
	zoom25 = new wxMenuItem((&zoomMenu), ID_MENUITEM2, _("25%"), wxEmptyString, wxITEM_NORMAL);
	zoomMenu.Append(zoom25);
	zoom50 = new wxMenuItem((&zoomMenu), ID_MENUITEM3, _("50%"), wxEmptyString, wxITEM_NORMAL);
	zoomMenu.Append(zoom50);
	zoom100 = new wxMenuItem((&zoomMenu), ID_MENUITEM4, _("100%"), wxEmptyString, wxITEM_NORMAL);
	zoomMenu.Append(zoom100);
	zoom150 = new wxMenuItem((&zoomMenu), ID_MENUITEM5, _("150%"), wxEmptyString, wxITEM_NORMAL);
	zoomMenu.Append(zoom150);
	zoom200 = new wxMenuItem((&zoomMenu), ID_MENUITEM6, _("200%"), wxEmptyString, wxITEM_NORMAL);
	zoomMenu.Append(zoom200);
	zoom500 = new wxMenuItem((&zoomMenu), ID_MENUITEM7, _("500%"), wxEmptyString, wxITEM_NORMAL);
	zoomMenu.Append(zoom500);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_SCROLLBAR2,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EditorScene::OnScrollBar2Scroll);
	Connect(ID_SCROLLBAR2,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&EditorScene::OnScrollBar2Scroll);
	Connect(ID_SCROLLBAR2,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EditorScene::OnScrollBar2Scroll);
	Connect(ID_SCROLLBAR1,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EditorScene::OnScrollBar1Scroll);
	Connect(ID_SCROLLBAR1,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&EditorScene::OnScrollBar1Scroll);
	Connect(ID_SCROLLBAR1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EditorScene::OnScrollBar1Scroll);
	sceneCanvas->Connect(wxEVT_SET_FOCUS,(wxObjectEventFunction)&EditorScene::OnsceneCanvasSetFocus,0,this);
	Panel4->Connect(wxEVT_SIZE,(wxObjectEventFunction)&EditorScene::OnPanel4Resize,0,this);
	Core->Connect(wxEVT_SIZE,(wxObjectEventFunction)&EditorScene::OnCoreResize1,0,this);
	scenePanel->Connect(wxEVT_SIZE,(wxObjectEventFunction)&EditorScene::OnscenePanelResize,0,this);
	Connect(ID_AUINOTEBOOK1,wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&EditorScene::OnnotebookPageChanged);
	Connect(ID_MENUITEM8,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorScene::Onzoom5Selected);
	Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorScene::Onzoom10Selected);
	Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorScene::Onzoom25Selected);
	Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorScene::Onzoom50Selected);
	Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorScene::Onzoom100Selected);
	Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorScene::Onzoom150Selected);
	Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorScene::Onzoom200Selected);
	Connect(ID_MENUITEM7,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorScene::Onzoom500Selected);
	//*)

    {
        int position = 1;
        wxConfigBase::Get()->Read("/SceneEditor/SceneEventsTab", &position);
        if (position == 0)
        {
            long style = notebook->GetWindowStyleFlag();
            style |= wxAUI_NB_TOP;
            style &= ~wxAUI_NB_BOTTOM;
            notebook->SetWindowStyleFlag(style);
        }
    }


	//Initialisation des �diteurs
    sceneCanvas->objectsEditor = new EditorObjets(this, game, scene, mainEditorCommand);
    sceneCanvas->layersEditor = new EditorLayers(this, game, scene, &scene.initialLayers, mainEditorCommand);
    sceneCanvas->SetScrollbars(ScrollBar1, ScrollBar2);
    sceneCanvas->debugger = new DebuggerGUI(this, sceneCanvas->scene);
    sceneCanvas->scene.debugger = sceneCanvas->debugger;
    sceneCanvas->initialPositionsBrowser = new InitialPositionBrowserDlg(this, scene.initialObjectsPositions, *sceneCanvas);
    sceneCanvas->m_mgr = &m_mgr;
    sceneCanvas->externalWindow = &externalWindow;
    sceneCanvas->SetInitialPositionBrowser(sceneCanvas->initialPositionsBrowser);

    notebook->SetArtProvider(new GDAuiTabArt);
    notebook->SetPageBitmap(0, wxBitmap( "res/sceneeditor.png", wxBITMAP_TYPE_ANY ) );
    notebook->SetPageBitmap(1, wxBitmap( "res/events16.png", wxBITMAP_TYPE_ANY ) );

    //notify wxAUI which frame to use
    m_mgr.SetManagedWindow( this );
    Game_Develop_EditorFrame::LoadSkin(&m_mgr);

    m_mgr.AddPane( notebook, wxAuiPaneInfo().Name( wxT( "ESCenter" ) ).Center().CloseButton( false ).Caption( _( "Editeur de sc�ne" ) ).MaximizeButton( true ).MinimizeButton( false ).CaptionVisible(false) );
    m_mgr.AddPane( sceneCanvas->objectsEditor, wxAuiPaneInfo().Name( wxT( "EO" ) ).Right().CloseButton( true ).Caption( _( "Editeur d'objets" ) ).MaximizeButton( true ).MinimizeButton( false ).CaptionVisible(true).MinSize(208, 100) );
    m_mgr.AddPane( sceneCanvas->layersEditor, wxAuiPaneInfo().Name( wxT( "EL" ) ).Float().CloseButton( true ).Caption( _( "Editeur de calques" ) ).MaximizeButton( true ).MinimizeButton( false ).CaptionVisible(true).MinSize(200, 100).Show(false) );
    m_mgr.AddPane( sceneCanvas->debugger, wxAuiPaneInfo().Name( wxT( "DBG" ) ).Float().CloseButton( true ).Caption( _( "Debugger" ) ).MaximizeButton( true ).MinimizeButton( false ).CaptionVisible(true).MinSize(200, 100).Show(false) );
    m_mgr.AddPane( sceneCanvas->initialPositionsBrowser, wxAuiPaneInfo().Name( wxT( "IPB" ) ).Float().CloseButton( true ).Caption( _( "Positions initiales des objets" ) ).MaximizeButton( true ).MinimizeButton( false ).CaptionVisible(true).MinSize(200, 100).Show(true) );

    mainEditorCommand.GetRibbon()->SetActivePage(3);
    sceneCanvas->ConnectEvents();

    m_mgr.Update();
    sceneCanvas->Reload();
}



void EditorScene::OnscenePanelResize(wxSizeEvent& event)
{
    //Manual resizing of scene's panel
    Core->SetSize(0, 0, event.GetSize().GetX(), event.GetSize().GetY());

    cout << "ScenePanel" << scenePanel->GetSize().GetWidth() << ";" << scenePanel->GetSize().GetHeight() << endl;
    cout << "Core" << Core->GetSize().GetWidth() << ";" << Core->GetSize().GetHeight() << endl;
    cout << "Panel4" << Panel4->GetSize().GetWidth() << ";" << Panel4->GetSize().GetHeight() << endl;
}

void EditorScene::OnPanel4Resize(wxSizeEvent& event)
{
    sceneCanvas->ChangeSize(event.GetSize().GetX(), event.GetSize().GetY());
    cout << "ScenePanel" << scenePanel->GetSize().GetWidth() << ";" << scenePanel->GetSize().GetHeight() << endl;
    cout << "Core" << Core->GetSize().GetWidth() << ";" << Core->GetSize().GetHeight() << endl;
    cout << "Panel4" << Panel4->GetSize().GetWidth() << ";" << Panel4->GetSize().GetHeight() << endl;
}

void EditorScene::OnCoreResize1(wxSizeEvent& event)
{
    //Manual resizing of scene's sub panel
    Panel4->SetSize(0, 0, event.GetSize().GetX(), event.GetSize().GetY());

    sceneCanvas->ChangeSize(event.GetSize().GetX(), event.GetSize().GetY());
    cout << "ScenePanel" << scenePanel->GetSize().GetWidth() << ";" << scenePanel->GetSize().GetHeight() << endl;
    cout << "Core" << Core->GetSize().GetWidth() << ";" << Core->GetSize().GetHeight() << endl;
    cout << "Panel4" << Panel4->GetSize().GetWidth() << ";" << Panel4->GetSize().GetHeight() << endl;
}

/**
 * Update the size and position of the panel containing the scene, and the scrollbars
 */
/*void EditorScene::UpdateScenePanelSize(int parentPanelWidht, int parentPanelHeight)
{
    if ( sceneCanvas->scene.editing )
    {
        //In edition mode, panel containing the scene must not use scrollbars space.
        Panel4->SetSize(parentPanelWidht-ScrollBar2->GetSize().GetX(), parentPanelHeight-ScrollBar1->GetSize().GetY());

    }
    else
    {

        //In preview mode, panel containing the scene can take all the space
        Panel4->SetSize(parentPanelWidht, parentPanelHeight);
    }
}*/

EditorScene::~EditorScene()
{
	std::cout << "Debug Message : Start destructor of EditorScene" << endl;

	//(*Destroy(EditorScene)
	//*)
	m_mgr.UnInit();
	std::cout << "Debug Message : Start deleting in destructor of EditorScene" << endl;
	if ( sceneCanvas->objectsEditor ) delete sceneCanvas->objectsEditor;
	if ( sceneCanvas->layersEditor ) delete sceneCanvas->layersEditor;
	if ( sceneCanvas->debugger ) delete sceneCanvas->debugger;
	if ( sceneCanvas->initialPositionsBrowser ) delete sceneCanvas->initialPositionsBrowser;
	std::cout << "Debug Message : END deleting in destructor of EditorScene" << endl;
}

/*
void EditorScene::Resize( int width, int height )
{
    if ( sceneCanvas != NULL )
        delete sceneCanvas;

	sceneCanvas = new SceneCanvas(Panel4, game, scene, mainEditorCommand, ID_CUSTOM1,wxPoint(0,0),wxSize(width, height), wxWANTS_CHARS | wxBORDER_SIMPLE);
    sceneCanvas->SetScrollbars(ScrollBar1, ScrollBar2);
    sceneCanvas->Reload();

	Refresh();
	Update();
	Layout();
}*/

////////////////////////////////////////////////////////////
/// Change la vue en fonction de la scrollbar, et agrandit celle ci si besoin.
////////////////////////////////////////////////////////////
void EditorScene::OnScrollBar2Scroll(wxScrollEvent& event)
{
    int position = event.GetPosition();

    int newY = position-(ScrollBar2->GetRange()/2)+(sceneCanvas->GetHeight()/2);
    sceneCanvas->scene.view.SetCenter( sceneCanvas->scene.view.GetCenter().x, newY);

    sceneCanvas->ManualRefresh();
}

////////////////////////////////////////////////////////////
/// Change la vue en fonction de la scrollbar, et agrandit celle ci si besoin.
////////////////////////////////////////////////////////////
void EditorScene::OnScrollBar1Scroll(wxScrollEvent& event)
{
    int position = event.GetPosition();

    int newX = position-(ScrollBar1->GetRange()/2)+(sceneCanvas->GetWidth()/2);
    sceneCanvas->scene.view.SetCenter( newX,  sceneCanvas->scene.view.GetCenter().y);

    sceneCanvas->ManualRefresh();
}
void EditorScene::ForceRefreshRibbonAndConnect()
{
    if ( notebook->GetPageText(notebook->GetSelection()) == _("Sc�ne") )
    {
        sceneCanvas->CreateToolsBar(mainEditorCommand.GetRibbonSceneEditorButtonBar(), sceneCanvas->scene.editing);
        mainEditorCommand.GetRibbon()->SetActivePage(3);
        sceneCanvas->ConnectEvents();
    }
    else if ( notebook->GetPageText(notebook->GetSelection()) == _("Ev�nements") )
    {
        mainEditorCommand.GetRibbon()->SetActivePage(4);
        eventsEditor->ConnectEvents();
    }
}

/**
 * Update ribbon
 */
void EditorScene::OnnotebookPageChanged(wxAuiNotebookEvent& event)
{
    ForceRefreshRibbonAndConnect();
}

void EditorScene::OnsceneCanvasSetFocus(wxFocusEvent& event)
{
    sceneCanvas->CreateToolsBar(mainEditorCommand.GetRibbonSceneEditorButtonBar(), sceneCanvas->scene.editing);
    mainEditorCommand.GetRibbon()->SetActivePage(3);
    sceneCanvas->ConnectEvents();
}


void EditorScene::Onzoom5Selected(wxCommandEvent& event)
{
    sceneCanvas->scene.view.SetSize(sceneCanvas->GetWidth()/0.05f, sceneCanvas->GetHeight()/0.05f);
}

void EditorScene::Onzoom10Selected(wxCommandEvent& event)
{
    sceneCanvas->scene.view.SetSize(sceneCanvas->GetWidth()/0.1f, sceneCanvas->GetHeight()/0.1f);
}

void EditorScene::Onzoom25Selected(wxCommandEvent& event)
{
    sceneCanvas->scene.view.SetSize(sceneCanvas->GetWidth()/0.25f, sceneCanvas->GetHeight()/0.25f);
}

void EditorScene::Onzoom50Selected(wxCommandEvent& event)
{
    sceneCanvas->scene.view.SetSize(sceneCanvas->GetWidth()/0.5f, sceneCanvas->GetHeight()/0.5f);
}

void EditorScene::Onzoom100Selected(wxCommandEvent& event)
{
    sceneCanvas->scene.view.SetSize(sceneCanvas->GetWidth(), sceneCanvas->GetHeight());
}

void EditorScene::Onzoom150Selected(wxCommandEvent& event)
{
    sceneCanvas->scene.view.SetSize(sceneCanvas->GetWidth()/1.5f, sceneCanvas->GetHeight()/1.5f);
}

void EditorScene::Onzoom200Selected(wxCommandEvent& event)
{
    sceneCanvas->scene.view.SetSize(sceneCanvas->GetWidth()/2.f, sceneCanvas->GetHeight()/2.f);
}

void EditorScene::Onzoom500Selected(wxCommandEvent& event)
{
    sceneCanvas->scene.view.SetSize(sceneCanvas->GetWidth()/5.f, sceneCanvas->GetHeight()/5.f);
}


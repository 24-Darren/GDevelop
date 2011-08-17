/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */
#include "EventsEditor.h"

//(*InternalHeaders(EventsEditor)
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)
#include <wx/event.h>
#include <wx/config.h>
#include <iostream>
#include <utility>
#include <algorithm>
#include "GDL/Game.h"
#include "GDL/Scene.h"
#include "GDL/Event.h"
#include "GDL/MainEditorCommand.h"
#include "GDL/EventsEditorItemsAreas.h"
#include "GDL/EventsEditorSelection.h"
#include "GDL/EventsRenderingHelper.h"
#include "GDL/CommonTools.h"
#include "GDL/EventsCodeCompiler.h"
#include "GDL/ExtensionsManager.h"
#include "GDL/HelpFileAccess.h"
#include "SceneCanvas.h"
#include "ProfileDlg.h"
#include "SearchEvents.h"
#include "CreateTemplate.h"
#include "ChoixTemplateEvent.h"
#include "ChoixCondition.h"
#include "ChoixAction.h"
#include "Clipboard.h"

#include <SFML/System.hpp>

using namespace std;

//(*IdInit(EventsEditor)
const long EventsEditor::ID_TEXTCTRL1 = wxNewId();
const long EventsEditor::ID_BITMAPBUTTON1 = wxNewId();
const long EventsEditor::ID_PANEL2 = wxNewId();
const long EventsEditor::ID_PANEL7 = wxNewId();
const long EventsEditor::ID_HYPERLINKCTRL2 = wxNewId();
const long EventsEditor::ID_PANEL6 = wxNewId();
const long EventsEditor::ID_HYPERLINKCTRL1 = wxNewId();
const long EventsEditor::ID_PANEL5 = wxNewId();
const long EventsEditor::ID_HYPERLINKCTRL3 = wxNewId();
const long EventsEditor::ID_PANEL3 = wxNewId();
const long EventsEditor::ID_PANEL8 = wxNewId();
const long EventsEditor::ID_HYPERLINKCTRL4 = wxNewId();
const long EventsEditor::ID_PANEL4 = wxNewId();
const long EventsEditor::ID_PANEL1 = wxNewId();
const long EventsEditor::ID_SCROLLBAR1 = wxNewId();
const long EventsEditor::deleteMenuItem = wxNewId();
const long EventsEditor::toggleActivationMenuItem = wxNewId();
const long EventsEditor::copyMenuItem = wxNewId();
const long EventsEditor::cutMenuItem = wxNewId();
const long EventsEditor::ID_MENUITEM4 = wxNewId();
const long EventsEditor::ID_MENUITEM5 = wxNewId();
const long EventsEditor::ID_MENUITEM6 = wxNewId();
const long EventsEditor::ID_MENUITEM7 = wxNewId();
const long EventsEditor::ID_MENUITEM11 = wxNewId();
const long EventsEditor::ID_MENUITEM12 = wxNewId();
//*)
const long EventsEditor::idRibbonEvent = wxNewId();
const long EventsEditor::idRibbonCom = wxNewId();
const long EventsEditor::idRibbonSubEvent = wxNewId();
const long EventsEditor::idRibbonSomeEvent = wxNewId();
const long EventsEditor::idRibbonDelEvent = wxNewId();
const long EventsEditor::idRibbonUndo = wxNewId();
const long EventsEditor::idRibbonRedo = wxNewId();
const long EventsEditor::idRibbonCopy = wxNewId();
const long EventsEditor::idRibbonCut = wxNewId();
const long EventsEditor::idRibbonPaste = wxNewId();
const long EventsEditor::idRibbonTemplate = wxNewId();
const long EventsEditor::idRibbonCreateTemplate = wxNewId();
const long EventsEditor::idRibbonHelp = wxNewId();
const long EventsEditor::idRibbonProfiling = wxNewId();
const long EventsEditor::idSearchReplace = wxNewId();

vector < std::pair<long, std::string> > EventsEditor::idForEventTypesMenu;

wxRibbonButtonBar * EventsEditor::insertRibbonBar = NULL;
wxRibbonButtonBar * EventsEditor::deleteRibbonBar = NULL;
wxRibbonButtonBar * EventsEditor::clipboardRibbonBar = NULL;
wxRibbonButtonBar * EventsEditor::templateRibbonBar = NULL;
wxRibbonButtonBar * EventsEditor::undoRibbonBar = NULL;

BEGIN_EVENT_TABLE(EventsEditor,wxPanel)
	//(*EventTable(EventsEditor)
	//*)
END_EVENT_TABLE()


EventsEditor::EventsEditor(wxWindow* parent, Game & game_, Scene & scene_, vector < BaseEventSPtr > * events_, MainEditorCommand & mainEditorCommand_ ) :
    game(game_),
    scene(scene_),
    events(events_),
    mainEditorCommand(mainEditorCommand_),
    conditionColumnWidth(350),
    isResizingColumns(false),
    leftMargin(20),
    foldBmp("res/fold.png", wxBITMAP_TYPE_ANY),
    unfoldBmp("res/unfold.png", wxBITMAP_TYPE_ANY),
    selection(refreshCallback),
    ctrlKeyDown(false),
    profilingActivated(false),
    refreshCallback(this)
{
	//(*Initialize(EventsEditor)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	eventsPanel = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	eventsPanel->SetBackgroundColour(wxColour(255,255,255));
	liveEditingPanel = new wxPanel(eventsPanel, ID_PANEL2, wxPoint(100,100), wxDefaultSize, wxSIMPLE_BORDER, _T("ID_PANEL2"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(0);
	liveEdit = new wxTextCtrl(liveEditingPanel, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(280,21), wxTE_AUTO_SCROLL|wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer2->Add(liveEdit, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	parameterEditBt = new wxBitmapButton(liveEditingPanel, ID_BITMAPBUTTON1, wxBitmap(wxImage(_T("res/editicon.png"))), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	FlexGridSizer2->Add(parameterEditBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	liveEditingPanel->SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(liveEditingPanel);
	FlexGridSizer2->SetSizeHints(liveEditingPanel);
	eventContextPanel = new wxPanel(eventsPanel, ID_PANEL3, wxPoint(136,24), wxSize(224,40), wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 6, 0, 0);
	addEventIconPnl = new wxPanel(eventContextPanel, ID_PANEL7, wxDefaultPosition, wxSize(16,16), wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL7"));
	FlexGridSizer3->Add(addEventIconPnl, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	addEventBt = new wxHyperlinkCtrl(eventContextPanel, ID_HYPERLINKCTRL2, _("Ajouter un �v�nement"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE|wxNO_BORDER, _T("ID_HYPERLINKCTRL2"));
	FlexGridSizer3->Add(addEventBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	addSubEventIconPnl = new wxPanel(eventContextPanel, ID_PANEL6, wxDefaultPosition, wxSize(16,16), wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL6"));
	FlexGridSizer3->Add(addSubEventIconPnl, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	addSubEventBt = new wxHyperlinkCtrl(eventContextPanel, ID_HYPERLINKCTRL1, _("Un sous �v�nement"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE|wxNO_BORDER, _T("ID_HYPERLINKCTRL1"));
	FlexGridSizer3->Add(addSubEventBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	addMoreIconPnl = new wxPanel(eventContextPanel, ID_PANEL5, wxDefaultPosition, wxSize(16,16), wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	FlexGridSizer3->Add(addMoreIconPnl, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	addMoreBt = new wxHyperlinkCtrl(eventContextPanel, ID_HYPERLINKCTRL3, _("Autre..."), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE|wxNO_BORDER, _T("ID_HYPERLINKCTRL3"));
	FlexGridSizer3->Add(addMoreBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	eventContextPanel->SetSizer(FlexGridSizer3);
	FlexGridSizer3->SetSizeHints(eventContextPanel);
	listContextPanel = new wxPanel(eventsPanel, ID_PANEL4, wxPoint(136,50), wxSize(224,40), wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	addInstrIconPnl = new wxPanel(listContextPanel, ID_PANEL8, wxDefaultPosition, wxSize(16,16), wxNO_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL8"));
	FlexGridSizer4->Add(addInstrIconPnl, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	addInstrBt = new wxHyperlinkCtrl(listContextPanel, ID_HYPERLINKCTRL4, _("Ajouter une condition"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE|wxNO_BORDER, _T("ID_HYPERLINKCTRL4"));
	FlexGridSizer4->Add(addInstrBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	listContextPanel->SetSizer(FlexGridSizer4);
	FlexGridSizer4->SetSizeHints(listContextPanel);
	FlexGridSizer1->Add(eventsPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	scrollBar = new wxScrollBar(this, ID_SCROLLBAR1, wxDefaultPosition, wxDefaultSize, wxSB_VERTICAL, wxDefaultValidator, _T("ID_SCROLLBAR1"));
	scrollBar->SetScrollbar(0, 1, 10, 1);
	FlexGridSizer1->Add(scrollBar, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer1);
	deleteMenu = new wxMenuItem((&eventsContextMenu), deleteMenuItem, _("Supprimer\tDEL"), wxEmptyString, wxITEM_NORMAL);
	deleteMenu->SetBitmap(wxBitmap(wxImage(_T("res/deleteicon.png"))));
	eventsContextMenu.Append(deleteMenu);
	toggleActivation = new wxMenuItem((&eventsContextMenu), toggleActivationMenuItem, _("D�s/activer"), wxEmptyString, wxITEM_NORMAL);
	eventsContextMenu.Append(toggleActivation);
	eventsContextMenu.AppendSeparator();
	eventCopyMenu = new wxMenuItem((&eventsContextMenu), copyMenuItem, _("Copier\tCtrl-C"), wxEmptyString, wxITEM_NORMAL);
	eventCopyMenu->SetBitmap(wxBitmap(wxImage(_T("res/copyicon.png"))));
	eventsContextMenu.Append(eventCopyMenu);
	eventCutMenu = new wxMenuItem((&eventsContextMenu), cutMenuItem, _("Couper\tCtrl-X"), wxEmptyString, wxITEM_NORMAL);
	eventCutMenu->SetBitmap(wxBitmap(wxImage(_T("res/cuticon.png"))));
	eventsContextMenu.Append(eventCutMenu);
	eventPasteMenu = new wxMenuItem((&eventsContextMenu), ID_MENUITEM4, _("Coller\tCtrl-V"), wxEmptyString, wxITEM_NORMAL);
	eventPasteMenu->SetBitmap(wxBitmap(wxImage(_T("res/pasteicon.png"))));
	eventsContextMenu.Append(eventPasteMenu);
	eventsContextMenu.AppendSeparator();
	undoMenu = new wxMenuItem((&eventsContextMenu), ID_MENUITEM5, _("Annuler\tCtrl-Z"), wxEmptyString, wxITEM_NORMAL);
	undoMenu->SetBitmap(wxBitmap(wxImage(_T("res/undo.png"))));
	eventsContextMenu.Append(undoMenu);
	redoMenu = new wxMenuItem((&eventsContextMenu), ID_MENUITEM6, _("Refaire\tCtrl-Y"), wxEmptyString, wxITEM_NORMAL);
	redoMenu->SetBitmap(wxBitmap(wxImage(_T("res/redo.png"))));
	eventsContextMenu.Append(redoMenu);
	MenuItem1 = new wxMenuItem((&multipleContextMenu), ID_MENUITEM7, _("Supprimer"), wxEmptyString, wxITEM_NORMAL);
	MenuItem1->SetBitmap(wxBitmap(wxImage(_T("res/deleteicon.png"))));
	multipleContextMenu.Append(MenuItem1);
	multipleContextMenu.AppendSeparator();
	MenuItem5 = new wxMenuItem((&multipleContextMenu), ID_MENUITEM11, _("Annuler"), wxEmptyString, wxITEM_NORMAL);
	multipleContextMenu.Append(MenuItem5);
	MenuItem6 = new wxMenuItem((&multipleContextMenu), ID_MENUITEM12, _("Refaire"), wxEmptyString, wxITEM_NORMAL);
	multipleContextMenu.Append(MenuItem6);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&EventsEditor::OnliveEditText);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&EventsEditor::OnliveEditTextEnter);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EventsEditor::OnparameterEditBtClick);
	addEventIconPnl->Connect(wxEVT_PAINT,(wxObjectEventFunction)&EventsEditor::OnaddEventIconPnlPaint,0,this);
	addEventIconPnl->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&EventsEditor::OnaddEventIconPnlLeftDown,0,this);
	Connect(ID_HYPERLINKCTRL2,wxEVT_COMMAND_HYPERLINK,(wxObjectEventFunction)&EventsEditor::OnaddEventBtClick);
	addSubEventIconPnl->Connect(wxEVT_PAINT,(wxObjectEventFunction)&EventsEditor::OnaddSubEventIconPnlPaint,0,this);
	addSubEventIconPnl->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&EventsEditor::OnaddSubEventIconPnlLeftDown,0,this);
	Connect(ID_HYPERLINKCTRL1,wxEVT_COMMAND_HYPERLINK,(wxObjectEventFunction)&EventsEditor::OnaddSubEventBtClick);
	addMoreIconPnl->Connect(wxEVT_PAINT,(wxObjectEventFunction)&EventsEditor::OnaddMoreIconPnlPaint,0,this);
	addMoreIconPnl->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&EventsEditor::OnaddMoreIconPnlLeftDown,0,this);
	Connect(ID_HYPERLINKCTRL3,wxEVT_COMMAND_HYPERLINK,(wxObjectEventFunction)&EventsEditor::OnaddMoreBtClick);
	eventContextPanel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&EventsEditor::OneventContextPanelPaint,0,this);
	addInstrIconPnl->Connect(wxEVT_PAINT,(wxObjectEventFunction)&EventsEditor::OnaddInstrIconPnlPaint,0,this);
	addInstrIconPnl->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&EventsEditor::OnaddInstrIconPnlLeftDown,0,this);
	Connect(ID_HYPERLINKCTRL4,wxEVT_COMMAND_HYPERLINK,(wxObjectEventFunction)&EventsEditor::OnaddInstrBtClick);
	listContextPanel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&EventsEditor::OnlistContextPanelPaint,0,this);
	eventsPanel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&EventsEditor::OneventsPanelPaint,0,this);
	eventsPanel->Connect(wxEVT_ERASE_BACKGROUND,(wxObjectEventFunction)&EventsEditor::OneventsPanelEraseBackground,0,this);
	eventsPanel->Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&EventsEditor::OneventsPanelKeyDown,0,this);
	eventsPanel->Connect(wxEVT_KEY_UP,(wxObjectEventFunction)&EventsEditor::OneventsPanelKeyUp,0,this);
	eventsPanel->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&EventsEditor::OneventsPanelLeftDown,0,this);
	eventsPanel->Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&EventsEditor::OneventsPanelLeftUp,0,this);
	eventsPanel->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&EventsEditor::OneventsPanelLeftDClick,0,this);
	eventsPanel->Connect(wxEVT_RIGHT_UP,(wxObjectEventFunction)&EventsEditor::OneventsPanelRightUp,0,this);
	eventsPanel->Connect(wxEVT_MOTION,(wxObjectEventFunction)&EventsEditor::OneventsPanelMouseMove,0,this);
	eventsPanel->Connect(wxEVT_LEAVE_WINDOW,(wxObjectEventFunction)&EventsEditor::OneventsPanelMouseLeave,0,this);
	eventsPanel->Connect(wxEVT_MOUSEWHEEL,(wxObjectEventFunction)&EventsEditor::OneventsPanelMouseWheel,0,this);
	eventsPanel->Connect(wxEVT_SIZE,(wxObjectEventFunction)&EventsEditor::OnResize,0,this);
	Connect(ID_SCROLLBAR1,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EventsEditor::OnscrollBarScroll);
	Connect(ID_SCROLLBAR1,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&EventsEditor::OnscrollBarScroll);
	Connect(ID_SCROLLBAR1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&EventsEditor::OnscrollBarScroll);
	Connect(deleteMenuItem,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EventsEditor::OndeleteMenuSelected);
	Connect(toggleActivationMenuItem,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EventsEditor::OntoggleActivationSelected);
	Connect(copyMenuItem,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EventsEditor::OneventCopyMenuSelected);
	Connect(cutMenuItem,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EventsEditor::OneventCutMenuSelected);
	Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EventsEditor::OneventPasteMenuSelected);
	Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EventsEditor::OnundoMenuSelected);
	Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EventsEditor::OnredoMenuSelected);
	Connect(ID_MENUITEM7,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EventsEditor::OndeleteMenuSelected);
	Connect(ID_MENUITEM11,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EventsEditor::OnundoMenuSelected);
	Connect(ID_MENUITEM12,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EventsEditor::OnredoMenuSelected);
	Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&EventsEditor::OneventsPanelKeyDown);
	Connect(wxEVT_KEY_UP,(wxObjectEventFunction)&EventsEditor::OneventsPanelKeyUp);
	//*)

    addInstrBt->SetVisitedColour(addInstrBt->GetNormalColour());
    addEventBt->SetVisitedColour(addEventBt->GetNormalColour());
    addSubEventBt->SetVisitedColour(addSubEventBt->GetNormalColour());
    addMoreBt->SetVisitedColour(addMoreBt->GetNormalColour());

	//Load configuration
	wxConfigBase * config = wxConfigBase::Get();
	conditionColumnWidth = config->ReadDouble("EventsEditor/ConditionColumnWidth", 350);

    //Adding events types
    GDpriv::ExtensionsManager * extensionManager = GDpriv::ExtensionsManager::GetInstance();
    const vector < boost::shared_ptr<ExtensionBase> > extensions = extensionManager->GetExtensions();

    //Insert extension objects actions
	for (unsigned int i = 0;i<extensions.size();++i)
	{
	    //Verify if that extension is enabled
	    if ( find(game.extensionsUsed.begin(),
                  game.extensionsUsed.end(),
                  extensions[i]->GetName()) == game.extensionsUsed.end() )
            continue;

        //Add each event type provided
	    std::map<std::string, EventInfos > allEventsProvidedByExtension = extensions[i]->GetAllEvents();
        for(std::map<string, EventInfos>::const_iterator it = allEventsProvidedByExtension.begin(); it != allEventsProvidedByExtension.end(); ++it)
        {
            //Find an identifier for the menu item
            long id = wxID_ANY;
            for (vector < std::pair<long, std::string> >::iterator idIter = idForEventTypesMenu.begin();
                 idIter != idForEventTypesMenu.end();
                 ++idIter)
            {
            	if ( idIter->second == it->first )
                    id = idIter->first;
            }
            if ( id == wxID_ANY )
            {
                id = wxNewId();
                idForEventTypesMenu.push_back(std::make_pair(id, it->first));
            }

            wxMenuItem * menuItem = new wxMenuItem(&eventTypesMenu, id, it->second.fullname, it->second.description);
            menuItem->SetBitmap(it->second.smallicon);
            eventTypesMenu.Append(menuItem);
            Connect(id,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EventsEditor::OnAddCustomEventFromMenuSelected);
            mainEditorCommand.GetMainEditor()->Connect(id, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&EventsEditor::OnAddCustomEventFromMenuSelected, NULL, this);
        }
	}

    searchDialog = new SearchEvents(this, game, scene, events);

    RecomputeAllEventsWidth(*events); //Recompute all widths
    liveEditingPanel->Show(false);
    liveEdit->SetFont(EventsRenderingHelper::GetInstance()->GetFont());
    liveEditingPanel->Show(false);
    eventContextPanel->Show(false);
    listContextPanel->Show(false);

    latestState = CloneVectorOfEvents(*events);
}

EventsEditor::~EventsEditor()
{
	//(*Destroy(EventsEditor)
	//*)
}

void EventsEditor::CreateRibbonPage(wxRibbonPage * page)
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    bool hideLabels = false;
    pConfig->Read( _T( "/Skin/HideLabels" ), &hideLabels );

    {
        wxRibbonPanel *ribbonPanel = new wxRibbonPanel(page, wxID_ANY, _("Insertion"), wxBitmap("res/add24.png", wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
        insertRibbonBar = new wxRibbonButtonBar(ribbonPanel, wxID_ANY);
        insertRibbonBar->AddButton(idRibbonEvent, !hideLabels ? _("Ajouter un �v�nement") : "", wxBitmap("res/eventadd24.png", wxBITMAP_TYPE_ANY));
        insertRibbonBar->AddButton(idRibbonSubEvent, !hideLabels ? _("Ajouter un sous-�v�nement") : "", wxBitmap("res/subeventadd24.png", wxBITMAP_TYPE_ANY));
        insertRibbonBar->AddButton(idRibbonCom, !hideLabels ? _("Ajouter un commentaire") : "", wxBitmap("res/commentaireadd24.png", wxBITMAP_TYPE_ANY));
        insertRibbonBar->AddDropdownButton(idRibbonSomeEvent, !hideLabels ? _("Ajouter...") : "", wxBitmap("res/add24.png", wxBITMAP_TYPE_ANY));
    }
    {
        wxRibbonPanel *ribbonPanel = new wxRibbonPanel(page, wxID_ANY, _("Suppression"), wxBitmap("res/delete24.png", wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
        deleteRibbonBar = new wxRibbonButtonBar(ribbonPanel, wxID_ANY);
        deleteRibbonBar->AddButton(idRibbonDelEvent, !hideLabels ? _("Supprimer la s�lection") : "", wxBitmap("res/delete24.png", wxBITMAP_TYPE_ANY));
    }
    {
        wxRibbonPanel *ribbonPanel = new wxRibbonPanel(page, wxID_ANY, _("Annulation"), wxBitmap("res/unredo24.png", wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
        undoRibbonBar = new wxRibbonButtonBar(ribbonPanel, wxID_ANY);
        undoRibbonBar->AddButton(idRibbonUndo, !hideLabels ? _("Annuler") : "", wxBitmap("res/undo24.png", wxBITMAP_TYPE_ANY));
        undoRibbonBar->AddButton(idRibbonRedo, !hideLabels ? _("Refaire") : "", wxBitmap("res/redo24.png", wxBITMAP_TYPE_ANY));
    }
    {
        wxRibbonPanel *ribbonPanel = new wxRibbonPanel(page, wxID_ANY, _("Presse papiers"), wxBitmap("res/copy24.png", wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
        clipboardRibbonBar = new wxRibbonButtonBar(ribbonPanel, wxID_ANY);
        clipboardRibbonBar->AddButton(idRibbonCopy, !hideLabels ? _("Copier") : "", wxBitmap("res/copy24.png", wxBITMAP_TYPE_ANY));
        clipboardRibbonBar->AddButton(idRibbonCut, !hideLabels ? _("Couper") : "", wxBitmap("res/cut24.png", wxBITMAP_TYPE_ANY));
        clipboardRibbonBar->AddButton(idRibbonPaste, !hideLabels ? _("Coller") : "", wxBitmap("res/paste24.png", wxBITMAP_TYPE_ANY));
    }
    {
        wxRibbonPanel *ribbonPanel = new wxRibbonPanel(page, wxID_ANY, _("Mod�les"), wxBitmap("res/template24.png", wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
        templateRibbonBar = new wxRibbonButtonBar(ribbonPanel, wxID_ANY);
        templateRibbonBar->AddButton(idRibbonTemplate, !hideLabels ? _("Ins�rer") : "", wxBitmap("res/template24.png", wxBITMAP_TYPE_ANY));
        templateRibbonBar->AddButton(idRibbonCreateTemplate, !hideLabels ? _("Cr�er") : "", wxBitmap("res/addtemplate24.png", wxBITMAP_TYPE_ANY));
    }
    {
        wxRibbonPanel *ribbonPanel = new wxRibbonPanel(page, wxID_ANY, _("Recherche"), wxBitmap("res/search24.png", wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
        wxRibbonButtonBar *ribbonBar = new wxRibbonButtonBar(ribbonPanel, wxID_ANY);
        ribbonBar->AddButton(idSearchReplace, !hideLabels ? _("Chercher / Remplacer") : "", wxBitmap("res/search24.png", wxBITMAP_TYPE_ANY));
    }
    {
        wxRibbonPanel *ribbonPanel = new wxRibbonPanel(page, wxID_ANY, _("Outils"), wxBitmap("res/profiler24.png", wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
        wxRibbonButtonBar *ribbonBar = new wxRibbonButtonBar(ribbonPanel, wxID_ANY);
        ribbonBar->AddButton(idRibbonProfiling, !hideLabels ? _("Afficher les performances") : "", wxBitmap("res/profiler24.png", wxBITMAP_TYPE_ANY));
    }
    {
        wxRibbonPanel *ribbonPanel = new wxRibbonPanel(page, wxID_ANY, _("Aide"), wxBitmap("res/helpicon24.png", wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, wxRIBBON_PANEL_DEFAULT_STYLE);
        wxRibbonButtonBar *ribbonBar = new wxRibbonButtonBar(ribbonPanel, wxID_ANY);
        ribbonBar->AddButton(idRibbonHelp, !hideLabels ? _("Aide") : "", wxBitmap("res/helpicon24.png", wxBITMAP_TYPE_ANY));
    }
}

void EventsEditor::ConnectEvents()
{
    mainEditorCommand.GetMainEditor()->Connect(idRibbonEvent, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::OnRibbonAddEventBtClick, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idRibbonCom, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::OnRibbonAddCommentBtClick, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idRibbonSomeEvent, wxEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED, (wxObjectEventFunction)&EventsEditor::OnRibbonAddCustomEventFromMenu, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idRibbonSubEvent, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::OnRibbonAddSubEventSelected, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idRibbonDelEvent, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::DeleteSelection, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idRibbonUndo, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::OnundoMenuSelected, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idRibbonRedo, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::OnredoMenuSelected, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idRibbonCopy, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::OneventCopyMenuSelected, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idRibbonCut, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::OneventCutMenuSelected, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idRibbonPaste, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::OneventPasteMenuSelected, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idRibbonTemplate, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::OnTemplateBtClick, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idRibbonCreateTemplate, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::OnCreateTemplateBtClick, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idSearchReplace, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::OnSearchBtClick, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idRibbonProfiling, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::OnProfilingBtClick, NULL, this);
    mainEditorCommand.GetMainEditor()->Connect(idRibbonHelp, wxEVT_COMMAND_RIBBONBUTTON_CLICKED, (wxObjectEventFunction)&EventsEditor::OnHelpBtClick, NULL, this);
}
void InternalEventsEditorRefreshCallbacks::Refresh()
{
    editor->Refresh();
}
void EventsEditor::Refresh()
{
    eventsPanel->Refresh();
    eventsPanel->Update(); //Immediately
}

/**
 * Mark all events as must be redraw
 */
void EventsEditor::RecomputeAllEventsWidth(vector < BaseEventSPtr > & eventsToRefresh)
{
    vector<BaseEventSPtr>::iterator e = eventsToRefresh.begin();
    vector<BaseEventSPtr>::const_iterator end = eventsToRefresh.end();

    for(;e != end;++e)
    {
        (*e)->eventHeightNeedUpdate = true;

        if ( (*e)->CanHaveSubEvents() )
            RecomputeAllEventsWidth((*e)->GetSubEvents());
    }
}

void EventsEditor::OnResize(wxSizeEvent& event)
{
    RecomputeAllEventsWidth(*events); //Recompute all widths
    Refresh();
}

void EventsEditor::OneventsPanelPaint(wxPaintEvent& event)
{
    //Prepare dc and background
    wxBufferedPaintDC dc(eventsPanel);
    dc.SetPen(wxPen(wxColour(246, 246, 246)));
    dc.SetBrush(wxBrush(wxColour(246, 246, 246)));
    dc.DrawRectangle(0,0,eventsPanel->GetSize().x,eventsPanel->GetSize().y);

    //Clear selection areas
    itemsAreas.Clear();

    unsigned int totalHeight = DrawEvents(dc, *events, leftMargin, -scrollBar->GetThumbPosition());

    wxString text;
    if ( events->empty() )
        text = _("Ajoutez un premier �v�nement avec ruban.\nPassez ensuite la souris sur un �v�nement/action/condition pour obtenir plus d'options d'�dition,\nou double cliquez pour �diter un �lement.");
    else
        text = _("Passez la souris sur un �v�nement/action/condition pour obtenir plus d'options d'�dition,\nou double cliquez pour �diter un �lement.");
    dc.SetTextForeground(wxColor(0,0,0));
    dc.SetFont(EventsRenderingHelper::GetInstance()->GetNiceFont());
    dc.DrawLabel(text,
                wxRect( (eventsPanel->GetSize().x-dc.GetMultiLineTextExtent(text).GetWidth())/2,-scrollBar->GetThumbPosition()+totalHeight+25,
                        (eventsPanel->GetSize().x+dc.GetMultiLineTextExtent(text).GetWidth())/2-(eventsPanel->GetSize().x-dc.GetMultiLineTextExtent(text).GetWidth())/2,0)
                , wxALIGN_CENTER);

    totalHeight += dc.GetMultiLineTextExtent(text).y;

    scrollBar->SetRange(totalHeight);
    scrollBar->SetPageSize(eventsPanel->GetSize().y);
    scrollBar->SetThumbSize(eventsPanel->GetSize().y);
}

unsigned int EventsEditor::DrawEvents(wxDC & dc, std::vector < boost::shared_ptr< BaseEvent > > & events, int x, int y, boost::shared_ptr< BaseEvent > scrollTo  )
{
    int originalYPosition = y;
    if (profilingActivated) x += 61;

    for (unsigned int i = 0;i<events.size();++i)
    {
        if ( scrollTo == events[i] ) scrollBar->SetThumbPosition(y);

        dc.SetFont(EventsRenderingHelper::GetInstance()->GetFont());
        dc.SetTextForeground(wxColour(0,0,0));

        EventsRenderingHelper::GetInstance()->SetConditionsColumnWidth(conditionColumnWidth-x);
        unsigned int width = eventsPanel->GetSize().x-x > 0 ? eventsPanel->GetSize().x-x : 1;
        unsigned int height = events[i]->GetRenderedHeight(width);

        if( !(y+static_cast<int>(height) < 0 || y > eventsPanel->GetSize().y) ) //Render only if needed
        {
            //Event drawing :
            EventItem eventAccessor(events[i], &events, i);

            bool drawDragTarget = false;
            if ( selection.EventHighlighted(eventAccessor) ) //Highlight and context panel if needed
            {
                dc.SetPen(EventsRenderingHelper::GetInstance()->GetHighlightedRectangleOutlinePen());
                dc.SetBrush(EventsRenderingHelper::GetInstance()->GetHighlightedRectangleFillBrush());
                dc.DrawRectangle(0,y,eventsPanel->GetSize().x,height);

                eventContextPanel->SetPosition(wxPoint(eventsPanel->GetSize().x-eventContextPanel->GetSize().x-10, y+height-1));
                eventContextPanel->Show(true);

                if ( selection.IsDraggingEvent() )
                    drawDragTarget = true;//Draw drag target, but after
            }
            if ( selection.EventSelected(eventAccessor) ) //Selection rectangle if needed
            {
                dc.SetPen(EventsRenderingHelper::GetInstance()->GetSelectedRectangleOutlinePen());
                dc.SetBrush(EventsRenderingHelper::GetInstance()->GetSelectedRectangleFillBrush());
                dc.DrawRectangle(0,y,eventsPanel->GetSize().x,height);
            }

            if (profilingActivated && events[i]->IsExecutable())
            {
                dc.DrawText(ToString(i+1), x-leftMargin+2-62, y);

                //Draw profile results
                dc.SetPen(wxPen(wxColour(0,0,0)));
                dc.SetBrush(wxColour(255.0f,255.0f*(1.0f-events[i]->percentDuringLastSession*0.05f),255.0f*(1.0f-events[i]->percentDuringLastSession*0.05f)));
                dc.DrawRectangle(x-61-2, y, 61,31);

                std::ostringstream timeStr; timeStr.setf(ios::fixed,ios::floatfield); timeStr.precision(2);
                timeStr << events[i]->totalTimeDuringLastSession/1000.0f;
                dc.DrawText(timeStr.str()+"ms", x-61, y+3);

                std::ostringstream percentStr; percentStr.setf(ios::fixed,ios::floatfield); percentStr.precision(2);
                percentStr << events[i]->percentDuringLastSession;
                dc.DrawText(percentStr.str()+"%", x-61, y+15);
            }
            else
                dc.DrawText(ToString(i+1), x-leftMargin+2, y+3);


            //Event rendering
            events[i]->Render(dc, x, y, width, itemsAreas, selection);

            if ( drawDragTarget )
            {
                dc.SetPen(wxPen(wxColour(0, 0, 0)));
                dc.SetBrush(wxBrush(wxColour(0, 0, 0)));
                dc.DrawRectangle(x+2, selection.IsEventHighlightedOnBottomPart() ? y+height-2 : y, eventsPanel->GetSize().x-x-2, 2);
            }

            //Registering event in items which are displayed
            wxRect eventArea(0,y,eventsPanel->GetSize().x,height);
            itemsAreas.AddEventArea( eventArea, eventAccessor );
        }

        y += height;

        //Folding and sub events
        if ( events[i]->CanHaveSubEvents() && !events[i]->GetSubEvents().empty())
        {
            FoldingItem foldingItem(events[i].get());

            if ( !events[i]->folded )
            {
                dc.DrawBitmap(foldBmp, x-5-foldBmp.GetWidth(), y-foldBmp.GetHeight()-2, true /*Use mask*/ );
                itemsAreas.AddFoldingItem(wxRect(x-5-foldBmp.GetWidth(), y-foldBmp.GetHeight()-2, foldBmp.GetWidth(), foldBmp.GetHeight()), foldingItem);

                //Draw sub events
                y += DrawEvents(dc, events[i]->GetSubEvents(), x+24, y);
            }
            else
            {
                dc.DrawBitmap(unfoldBmp, x-5-unfoldBmp.GetWidth(), y-unfoldBmp.GetHeight()-2, true /*Use mask*/ );
                itemsAreas.AddFoldingItem(wxRect(x-5-unfoldBmp.GetWidth(), y-unfoldBmp.GetHeight()-2, unfoldBmp.GetWidth(), unfoldBmp.GetHeight()), foldingItem);

                dc.SetPen(wxPen(wxColour(0,0,0)));
                dc.DrawLine(x-5-unfoldBmp.GetWidth(), y-2, eventsPanel->GetSize().x, y-2);

                y += 2;
            }
        }
    }

    return y-originalYPosition;
}


void EventsEditor::OnlistContextPanelPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(listContextPanel);

    if ( selection.GetHighlightedInstructionList().isConditionList )
    {
        dc.SetPen(EventsRenderingHelper::GetInstance()->GetConditionsRectangleOutlinePen());
        dc.SetBrush(EventsRenderingHelper::GetInstance()->GetConditionsRectangleFillBrush());
    }
    else
    {
        dc.SetPen(EventsRenderingHelper::GetInstance()->GetActionsRectangleOutlinePen());
        dc.SetBrush(EventsRenderingHelper::GetInstance()->GetActionsRectangleFillBrush());
    }
    dc.DrawRectangle(0,-1,listContextPanel->GetSize().x,listContextPanel->GetSize().y+1);
    addInstrBt->SetBackgroundColour(dc.GetBrush().GetColour());
}
void EventsEditor::OnaddInstrIconPnlPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(addInstrIconPnl);

    if ( selection.GetHighlightedInstructionList().isConditionList )
        dc.SetBrush(EventsRenderingHelper::GetInstance()->GetConditionsRectangleFillBrush());
    else
        dc.SetBrush(EventsRenderingHelper::GetInstance()->GetActionsRectangleFillBrush());

    dc.DrawRectangle(-1,-1,eventContextPanel->GetSize().x+2,eventContextPanel->GetSize().y+2);
    dc.DrawBitmap(wxBitmap("res/addicon.png",wxBITMAP_TYPE_ANY), 0,0,true);
}

void EventsEditor::OnaddMoreIconPnlPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(addMoreIconPnl);

    if ( selection.EventSelected(selection.GetHighlightedEvent()) )
        dc.SetBrush(EventsRenderingHelper::GetInstance()->GetSelectedRectangleFillBrush());
    else
        dc.SetBrush(EventsRenderingHelper::GetInstance()->GetHighlightedRectangleFillBrush());

    dc.DrawRectangle(-1,-1,addMoreIconPnl->GetSize().x+2,addMoreIconPnl->GetSize().y+2);
    dc.DrawBitmap(wxBitmap("res/addicon.png",wxBITMAP_TYPE_ANY), 0,0,true);
}
void EventsEditor::OnaddSubEventIconPnlPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(addSubEventIconPnl);

    if ( selection.EventSelected(selection.GetHighlightedEvent()) )
        dc.SetBrush(EventsRenderingHelper::GetInstance()->GetSelectedRectangleFillBrush());
    else
        dc.SetBrush(EventsRenderingHelper::GetInstance()->GetHighlightedRectangleFillBrush());

    dc.DrawRectangle(-1,-1,addSubEventIconPnl->GetSize().x+2,addSubEventIconPnl->GetSize().y+2);
    dc.DrawBitmap(wxBitmap("res/subeventaddicon.png",wxBITMAP_TYPE_ANY), 0,0,true);
}
void EventsEditor::OnaddEventIconPnlPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(addEventIconPnl);

    if ( selection.EventSelected(selection.GetHighlightedEvent()) )
        dc.SetBrush(EventsRenderingHelper::GetInstance()->GetSelectedRectangleFillBrush());
    else
        dc.SetBrush(EventsRenderingHelper::GetInstance()->GetHighlightedRectangleFillBrush());

    dc.DrawRectangle(-1,-1,addMoreIconPnl->GetSize().x+2,addMoreIconPnl->GetSize().y+2);
    dc.DrawBitmap(wxBitmap("res/eventaddicon.png",wxBITMAP_TYPE_ANY), 0,0,true);
}

void EventsEditor::OneventContextPanelPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(eventContextPanel);

    if ( selection.EventSelected(selection.GetHighlightedEvent()) )
    {
        dc.SetPen(EventsRenderingHelper::GetInstance()->GetSelectedRectangleOutlinePen());
        dc.SetBrush(EventsRenderingHelper::GetInstance()->GetSelectedRectangleFillBrush());
    }
    else
    {
        dc.SetPen(EventsRenderingHelper::GetInstance()->GetHighlightedRectangleOutlinePen());
        dc.SetBrush(EventsRenderingHelper::GetInstance()->GetHighlightedRectangleFillBrush());
    }
    dc.DrawRectangle(0,-1,eventContextPanel->GetSize().x,eventContextPanel->GetSize().y+1);
    addEventBt->SetBackgroundColour(dc.GetBrush().GetColour());
    addSubEventBt->SetBackgroundColour(dc.GetBrush().GetColour());
    addMoreBt->SetBackgroundColour(dc.GetBrush().GetColour());
}



/**
 * De/activate ribbon buttons
 */
void EventsEditor::UpdateRibbonBars()
{
    if ( insertRibbonBar != NULL ) insertRibbonBar->EnableButton(idRibbonSubEvent, selection.HasSelectedEvents());
    if ( deleteRibbonBar != NULL ) deleteRibbonBar->EnableButton(idRibbonDelEvent, selection.HasSelectedEvents() || selection.HasSelectedInstructions());
    if ( clipboardRibbonBar != NULL ) clipboardRibbonBar->EnableButton(idRibbonCopy, selection.HasSelectedEvents()|| selection.HasSelectedInstructions());
    if ( clipboardRibbonBar != NULL ) clipboardRibbonBar->EnableButton(idRibbonCut, selection.HasSelectedEvents()|| selection.HasSelectedInstructions());
    if ( templateRibbonBar != NULL ) templateRibbonBar->EnableButton(idRibbonTemplate, selection.HasSelectedEvents());
    if ( undoRibbonBar != NULL ) undoRibbonBar->EnableButton(idRibbonUndo, !history.empty());
    if ( undoRibbonBar != NULL ) undoRibbonBar->EnableButton(idRibbonRedo, !redoHistory.empty());
}

void EventsEditor::OneventsPanelLeftUp(wxMouseEvent& event)
{
    UpdateRibbonBars();

    //End resizing condition column ?
    if ( isResizingColumns )
    {
        conditionColumnWidth = event.GetX();
        RecomputeAllEventsWidth(*events);
        isResizingColumns = false;
    }

    if ( selection.EndDragEvent(!ctrlKeyDown, selection.IsEventHighlightedOnBottomPart()) || selection.EndDragInstruction(!ctrlKeyDown, selection.IsInstructionHighlightedOnBottomPart()) )
        ChangesMadeOnEvents();

    Refresh();
}

void EventsEditor::OneventsPanelLeftDown(wxMouseEvent& event)
{
    eventsPanel->SetFocusIgnoringChildren();

    //Want to resize conditions column ?
    if ( event.GetX() >= conditionColumnWidth-2 && event.GetX() <= conditionColumnWidth+2  )
        isResizingColumns = true;

    //End live editing a parameter?
    if ( liveEditingPanel->IsShown() )
    {
        EndLiveEditing();
        return;
    }

    //Start editing a parameter?
    HandleSelectionAfterClick(event.GetX(), event.GetY());

    //Begin drag
    if ( itemsAreas.IsOnInstruction(event.GetX(), event.GetY()) && selection.InstructionSelected(itemsAreas.GetInstructionAt(event.GetX(), event.GetY())))
        selection.BeginDragInstruction();
    else if ( itemsAreas.IsOnEvent(event.GetX(), event.GetY()) && selection.EventSelected(itemsAreas.GetEventAt(event.GetX(), event.GetY())))
        selection.BeginDragEvent();
}

void EventsEditor::HandleSelectionAfterClick(int x, int y, bool allowLiveEditingParameters)
{
    if ( allowLiveEditingParameters && itemsAreas.IsOnParameter(x, y) )
    {
        selection.ClearSelection();

        wxRect parameterArea = itemsAreas.GetAreaOfParameterAt(x, y);
        liveEditedParameter = itemsAreas.GetParameterAt(x, y);
        liveEditedAssociatedInstruction = itemsAreas.GetInstructionAt(x, y);

        if (liveEditedParameter.parameter == NULL ) return;

        liveEditingPanel->SetPosition(wxPoint(parameterArea.x+liveEditingPanel->GetSize().x < eventsPanel->GetSize().x ? parameterArea.x : (eventsPanel->GetSize().x-liveEditingPanel->GetSize().x), parameterArea.y));
        liveEdit->SetValue(liveEditedParameter.parameter->GetPlainString());
        liveEditingPanel->Layout();
        liveEditingPanel->Show(true);
        liveEdit->SetFocus();
        liveEditingChangesMade = false;
    }
    //Instruction selection?
    else if ( itemsAreas.IsOnInstruction(x, y) )
    {
        InstructionItem item = itemsAreas.GetInstructionAt(x, y);

        if ( !ctrlKeyDown && !selection.InstructionSelected(item) ) selection.ClearSelection();
        selection.AddInstruction(item);
    }
    //Un/folding?
    else if ( itemsAreas.IsOnFoldingItem(x, y) )
    {
        if ( !ctrlKeyDown ) selection.ClearSelection();
        BaseEvent * eventToFold = itemsAreas.GetFoldingItemAt(x, y).event;
        if ( eventToFold != NULL )
        {
            eventToFold->folded = !eventToFold->folded;
            Refresh();
        }
    }
    //Event selection?
    else if ( itemsAreas.IsOnEvent(x, y) )
    {
        EventItem item = itemsAreas.GetEventAt(x, y);

        if ( !ctrlKeyDown && !selection.EventSelected(item) ) selection.ClearSelection();
        selection.AddEvent(item);
    }
}

void EventsEditor::OneventsPanelLeftDClick(wxMouseEvent& event)
{
    //Instruction selection?
    if ( itemsAreas.IsOnInstruction(event.GetX(), event.GetY()) )
    {
        InstructionItem item = itemsAreas.GetInstructionAt(event.GetX(), event.GetY());

        if (item.instruction == NULL || item.instructionList == NULL || item.event == NULL) return;

        if ( item.isCondition )
        {
            ChoixCondition dialog(this, game, scene);
            dialog.Type = item.instruction->GetType();
            dialog.Param = item.instruction->GetParameters();
            dialog.Loc = item.instruction->IsLocal();
            dialog.Contraire = item.instruction->IsInverted();
            dialog.RefreshFromCondition();
            dialog.Fit();

            if ( dialog.ShowModal() == 0)
            {
                item.instruction->SetType( dialog.Type );
                item.instruction->SetParameters( dialog.Param );
                item.instruction->SetLocal( dialog.Loc );
                item.instruction->SetInversion( dialog.Contraire );

                item.event->eventHeightNeedUpdate = true;
                ChangesMadeOnEvents();
                Refresh();
            }
        }
        else
        {
            ChoixAction dialog(this, game, scene);
            dialog.Type = item.instruction->GetType();
            dialog.Param = item.instruction->GetParameters();
            dialog.Loc = item.instruction->IsLocal();
            dialog.RefreshFromAction();
            dialog.Fit();

            if ( dialog.ShowModal() == 0)
            {
                item.instruction->SetType( dialog.Type );
                item.instruction->SetParameters( dialog.Param );
                item.instruction->SetLocal( dialog.Loc );

                item.event->eventHeightNeedUpdate = true;
                ChangesMadeOnEvents();
                Refresh();
            }
        }
    }
    else if (itemsAreas.IsOnInstructionList(event.GetX(), event.GetY()) )
    {
        InstructionListItem item = itemsAreas.GetInstructionListAt(event.GetX(), event.GetY());

        if ( item.instructionList == NULL || item.event == NULL) return;

        if ( item.isConditionList )
        {
            ChoixCondition dialog(this, game, scene);
            if ( dialog.ShowModal() == 0)
            {
                Instruction instruction;
                instruction.SetType( dialog.Type );
                instruction.SetParameters( dialog.Param );
                instruction.SetLocal( dialog.Loc );
                instruction.SetInversion( dialog.Contraire );

                item.instructionList->push_back(instruction);
                item.event->eventHeightNeedUpdate = true;
                ChangesMadeOnEvents();
                Refresh();
            }
        }
        else
        {
            ChoixAction dialog(this, game, scene);
            if ( dialog.ShowModal() == 0)
            {
                Instruction instruction;
                instruction.SetType( dialog.Type );
                instruction.SetParameters( dialog.Param );
                instruction.SetLocal( dialog.Loc );

                item.instructionList->push_back(instruction);
                item.event->eventHeightNeedUpdate = true;
                ChangesMadeOnEvents();
                Refresh();
            }
        }
    }
    //Event selection?
    else if ( itemsAreas.IsOnEvent(event.GetX(), event.GetY()) )
    {
        boost::shared_ptr<BaseEvent> evt = itemsAreas.GetEventAt(event.GetX(), event.GetY()).event;

        if ( evt == boost::shared_ptr<BaseEvent>() ) return;

        evt->EditEvent(this, game, scene, mainEditorCommand);
        evt->eventHeightNeedUpdate = true;

        ChangesMadeOnEvents();
    }
}

void EventsEditor::OneventsPanelMouseMove(wxMouseEvent& event)
{
    if (!liveEditingPanel->IsShown())
        eventsPanel->SetFocusIgnoringChildren();

    //Column resizing
    if ( (event.GetX() >= conditionColumnWidth-2 && event.GetX() <= conditionColumnWidth+2) || isResizingColumns)
    {
        SetCursor(wxCURSOR_SIZEWE);
        if ( isResizingColumns ) return;
    }
    else
        SetCursor(wxNullCursor);

    bool showlistContextPanel = false;

    //Reset highlighted items.
    ParameterItem dummy;
    selection.SetHighlighted(dummy);
    InstructionListItem dummy2;
    selection.SetHighlighted(dummy2);
    InstructionItem dummy3;
    selection.SetHighlighted(dummy3);
    EventItem dummy4;
    selection.SetHighlighted(dummy4);

    //Highlight management
    if ( itemsAreas.IsOnEvent(event.GetX(), event.GetY()) )
    {
        selection.SetHighlighted(itemsAreas.GetEventAt(event.GetX(), event.GetY()));

        wxRect area = itemsAreas.GetAreaOfEventAt(event.GetX(), event.GetY());
        selection.EventHighlightedOnBottomPart(area.y+area.height/2.0 < event.GetY());

        if ( itemsAreas.IsOnInstructionList(event.GetX(), event.GetY()) )
        {
            selection.SetHighlighted(itemsAreas.GetInstructionListAt(event.GetX(), event.GetY()));
            wxRect area = itemsAreas.GetAreaOfInstructionListAt(event.GetX(), event.GetY());
            addInstrBt->SetLabel(itemsAreas.GetInstructionListAt(event.GetX(), event.GetY()).isConditionList ? _("Ajouter une condition") : _("Ajouter une action"));
            listContextPanel->SetPosition(wxPoint(area.x, area.y+area.height-1));
            showlistContextPanel = true;

            if ( itemsAreas.IsOnInstruction(event.GetX(), event.GetY()) )
            {
                selection.SetHighlighted(itemsAreas.GetInstructionAt(event.GetX(), event.GetY()));

                wxRect area = itemsAreas.GetAreaOfInstructionAt(event.GetX(), event.GetY());
                selection.InstructionHighlightedOnBottomPart(area.y+area.height/2.0 < event.GetY());

                if ( itemsAreas.IsOnParameter(event.GetX(), event.GetY()) )
                    selection.SetHighlighted(itemsAreas.GetParameterAt(event.GetX(), event.GetY()));
            }
        }
        else if ( itemsAreas.IsOnParameter(event.GetX(), event.GetY()) ) //Parameter without list ( a simple GDExpression )
            selection.SetHighlighted(itemsAreas.GetParameterAt(event.GetX(), event.GetY()));

    }
    else
        eventContextPanel->Show(false);

    listContextPanel->Show(showlistContextPanel); //Prevent flickering by change the state only once we know the real state.
    Refresh();
}


void EventsEditor::OneventsPanelRightUp(wxMouseEvent& event)
{
    HandleSelectionAfterClick(event.GetX(), event.GetY(), false /*Do not start editing a parameter*/);

    if ( itemsAreas.IsOnInstruction(event.GetX(), event.GetY()) )
    {
        eventsContextMenu.Enable(deleteMenuItem, true);
        eventsContextMenu.Enable(toggleActivationMenuItem, false);
        eventsContextMenu.Enable(copyMenuItem, true);
        eventsContextMenu.Enable(cutMenuItem, true);
        PopupMenu(&eventsContextMenu);
    }
    else if ( itemsAreas.IsOnInstructionList(event.GetX(), event.GetY()) )
    {
        eventsContextMenu.Enable(deleteMenuItem, false);
        eventsContextMenu.Enable(toggleActivationMenuItem, false);
        eventsContextMenu.Enable(copyMenuItem, false);
        eventsContextMenu.Enable(cutMenuItem, false);
        PopupMenu(&eventsContextMenu);
    }
    else if ( itemsAreas.IsOnEvent(event.GetX(), event.GetY()) )
    {
        eventsContextMenu.Enable(deleteMenuItem, true);
        eventsContextMenu.Enable(toggleActivationMenuItem, true);
        eventsContextMenu.Enable(copyMenuItem, true);
        eventsContextMenu.Enable(cutMenuItem, true);
        PopupMenu(&eventsContextMenu);
    }
}

void EventsEditor::OneventsPanelMouseLeave(wxMouseEvent& event)
{
}


/**
 * Manage keyboard input
 */
void EventsEditor::OneventsPanelKeyDown(wxKeyEvent& event)
{
    if ( event.GetKeyCode() == WXK_CONTROL )
    {
        ctrlKeyDown = true;
    }
    else if ( event.GetKeyCode() == WXK_DELETE )
    {
        DeleteSelection();
    }
    else if ( event.GetKeyCode() == WXK_INSERT )
    {
        wxCommandEvent unusedEvent;
        OnaddEventBtClick( unusedEvent );
    }
    if ( event.GetModifiers() == wxMOD_CMD ) //Ctrl-xxx
    {
        switch ( event.GetKeyCode() )
        {
            case 67: //Ctrl C
            {
                wxCommandEvent unusedEvent;
                OneventCopyMenuSelected( unusedEvent );
                break;
            }
            case 86: //Ctrl-V
            {
                wxCommandEvent unusedEvent;
                OneventPasteMenuSelected( unusedEvent );
                break;
            }
            case 88: //Ctrl-X
            {
                wxCommandEvent unusedEvent;
                OneventCutMenuSelected( unusedEvent );
                break;
            }
            case 89: //Ctrl-Y
            {
                wxCommandEvent unusedEvent;
                OnredoMenuSelected( unusedEvent );
                break;
            }
            case 90: //Ctrl-Z
            {
                wxCommandEvent unusedEvent;
                OnundoMenuSelected( unusedEvent );
                break;
            }
            default:
                break;
        }
    }
}

/**
 * Manage keyboard input
 */
void EventsEditor::OneventsPanelKeyUp(wxKeyEvent& event)
{
    if ( event.GetKeyCode() == WXK_CONTROL )
    {
        ctrlKeyDown = false;
    }
}

void EventsEditor::DeleteSelection()
{
    //Delete selected instructions..
    selection.DeleteAllInstructionSelected();

    //..and events
    std::vector<EventItem> eventsSelection = selection.GetAllSelectedEvents();
    for (unsigned int i = 0; i<eventsSelection.size();++i)
    {
        if ( eventsSelection[i].event != boost::shared_ptr<BaseEvent>() && eventsSelection[i].eventsList != NULL)
            eventsSelection[i].eventsList->erase(std::remove(eventsSelection[i].eventsList->begin(), eventsSelection[i].eventsList->end(), eventsSelection[i].event) , eventsSelection[i].eventsList->end());
    }

    selection.ClearSelection();
    ChangesMadeOnEvents();
    Refresh();
}

void EventsEditor::ChangesMadeOnEvents(bool updateHistory)
{
    if ( updateHistory )
    {
        history.push_back(CloneVectorOfEvents(latestState));
        redoHistory.clear();
        latestState = CloneVectorOfEvents(*events);
    }

    scene.wasModified = true;
    scene.eventsModified = true;
    EventsCodeCompiler::GetInstance()->EventsCompilationNeeded(EventsCodeCompiler::Task(&game, &scene));
}

/**
 * Live editing is ended ( by Enter or a click )
 */
void EventsEditor::EndLiveEditing()
{
    if ( liveEditedParameter.parameter == NULL )
    {
        std::cout << "Warning, live edited parameter is invalid" << std::endl;
        return;
    }
    if ( liveEditedParameter.event == NULL )
    {
        std::cout << "Warning, live edited event is invalid" << std::endl;
        return;
    }

    eventsPanel->SetFocusIgnoringChildren();
    *liveEditedParameter.parameter = GDExpression(ToString(liveEdit->GetValue()));
    liveEditedParameter.event->eventHeightNeedUpdate = true;
    liveEditingPanel->Show(false);

    if (liveEditingChangesMade)
        ChangesMadeOnEvents();
    Refresh();
    return;
}

void EventsEditor::OneventsPanelEraseBackground(wxEraseEvent& event)
{
    //Prevent flickering
}

void EventsEditor::OnscrollBarScroll(wxScrollEvent& event)
{
    Refresh();
}

void EventsEditor::OnliveEditTextEnter(wxCommandEvent& event)
{
    EndLiveEditing();
}

void EventsEditor::OneventsPanelMouseWheel(wxMouseEvent& event)
{
    scrollBar->SetThumbPosition(scrollBar->GetThumbPosition()-event.GetWheelRotation());
    Refresh();
}

void EventsEditor::OnliveEditText(wxCommandEvent& event)
{
    liveEditingChangesMade = true;
}


void EventsEditor::OnaddInstrBtClick(wxCommandEvent& event)
{
    InstructionListItem listHighlighted = selection.GetHighlightedInstructionList();
    if ( listHighlighted.instructionList == NULL ) return;

    if ( listHighlighted.isConditionList )
    {
        ChoixCondition dialog(this, game, scene);
        if ( dialog.ShowModal() == 0)
        {
            Instruction instruction;
            instruction.SetType(dialog.Type);
            instruction.SetParameters(dialog.Param);
            instruction.SetLocal(dialog.Loc);
            instruction.SetInversion(dialog.Contraire);

            listHighlighted.instructionList->push_back(instruction);
            listHighlighted.event->eventHeightNeedUpdate = true;
            ChangesMadeOnEvents();
            Refresh();
        }
    }
    else
    {
        ChoixAction dialog(this, game, scene);
        if ( dialog.ShowModal() == 0)
        {
            Instruction instruction;
            instruction.SetType(dialog.Type);
            instruction.SetParameters(dialog.Param);
            instruction.SetLocal(dialog.Loc);

            listHighlighted.instructionList->push_back(instruction);
            listHighlighted.event->eventHeightNeedUpdate = true;
            ChangesMadeOnEvents();
            Refresh();
        }
    }
}

/**
 * Add an event
 */
void EventsEditor::AddEvent(EventItem & previousEventItem)
{
    BaseEventSPtr eventToAdd = GDpriv::ExtensionsManager::GetInstance()->CreateEvent("BuiltinCommonInstructions::Standard");
    if ( eventToAdd != boost::shared_ptr<BaseEvent>() )
    {
        eventToAdd->EditEvent(this, game, scene, mainEditorCommand);

        //Adding event
        if ( previousEventItem.eventsList != NULL )
        {
            if ( previousEventItem.positionInList < previousEventItem.eventsList->size() )
                previousEventItem.eventsList->insert( previousEventItem.eventsList->begin() + previousEventItem.positionInList+1, eventToAdd );
            else
                previousEventItem.eventsList->push_back( eventToAdd );
        }
        else if ( events != NULL )
            events->push_back( eventToAdd );


        ChangesMadeOnEvents();
        Refresh();
    }
    else
        wxLogError(_("Impossible de cr�er un �v�nement standard"));
}

void EventsEditor::OnaddEventBtClick(wxCommandEvent& event)
{
    EventItem & highlightedEvent = selection.GetHighlightedEvent();
    if ( highlightedEvent.event == boost::shared_ptr<BaseEvent>() ) return;

    AddEvent(highlightedEvent);
}
void EventsEditor::OnRibbonAddEventBtClick(wxRibbonButtonBarEvent& evt)
{
    std::vector< EventItem > eventsSelected = selection.GetAllSelectedEvents();

    if ( !eventsSelected.empty() && eventsSelected[0].event != boost::shared_ptr<BaseEvent>() )
        AddEvent(eventsSelected[0]);
    else
    {
        EventItem dummy;
        AddEvent(dummy);
    }
}

/**
 * Ribbon specific : add a comment
 */
void EventsEditor::OnRibbonAddCommentBtClick(wxRibbonButtonBarEvent& evt)
{
    std::vector< EventItem > eventsSelected = selection.GetAllSelectedEvents();
    EventItem previousEventItem;
    if ( !eventsSelected.empty() && eventsSelected[0].event != boost::shared_ptr<BaseEvent>() ) previousEventItem = eventsSelected[0];

    BaseEventSPtr eventToAdd = GDpriv::ExtensionsManager::GetInstance()->CreateEvent("BuiltinCommonInstructions::Comment");
    if ( eventToAdd != boost::shared_ptr<BaseEvent>() )
    {
        eventToAdd->EditEvent(this, game, scene, mainEditorCommand);

        //Adding event
        if ( previousEventItem.eventsList != NULL )
        {
            if ( previousEventItem.positionInList < previousEventItem.eventsList->size() )
                previousEventItem.eventsList->insert( previousEventItem.eventsList->begin() + previousEventItem.positionInList+1, eventToAdd );
            else
                previousEventItem.eventsList->push_back( eventToAdd );
        }
        else if ( events != NULL)
            events->push_back( eventToAdd );

        ChangesMadeOnEvents();
        Refresh();
    }
    else
        wxLogError(_("Impossible de cr�er un �v�nement commentaire."));
}

/**
 * Add a sub event
 */
void EventsEditor::AddSubEvent(EventItem & parentEventItem)
{
    BaseEventSPtr eventToAdd = GDpriv::ExtensionsManager::GetInstance()->CreateEvent("BuiltinCommonInstructions::Standard");
    if ( eventToAdd != boost::shared_ptr<BaseEvent>() )
    {
        eventToAdd->EditEvent(this, game, scene, mainEditorCommand);

        //Adding event
        parentEventItem.event->GetSubEvents().insert( parentEventItem.event->GetSubEvents().begin(), eventToAdd );

        ChangesMadeOnEvents();
        Refresh();
    }
    else
        wxLogError(_("Impossible de cr�er un �v�nement standard"));
}

void EventsEditor::OnaddSubEventBtClick(wxCommandEvent& event)
{
    EventItem & highlightedEvent = selection.GetHighlightedEvent();
    if ( highlightedEvent.event == boost::shared_ptr<BaseEvent>() || !highlightedEvent.event->CanHaveSubEvents() ) return;

    AddSubEvent(highlightedEvent);
}
void EventsEditor::OnRibbonAddSubEventSelected(wxRibbonButtonBarEvent& evt)
{
    std::vector< EventItem > eventsSelected = selection.GetAllSelectedEvents();
    if ( eventsSelected.empty() || eventsSelected[0].event == boost::shared_ptr<BaseEvent>() ) return;

    AddSubEvent(eventsSelected[0]);
}

/**
 * Add event of selected type
 */
void EventsEditor::AddCustomEventFromMenu(unsigned int menuID, EventItem & previousEventItem)
{
    //Retrieve event type
    string eventType;
    for (unsigned int i = 0;i<idForEventTypesMenu.size();++i)
    {
    	if ( idForEventTypesMenu[i].first == menuID )
            eventType = idForEventTypesMenu[i].second;
    }

    //Create event
    if ( !GDpriv::ExtensionsManager::GetInstance()->HasEventType(eventType) ) return;
    BaseEventSPtr eventToAdd = GDpriv::ExtensionsManager::GetInstance()->CreateEvent(eventType);
    eventToAdd->EditEvent(this, game, scene, mainEditorCommand);

    //Adding event
    if ( previousEventItem.eventsList != NULL )
    {
        if ( previousEventItem.positionInList < previousEventItem.eventsList->size() )
            previousEventItem.eventsList->insert( previousEventItem.eventsList->begin() + previousEventItem.positionInList+1, eventToAdd );
        else
            previousEventItem.eventsList->push_back( eventToAdd );
    }
    else if ( events != NULL)
        events->push_back( eventToAdd );

    ChangesMadeOnEvents();
    Refresh();
}

void EventsEditor::OnAddCustomEventFromMenuSelected(wxCommandEvent& event)
{
    std::vector< EventItem > eventsSelected = selection.GetAllSelectedEventsWithoutSubEvents();
    if ( !eventsSelected.empty() )
        AddCustomEventFromMenu(event.GetId(), eventsSelected[0]);
    else
    {
        EventItem dummy;
        AddCustomEventFromMenu(event.GetId(), dummy);
    }
}

void EventsEditor::OnRibbonAddCustomEventFromMenu(wxRibbonButtonBarEvent& evt)
{
    evt.PopupMenu(&eventTypesMenu);
}

void EventsEditor::OnaddMoreBtClick(wxCommandEvent& event)
{
    selection.ClearSelection();
    if ( selection.GetHighlightedEvent().event == boost::shared_ptr<BaseEvent>() ) return;
    selection.AddEvent(selection.GetHighlightedEvent());

    PopupMenu(&eventTypesMenu);
}

void EventsEditor::ScrollToEvent(BaseEventSPtr eventToScrollTo)
{
    wxClientDC dc(eventsPanel);
    DrawEvents(dc, *events, leftMargin, 0, eventToScrollTo);
    Refresh();
}

void EventsEditor::OndeleteMenuSelected(wxCommandEvent& event)
{
    DeleteSelection();
}


void EventsEditor::OneventCopyMenuSelected(wxCommandEvent& event)
{
    if ( selection.HasSelectedConditions())
    {
        std::vector < InstructionItem > itemsSelected = selection.GetAllSelectedInstructions();
        std::vector < Instruction > instructionsToCopy;
        for (unsigned int i = 0;i<itemsSelected.size();++i)
        {
            if (itemsSelected[i].instruction != NULL)
                instructionsToCopy.push_back(*itemsSelected[i].instruction);
        }

        Clipboard::GetInstance()->SetConditions(instructionsToCopy);
    }
    else if ( selection.HasSelectedActions())
    {
        std::vector < InstructionItem > itemsSelected = selection.GetAllSelectedInstructions();
        std::vector < Instruction > instructionsToCopy;
        for (unsigned int i = 0;i<itemsSelected.size();++i)
        {
            if (itemsSelected[i].instruction != NULL)
                instructionsToCopy.push_back(*itemsSelected[i].instruction);
        }

        Clipboard::GetInstance()->SetActions(instructionsToCopy);
    }
    else if ( selection.HasSelectedEvents() )
    {
        std::vector < EventItem > itemsSelected = selection.GetAllSelectedEventsWithoutSubEvents();
        std::vector < boost::shared_ptr<BaseEvent> > eventsToCopy;
        for (unsigned int i = 0;i<itemsSelected.size();++i)
        {
            if (itemsSelected[i].event != boost::shared_ptr<BaseEvent>())
                eventsToCopy.push_back(itemsSelected[i].event->Clone());
        }

        Clipboard::GetInstance()->SetEvents(eventsToCopy);
    }
}

void EventsEditor::OneventCutMenuSelected(wxCommandEvent& event)
{
    //Do initially the same thing as copy
    OneventCopyMenuSelected(event);

    if ( selection.HasSelectedConditions())
        DeleteSelection();
    else if ( selection.HasSelectedActions())
        DeleteSelection();
    else if ( selection.HasSelectedEvents() )
        DeleteSelection();
}

void EventsEditor::OneventPasteMenuSelected(wxCommandEvent& event)
{
        cout << "allo";
    if ( selection.HasSelectedConditions() || (selection.GetHighlightedInstructionList().instructionList != NULL && selection.GetHighlightedInstructionList().isConditionList) )
    {
        if ( !Clipboard::GetInstance()->HasCondition() ) return;

        //Get information about list where conditions must be pasted
        std::vector<Instruction> * instructionList = selection.HasSelectedConditions() ? selection.GetAllSelectedInstructions().back().instructionList : selection.GetHighlightedInstructionList().instructionList;
        size_t positionInThisList = selection.HasSelectedConditions() ? selection.GetAllSelectedInstructions().back().positionInList : std::string::npos;
        BaseEvent * event = selection.HasSelectedConditions() ? selection.GetAllSelectedInstructions().back().event : selection.GetHighlightedInstructionList().event;
        if (instructionList == NULL) return;

        //Paste all conditions
        const vector < Instruction > & instructions = Clipboard::GetInstance()->GetInstructions();
        for (unsigned int i = 0;i<instructions.size();++i)
        {
            if ( positionInThisList < instructionList->size() )
                instructionList->insert(instructionList->begin()+positionInThisList, instructions[i]);
            else
                instructionList->push_back(instructions[i]);
        }

        if ( event != NULL ) event->eventHeightNeedUpdate = true;
        if ( !instructions.empty() ) ChangesMadeOnEvents();
        Refresh();
    }
    else if ( selection.HasSelectedActions()|| (selection.GetHighlightedInstructionList().instructionList != NULL && !selection.GetHighlightedInstructionList().isConditionList) )
    {
        if ( !Clipboard::GetInstance()->HasAction() ) return;

        //Get information about list where actions must be pasted
        std::vector<Instruction> * instructionList = selection.HasSelectedActions() ? selection.GetAllSelectedInstructions().back().instructionList : selection.GetHighlightedInstructionList().instructionList;
        size_t positionInThisList = selection.HasSelectedActions() ? selection.GetAllSelectedInstructions().back().positionInList : std::string::npos;
        BaseEvent * event = selection.HasSelectedActions() ? selection.GetAllSelectedInstructions().back().event : selection.GetHighlightedInstructionList().event;
        if (instructionList == NULL) return;

        //Paste all actions
        const vector < Instruction > & instructions = Clipboard::GetInstance()->GetInstructions();
        for (unsigned int i = 0;i<instructions.size();++i)
        {
            if ( positionInThisList < instructionList->size() )
                instructionList->insert(instructionList->begin()+positionInThisList, instructions[i]);
            else
                instructionList->push_back(instructions[i]);
        }

        if ( event != NULL ) event->eventHeightNeedUpdate = true;
        if ( !instructions.empty() ) ChangesMadeOnEvents();
        Refresh();
    }
    else if ( selection.HasSelectedEvents())
    {
        cout << "lola";
        EventItem item = selection.GetAllSelectedEvents().back();
        if (item.eventsList == NULL) return;

        const vector < boost::shared_ptr<BaseEvent> > & eventsToPaste = Clipboard::GetInstance()->GetEvents();
        for (unsigned int i = 0;i<eventsToPaste.size();++i)
        {
            if ( item.positionInList < item.eventsList->size() )
                item.eventsList->insert(item.eventsList->begin()+item.positionInList, eventsToPaste[i]->Clone());
            else
                item.eventsList->push_back(eventsToPaste[i]->Clone());
        }

        if ( !eventsToPaste.empty() ) ChangesMadeOnEvents();
        Refresh();
    }
}

void EventsEditor::OnundoMenuSelected(wxCommandEvent& event)
{
    if ( history.empty() ) return;

    redoHistory.push_back(CloneVectorOfEvents(*events));
    *events = CloneVectorOfEvents(history.back());
    history.pop_back();

    latestState = CloneVectorOfEvents(*events);

    ChangesMadeOnEvents(false);
    Refresh();
    UpdateRibbonBars();
}

void EventsEditor::OnredoMenuSelected(wxCommandEvent& event)
{
    if ( redoHistory.empty() ) return;

    history.push_back(CloneVectorOfEvents(*events));
    *events = CloneVectorOfEvents(redoHistory.back());
    redoHistory.pop_back();

    latestState = CloneVectorOfEvents(*events);

    ChangesMadeOnEvents(false);
    Refresh();
    UpdateRibbonBars();
}

void EventsEditor::OnHelpBtClick(wxCommandEvent& event)
{
    HelpFileAccess * helpFileAccess = HelpFileAccess::GetInstance();
    helpFileAccess->DisplaySection(11);
}

void EventsEditor::OnCreateTemplateBtClick( wxCommandEvent& event )
{
    std::vector< EventItem > eventsSelected = selection.GetAllSelectedEventsWithoutSubEvents();
    if ( eventsSelected.empty() ) return;

    std::vector< boost::shared_ptr<BaseEvent> > eventsToUse;
    for (unsigned int i = 0;i<eventsSelected.size();++i)
    {
        if (eventsSelected[i].event != boost::shared_ptr<BaseEvent>())
            eventsToUse.push_back(eventsSelected[i].event->Clone());
    }

    CreateTemplate dialog( this, eventsToUse );
    dialog.ShowModal();
}

void EventsEditor::OnTemplateBtClick( wxCommandEvent& event )
{
    std::vector< EventItem > eventsSelected = selection.GetAllSelectedEventsWithoutSubEvents();
    if ( eventsSelected.empty() || eventsSelected[0].eventsList == NULL ) return;

    ChoixTemplateEvent dialog( this );
    if ( dialog.ShowModal() != 1 ) return;

    //Insert new events
    for ( unsigned int i = 0;i < dialog.finalTemplate.events.size();i++ )
    {
        if ( eventsSelected[0].positionInList < eventsSelected[0].eventsList->size() )
            eventsSelected[0].eventsList->insert( eventsSelected[0].eventsList->begin()+eventsSelected[0].positionInList+1, dialog.finalTemplate.events[i] );
        else
            eventsSelected[0].eventsList->push_back( dialog.finalTemplate.events[i] );
    }

    ChangesMadeOnEvents();
}

void EventsEditor::OnSearchBtClick(wxCommandEvent& event)
{
    if ( searchDialog )
        searchDialog->Show();
}

void EventsEditor::OnProfilingBtClick(wxCommandEvent& event)
{
    if ( !profilingActivated && sceneCanvas && sceneCanvas->GetOwnedProfileDialog() != boost::shared_ptr<ProfileDlg>() && !sceneCanvas->GetOwnedProfileDialog()->profilingActivated)
    {
        wxLogMessage(_("Le suivi des performances n'est pas activ�. Activez le suivi des �v�nements � l'aide de la fen�tre Performances lors de l'aper�u puis lancez un aper�u de la sc�ne."));
        return;
    }

    profilingActivated = !profilingActivated;
    RecomputeAllEventsWidth(*events); //Recompute all widths
    Refresh();
}

void EventsEditor::OnparameterEditBtClick(wxCommandEvent& event)
{
    EndLiveEditing();

    if ( liveEditedAssociatedInstruction.instruction == NULL ) return;

    InstructionItem & item = liveEditedAssociatedInstruction;

    if (item.instruction == NULL || item.instructionList == NULL || item.event == NULL) return;

    if ( item.isCondition )
    {
        ChoixCondition dialog(this, game, scene);
        dialog.Type = item.instruction->GetType();
        dialog.Param = item.instruction->GetParameters();
        dialog.Loc = item.instruction->IsLocal();
        dialog.Contraire = item.instruction->IsInverted();
        dialog.RefreshFromCondition();
        dialog.Fit();

        if ( dialog.ShowModal() == 0)
        {
            item.instruction->SetType( dialog.Type );
            item.instruction->SetParameters( dialog.Param );
            item.instruction->SetLocal( dialog.Loc );
            item.instruction->SetInversion( dialog.Contraire );

            item.event->eventHeightNeedUpdate = true;
            ChangesMadeOnEvents();
            Refresh();
        }
    }
    else
    {
        ChoixAction dialog(this, game, scene);
        dialog.Type = item.instruction->GetType();
        dialog.Param = item.instruction->GetParameters();
        dialog.Loc = item.instruction->IsLocal();
        dialog.RefreshFromAction();
        dialog.Fit();

        if ( dialog.ShowModal() == 0)
        {
            item.instruction->SetType( dialog.Type );
            item.instruction->SetParameters( dialog.Param );
            item.instruction->SetLocal( dialog.Loc );

            item.event->eventHeightNeedUpdate = true;
            ChangesMadeOnEvents();
            Refresh();
        }
    }
}


void EventsEditor::OntoggleActivationSelected(wxCommandEvent& event)
{
    std::vector< EventItem > eventsSelected = selection.GetAllSelectedEvents();
    for (unsigned int i = 0;i<eventsSelected.size();++i)
    {
        if ( eventsSelected[i].event != boost::shared_ptr<BaseEvent>())
            eventsSelected[i].event->SetDisabled(!eventsSelected[i].event->IsDisabled());
    }
}


void EventsEditor::OnaddMoreIconPnlLeftDown(wxMouseEvent& event)
{
    wxCommandEvent useless;
    OnaddMoreBtClick(useless);
}
void EventsEditor::OnaddSubEventIconPnlLeftDown(wxMouseEvent& event)
{
    wxCommandEvent useless;
    OnaddSubEventBtClick(useless);
}
void EventsEditor::OnaddEventIconPnlLeftDown(wxMouseEvent& event)
{
    wxCommandEvent useless;
    OnaddEventBtClick(useless);
}
void EventsEditor::OnaddInstrIconPnlLeftDown(wxMouseEvent& event)
{
    wxCommandEvent useless;
    OnaddInstrBtClick(useless);
}

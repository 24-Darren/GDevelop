#include "EditTexte.h"

//(*InternalHeaders(EditTexte)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include "GDL/EditExpression.h"
#include <wx/textdlg.h>
class Game;
class Scene;

//(*IdInit(EditTexte)
const long EditTexte::ID_TEXTCTRL1 = wxNewId();
const long EditTexte::ID_STATICLINE1 = wxNewId();
const long EditTexte::ID_STATICTEXT3 = wxNewId();
const long EditTexte::ID_STATICTEXT2 = wxNewId();
const long EditTexte::ID_BUTTON3 = wxNewId();
const long EditTexte::ID_STATICTEXT1 = wxNewId();
const long EditTexte::ID_TREECTRL1 = wxNewId();
const long EditTexte::ID_BUTTON10 = wxNewId();
const long EditTexte::ID_STATICTEXT4 = wxNewId();
const long EditTexte::ID_TREECTRL2 = wxNewId();
const long EditTexte::ID_BUTTON7 = wxNewId();
const long EditTexte::ID_STATICLINE2 = wxNewId();
const long EditTexte::ID_BUTTON2 = wxNewId();
const long EditTexte::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EditTexte,wxDialog)
	//(*EventTable(EditTexte)
	//*)
END_EVENT_TABLE()

EditTexte::EditTexte(wxWindow* parent, string texte, Game & game_, Scene & scene_, bool canSelectGroup_, const vector < string > & mainObjectsName_) :
game(game_),
scene(scene_),
canSelectGroup(canSelectGroup_),
mainObjectsName(mainObjectsName_)
{
	//(*Initialize(EditTexte)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, _("Editer le texte"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	TexteEdit = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(331,110), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(TexteEdit, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	FlexGridSizer1->Add(StaticLine1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Editer le texte"));
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer4->AddGrowableRow(0);
	FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Op�rations sur le texte"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer6->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Expression num�rique"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer6->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	InsertBt = new wxButton(this, ID_BUTTON3, _("Ins�rer une expression num�rique"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	InsertBt->SetToolTip(_("Permet d\'ins�rer un calcul, ou la valeur d\'une variable"));
	FlexGridSizer6->Add(InsertBt, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer6, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
	FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Propri�t�s des objets"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer5->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ObjList = new wxTreeCtrl(this, ID_TREECTRL1, wxDefaultPosition, wxSize(195,177), wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
	FlexGridSizer5->Add(ObjList, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	AddPropBt = new wxButton(this, ID_BUTTON10, _("Ajouter"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
	FlexGridSizer5->Add(AddPropBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer7 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Valeurs sp�ciales"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer7->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TreeCtrl1 = new wxTreeCtrl(this, ID_TREECTRL2, wxDefaultPosition, wxSize(195,177), wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL2"));
	FlexGridSizer7->Add(TreeCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(this, ID_BUTTON7, _("Ajouter"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	FlexGridSizer7->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticBoxSizer1->Add(FlexGridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
	FlexGridSizer2->Add(StaticLine2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	OkBt = new wxButton(this, ID_BUTTON2, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer3->Add(OkBt, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	AnnulerBt = new wxButton(this, ID_BUTTON1, _("Annuler"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(AnnulerBt, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	Center();

	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditTexte::OnInsertBtClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditTexte::OnOkBtClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditTexte::OnAnnulerBtClick);
	//*)

	TexteEdit->ChangeValue(texte);
}

EditTexte::~EditTexte()
{
	//(*Destroy(EditTexte)
	//*)
}


void EditTexte::OnAnnulerBtClick(wxCommandEvent& event)
{
    EndModal(0);
}

void EditTexte::OnOkBtClick(wxCommandEvent& event)
{
    texteFinal = string(TexteEdit->GetValue().mb_str());

    GDExpression expressionTest(texteFinal);
    if ( !expressionTest.PrepareForTextEvaluationOnly(game, scene) )
    {
        wxLogWarning(wxString(expressionTest.GetFirstErrorDuringPreprocessingText()));
    }

    EndModal(1);
}


////////////////////////////////////////////////////////////
/// Insertion d'une expression
///
/// Utilise l'�diteur d'expressions
////////////////////////////////////////////////////////////
void EditTexte::OnInsertBtClick(wxCommandEvent& event)
{
    EditExpression dialog(this, "", game, scene, true, mainObjectsName);
    dialog.ShowModal();

    TexteEdit->WriteText("CAL\""+dialog.expression+"\"");
}

////////////////////////////////////////////////////////////
/// Insertion d'une variable d'un objet
////////////////////////////////////////////////////////////
void EditTexte::OnExpressionTxtEditClick(wxCommandEvent& event)
{
    string nom = static_cast<string> (wxGetTextFromUser(_("Entrez le nom de l'objet"), _("Nom de l'objet"), "", this));
    if ( nom == "" ) return;
    string var = static_cast<string> (wxGetTextFromUser(_("Entrez le nom de la variable"), _("Nom de la variable"), "", this));
    if ( var == "" ) return;

    TexteEdit->WriteText("TXT\"OBJ("+nom+"["+var+"])\"");
}

////////////////////////////////////////////////////////////
/// Insertion d'une variable globale
////////////////////////////////////////////////////////////
void EditTexte::OnVarGlobalTxtEditClick(wxCommandEvent& event)
{
    string var = static_cast<string> (wxGetTextFromUser(_("Entrez le nom de la variable"), _("Nom de la variable globale"), "", this));
    if ( var == "" ) return;

    TexteEdit->WriteText("TXT\"GBL("+var+"[])\"");
}

////////////////////////////////////////////////////////////
/// Insertion d'une variable d'une sc�ne
////////////////////////////////////////////////////////////
void EditTexte::OnVarSceneTxtEditClick(wxCommandEvent& event)
{
    string var = static_cast<string> (wxGetTextFromUser(_("Entrez le nom de la variable"), _("Nom de la variable de la sc�ne"), "", this));
    if ( var == "" ) return;

    TexteEdit->WriteText("TXT\"VAL("+var+"[])\"");
}

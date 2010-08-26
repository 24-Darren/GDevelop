/**
 *  Game Develop
 *  2008-2010 Florian Rival (Florian.Rival@gmail.com)
 */

#if defined(GDE)
#include "GDL/PropImage.h"

//(*InternalHeaders(PropImage)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/dcbuffer.h>
#include <wx/filedlg.h>
#include "GDL/BitmapGUIManager.h"
#include "GDL/CommonTools.h"

//(*IdInit(PropImage)
const long PropImage::ID_STATICTEXT1 = wxNewId();
const long PropImage::ID_TEXTCTRL1 = wxNewId();
const long PropImage::ID_STATICTEXT2 = wxNewId();
const long PropImage::ID_TEXTCTRL2 = wxNewId();
const long PropImage::ID_BUTTON3 = wxNewId();
const long PropImage::ID_CHECKBOX1 = wxNewId();
const long PropImage::ID_CHECKBOX2 = wxNewId();
const long PropImage::ID_STATICTEXT4 = wxNewId();
const long PropImage::ID_STATICTEXT6 = wxNewId();
const long PropImage::ID_STATICTEXT5 = wxNewId();
const long PropImage::ID_STATICTEXT3 = wxNewId();
const long PropImage::ID_BUTTON1 = wxNewId();
const long PropImage::ID_BUTTON2 = wxNewId();
const long PropImage::ID_PANEL1 = wxNewId();
const long PropImage::ID_SCROLLBAR1 = wxNewId();
const long PropImage::ID_SCROLLBAR2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PropImage,wxDialog)
	//(*EventTable(PropImage)
	//*)
	EVT_SIZE    (PropImage::OnSize)
END_EVENT_TABLE()

PropImage::PropImage(wxWindow* parent, Image & pImage) :
image(pImage)
{
	//(*Initialize(PropImage)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	
	Create(parent, wxID_ANY, _("Modifier les propri�t�s de l\'image"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(1);
	FlexGridSizer1->AddGrowableRow(0);
	FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Propri�t�s de l\'image"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Nom :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer3->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	NomEdit = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(150,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer3->Add(NomEdit, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Fichier :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer3->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 0);
	FichierEdit = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(192,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer7->Add(FichierEdit, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BrowseBt = new wxButton(this, ID_BUTTON3, _("Parcourir"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer7->Add(BrowseBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	LissageCheck = new wxCheckBox(this, ID_CHECKBOX1, _("Lisser l\'image"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	LissageCheck->SetValue(false);
	LissageCheck->SetToolTip(_("Activ� par d�faut, permet de \"lisser\" l\'image, de fa�on � moins voir les pixels."));
	FlexGridSizer3->Add(LissageCheck, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	alwaysLoadedCheck = new wxCheckBox(this, ID_CHECKBOX2, _("Toujours conserver l\'image en m�moire"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	alwaysLoadedCheck->SetValue(false);
	alwaysLoadedCheck->SetToolTip(_("Laisser l\'image en m�moire, afin d\'�viter par exemple de la recharger si elle n\'est pas utilis� continuellement par un objet, mais utilis�e dans des actions de dessin."));
	FlexGridSizer3->Add(alwaysLoadedCheck, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Informations sur l\'image"));
	FlexGridSizer8 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Largeur :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer8->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	widthTxt = new wxStaticText(this, ID_STATICTEXT6, _("0 pixels"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer8->Add(widthTxt, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Hauteur :"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer8->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	heightTxt = new wxStaticText(this, ID_STATICTEXT3, _("0 pixels"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer8->Add(heightTxt, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	OkBt = new wxButton(this, ID_BUTTON1, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(OkBt, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	AnnulerBt = new wxButton(this, ID_BUTTON2, _("Annuler"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer2->Add(AnnulerBt, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer1->Add(FlexGridSizer4, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
	FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer5->AddGrowableCol(0);
	FlexGridSizer5->AddGrowableRow(0);
	FlexGridSizer6 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer6->AddGrowableCol(0);
	FlexGridSizer6->AddGrowableRow(0);
	apercuPanel = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(285,255), wxSUNKEN_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer6->Add(apercuPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	scrollHeight = new wxScrollBar(this, ID_SCROLLBAR1, wxDefaultPosition, wxDefaultSize, wxSB_VERTICAL, wxDefaultValidator, _T("ID_SCROLLBAR1"));
	scrollHeight->SetScrollbar(0, 1, 10, 1);
	FlexGridSizer6->Add(scrollHeight, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	scrollWidth = new wxScrollBar(this, ID_SCROLLBAR2, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL, wxDefaultValidator, _T("ID_SCROLLBAR2"));
	scrollWidth->SetScrollbar(0, 1, 10, 1);
	FlexGridSizer6->Add(scrollWidth, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer5->Add(FlexGridSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer1->Add(FlexGridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	
	Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&PropImage::OnFichierEditText);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PropImage::OnOkBtClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PropImage::OnAnnulerBtClick);
	apercuPanel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&PropImage::OnapercuPanelPaint,0,this);
	Connect(ID_SCROLLBAR1,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&PropImage::OnscrollHeightScroll);
	Connect(ID_SCROLLBAR1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&PropImage::OnscrollHeightScroll);
	Connect(ID_SCROLLBAR2,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&PropImage::OnscrollWidthScroll);
	Connect(ID_SCROLLBAR2,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&PropImage::OnscrollWidthScroll);
	//*)

    LissageCheck->SetValue(image.smooth);
    NomEdit->ChangeValue(image.nom);
    FichierEdit->ChangeValue(image.file);
    alwaysLoadedCheck->SetValue(image.alwaysLoaded);
}

PropImage::~PropImage()
{
	//(*Destroy(PropImage)
	//*)
}


void PropImage::OnOkBtClick(wxCommandEvent& event)
{
    image.smooth = LissageCheck->GetValue();
    image.nom = NomEdit->GetValue();
    image.file = FichierEdit->GetValue();
    image.alwaysLoaded = alwaysLoadedCheck->GetValue();

    EndModal(1);
}

void PropImage::OnAnnulerBtClick(wxCommandEvent& event)
{
    EndModal(0);
}

void PropImage::OnSize(wxSizeEvent& event)
{
    Layout();
    apercuPanel->Refresh();
    apercuPanel->Update(); //Imm�diatement
}

void PropImage::OnFichierEditText(wxCommandEvent& event)
{
    apercuPanel->Refresh();
    apercuPanel->Update(); //Imm�diatement
}

////////////////////////////////////////////////////////////
/// Aper�u de l'image
////////////////////////////////////////////////////////////
void PropImage::OnapercuPanelPaint(wxPaintEvent& event)
{
    wxPaintDC dc( apercuPanel ); //Cr�ation obligatoire du wxBufferedPaintDC
    wxSize size = apercuPanel->GetSize();

    BitmapGUIManager * bitmapGUIManager = BitmapGUIManager::getInstance();

    //Fond en damier
    dc.SetBrush(bitmapGUIManager->transparentBg);
    dc.DrawRectangle(0,0, size.GetWidth(), size.GetHeight());

    if ( !wxFileExists(FichierEdit->GetValue()) )
        return;

    wxBitmap bmp( FichierEdit->GetValue(), wxBITMAP_TYPE_ANY);
    widthTxt->SetLabel(ToString(bmp.GetWidth()) + " pixels");
    heightTxt->SetLabel(ToString(bmp.GetHeight()) + " pixels");

    //Mise � jour des scrollbars
    scrollWidth->SetScrollbar(scrollWidth->GetThumbPosition(),
                               size.GetWidth(),
                               bmp.GetWidth(),
                               size.GetWidth());

    scrollHeight->SetScrollbar(scrollHeight->GetThumbPosition(),
                               size.GetHeight(),
                               bmp.GetHeight(),
                               size.GetHeight());

    //Affichage au centre de l'image
    dc.DrawBitmap(bmp,
                  (size.GetWidth() - bmp.GetWidth() - scrollWidth->GetThumbPosition()) / 2 ,
                  (size.GetHeight() - bmp.GetHeight() - scrollHeight->GetThumbPosition()) / 2,
                  true /* use mask */);
}

void PropImage::OnscrollWidthScroll(wxScrollEvent& event)
{
    apercuPanel->Refresh();
    apercuPanel->Update(); //Imm�diatement
}

void PropImage::OnscrollHeightScroll(wxScrollEvent& event)
{
    apercuPanel->Refresh();
    apercuPanel->Update(); //Imm�diatement
}


////////////////////////////////////////////////////////////
/// Parcourir pour modifier l'image
////////////////////////////////////////////////////////////
void PropImage::OnBrowseBtClick(wxCommandEvent& event)
{
    wxFileDialog FileDialog( this, "Choisissez l'image", "", "", "Images support�es|*.bmp;*.gif;*.jpg;*.png;*.tga;*.dds|Tous les fichiers|*.*", wxFD_MULTIPLE );

    if ( FileDialog.ShowModal() == wxID_OK )
    {
        FichierEdit->SetValue(FileDialog.GetPath());

        apercuPanel->Refresh();
        apercuPanel->Update(); //Imm�diatement
    }
}
#endif

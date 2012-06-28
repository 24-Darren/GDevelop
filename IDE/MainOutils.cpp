#include "MainFrame.h"
#include "mp3ogg.h"
#include "ImportImage.h"

////////////////////////////////////////////////////////////
/// Encoder fichier mp3 en ogg
////////////////////////////////////////////////////////////
void MainFrame::OnMenuItem23Selected(wxCommandEvent& event)
{
    mp3ogg dialog(this);
    dialog.ShowModal();
}

////////////////////////////////////////////////////////////
/// D�composer un GIF en plusieurs images
////////////////////////////////////////////////////////////
void MainFrame::OnDecomposeGIFSelected(wxCommandEvent& event)
{
    ImportImage dialog(this, 0);
    dialog.ShowModal();
}

////////////////////////////////////////////////////////////
/// D�composer une feuille de sprite de personnage RPG Maker en plusieurs images
////////////////////////////////////////////////////////////
void MainFrame::OnDecomposeRPGSelected(wxCommandEvent& event)
{
    ImportImage dialog(this, 1);
    dialog.ShowModal();
}

////////////////////////////////////////////////////////////
/// D�composer une feuille de sprite g�n�rale en plusieurs images
////////////////////////////////////////////////////////////
void MainFrame::OnDecomposeSSSelected(wxCommandEvent& event)
{
    ImportImage dialog(this, 2);
    dialog.ShowModal();
}

void MainFrame::OnRibbonDecomposerDropDownClicked(wxRibbonButtonBarEvent& evt)
{
    evt.PopupMenu(&decomposerContextMenu);
}

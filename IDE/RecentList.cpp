#include "RecentList.h"

RecentList::RecentList()
{
    p_iMax=0;
    sEntry.Clear();
    p_Menu=NULL;
}

RecentList::~RecentList()
{

}

void RecentList::Append(const wxString &sValue)
{
    wxString sTxt;
    if (((int)sEntry.Count()<p_iMax)&&(sValue!=wxEmptyString))
    {
        sEntry.Add(sValue);
        UpdateMenu();
    }
}

void RecentList::SetLastUsed(const wxString &sValue)
{
    if (sValue==wxEmptyString) return;
    wxString pSVal=sValue;
    /*if (pSVal.Last()!='\\') pSVal+='\\';*/
    int idx=sEntry.Index(pSVal,FALSE);
    wxString sTxt;
    // si l'entr�e existe d�j� dans la liste
    if (idx!=wxNOT_FOUND)
    {
        // Si l'entr�e est d�j� au d�but de la liste,
        // alors, il n'y a rien � faire => On sort
        if (idx==0) return;
        // sinon, on enl�ve l'entr�e de son emplacement actuel
        sEntry.RemoveAt(idx);
    }
    // On insert l'entr�e au d�but de celle-ci
    sEntry.Insert(pSVal,0);
    // Si on a d�pass� le nombre maxi d'entr�es voulues, alors, on enl�ve la derni�re
    while ((int)sEntry.Count()>p_iMax)
    {
        sEntry.RemoveAt(sEntry.Count()-1);
    }
    // Mise � jour �ventuelle du menu associ�
    UpdateMenu();
}

int RecentList::GetEntryCount()
{
    return (int)sEntry.Count();
}

int RecentList::GetMaxEntries()
{
    return p_iMax;
}

wxString RecentList::GetEntry(int Index)
{
    if (Index>(p_iMax-1)) return wxEmptyString;
    if (Index>(int)(sEntry.Count()-1)) return wxEmptyString;
    return sEntry[Index];
}

void RecentList::SetMaxEntries(int iNbEntries)
{
    if ((iNbEntries==0)||(iNbEntries==p_iMax)) return;
    // On ne peut mettre que 9 entr�es maximum, sinon, il faut passer par des
    // IDs personnalis�s
    if (iNbEntries>9) return;
    // Si on veut diminuer le nombre maximum d'entr�es
    if (iNbEntries<p_iMax)
    {
        // on supprime la derni�re entr�e jusqu'� obtenir
        // le nombre correct de valeurs
        while(iNbEntries<(int)sEntry.Count())
        {
            sEntry.RemoveAt(sEntry.Count()-1);
        }
    }
    // Dans les deux cas, on d�finit le nouveau nombre maximum d'entr�es dans la liste
    p_iMax=iNbEntries;
    // et on met � jour le menu
    UpdateMenu();
}

void RecentList::SetAssociatedMenu(wxMenu *Menu)
{
    p_Menu=Menu;
    if (p_Menu==NULL) return;
    if ((int)Menu->GetMenuItemCount()>0) return;
    int imax;
    wxString sTxt;
    imax=p_iMax;
    if ((int)sEntry.Count()<imax) imax=sEntry.Count();
    // On cr�e la premi�re entr�e du menu ici
    p_Menu->Append(wxID_FILE1,_("Liste vide"));
    p_Menu->Enable(wxID_FILE1,false);
    UpdateMenu();
}

void RecentList::UpdateMenu()
{
    int i,imax,immax;
    wxString sTxt;
    if (p_Menu==NULL) return;
    immax=p_Menu->GetMenuItemCount();
    imax=sEntry.Count();
    if (immax!=imax) // Si on n'a pas le m�me nombre d'entr�es que de menuitems
    {
        // il y a un cas particulier : 1 menuitem et 0 entr�es dans la liste
        // c'est normal, l'item est "Liste Vide"
        if ((immax==1)&&(imax==0)) return;
        // Si on a plus de menuitems que d'entr�es dans la liste, ce qui peut
        // se produire lors d'un changement du nombre maxi d'entr�es
        while(immax>imax)
        {
            p_Menu->Destroy(wxID_FILE1+immax-1);
            immax--;
        }
        // Si on a moins de menuitems que d'entr�es dans la liste
        while(immax<imax)
        {
            // On cr�e un menuitem avec un texte temporaire
            p_Menu->Append(wxID_FILE1+immax,_T("Recent Entry"));
            immax++;
        }
    }
    // Mise � jour des entr�es du menu
    for (i=0;i<immax;i++)
    {
        sTxt.Printf(_("Ouvrir le fichier \"%s\""),sEntry[i].c_str());
        p_Menu->SetLabel(wxID_FILE1+i,sEntry[i]);
        p_Menu->SetHelpString(wxID_FILE1+i,sTxt);
    }
    // Activation de la premi�re entr�e, si ce n'�tais pas d�j� fait
    p_Menu->Enable(wxID_FILE1,true);
}

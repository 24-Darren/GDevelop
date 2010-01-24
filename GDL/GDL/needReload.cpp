#if defined(GDE)
#include <string>
#include <vector>
#include <algorithm>  // For find

#include "GDL/needReload.h"
using namespace std;

needReload::needReload() :
imagesMustBeReload(false)
{
    //ctor
}

needReload::~needReload()
{
    //dtor
}

void needReload::SetImagesMustBeReloaded()
{
    imagesMustBeReload = true;
    SetAllScenesMustBeReloaded();
}
void needReload::SetImagesAreUpToDate()
{
    imagesMustBeReload = false;
}
bool needReload::GetImagesMustBeReloaded()
{
    return imagesMustBeReload;
}

void needReload::SetAllScenesMustBeReloaded()
{
    sceneIsUpToDate.clear(); //Toutes les sc�nes doivent recharger
}

void needReload::SetASceneMustBeReloaded( int nb )
{
    //On enl�ve la sc�ne des sc�nes � jour
    if ( find(sceneIsUpToDate.begin(), sceneIsUpToDate.end(), nb) != sceneIsUpToDate.end() )
        sceneIsUpToDate.erase(find(sceneIsUpToDate.begin(), sceneIsUpToDate.end(), nb));
}

void needReload::SetASceneIsUpToDate( int nb )
{
    //On ajoute la sc�ne aux sc�nes � jour
    if ( find(sceneIsUpToDate.begin(), sceneIsUpToDate.end(), nb) == sceneIsUpToDate.end() )
        sceneIsUpToDate.push_back(nb);
}

bool needReload::MustTheSceneBeReloaded(int nb)
{
    //Si la sc�ne n'est pas dans la liste des sc�nes � jour,
    //elle doit �tre recharg�e.
    if ( find(sceneIsUpToDate.begin(), sceneIsUpToDate.end(), nb) == sceneIsUpToDate.end() )
        return true;

    return false;
}
#endif
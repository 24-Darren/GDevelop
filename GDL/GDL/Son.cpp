/**
 * Game Develop
 *    Player
 *
 *  Par Florian "4ian" Rival
 *
 */
/**
 *
 *
 *  Classe g�rant le son ( pas les musiques ).
 *  Sert essentiellement � relier un sf::SoundBuffer et son sf::Sound associ�
 *  ( L'un ne marchant pas sans l'autre )
 */

#include "GDL/Son.h"
#include <SFML/Audio.hpp>
#include "GDL/MemTrace.h"
#include "GDL/RessourcesLoader.h"
#include <string>
#include <vector>
#include <iostream>
#include "GDL/SoundManager.h"

using namespace std;


Son::Son(string pFile) :
file(pFile),
volume(100)
{
    RessourcesLoader * ressourcesLoader = RessourcesLoader::getInstance();

    buffer = ressourcesLoader->LoadSoundBuffer(file);
    sound.SetBuffer(buffer);
}

Son::Son() :
volume(100)
{
    sound.SetBuffer(buffer);
}

Son::~Son()
{
    //dtor
}

Son::Son(const Son & copy) :
file(copy.file)
{
    RessourcesLoader * ressourcesLoader = RessourcesLoader::getInstance();

    buffer = ressourcesLoader->LoadSoundBuffer(file);
    sound.SetBuffer(buffer);
}

////////////////////////////////////////////////////////////
/// Mise � jour du volume fictif du son
////////////////////////////////////////////////////////////
void Son::SetVolume(float volume_)
{
    volume = volume_;
    if ( volume < 0 ) volume = 0;
    if ( volume > 100 ) volume = 100;

    UpdateVolume(); //Mise � jour du volume r�el.
}

////////////////////////////////////////////////////////////
/// Mise � jour du volume r�el du son en fonction du volume
/// global et du son.
////////////////////////////////////////////////////////////
void Son::UpdateVolume()
{
    SoundManager * soundManager = SoundManager::getInstance();

    sound.SetVolume(volume*soundManager->GetGlobalVolume()/100.f);
}

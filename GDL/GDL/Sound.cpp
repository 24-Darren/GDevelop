/** \file
 *  Game Develop
 *  2008-2012 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/Sound.h"
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "GDL/RessourcesLoader.h"
#include "GDL/SoundManager.h"

using namespace std;


Sound::Sound(string pFile) :
file(pFile),
volume(100)
{
    RessourcesLoader * ressourcesLoader = RessourcesLoader::GetInstance();

    buffer = ressourcesLoader->LoadSoundBuffer(file);
    sound.SetBuffer(buffer);
}

Sound::Sound() :
volume(100)
{
    sound.SetBuffer(buffer);
}

Sound::~Sound()
{
    //dtor
}

Sound::Sound(const Sound & copy) :
file(copy.file)
{
    RessourcesLoader * ressourcesLoader = RessourcesLoader::GetInstance();

    buffer = ressourcesLoader->LoadSoundBuffer(file);
    sound.SetBuffer(buffer);
}

////////////////////////////////////////////////////////////
/// Mise � jour du volume fictif du son
////////////////////////////////////////////////////////////
void Sound::SetVolume(float volume_)
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
void Sound::UpdateVolume()
{
    SoundManager * soundManager = SoundManager::GetInstance();

    sound.SetVolume(volume*soundManager->GetGlobalVolume()/100.f);
}


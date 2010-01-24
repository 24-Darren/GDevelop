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
 *  SoundManager : Classe unique qui g�re les sons et musiques
 *  Pour les sons : utilise un tableau pour les channels
 *  Pour les sons sans channels : utilise un vector de pointeur, pour �viter des coupures.
 *  Idem pour les musiques, sauf que le vector utilise aussi des pointeurs car
 *  les musiques sont non-copyable.
 */

#include "GDL/SoundManager.h"
#include "GDL/Music.h"
#include "GDL/Son.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

SoundManager *SoundManager::_singleton = NULL;

////////////////////////////////////////////////////////////
/// Constructeur
///
/// Initialise en particulier les sons et musiques sur canaux
////////////////////////////////////////////////////////////
SoundManager::SoundManager() :
globalVolume(100)
{
    for (unsigned int i = 0;i<MAX_CANAUX_SON;++i)
    {
        Son * son = new Son;
        soundsChannel.push_back(son);
    }
    for (unsigned int i = 0;i<MAX_CANAUX_SON;++i)
    {
        Music * music = new Music;
        musicsChannel.push_back(music);
    }
}

////////////////////////////////////////////////////////////
/// Destructeur
///
/// Supprime les sons et musiques d�tenus par le soundManager
/// ( c'est � dire les sons et musiques sur les canaux )
////////////////////////////////////////////////////////////
SoundManager::~SoundManager()
{
    for (unsigned int channel = 0;channel<MAX_CANAUX_SON;++channel)
    {
        if ( soundsChannel.at(channel) != NULL )
            delete soundsChannel.at(channel);
    }
    for (unsigned int channel = 0;channel<MAX_CANAUX_SON;++channel)
    {
        if ( musicsChannel.at(channel) != NULL )
            delete musicsChannel.at(channel);
    }
}

////////////////////////////////////////////////////////////
/// R�cup�ration d'une musiques sur un canal
///
/// Pour pouvoir ensuite agir dessus ( arr�t, pause... )
////////////////////////////////////////////////////////////
Music * SoundManager::GetMusicOnChannel(int channel)
{
    if ( channel >= 0 && static_cast<unsigned>(channel) < musicsChannel.size())
        return musicsChannel.at(channel);

    cout << "return null";
    return NULL;
}

////////////////////////////////////////////////////////////
/// Assignement d'une musique sur un canal
///
/// La musique appartient ensuite au soundManager, qui s'occupera de
/// la d�truire.
////////////////////////////////////////////////////////////
void SoundManager::SetMusicOnChannel(int channel, Music * music)
{
    if ( channel >= 0 && static_cast<unsigned>(channel) < musicsChannel.size())
    {
        //On supprime l'ancien son
        if ( musicsChannel.at(channel) != NULL )
            delete musicsChannel.at(channel);

        //On assigne le nouveau
        musicsChannel.at(channel) = music;
    }
}

////////////////////////////////////////////////////////////
/// Assignement d'un son sur un canal
///
/// Le son appartient ensuite au soundManager, qui s'occupera de
/// le d�truire.
////////////////////////////////////////////////////////////
void SoundManager::SetSoundOnChannel(int channel, Son * son)
{
    if ( channel >= 0 && static_cast<unsigned>(channel) < soundsChannel.size())
    {
        //On supprime l'ancien son
        if ( soundsChannel.at(channel) != NULL )
            delete soundsChannel.at(channel);

        //On assigne le nouveau
        soundsChannel.at(channel) = son;
    }
}

////////////////////////////////////////////////////////////
/// R�cup�ration d'un son sur un canal
///
/// Pour pouvoir ensuite agir dessus ( arr�t, pause... )
////////////////////////////////////////////////////////////
Son * SoundManager::GetSoundOnChannel(int channel)
{
    if ( channel >= 0 && static_cast<unsigned>(channel) < soundsChannel.size())
        return soundsChannel.at(channel);

    cout << "return null";
    return NULL;
}

////////////////////////////////////////////////////////////
/// Modifier le volume global
////////////////////////////////////////////////////////////
void SoundManager::SetGlobalVolume(float volume)
{
    globalVolume = volume;

    if ( globalVolume < 0.0 )
        globalVolume = 0.0;

    if ( globalVolume > 100.0 )
        globalVolume = 100.0;

    //Mise � jour des volumes des sons
    for (unsigned int i =0;i<soundsChannel.size();++i)
    {
        if ( soundsChannel[i] != NULL )
            soundsChannel[i]->UpdateVolume();
    }
    for (unsigned int i =0;i<musicsChannel.size();++i)
    {
        if ( musicsChannel[i] != NULL )
            musicsChannel[i]->UpdateVolume();
    }
    for (unsigned int i =0;i<sounds.size();++i)
    {
        if ( sounds[i] != NULL )
            sounds[i]->UpdateVolume();
    }
    for (unsigned int i =0;i<musics.size();++i)
    {
        if ( musics[i] != NULL )
            musics[i]->UpdateVolume();
    }
}

#include "GDL/AudioExtension.h"
#include "GDL/cMusic.h"
#include "GDL/aMusic.h"
#include "GDL/ResourcesMergingHelper.h"
#include "GDL/Instruction.h"
#include "GDL/SoundManager.h"
#include "GDL/eFreeFunctions.h"
#include <iostream>

AudioExtension::AudioExtension()
{
    DECLARE_THE_EXTENSION("BuiltinAudio",
                          _T("Audio"),
                          _T("Extension audio integr�e en standard"),
                          "Compil Games",
                          "Freeware")

    DECLARE_ACTION("PlaySoundCanal",
                   _T("Jouer un son sur un canal"),
                   _T("Joue un son ( court fichier audio ) sur un canal pr�cis,\npour pouvoir ensuite interagir avec."),
                   _T("Jouer le son _PARAM0_ sur le canal _PARAM1_"),
                   _T("Sons"),
                   "res/actions/son24.png",
                   "res/actions/son.png",
                   &ActPlaySoundCanal);

        DECLARE_PARAMETER("soundfile", _T("Fichier audio"), false, "")
        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("yesorno", _T("Boucler le son ?"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Volume ( De 0 � 100, 100 par d�faut )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Pitch ( Vitesse ) ( 1 par d�faut )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("StopSoundCanal",
                   _T("Arr�ter le son sur un canal"),
                   _T("Arr�ter le son jou� sur le canal indiqu�."),
                   _T("Arr�ter le son du canal _PARAM0_"),
                   _T("Sons"),
                   "res/actions/son24.png",
                   "res/actions/son.png",
                   &ActStopSoundCanal);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("PauseSoundCanal",
                   _T("Mettre en pause le son d'un canal"),
                   _T("Mettre en pause le son jou� sur le canal indiqu�."),
                   _T("Mettre en pause le son du canal _PARAM0_"),
                   _T("Sons"),
                   "res/actions/son24.png",
                   "res/actions/son.png",
                   &ActPauseSoundCanal);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("RePlaySoundCanal",
                   _T("Jouer le son d'un canal"),
                   _T("(Re)jouer le son du canal."),
                   _T("Jouer le son du canal _PARAM0_"),
                   _T("Sons"),
                   "res/actions/son24.png",
                   "res/actions/son.png",
                   &ActRePlaySoundCanal);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("PlayMusicCanal",
                   _T("Jouer une musique sur un canal"),
                   _T("Joue une musique sur un canal pr�cis,\npour pouvoir ensuite interagir avec."),
                   _T("Jouer la musique _PARAM0_ sur le canal _PARAM1_"),
                   _T("Musiques"),
                   "res/actions/music24.png",
                   "res/actions/music.png",
                   &ActPlayMusicCanal);

        DECLARE_PARAMETER("musicfile", _T("Fichier audio"), false, "")
        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("yesorno", _T("Boucler le son ?"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Volume ( De 0 � 100, 100 par d�faut )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Pitch ( Vitesse ) ( 1 par d�faut )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("StopMusicCanal",
                   _T("Arr�ter la musique sur un canal"),
                   _T("Arr�ter la musique jou�e sur le canal indiqu�."),
                   _T("Arr�ter la musique du canal _PARAM0_"),
                   _T("Musiques"),
                   "res/actions/music24.png",
                   "res/actions/music.png",
                   &ActStopMusicCanal);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("PauseMusicCanal",
                   _T("Mettre en pause la musique d'un canal"),
                   _T("Mettre en pause la musique jou�e sur le canal indiqu�."),
                   _T("Mettre en pause la musique du canal _PARAM0_"),
                   _T("Musiques"),
                   "res/actions/music24.png",
                   "res/actions/music.png",
                   &ActPauseMusicCanal);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("RePlayMusicCanal",
                   _T("Jouer la musique d'un canal"),
                   _T("(Re)jouer la musique du canal."),
                   _T("Jouer la musique du canal _PARAM0_"),
                   _T("Musiques"),
                   "res/actions/music24.png",
                   "res/actions/music.png",
                   &ActRePlayMusicCanal);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("ModVolumeSoundCanal",
                   _T("Volume d'un son sur un canal"),
                   _T("Cette action modifie le volume du son sur le canal sp�cifi�. Le volume est compris entre 0 et 100."),
                   _T("Faire _PARAM2__PARAM1_ au volume du son sur le canal  _PARAM0_"),
                   _T("Volume sonore"),
                   "res/actions/sonVolume24.png",
                   "res/actions/sonVolume.png",
                   &ActModVolumeSoundCanal);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Valeur"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe de la modification"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("ModVolumeMusicCanal",
                   _T("Volume de la musique d'un canal"),
                   _T("Cette action modifie le volume de la musique sur le canal sp�cifi�. Le volume est compris entre 0 et 100."),
                   _T("Faire _PARAM2__PARAM1_ au volume de la musique du canal  _PARAM0_"),
                   _T("Volume sonore"),
                   "res/actions/sonVolume24.png",
                   "res/actions/sonVolume.png",
                   &ActModVolumeMusicCanal);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Valeur"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe de la modification"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("ModGlobalVolume",
                   _T("Volume global du jeu"),
                   _T("Cette action modifie le volume sonore global du jeu. Le volume est compris entre 0 et 100."),
                   _T("Faire _PARAM1__PARAM0_ au volume sonore global"),
                   _T("Volume sonore"),
                   "res/actions/volume24.png",
                   "res/actions/volume.png",
                   &ActModGlobalVolume);

        DECLARE_PARAMETER("expression", _T("Valeur"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe de la modification"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("ModPitchSoundChannel",
                   _T("Pitch d'un son sur un canal"),
                   _T("Cette action modifie le pitch ( vitesse ) du son d'un canal.\nUn pitch de 1 indique une vitesse normale."),
                   _T("Faire _PARAM2__PARAM1_ au pitch du son sur le canal _PARAM0_"),
                   _T("Sons"),
                   "res/actions/son24.png",
                   "res/actions/son.png",
                   &ActModPitchSoundChannel);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Valeur"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe de la modification"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("ModPitchMusicChannel",
                   _T("Pitch de la musique d'un canal"),
                   _T("Cette action modifie le pitch de la musique sur un canal.\nUn pitch de 1 indique une vitesse normale."),
                   _T("Faire _PARAM2__PARAM1_ au pitch de la musique du canal _PARAM0_"),
                   _T("Musiques"),
                   "res/actions/music24.png",
                   "res/actions/music.png",
                   &ActModPitchMusicChannel);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Valeur"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe de la modification"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("ModPlayingOffsetSoundChannel",
                   _T("Position de lecture d'un son sur un canal"),
                   _T("Cette action modifie la position de lecture du son d'un canal."),
                   _T("Faire _PARAM2__PARAM1_s � la position de lecture du son sur le canal _PARAM0_"),
                   _T("Sons"),
                   "res/actions/son24.png",
                   "res/actions/son.png",
                   &ActModPlayingOffsetSoundChannel);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Valeur"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe de la modification"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("ModPlayingOffsetMusicChannel",
                   _T("Position de lecture de la musique d'un canal"),
                   _T("Cette action modifie la position de lecture de la musique sur un canal."),
                   _T("Faire _PARAM2__PARAM1_s � la position de lecture de la musique du canal _PARAM0_"),
                   _T("Musiques"),
                   "res/actions/music24.png",
                   "res/actions/music.png",
                   &ActModPlayingOffsetMusicChannel);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Valeur"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe de la modification"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("PlaySound",
                   _T("Jouer un son"),
                   _T("Joue un son."),
                   _T("Jouer le son _PARAM0_"),
                   _T("Sons"),
                   "res/actions/son24.png",
                   "res/actions/son.png",
                   &ActPlaySound);

        DECLARE_PARAMETER("soundfile", _T("Fichier audio"), false, "")
        DECLARE_PARAMETER_OPTIONAL("yesorno", _T("Boucler le son ?"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Volume ( De 0 � 100, 100 par d�faut )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Pitch ( Vitesse ) ( 1 par d�faut )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_ACTION("PlayMusic",
                   _T("Jouer une musique"),
                   _T("Joue une musique."),
                   _T("Jouer la musique _PARAM0_"),
                   _T("Musiques"),
                   "res/actions/music24.png",
                   "res/actions/music.png",
                   &ActPlayMusic);

        DECLARE_PARAMETER("musicfile", _T("Fichier audio"), false, "")
        DECLARE_PARAMETER_OPTIONAL("yesorno", _T("Boucler le son ?"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Volume ( De 0 � 100, 100 par d�faut )"), false, "")
        DECLARE_PARAMETER_OPTIONAL("expression", _T("Pitch ( Vitesse ) ( 1 par d�faut )"), false, "")

    DECLARE_END_ACTION()

    DECLARE_CONDITION("MusicPlaying",
                   _T("Une musique est entrain d'�tre jou�e"),
                   _T("Teste si la musique sur le canal indiqu� est entrain d'�tre jou�e."),
                   _T("La musique sur le canal _PARAM0_ est entrain d'�tre jou�e"),
                   _T("Musiques"),
                   "res/conditions/musicplaying24.png",
                   "res/conditions/musicplaying.png",
                   &CondMusicPlaying);

        DECLARE_PARAMETER("expression", _T("Canal"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("MusicPaused",
                   _T("Une musique est en pause"),
                   _T("Teste si la musique sur le canal indiqu� est en pause."),
                   _T("La musique sur le canal _PARAM0_ est en pause"),
                   _T("Musiques"),
                   "res/conditions/musicpaused24.png",
                   "res/conditions/musicpaused.png",
                   &CondMusicPaused);

        DECLARE_PARAMETER("expression", _T("Canal"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("MusicStopped",
                   _T("Une musique est arr�t�e"),
                   _T("Teste si la musique sur le canal indiqu� est arr�t�e."),
                   _T("La musique sur le canal _PARAM0_ est arr�t�e"),
                   _T("Musiques"),
                   "res/conditions/musicstopped24.png",
                   "res/conditions/musicstopped.png",
                   &CondMusicStopped);

        DECLARE_PARAMETER("expression", _T("Canal"), false, "")

    DECLARE_END_CONDITION()
    DECLARE_CONDITION("SoundPlaying",
                   _T("Un son est entrain d'�tre jou�e"),
                   _T("Teste si le son sur le canal indiqu� est entrain d'�tre jou�."),
                   _T("Le son sur le canal _PARAM0_ est entrain d'�tre jou�"),
                   _T("Sons"),
                   "res/conditions/sonplaying24.png",
                   "res/conditions/sonplaying.png",
                   &CondSoundPlaying);

        DECLARE_PARAMETER("expression", _T("Canal"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("SoundPaused",
                   _T("Un son est en pause"),
                   _T("Teste si le son sur le canal indiqu� est en pause."),
                   _T("Le son sur le canal _PARAM0_ est en pause"),
                   _T("Sons"),
                   "res/conditions/sonpaused24.png",
                   "res/conditions/sonpaused.png",
                   &CondSoundPaused);

        DECLARE_PARAMETER("expression", _T("Canal"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("SoundStopped",
                   _T("Un son est arr�t�e"),
                   _T("Teste si le son sur le canal indiqu� est arr�t�."),
                   _T("Le son sur le canal _PARAM0_ est arr�t�"),
                   _T("Sons"),
                   "res/conditions/sonstopped24.png",
                   "res/conditions/sonstopped.png",
                   &CondSoundStopped);

        DECLARE_PARAMETER("expression", _T("Canal"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("SoundCanalVolume",
                   _T("Volume d'un son sur un canal"),
                   _T("Teste le volume du son sur le canal indiqu�. Le volume est compris entre 0 et 100."),
                   _T("Le volume du son sur le canal _PARAM0_ est _PARAM2_ � _PARAM1_"),
                   _T("Volume sonore"),
                   "res/conditions/sonVolume24.png",
                   "res/conditions/sonVolume.png",
                   &CondSoundCanalVolume);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Volume � tester"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe du test"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("MusicCanalVolume",
                   _T("Volume de la musique sur un canal"),
                   _T("Teste le volume de la musique sur le canal indiqu�. Le volume est compris entre 0 et 100."),
                   _T("Le volume de la musique sur le canal _PARAM0_ est _PARAM2_ � _PARAM1_"),
                   _T("Volume sonore"),
                   "res/conditions/musicVolume24.png",
                   "res/conditions/musicVolume.png",
                   &CondMusicCanalVolume);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Volume � tester"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe du test"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("GlobalVolume",
                   _T("Volume sonore global"),
                   _T("V�rifie que le volume sonore global correspond au test. Le volume est compris entre 0 et 100."),
                   _T("Le volume sonore global est _PARAM1_ � _PARAM0_"),
                   _T("Volume sonore"),
                   "res/conditions/volume24.png",
                   "res/conditions/volume.png",
                   &CondGlobalVolume);

        DECLARE_PARAMETER("expression", _T("Volume � tester"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe du test"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("SoundChannelPitch",
                   _T("Pitch du son d'un canal"),
                   _T("Teste le pitch ( vitesse ) du son sur le canal indiqu�. Un pitch de 1 indique une vitesse normale."),
                   _T("Le pitch du son sur le canal _PARAM0_ est _PARAM2_ � _PARAM1_"),
                   _T("Sons"),
                   "res/conditions/sonVolume24.png",
                   "res/conditions/sonVolume.png",
                   &CondSoundChannelPitch);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Pitch � tester"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe du test"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("MusicChannelPitch",
                   _T("Pitch de la musique d'un canal"),
                   _T("Teste le pitch ( vitesse ) de la musique sur le canal indiqu�. Un pitch de 1 indique une vitesse normale."),
                   _T("Le volume de la musique sur le canal _PARAM0_ est _PARAM2_ � _PARAM1_"),
                   _T("Musiques"),
                   "res/conditions/musicVolume24.png",
                   "res/conditions/musicVolume.png",
                   &CondMusicChannelPitch);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Pitch � tester"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe du test"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("SoundChannelPlayingOffset",
                   _T("Position de lecture du son d'un canal"),
                   _T("Teste la position de lecture du son sur le canal indiqu�."),
                   _T("La position de lecture du son sur le canal _PARAM0_ est _PARAM2_ � _PARAM1_s"),
                   _T("Sons"),
                   "res/conditions/sonVolume24.png",
                   "res/conditions/sonVolume.png",
                   &CondSoundChannelPlayingOffset);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Position � tester ( en secondes )"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe du test"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_CONDITION("MusicChannelPlayingOffset",
                   _T("Position de lecture de la musique d'un canal"),
                   _T("Teste la position de lecture de la musique sur le canal indiqu�."),
                   _T("La position de lecture la musique sur le canal _PARAM0_ est _PARAM2_ � _PARAM1_s"),
                   _T("Musiques"),
                   "res/conditions/musicVolume24.png",
                   "res/conditions/musicVolume.png",
                   &CondMusicChannelPlayingOffset);

        DECLARE_PARAMETER("expression", _T("Canal ( 0 � 15 )"), false, "")
        DECLARE_PARAMETER("expression", _T("Position � tester ( en secondes )"), false, "")
        DECLARE_PARAMETER("signe", _T("Signe du test"), false, "")

    DECLARE_END_CONDITION()

    DECLARE_EXPRESSION("SoundChannelPlayingOffset", _T("Position de lecture d'un son"), _T("Position de lecture d'un son"), _T("Sons"), "res/actions/son.png", &ExpGetSoundChannelPlayingOffset)
        DECLARE_PARAMETER("expression", _T("Canal"), false, "")
    DECLARE_END_EXPRESSION()
    DECLARE_EXPRESSION("MusicChannelPlayingOffset", _T("Position de lecture d'une musique"), _T("Position de lecture d'une musique"), _T("Musiques"), "res/actions/music.png", &ExpGetMusicChannelPlayingOffset)
        DECLARE_PARAMETER("expression", _T("Canal"), false, "")
    DECLARE_END_EXPRESSION()
    DECLARE_EXPRESSION("SoundChannelVolume", _T("Volume d'un son"), _T("Volume d'un son"), _T("Sons"), "res/actions/son.png", &ExpGetSoundChannelVolume)
        DECLARE_PARAMETER("expression", _T("Canal"), false, "")
    DECLARE_END_EXPRESSION()
    DECLARE_EXPRESSION("MusicChannelVolume", _T("Volume d'une musique"), _T("Volume d'une musique"), _T("Musiques"), "res/actions/music.png", &ExpGetMusicChannelVolume)
        DECLARE_PARAMETER("expression", _T("Canal"), false, "")
    DECLARE_END_EXPRESSION()
    DECLARE_EXPRESSION("SoundChannelPitch", _T("Pitch d'un son"), _T("Pitch d'un son"), _T("Sons"), "res/actions/son.png", &ExpGetSoundChannelPitch)
        DECLARE_PARAMETER("expression", _T("Canal"), false, "")
    DECLARE_END_EXPRESSION()
    DECLARE_EXPRESSION("MusicChannelPitch", _T("Pitch d'une musique"), _T("Pitch d'une musique"), _T("Musiques"), "res/actions/music.png", &ExpGetMusicChannelPitch)
        DECLARE_PARAMETER("expression", _T("Canal"), false, "")
    DECLARE_END_EXPRESSION()
}

#if defined(GD_IDE_ONLY)
void AudioExtension::PrepareActionsResourcesForMerging(Instruction & action, ResourcesMergingHelper & resourcesMergingHelper)
{
    if ( action.GetType() == "PlaySound" || action.GetType() == "PlaySoundCanal" || action.GetType() == "PlayMusic" || action.GetType() == "PlayMusicCanal" )
        action.SetParameter( 0, resourcesMergingHelper.GetNewFilename(action.GetParameter(0).GetPlainString()));
}

void AudioExtension::GetPropertyForDebugger(RuntimeScene & scene, unsigned int propertyNb, std::string & name, std::string & value) const
{
    if ( propertyNb < SoundManager::GetInstance()->sounds.size() )
    {
        sf::Sound::Status soundStatus = SoundManager::GetInstance()->sounds[propertyNb]->GetStatus();

        if ( soundStatus == sf::Sound::Playing)
            name = _T("Son jou� :");
        else if ( soundStatus == sf::Sound::Stopped)
            name = _T("Son stopp� :");
        else if ( soundStatus == sf::Sound::Paused)
            name = _T("Son en pause :");

        value = SoundManager::GetInstance()->sounds[propertyNb]->file;
    }
    if ( propertyNb-SoundManager::GetInstance()->sounds.size() < SoundManager::GetInstance()->musics.size() )
    {
        sf::Sound::Status soundStatus = SoundManager::GetInstance()->musics[propertyNb-SoundManager::GetInstance()->sounds.size()]->GetStatus();

        if ( soundStatus == sf::Sound::Playing)
            name = _T("Musique jou�e :");
        else if ( soundStatus == sf::Sound::Stopped)
            name = _T("Musique stopp�e :");
        else if ( soundStatus == sf::Sound::Paused)
            name = _T("Musique en pause :");

        value = SoundManager::GetInstance()->musics[propertyNb-SoundManager::GetInstance()->sounds.size()]->file;
    }
}

bool AudioExtension::ChangeProperty(RuntimeScene & scene, unsigned int propertyNb, std::string newValue)
{
    return false;
}

unsigned int AudioExtension::GetNumberOfProperties(RuntimeScene & scene) const
{
    return SoundManager::GetInstance()->musics.size()+SoundManager::GetInstance()->sounds.size();
}

#endif

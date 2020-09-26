//
// Created by kris on 26.09.20.
//

#ifndef BOT_SOUNDHANDLER_H
#define BOT_SOUNDHANDLER_H

#include "cinder/app/App.h"
#include "cinder/audio/Voice.h"
#include "cinder/audio/Source.h"
#include "../settings/SettingsHandler.h"
enum class SOUND { START_UP,BEEP,ERROR };
class SoundHandler
{
public:

    SoundHandler();
    void loadSounds();
    void play(SOUND sound);
    void play( ci::audio::VoiceRef vr);
    ci::audio::VoiceRef startup;
    ci::audio::VoiceRef error;
    std::vector<ci::audio::VoiceRef> beeps;

    Sbool isSound = SETTINGS()->getBool("AppSettings", "sound", true);
};


#endif //BOT_SOUNDHANDLER_H

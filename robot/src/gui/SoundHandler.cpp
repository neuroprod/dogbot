//
// Created by kris on 26.09.20.
//

#include "SoundHandler.h"

using namespace ci;
using namespace ci::app;

SoundHandler::SoundHandler()
{
    loadSounds();
}

void SoundHandler::loadSounds()
{
    startup = audio::Voice::create(audio::load(loadAsset("sounds/startup.ogg")));
    error = audio::Voice::create(audio::load(loadAsset("sounds/error.ogg")));
    beeps.push_back(audio::Voice::create(audio::load(loadAsset("sounds/beep1.ogg"))));
    beeps.push_back(audio::Voice::create(audio::load(loadAsset("sounds/beep2.ogg"))));
    beeps.push_back(audio::Voice::create(audio::load(loadAsset("sounds/beep3.ogg"))));
}

void SoundHandler::play(SOUND sound)
{

    if(!isSound->value())return;

    if (sound == SOUND::START_UP)
    {
        play(startup);
    }
    if (sound == SOUND::ERROR)
    {
        play(error);
    }
    if (sound == SOUND::BEEP)
    {
        int i = rand() % 3;
        play(beeps[i]);
    }
}

void SoundHandler::play(ci::audio::VoiceRef vr)
{
    if(!isSound->value())return;

    if (vr->isPlaying())
        vr->stop();

    vr->start();


}
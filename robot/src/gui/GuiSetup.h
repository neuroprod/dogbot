//
// Created by kris on 30.08.20.
//

#ifndef BOT_GUISETUP_H
#define BOT_GUISETUP_H

#include "../settings/SettingsHandler.h"

class GuiSetup
        {

        public:
            GuiSetup(){};
            void setup();
            void update();
            Sbool isSimulation;
            Sbool isSound;
        };
#endif //BOT_GUISETUP_H

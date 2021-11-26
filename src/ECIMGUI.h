#pragma once

#include "consts.h"
#include "EvolveClimber.h"

#include "imgui.h"

namespace EC
{
    class ECIMGUI
    {         
        bool m_showSettings;
        int m_menu;

        EvolveClimber* m_evolveClimber;

        public:
        ECIMGUI(EvolveClimber* evolveClimber);
        void draw_main();

        void onClickSettings() {m_showSettings = !m_showSettings;};
        void setEvolveClimber(EvolveClimber* evolveClimber) {m_evolveClimber = evolveClimber;}

        private:
        void startMenu();
        void gen0Menu();
    };
}

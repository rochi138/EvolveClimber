#pragma once

#include "consts.h"
#include "EvolveClimber.h"

namespace EC
{
    class ECIMGUI
    {         
        public:
        ECIMGUI(EvolveClimber* evolveClimber);
        void draw_main();

        void onClickSettings() {m_showSettings = !m_showSettings;};
        void setEvolveClimber(EvolveClimber* evolveClimber) {m_evolveClimber = evolveClimber;}

        private:
        bool m_showSettings;
        int m_menu;

        EvolveClimber* m_evolveClimber;

        void draw_menus();
        void startMenu();
        void gen0Menu();
        void simulationMenu();        
        void overviewMenu();
        void viewGenMenu();

        void draw_settings();

        void displayGen();    
        void onClickButton();

        void drawPosts(int toImage);
        void drawGround(int toImage);
        void drawSkipButton();
        void drawOtherButtons();

    };
}

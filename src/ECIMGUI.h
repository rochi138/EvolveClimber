#pragma once

#include "consts.h"
#include "EvolveClimber.h"
#include "imgui.h"

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
        int m_genToDo;
        int m_runUntilGen;
        ImColor m_creatureBackgroundColor; 

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

        void overviewMenuLeftColumn();
        
        void overviewMenuRightColumn();
        void overviewMenuRightButtons();
        void overviewMenuDatabase();

        void drawCreatureWhole(ImVec2 p, vector<Creature>::iterator creature, float width, ImDrawList* draw_list);
        void drawMuscle(bool contracted, vector<Node>::iterator ni1, vector<Node>::iterator ni2, ImVec2 origin, ImDrawList* draw_list, float scale, float rigidity);
        void drawNode(vector<Node>::iterator ni, ImVec2 origin, ImDrawList* draw_list, float scale);
    };
}

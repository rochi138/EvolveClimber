#pragma once

#include "consts.h"

#include "imgui.h"

namespace EC
{
    class ECIMGUI
    {
        bool show_demo_window = true;
        bool show_another_window = false;           
        float f = 0.0f;
        int counter = 0; 
        int menu;

        public:
        ECIMGUI();
        void draw_main();
    };
}

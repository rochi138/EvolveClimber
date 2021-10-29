#pragma once

#include "imgui.h"

namespace EC
{
    class EvolveClimber
    {
        bool show_demo_window = true;
        bool show_another_window = false;           
        float f = 0.0f;
        int counter = 0; 

        public:
        void draw_main();
    };
}

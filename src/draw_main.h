#pragma once

#include "imgui.h"

namespace EC
{
    class EvolveClimber
    {
        bool show_demo_window = true;
        bool show_another_window = false;        

        public:
        void draw_main();
    };
}

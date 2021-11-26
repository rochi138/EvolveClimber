#include <stdio.h>
#include <iostream>

#include "ECIMGUI.h"

using namespace EC;

ECIMGUI::ECIMGUI(EvolveClimber* evolveClimber)
: m_showSettings(false)
, m_menu(0)
, m_evolveClimber(evolveClimber)
{}

void ECIMGUI::draw_main()
{
    ImGui::SetNextWindowPos(ImVec2(20, 20));
    ImGui::SetNextWindowSize(ImVec2(800, 600));
    ImGui::Begin("Evolve Climber");
    
    switch (m_menu)
    {
        case 0: startMenu(); break;
        case 1: gen0Menu(); break;
    }

    ImGui::End();

    if (m_showSettings)
    {
        ImGui::SetNextWindowPos(ImVec2(820, 20));
        ImGui::SetNextWindowSize(ImVec2(200, 600));
        ImGui::Begin("Settings", &m_showSettings);
        ImGui::Text("Setttings go here");
        ImGui::End();
    }
}

void ECIMGUI::startMenu()
{
    ImGui::Text("EVOLUTION!");
    if (ImGui::Button("START"))
    {
        m_menu = 1;
    }
}

void ECIMGUI::gen0Menu()
{
    ImGui::Text("Generation 0");
    ImGui::Text("Sine there are no creatures yet, create 1000 creatures!");
    ImGui::Text("They will be randomly created, and also very simple.");
    if (ImGui::Button("CREATE"))
    {
        m_menu = 2;
    }
}

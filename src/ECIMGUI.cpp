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
    draw_menus();
    draw_settings();    
}

#pragma region --Menus--

void ECIMGUI::draw_menus()
{
    ImGui::SetNextWindowPos(ImVec2(20, 20));
    ImGui::SetNextWindowSize(ImVec2(800, 600));
    ImGui::Begin("Evolve Climber");
    
    switch (m_menu)
    {
        case 0: startMenu(); break;
        case 1: gen0Menu(); break;
        case 2: simulationMenu(); break;
        case 3: overviewMenu(); break;
        default: viewGenMenu();
    }

    ImGui::End();
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
        m_menu = 8;
    }
}

void ECIMGUI::overviewMenu()
{
    ImGui::Text("Generation %i", m_evolveClimber->getGen());
    ImGui::Text("Median Distance");
    if( ImGui::Button("Do 1 step-by-step generation") )
    {
        m_menu = 4;
    }
    ImGui::Button("Do 1 quick generation");
    ImGui::Button("Do 1 gen ASAP");
    ImGui::Button("Do 1 gen ALAP");
    ImGui::Button("Run until");
    ImGui::Button("Do X gen ASAP");

    float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
    ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));
    ImGui::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, ImVec2(0, 80.0f));
}

#pragma endregion

#pragma region --Settings--
void ECIMGUI::draw_settings()
{
    if (m_showSettings)
    {
        ImGui::SetNextWindowPos(ImVec2(820, 20));
        ImGui::SetNextWindowSize(ImVec2(200, 600));
        ImGui::Begin("Settings", &m_showSettings);
        ImGui::Text("Setttings go here");
        ImGui::End();
    }
}
#pragma endregion
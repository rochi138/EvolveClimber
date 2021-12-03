#include <stdio.h>
#include <iostream>

#include "ECIMGUI.h"
#include "imgui.h"

using namespace EC;

ECIMGUI::ECIMGUI(EvolveClimber* evolveClimber)
: m_showSettings(false)
, m_menu(0)
, m_evolveClimber(evolveClimber)
{}

// namespace EC {
//     double RandomGauss() {
// 	static double V1, V2, S;
// 	static int phase = 0;
// 	double X;
// 	if(phase == 0) {
// 		do {
// 			double U1 = (double)rand() / RAND_MAX;
// 			double U2 = (double)rand() / RAND_MAX;
// 			V1 = 2 * U1 - 1;
// 			V2 = 2 * U2 - 1;
// 			S = V1 * V1 + V2 * V2;
// 			} while(S >= 1 || S == 0);

// 		X = V1 * sqrt(-2 * log(S) / S);
// 	} else
// 		X = V2 * sqrt(-2 * log(S) / S);
// 	phase = 1 - phase;
// 	return X;
// }
//     template <int N>
// struct NormalDistribution {
//     NormalDistribution(double mean, double sd) {
//         for (int i = 0; i < N; ++i)
//             Data[i] = RandomGauss()*sd + mean;
//     }
//     double Data[N];
// };
// }

void ECIMGUI::draw_main()
{
    // ImPlot::ShowDemoWindow();
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
    ImGui::Text("Since there are no creatures yet, create 1000 creatures!");
    ImGui::Text("They will be randomly created, and also very simple.");
    if (ImGui::Button("CREATE"))
    {
        m_evolveClimber->onClickCreate();
        m_menu = 8;
    }
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
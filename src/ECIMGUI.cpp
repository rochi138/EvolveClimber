#include <stdio.h>

#include "consts.h"
#include "ECIMGUI.h"
#include "imgui.h"
// #include "implot.h"

using namespace EC;

ECIMGUI::ECIMGUI(EvolveClimber* evolveClimber)
: m_showSettings(false)
, m_menu(0)
, m_creatureBackgroundColor(0.6627f, 0.6627f, 0.6627f, 1.0f)
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
//
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
    //ImPlot::ShowDemoWindow();
    draw_menus();
    draw_settings();    
}

#pragma region --Menus--

void ECIMGUI::draw_menus()
{
    ImGui::SetNextWindowPos(ImVec2(20, 20));
    ImGui::SetNextWindowSize(ImVec2(1000, 800));
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
    if (!m_showSettings)
        return;

    ImGui::SetNextWindowPos(ImVec2(1020, 20));
    ImGui::SetNextWindowSize(ImVec2(200, 800));
    ImGui::Begin("Settings", &m_showSettings);
    {
        ImGui::Text("Set random seed");
        ImGui::InputInt("##InputSeed", m_evolveClimber->getSeed());
        if (ImGui::Button("Apply"))
        {
            m_evolveClimber->onClickSeed();
        }

        ImGui::Text("Set simulation duration");
        ImGui::InputInt("##InputMaxTime", m_evolveClimber->getMaxTime());
        ImGui::Text("Set big change mutability");
        ImGui::InputFloat("##InputBig", &bigMutationChance, 0.01f, 1.0f, "%.3f");
        ImGui::Text("Set gravity");
        ImGui::InputFloat("##InputGravity", &gravity, 0.01f, 1.0f, "%.3f");
        ImGui::Text("Set friction");
        ImGui::InputFloat("##InputFriction", &FRICTION, 0.01f, 1.0f, "%.3f");
        ImGui::Text("Set air friction");
        ImGui::InputFloat("##InputAirFriction", &airFriction, 0.01f, 1.0f, "%.3f");

        ImGui::Separator();
        ImGui::Text("Change selection function");
        int* selectionFunction = m_evolveClimber->getSelectionFunction();
        ImGui::RadioButton("Cubic", selectionFunction, 0);
        ImGui::RadioButton("Step", selectionFunction, 1);
        ImGui::RadioButton("Linear", selectionFunction, 2);
        ImGui::RadioButton("Uniform", selectionFunction, 3);
    }
    
    ImGui::End();

}
#pragma endregion
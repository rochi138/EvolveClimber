#include <stdio.h>
#include <iostream>

#include "ECIMGUI.h"
#include "imgui.h"
#include "implot.h"

using namespace EC;

ECIMGUI::ECIMGUI(EvolveClimber* evolveClimber)
: m_showSettings(false)
, m_menu(0)
, m_evolveClimber(evolveClimber)
{}

namespace EC {
    double RandomGauss() {
	static double V1, V2, S;
	static int phase = 0;
	double X;
	if(phase == 0) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;
			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
			} while(S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	} else
		X = V2 * sqrt(-2 * log(S) / S);
	phase = 1 - phase;
	return X;
}
    template <int N>
struct NormalDistribution {
    NormalDistribution(double mean, double sd) {
        for (int i = 0; i < N; ++i)
            Data[i] = RandomGauss()*sd + mean;
    }
    double Data[N];
};
}

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

void ECIMGUI::overviewMenu()
{
    ImGui::Text("Generation %i", m_evolveClimber->getGen());
    ImGui::Text("Median Distance");
    ImGui::Button("Do 1 step-by-step generation");
    if (ImGui::Button("Do 1 quick generation"))
    {
        m_menu = 4;
        m_evolveClimber->testGen();
    }
    if (ImGui::Button("Do 1 gen ASAP"))
    {
        m_evolveClimber->onClickASAP();
    }
    // if (ImGui::Button("Do gens ALAP"))
    // {
    //     m_evolveClimber->onClickALAP();
    // }
    // if (ImGui::Button("STOP"))
    // {
    //     m_evolveClimber->onClickStop();
    // }
    ImGui::Text("Do ");
    ImGui::SameLine();
    ImGui::InputInt("gens ASAP", m_evolveClimber->getGenToDo());
    ImGui::SameLine();
    if (ImGui::Button("Go###DoXGensButton"))
    {
        m_evolveClimber->onClickDoXGens();
    }
    
    ImGui::Text("Run until Generation");
    ImGui::SameLine();
    ImGui::InputInt("##RunUntilNum", m_evolveClimber->getRunUntilGen());
    ImGui::SameLine();
    if (ImGui::Button("Go###RunUntilButton"))
    {
        m_evolveClimber->onClickRunUntil();
    }

    if (ImPlot::BeginPlot("Median Distance", ImVec2(-1,0), ImPlotFlags_NoMouseText)) {
        ImPlot::SetupAxes("Gen #","Distance (m)", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);

        vector<vector<float>> percentile = *m_evolveClimber->getPercentile();
        vector<float> xAxis = *m_evolveClimber->getXAxis();
        int len = m_evolveClimber->getGen() +1;

        for (vector<vector<float>>::iterator it = percentile.begin(); it != percentile.end(); ++it)
        {
            ImPlot::PlotLine(p_text[it - percentile.begin()].c_str(), &(*it)[0], len);
        }

        ImPlot::EndPlot();
    }

    static int  bins       = 50;
    static bool cumulative = false;
    static bool density    = true;
    static bool outliers   = true;
    static double mu       = 5;
    static double sigma    = 2;

    ImGui::SetNextItemWidth(200);
    if (ImGui::RadioButton("Sqrt",bins==ImPlotBin_Sqrt))       { bins = ImPlotBin_Sqrt;    } ImGui::SameLine();
    if (ImGui::RadioButton("Sturges",bins==ImPlotBin_Sturges)) { bins = ImPlotBin_Sturges; } ImGui::SameLine();
    if (ImGui::RadioButton("Rice",bins==ImPlotBin_Rice))       { bins = ImPlotBin_Rice;    } ImGui::SameLine();
    if (ImGui::RadioButton("Scott",bins==ImPlotBin_Scott))     { bins = ImPlotBin_Scott;   } ImGui::SameLine();
    if (ImGui::RadioButton("N Bins",bins>=0))                       bins = 50;
    if (bins>=0) {
        ImGui::SameLine();
        ImGui::SetNextItemWidth(200);
        ImGui::SliderInt("##Bins", &bins, 1, 100);
    }
    if (ImGui::Checkbox("Density", &density))
    {
        ImPlot::SetNextAxisToFit(ImAxis_X1);
        ImPlot::SetNextAxisToFit(ImAxis_Y1);
    }
    ImGui::SameLine();
    if (ImGui::Checkbox("Cumulative", &cumulative))
    {
        ImPlot::SetNextAxisToFit(ImAxis_X1);
        ImPlot::SetNextAxisToFit(ImAxis_Y1);
    }
    ImGui::SameLine();
    static bool range = false;
    ImGui::Checkbox("Range", &range);
    static float rmin = -3;
    static float rmax = 13;
    if (range) {
        ImGui::SameLine();
        ImGui::SetNextItemWidth(200);
        ImGui::DragFloat2("##Range",&rmin,0.1f,-3,13);
        ImGui::SameLine();
        ImGui::Checkbox("Outliers",&outliers);
    }

    static NormalDistribution<10000> dist(mu, sigma);
    static double x[100];
    static double y[100];
    if (density) {
        for (int i = 0; i < 100; ++i) {
            x[i] = -3 + 16 * (double)i/99.0;
            y[i] = exp( - (x[i]-mu)*(x[i]-mu) / (2*sigma*sigma)) / (sigma * sqrt(2*3.141592653589793238));
        }
        if (cumulative) {
            for (int i = 1; i < 100; ++i)
                y[i] += y[i-1];
            for (int i = 0; i < 100; ++i)
                y[i] /= y[99];
        }
    }

    if (ImPlot::BeginPlot("##Histograms")) {
        ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);
        ImPlot::PlotHistogram("Empirical", dist.Data, 10000, bins, cumulative, density, range ? ImPlotRange(rmin,rmax) : ImPlotRange(), outliers);
        if (density && outliers)
            ImPlot::PlotLine("Theoretical",x,y,100);
        ImPlot::EndPlot();
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
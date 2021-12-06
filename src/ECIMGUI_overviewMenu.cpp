#include <stdio.h>
#include <iostream>

#include "ECIMGUI.h"
#include "imgui.h"
#include "implot.h"

using namespace std;
using namespace EC;

void ECIMGUI::overviewMenu()
{	
	ImGui::BeginChild("##LeftCol", ImVec2(ImGui::GetContentRegionAvail().x * 0.7f, ImGui::GetContentRegionAvail().y), false);
	overviewMenuLeftColumn();	
	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("##RightCol", ImVec2(0, ImGui::GetContentRegionAvail().y), false);
	overviewMenuRightColumn();	
	ImGui::EndChild();

    // static int  bins       = 50;
    // static bool cumulative = false;
    // static bool density    = true;
    // static bool outliers   = true;
    // static double mu       = 5;
    // static double sigma    = 2;
	//
    // ImGui::SetNextItemWidth(200);
    // if (ImGui::RadioButton("Sqrt",bins==ImPlotBin_Sqrt))       { bins = ImPlotBin_Sqrt;    } ImGui::SameLine();
    // if (ImGui::RadioButton("Sturges",bins==ImPlotBin_Sturges)) { bins = ImPlotBin_Sturges; } ImGui::SameLine();
    // if (ImGui::RadioButton("Rice",bins==ImPlotBin_Rice))       { bins = ImPlotBin_Rice;    } ImGui::SameLine();
    // if (ImGui::RadioButton("Scott",bins==ImPlotBin_Scott))     { bins = ImPlotBin_Scott;   } ImGui::SameLine();
    // if (ImGui::RadioButton("N Bins",bins>=0))                       bins = 50;
    // if (bins>=0) {
    //     ImGui::SameLine();
    //     ImGui::SetNextItemWidth(200);
    //     ImGui::SliderInt("##Bins", &bins, 1, 100);
    // }
    // if (ImGui::Checkbox("Density", &density))
    // {
    //     ImPlot::SetNextAxisToFit(ImAxis_X1);
    //     ImPlot::SetNextAxisToFit(ImAxis_Y1);
    // }
    // ImGui::SameLine();
    // if (ImGui::Checkbox("Cumulative", &cumulative))
    // {
    //     ImPlot::SetNextAxisToFit(ImAxis_X1);
    //     ImPlot::SetNextAxisToFit(ImAxis_Y1);
    // }
    // ImGui::SameLine();
    // static bool range = false;
    // ImGui::Checkbox("Range", &range);
    // static float rmin = -3;
    // static float rmax = 13;
    // if (range) {
    //     ImGui::SameLine();
    //     ImGui::SetNextItemWidth(200);
    //     ImGui::DragFloat2("##Range",&rmin,0.1f,-3,13);
    //     ImGui::SameLine();
    //     ImGui::Checkbox("Outliers",&outliers);
    // }
	//
    // static NormalDistribution<10000> dist(mu, sigma);
    // static double x[100];
    // static double y[100];
    // if (density) {
    //     for (int i = 0; i < 100; ++i) {
    //         x[i] = -3 + 16 * (double)i/99.0;
    //         y[i] = exp( - (x[i]-mu)*(x[i]-mu) / (2*sigma*sigma)) / (sigma * sqrt(2*3.141592653589793238));
    //     }
    //     if (cumulative) {
    //         for (int i = 1; i < 100; ++i)
    //             y[i] += y[i-1];
    //         for (int i = 0; i < 100; ++i)
    //             y[i] /= y[99];
    //     }
    // }
	//
    // if (ImPlot::BeginPlot("##Histograms")) {
    //     ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);
    //     ImPlot::PlotHistogram("Empirical", dist.Data, 10000, bins, cumulative, density, range ? ImPlotRange(rmin,rmax) : ImPlotRange(), outliers);
    //     if (density && outliers)
    //         ImPlot::PlotLine("Theoretical",x,y,100);
    //     ImPlot::EndPlot();
    // }
}

#pragma region --Left--

void ECIMGUI::overviewMenuLeftColumn()
{
    int gen = m_evolveClimber->getGen();
	ImGui::Text("Generation %i", gen);
    int topSpecies = m_evolveClimber->getTopSpecies()->back();
    ImGui::Text("Dominant Species: %i nodes, %i muscles", topSpecies/10, topSpecies%10);

    vector<vector<float>> percentile = *m_evolveClimber->getPercentile();
    ImGui::Text("Best: %.3fm", (percentile.begin())->back());
    ImGui::Text("Median: %.3fm", (percentile.begin() + 2)->back());

    if (!m_evolveClimber->getRunCoroutine() || gen < 100)
    {
        char title[50];
        sprintf(title, "Median Distance - %.3fm", (percentile.begin() + 2)->back());
        if (ImPlot::BeginPlot(title, ImVec2(-1,0), ImPlotFlags_NoMouseText)) {
            ImPlot::SetupAxes("Gen #","Distance (m)", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);

            vector<float> xAxis = *m_evolveClimber->getXAxis();
            int len = m_evolveClimber->getGen() +1;

            for (vector<vector<float>>::iterator it = percentile.begin(); it != percentile.end(); ++it)
            {
                ImPlot::PlotLine(p_text[it - percentile.begin()].c_str(), &(*it)[0], len);
            }

            ImPlot::EndPlot();
        }
        overviewMenuDatabase();
    }
    else
    {
        ImGui::Text("Graphs unavailable while simulating due to memory issues");
    }    
}

#pragma endregion

#pragma region --Right--

void ECIMGUI::overviewMenuRightColumn()
{
	overviewMenuRightButtons();
}

void ECIMGUI::overviewMenuRightButtons()
{
    if (m_evolveClimber->getRunCoroutine())
    {
        if (ImGui::Button("STOP"))
            m_evolveClimber->onClickStop();
    } 
    else {
        // ImGui::Button("Do 1 step-by-step generation");
        if (ImGui::Button("Do 1 quick generation"))
        {
            m_menu = 4;
            m_evolveClimber->testGen();
        }

        if (ImGui::Button("Do 1 gen ASAP"))
            m_evolveClimber->onClickASAP();
        if (ImGui::Button("Do gens ALAP"))
            m_evolveClimber->onClickALAP();
        
        ImGui::Text("Do ");
        ImGui::SameLine();
        ImGui::InputInt("gens ASAP", m_evolveClimber->getGenToDoInput());
        if (ImGui::Button("Go###DoXGensButton"))
            m_evolveClimber->onClickDoXGens();
        
        ImGui::Text("Run until Generation");
        ImGui::InputInt("##RunUntilNum", m_evolveClimber->getRunUntilGen());
        if (ImGui::Button("Go###RunUntilButton"))
            m_evolveClimber->onClickRunUntil();
    }
	
}

void ECIMGUI::overviewMenuDatabase()
{
    int genSelected = m_evolveClimber->getGen();
    if (genSelected > 0 )
    {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        float x = ImGui::GetContentRegionAvailWidth();
        float spacing = 10.0f;
        float width = (x-2*spacing) /3.0f;
        
        vector<Creature> creatureDatabase = *m_evolveClimber->getCreatureDatabase();
        vector<Creature>::iterator idx = creatureDatabase.begin() + (genSelected-1)*3;
        ImVec2 p = ImGui::GetCursorScreenPos();
        draw_list->AddRectFilled(p, ImVec2(p.x+width, p.y+width), m_creatureBackgroundColor);
        drawCreatureWhole(p, idx, width, draw_list);
        p = ImVec2(p.x + width + spacing, p.y);
        draw_list->AddRectFilled(p, ImVec2(p.x+width, p.y+width), m_creatureBackgroundColor);
        drawCreatureWhole(p, idx +1, width, draw_list);
        p = ImVec2(p.x + width + spacing, p.y);
        draw_list->AddRectFilled(p, ImVec2(p.x+width, p.y+width), m_creatureBackgroundColor);
        drawCreatureWhole(p, idx + 2, width, draw_list);
    }    
}

#pragma endregion
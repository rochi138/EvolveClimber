#include <stdio.h>
#include <iostream>

#include "ECIMGUI.h"

using namespace EC;

void ECIMGUI::viewGenMenu()
{
    int idx = m_menu - viewGenMenu_idx;
    string topText = idx == 4 ? viewGenMenu_topText[idx] + std::to_string(m_evolveClimber->getGen()) : viewGenMenu_topText[idx];

    ImGui::Text("%s", topText.c_str());
    displayGen();
    ImGui::Text("%s", viewGenMenu_bottomText[idx].c_str());
    if (ImGui::Button(viewGenMenu_buttonText[idx].c_str()))
        onClickButton();
}

void ECIMGUI::displayGen()
{
    // int gen = m_evolveClimber->getGen();
    // ImDrawList* draw_list = ImGui::GetWindowDrawList();
    // float x = ImGui::GetContentRegionAvailWidth();
    // float width = x /40.0f;
    // ImVec2 p = ImGui::GetCursorScreenPos();

    // vector<Creature>* cToDraw = m_menu == 8 ? m_evolveClimber->getCreaturePopulation() : m_evolveClimber->getCreatureSorted();

    // std::cout << "cToDraw size " << cToDraw->size() << std::endl;
    // std::cout << "display width " << width << std::endl;
    
    // if (cToDraw->size() == 1000)
    // {
    //     vector<Creature>::iterator it = cToDraw->begin();
            
    //     draw_list->AddRectFilled(p, ImVec2(p.x+40*width, p.y+25*width), m_creatureBackgroundColor);
        
    //     for (int y = 0; y < 25; ++y)
    //     {
    //         for (int x = 0; x < 40; ++x)
    //         {
    //             ImVec2 corn = ImVec2(p.x + x*width, p.y + y*width);            
    //             drawCreatureWhole(corn, it, width, draw_list);
    //             ++it;
    //         }
    //     }
    // }

    vector<array<int, 101>>::iterator speciesCount = m_evolveClimber->getSpeciesCounts()->end() -1;

    if( ImGui::BeginTable("Species Breakdown", 11) )
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Muscle #");
        ImGui::TableNextColumn();
        ImGui::Text("Node #");

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        for (int i = 3; i < 10; ++i)
        {
            ImGui::TableNextColumn();
            ImGui::Text("%i", i);
        }
        for (int i = 0; i < 3; ++i)
        {
            ImGui::TableNextColumn();
            ImGui::Text("%i", i+10);
        }
        for(int y = 2; y < 10; y++)
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%i", y);

            for (int x = 3; x < 10; ++x)
            {
                ImGui::TableNextColumn();
                ImGui::Text("%i", (*speciesCount)[x*10+y]);
            }
            for (int x = 0; x < 3; ++x)
            {
                ImGui::TableNextColumn();
                ImGui::Text("%i", (*speciesCount)[x*10+y]);
            }
        }
        for(int y = 0; y < 2; y++)
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%i", y+10);

            for (int x = 3; x < 10; ++x)
            {
                ImGui::TableNextColumn();
                ImGui::Text("%i", (*speciesCount)[x*10+y]);
            }
            for (int x = 0; x < 3; ++x)
            {
                ImGui::TableNextColumn();
                ImGui::Text("%i", (*speciesCount)[x*10+y]);
            }
        }
        ImGui::EndTable();
    }    
}

void ECIMGUI::onClickButton()
{
    switch(m_menu)
    {
        case 4:  break;
        case 5:  break;
        case 6: m_evolveClimber->compileGenData(); m_evolveClimber->kill(); break;
        case 7: m_evolveClimber->reproduce(); break;
        case 8:  break;
    }    

    if (m_menu == 8)
        m_menu = 3;
    else if (m_menu == 4)
        m_menu = 6;
    else
        m_menu += 1;
}

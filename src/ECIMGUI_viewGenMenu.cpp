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

}

void ECIMGUI::onClickButton()
{
    switch(m_menu)
    {
        case 4:  break;
        case 5:  break;
        case 6:  break;
        case 7:  break;
        case 8:  break;
    }    

    if (m_menu == 8)
        m_menu = 3;
    else
        m_menu += 1;
}

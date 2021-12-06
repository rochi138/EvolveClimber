#include <stdio.h>
#include <iostream>

#include "ECIMGUI.h"
#include "imgui.h"
#include "implot.h"

using namespace std;
using namespace EC;

void ECIMGUI::drawCreatureWhole(ImVec2 p, vector<Creature>::iterator creature, float width, ImDrawList* draw_list)
{
    const ImVec2 origin = ImVec2(p.x+width/2.0f, p.y+width);
    float scale = 0.4f*width;
    vector<Node>* draw_n = creature->getN();
    vector<Muscle>* draw_m = creature->getM();

    for (vector<Muscle>::iterator it = draw_m->begin(); it != draw_m->end(); ++it)
    {
        drawMuscle(it->getContracted(), draw_n->begin() + it->getC1(), draw_n->begin() + it->getC2(), origin, draw_list, scale, it->getRigidity());
    }
    for (vector<Node>::iterator it = draw_n->begin(); it != draw_n->end(); ++ it)
    {
        drawNode(it, origin, draw_list, scale);
    }
}

void ECIMGUI::drawMuscle(bool contracted, vector<Node>::iterator ni1, vector<Node>::iterator ni2, ImVec2 origin, ImDrawList* draw_list, float scale, float rigidity)
{
    float w = contracted ? scale*0.1 : scale*0.05;
    draw_list->AddLine(ImVec2(ni1->getX()*scale+origin.x, ni1->getY()*scale+origin.y), ImVec2(ni2->getX()*scale+origin.x, ni2->getY()*scale+origin.y), ImColor(0.0f, 0.0f, 0.0f, rigidity*3000.0f/255.0f), w);
}

void ECIMGUI::drawNode(vector<Node>::iterator ni, ImVec2 origin, ImDrawList* draw_list, float scale)
{
    float r = scale*0.14;
    ImColor c = ImColor(2.0f*(1.0f-ni->getF()), 0.0f, 0.0f, 1.0f);
    if(ni->getF() <= 0.5f){
        c = ImColor(1.0f, 1.0f-ni->getF()*2.0f, 1.0f-ni->getF()*2.0f, 1.0f);
    }
    draw_list->AddCircleFilled(ImVec2(ni->getX()*scale+origin.x, ni->getY()*scale+origin.y), r, c);
}
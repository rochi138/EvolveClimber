#pragma once

#include <vector>
#include <string>
#include "imgui.h"

#include "Components/Creature.h"

using namespace std;
namespace EC
{

// static const ImVec4 black = ImVec4(Color32::black);
extern float windowSizeMultiplier;

extern int minBar;
extern int maxBar;

extern bool haveGround;
extern int histBarsPerMeter;
extern float FRICTION;
extern float bigMutationChance;

extern float cTimer;
extern float scaleToFixBug;

extern float lineY1;
extern float lineY2;
extern uint32_t axonColor;

extern int windowWidth;
extern int windowHeight;
extern int timer;
extern float camX;
extern float camY;
extern int frames;
extern int menu;
extern float sliderX;
extern int genSelected;
extern bool drag;
extern bool justGotBack;
extern int creatures;
extern int creaturesTested;
extern int statusWindow;
extern int prevStatusWindow;
extern int overallTimer;
extern bool miniSimulation;
extern int creatureWatching;
extern int simulationTimer;

extern float camZoom;
extern float gravity;
extern float airFriction;

extern int speed;
extern int id;
extern bool stepbystep;
extern bool stepbystepslow;
extern int timeShow;
extern int p[5];
extern string p_text[5];

extern int viewGenMenu_idx;
extern string viewGenMenu_topText[5];
extern string viewGenMenu_bottomText[5];
extern string viewGenMenu_buttonText[5];
}
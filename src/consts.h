#pragma once

#include <vector>
#include <string>
#include "imgui.h"

#include "Components/Creature.h"
#include "Components/Rectangle.h"

using namespace std;
namespace EC
{

// static const ImVec4 black = ImVec4(Color32::black);
extern float windowSizeMultiplier;

extern vector<Creature> creatureDatabase;
extern vector<Rectangle> rects;
// PGraphics graphImage;
// PGraphics screenImage;
// PGraphics popUpImage;
// PGraphics segBarImage;
extern bool haveGround;
extern int histBarsPerMeter;
extern string operationNames[12];
extern int operationAxons[12];
extern int operationCount;
extern string fitnessUnit;
extern string fitnessName;
extern float baselineEnergy;
extern int energyDirection;
extern float FRICTION;
extern float bigMutationChance;
extern float hazelStairs;
extern bool saveFramesPerGeneration;

extern int lastImageSaved;
extern float pressureUnit;
extern float energyUnit;
extern float nauseaUnit;
extern int gensToDo;
extern float cTimer;
extern float postFontSize;
extern float scaleToFixBug;
extern float energy;
extern float averageNodeNausea;
extern float totalNodeNausea;

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
extern int gen;
extern float sliderX;
extern int genSelected;
extern bool drag;
extern bool justGotBack;
extern int creatures;
extern int creaturesTested;
extern int fontSize;
extern int fontSizes[8];
extern int statusWindow;
extern int prevStatusWindow;
extern int overallTimer;
extern bool miniSimulation;
extern int creatureWatching;
extern int simulationTimer;
extern int creaturesInPosition[1000];

extern float camZoom;
extern float gravity;
extern float airFriction;

extern float target;
extern float force;
extern float averageX;
extern float averageY;
extern int speed;
extern int id;
extern bool stepbystep;
extern bool stepbystepslow;
extern bool slowDies;
extern int timeShow;
extern int p[29];

extern int viewGenMenu_idx;
extern string viewGenMenu_topText[5];
extern string viewGenMenu_bottomText[5];
extern string viewGenMenu_buttonText[5];
}
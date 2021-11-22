#include <vector>
#include <string>
#include "imgui.h"

#include "Components/Creature.h"
#include "Components/Rectangle.h"
#include "consts.h"

using namespace std;
namespace EC
{

// static const ImVec4 black = ImVec4(Color32::black);
float windowSizeMultiplier = 0.8;
int SEED = 0;

bool haveGround = true;
int histBarsPerMeter = 5;
string operationNames[] = {"#","time","px","py","+","-","*","÷","%","sin","sig","pres"};
int operationAxons[] =    {0,   0,    0,   0,   2,  2,  2,  2,  2,  1,    1,   0};
int operationCount = 12;
string fitnessUnit = "m";
string fitnessName = "Distance";
float baselineEnergy = 0.0;
int energyDirection = 1; // if 1, it'll count up how much energy is used.  if -1, it'll count down from the baseline energy, and when energy hits 0, the creature dies.
float FRICTION = 4;
float bigMutationChance = 0.06;
float hazelStairs = -1;
bool saveFramesPerGeneration = true;

int lastImageSaved = -1;
float pressureUnit = 500.0/2.37;
float energyUnit = 20;
float nauseaUnit = 5;
int minBar = -10;
int maxBar = 100;
int barLen = maxBar-minBar;
int gensToDo = 0;
float cTimer = 60;
float postFontSize = 0.96;
float scaleToFixBug = 1000;
float energy = 0;
float averageNodeNausea = 0;
float totalNodeNausea = 0;

float lineY1 = -0.08; // These are for the lines of text on each node.
float lineY2 = 0.35;
uint32_t axonColor = 0xFFFF00;

int windowWidth = 1280;
int windowHeight = 720;
int timer = 0;
float camX = 0;
float camY = 0;
int frames = 60;
int menu = 0;
int gen = -1;
float sliderX = 1170;
int genSelected = 0;
bool drag = false;
bool justGotBack = false;
int creatures = 0;
int creaturesTested = 0;
int fontSize = 0;
int fontSizes[] = {
  50, 36, 25, 20, 16, 14, 11, 9
};
int statusWindow = -4;
int prevStatusWindow = -4;
int overallTimer = 0;
bool miniSimulation = false;
int creatureWatching = 0;
int simulationTimer = 0;

float camZoom = 0.015;
float gravity = 0.005;
float airFriction = 0.95;

int p[] = {
  0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 
  100, 200, 300, 400, 500, 600, 700, 800, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 999
};
}
#include <vector>
#include <string>
#include "imgui.h"

#include "Components/Creature.h"
#include "consts.h"

using namespace std;
namespace EC
{

// static const ImVec4 black = ImVec4(Color32::black);
float windowSizeMultiplier = 0.8f;
int minBar = -10;
int maxBar = 100;

bool haveGround = true;
int histBarsPerMeter = 5;
float FRICTION = 4.0f;
float bigMutationChance = 0.06f;

float cTimer = 60.0f;
float scaleToFixBug = 1000.0f;

float lineY1 = -0.08f; // These are for the lines of text on each node.
float lineY2 = 0.35f;
uint32_t axonColor = 0xFFFF00;

int windowWidth = 1280;
int windowHeight = 720;
int timer = 0;
// float camX = 0;
// float camY = 0;
int frames = 60;
float sliderX = 1170.0f;
int genSelected = 0;
bool drag = false;
bool justGotBack = false;
int creatures = 0;
int creaturesTested = 0;
int statusWindow = -4;
int prevStatusWindow = -4;
int overallTimer = 0;
bool miniSimulation = false;
int creatureWatching = 0;
int simulationTimer = 0;

float camZoom = 0.015f;
float gravity = 0.005f;
float airFriction = 0.95f;

// int p[29] = {
//   0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 
//   100, 200, 300, 400, 500, 600, 700, 800, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 999
// };
int p[5] = {
  0, 250, 500, 750, 999
};
string p_text[5] = {
  "Best",
  "75th percentile",
  "Median",
  "25th percentile",
  "Worst"
};

int viewGenMenu_idx = 4;
string viewGenMenu_topText[5] = {
  "",
  "",
  "Faster creatures at the top!",
  "Faster creatures are more likely to survive because they can outrun their predators.  Slow creatures get eaten.",
  "These are the creatures of generation #"
};
string viewGenMenu_bottomText[5] = {
  "All 1,000 creatures have been tested.  Now let's sort them!",
  "",
  "Slowest creatures at the bottom. (Going backward = slow)",
  "Because of random chance, a few fast ones get eaten, while a few slow ones survive.",
  "What perils will they face? Find out next time!"
};
string viewGenMenu_buttonText[5] = {
  "Sort",
  "Skip",
  "Kill",
  "Reproduce",
  "Continue"
};
}

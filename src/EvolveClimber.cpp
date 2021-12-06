#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <iostream>

#include "consts.h"
#include "EvolveClimber.h"
#include "HelperFunctions.h"

using namespace EC;

EvolveClimber::EvolveClimber()
: m_alap(false)
, m_stepbystep(false)
, m_stepbystepslow(false)
, m_gen(-1)
, m_genToDo(0)
, m_genToDoInput(1)
, m_maxTime(900)
, m_runUntilGen(1)
, m_SEED(0)
, m_selectionFunction(0)
, m_barCounts(0)
, m_speciesCounts(0)
, m_speciesCum(0)
, m_percentile(0)
, m_topSpeciesCounts(0)
, m_xAxis(0)
{
  srand(m_SEED);

  // array<int,110> beginBar = {};
  array<int,101> beginSpecies = {};  
  m_speciesCounts.push_back(beginSpecies);
  // for (int i = 0; i < 101; ++i)
  // {
  //   beginSpecies[i] = 500;
  // }

  // m_barCounts.push_back(beginBar);
  m_speciesCounts.push_back(beginSpecies);
  m_topSpeciesCounts.push_back(0);
  m_xAxis.push_back(0);

  for (int i = 0; i < 5; ++i)
  {
    vector<float> beginPercentile(1);
    m_percentile.push_back(beginPercentile);
  }
}

void EvolveClimber::onClickASAP()
{
  m_genToDo = 1;
  m_runUntilGen = m_gen + 1;
}

void EvolveClimber::onClickDoXGens()
{
  if (m_genToDoInput > 0)
  {
    m_genToDo = m_genToDoInput;
  }
  m_runUntilGen = m_gen + m_genToDoInput + 1;
}

void EvolveClimber::onClickRunUntil()
{
  if (m_runUntilGen > m_gen)
  {
    m_genToDo = m_runUntilGen - m_gen;
  }
  ++m_runUntilGen;
}

void EvolveClimber::testGen()
{
  // creaturesTested = 0;
  // setGlobalVariables(c.begin() + creaturesTested);
  // camZoom = 0.01;
  // setMenu(5);
  // if (!m_stepbystepslow) {
  for (vector<Creature>::iterator it = m_creaturePopulation.begin(); it != m_creaturePopulation.end(); ++it)
  {
    // simulation variables   
    vector<Node> test_n;
    vector<Muscle> test_m;
    vector<Node>* c_n = it->getN();
    vector<Muscle>* c_m = it->getM();
    for (vector<Node>::iterator it = c_n->begin(); it != c_n->end(); ++it)
    {
      test_n.push_back(it->copyNode());
    }
    for (vector<Muscle>::iterator it = c_m->begin(); it != c_m->end(); ++it)
    {
      test_m.push_back(it->copyMuscle());
    }
    id = it->getId();
    timer = 0;
    // camZoom = 0.01;
    // camX = 0;
    // camY = 0;
    cTimer = it->getCreatureTimer();
    simulationTimer = 0;

    for (int s = 0; s < m_maxTime; s++) {
      simulate(test_n, test_m);
      simulationTimer++;
      timer++;
    }
    it->setD(calcAverages(test_n)*0.2); // scale
  }
  // }
}

void EvolveClimber::compileGenData()
{
  m_creaturePopulationSorted = m_creaturePopulation;
  std::sort(m_creaturePopulationSorted.begin(), m_creaturePopulationSorted.end(), [](Creature& a, Creature& b) { return a.getD() > b.getD(); });

  for (vector<vector<float>>::iterator it = m_percentile.begin(); it != m_percentile.end(); ++it)
  {
    it->push_back(m_creaturePopulationSorted.at(p[it - m_percentile.begin()]).getD());
  }

  m_creatureDatabase.push_back(m_creaturePopulationSorted.at(999).copyCreature(-1));
  m_creatureDatabase.push_back(m_creaturePopulationSorted.at(499).copyCreature(-1));
  m_creatureDatabase.push_back(m_creaturePopulationSorted.at(0).copyCreature(-1));

  // array<int,110> beginBar = {};
  // for (vector<Creature>::iterator it = m_creaturePopulationSorted.begin(); it != m_creaturePopulationSorted.end(); ++it)
  // {
    // int bar = floor(it->getD()*histBarsPerMeter-minBar);
    // if (bar >= 0 && bar < maxBar-minBar)
    // {
    //   ++beginBar[bar];
    // }
  // }

  vector<array<int, 101>>::iterator beginSpecies = m_speciesCounts.end() -1;

  array<int,101> beginSpeciesCounts = {};
  int cum = 0;
  int record = 0;
  int holder = 0;
  for (int i = 0; i < 100; i++) {
    cum += (*beginSpecies)[i];
    beginSpeciesCounts[i+1] = cum;
    if ((*beginSpecies)[i] > record) {
      record = (*beginSpecies)[i];
      holder = i;
    }
  }
  // m_speciesCum.push_back(beginSpeciesCounts);
  m_topSpeciesCounts.push_back(holder);
  m_xAxis.push_back(m_gen+1);

  // if (stepbystep) {
  //   drawScreenImage(0);
  //   setMenu(7);
  // } else {
  //   setMenu(10);
  // }
}

void EvolveClimber::simulate(vector<Node> &n, vector<Muscle> &m) {
  for (vector<Muscle>::iterator it = m.begin(); it != m.end(); ++it)
  {
    it->setThruPeriod(fmod((float(timer)/cTimer)/float(it->getPeriod()), 1.0f));
    float target = it->getCondition() ? it->getContractLength() : it->getExtendLength();
    it->setContracted(it->getCondition());
    it->applyForce(n, target);
  }
  for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
  {
    it->applyGravity();
    it->applyForces();
    it->hitWalls();
  }
}

void EvolveClimber::kill()
{
  for (vector<Creature>::iterator it = m_creaturePopulationSorted.begin(); it != m_creaturePopulationSorted.begin() + 500; ++it)
  {
    float f = float(it - m_creaturePopulationSorted.begin())/1000;
    float rand = (pow(rFloat(-1.0f, 1.0f), 3.0f)+1.0f)/2.0f; //cube function

    switch (m_selectionFunction)
    {
      case 1: rand = 1.0f; break;
      case 2: rand = rFloat(0.0f, 1.0f); break;
      case 3: rand = (float) rInt(0,2); break;
    }

    vector<Creature>::iterator survivor = f <= rand ? it : m_creaturePopulationSorted.end() - (it - m_creaturePopulationSorted.begin() + 1);
    vector<Creature>::iterator dead = f <= rand ? m_creaturePopulationSorted.end() - (it - m_creaturePopulationSorted.begin() + 1) : it;
    survivor->setAlive(true);
    dead->setAlive(false);
  }
  // if (stepbystep) {
  //   drawScreenImage(2);
  //   setMenu(11);
  // } else {
  //   setMenu(12);
  // }
}

void EvolveClimber::reproduce()
{
  ++m_gen;
  --m_genToDo;
  justGotBack = true;
  array<int,101> beginSpecies = {};

  for (vector<Creature>::iterator it = m_creaturePopulationSorted.begin(); it != m_creaturePopulationSorted.begin() + 500; ++it)
  {
    vector<Creature>::iterator original = it->getAlive() ? it: m_creaturePopulationSorted.end() - (it - m_creaturePopulationSorted.begin() + 1);
    vector<Creature>::iterator mutant = it->getAlive() ? m_creaturePopulationSorted.end() - (it - m_creaturePopulationSorted.begin() + 1) : it;

    *original = original->copyCreature(original->getId()+1000);   //duplicate
    *mutant = original->modified(mutant->getId()+1000);       //mutated offspring 1

    toStableConfiguration(*mutant->getN(), *mutant->getM());
    adjustToCenter(*mutant->getN());  
  }
  
  for (vector<Creature>::iterator it = m_creaturePopulationSorted.begin(); it != m_creaturePopulationSorted.end(); ++it)
  {
    m_creaturePopulation.at(it->getId()-m_gen*1000) = it->copyCreature(-1);
    int species = (it->getN()->size()%10)*10 + it->getM()->size()%10;
    ++beginSpecies[species];
  }
  m_speciesCounts.push_back(beginSpecies);

  // drawScreenImage(3);
  // if (stepbystep) {
  //   setMenu(13);
  // } else {
  //   setMenu(1);
  // }
}

float EvolveClimber::calcAverages(vector<Node> &n) {
  float averageX = 0;
  float averageY = 0;
  for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
  {
    averageX += it->getX();
    averageY += it->getY();
  }
  averageX = averageX/n.size();
  averageY = averageY/n.size();

  return averageX;
}

void EvolveClimber::onClickCreate()
{
  m_gen = 0;  
  array<int,101> beginSpecies = {};
  for (int id = 0; id < 1000; ++id) {
    vector<Node> create_n;
    vector<Muscle> create_m;
    int nodeNum = rInt(3,6);
    int muscleNum = rInt(nodeNum-1, nodeNum*3-5);

    for (int i = 0; i < nodeNum; ++i) {
        Node newNode(rFloat(-1.0f, 1.0f), rFloat(-1.0f, 1.0f), 0.0f, 0.0f, 0.4f, rFloat(0.0f, 1.0f)); //replaced all nodes' sizes with 0.4, used to be random(0.1,1), random(0,1)
      create_n.push_back(newNode);
    }

    for (int i = 0; i < muscleNum; ++i) {
      int tc1 = i < nodeNum-1 ? i : rInt(0, nodeNum);
      int tm_creaturePopulationSorted = i < nodeNum-1 ? i+1 : tc1;        
      while (tm_creaturePopulationSorted == tc1) {
        tm_creaturePopulationSorted = rInt(0, nodeNum);
      }

      float rlength1 = rFloat(0.5f,1.5f);
      float rlength2 = rFloat(0.5f,1.5f);
      float rtime1 = rFloat(0.0f,1.0f);
      float rtime2 = rFloat(0.0f,1.0f);

      Muscle newMuscle(rInt(1,3),tc1,tm_creaturePopulationSorted,rtime1,rtime2, min(rlength1,rlength2),max(rlength1,rlength2),isItContracted(rtime1,rtime2),rFloat(0.02f,0.08f));
      create_m.push_back(newMuscle);
    }
    
    toStableConfiguration(create_n, create_m);
    adjustToCenter(create_n);

    Creature newCreature(id, create_n, create_m, 0.0f, true, rFloat(40.0f, 80.0f), 1.0f);
    newCreature.checkForOverlap();
    newCreature.checkForLoneNodes();
    m_creaturePopulation.push_back(newCreature);

    int species = (nodeNum%10)*10 + muscleNum%10;
    ++beginSpecies[species];
  }
  m_speciesCounts.push_back(beginSpecies);
}

void EvolveClimber::toStableConfiguration(vector<Node> &n, vector<Muscle> &m) {
  for (int j = 0; j < 200; ++j) {
    for (vector<Muscle>::iterator it = m.begin(); it != m.end(); ++it)
    {
      it->applyForce(n, it->getContracted() ? it->getContractLength() : it->getExtendLength());
    }
    for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
    {
      it->applyForces();
    }
  }
  for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
  {
    it->setVx(0.0f);
    it->setVy(0.0f);
  }
}

void EvolveClimber::adjustToCenter(vector<Node> &n) {
  float avx = 0.0f;
  float lowY = -1000.0f;
  for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
  {
    avx += it->getX();
    if (it->getY()+it->getM()/2.0f > lowY) {
        lowY = it->getY()+it->getM()/2.0f;
    }
  }
  avx /= (float)n.size();
  for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
  {
    it->incrementX(-avx);
    it->incrementY(-lowY);
  }
}

#include <algorithm>
#include <exception>
#include <stdio.h>
#include <iostream>

#include "EvolveClimber.h"
#include "HelperFunctions.h"

using namespace EC;

EvolveClimber::EvolveClimber()
: m_alap(false)
, m_stepbystep(false)
, m_stepbystepslow(false)
, m_creatures(0)
, m_gen(-1)
, m_genToDo(0)
, m_genToDoInput(1)
, m_runUntilGen(1)
, m_SEED(0)
, m_barCounts(0)
, m_speciesCounts(0)
, m_percentile(0)
, m_topSpeciesCounts(0)
, m_xAxis(0)
{
  srand(m_SEED);

  array<int,110> beginBar = {};
  array<int,101> beginSpecies = {};
  for (int i = 0; i < 101; ++i)
  {
    beginSpecies[i] = 500;
  }

  m_barCounts.push_back(beginBar);
  m_speciesCounts.push_back(beginSpecies);
  m_topSpeciesCounts.push_back(0);
  m_xAxis.push_back(0);

  for (int i = 0; i < 5; ++i)
  {
    vector<float> beginPercentile(1);
    m_percentile.push_back(beginPercentile);
  }
}

void EvolveClimber::genCoroutine()
{
  --m_genToDo;
  runGenASAP();
}
void EvolveClimber::onClickASAP()
{
  m_genToDo = 1;
  m_runUntilGen = m_gen + 1;
}

void EvolveClimber::runGenASAP()
{
  testGen();
  kill();
  reproduce();
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
  creaturesTested = 0;
  setGlobalVariables(c.begin() + creaturesTested);
  // camZoom = 0.01;
  // setMenu(5);
  if (!m_stepbystepslow) {
    for (vector<Creature>::iterator it = c.begin(); it != c.end(); ++it)
    {
      setGlobalVariables(it);
      for (int s = 0; s < 900; s++) {
        simulate();
      }
      setAverages();
      setFitness(it);
    }
    compileGenData();
  }
}

void EvolveClimber::compileGenData()
{
  c2 = c;
  std::sort(c2.begin(), c2.end(), [](Creature& a, Creature& b) { return a.getD() > b.getD(); });

  for (vector<vector<float>>::iterator it = m_percentile.begin(); it != m_percentile.end(); ++it)
  {
    it->push_back(c2.at(p[it - m_percentile.begin()]).getD());
  }

  m_creatureDatabase.push_back(c2.at(999).copyCreature(-1));
  m_creatureDatabase.push_back(c2.at(499).copyCreature(-1));
  m_creatureDatabase.push_back(c2.at(0).copyCreature(-1));

  array<int,110> beginBar = {};
  array<int,101> beginSpecies = {};

  for (vector<Creature>::iterator it = c2.begin(); it != c2.end(); ++it)
  {
    int bar = floor(it->getD()*histBarsPerMeter-minBar);
    if (bar >= 0 && bar < maxBar-minBar)
    {
      ++beginBar[bar];
    }
    int species = (it->getN()->size()%10)*10 + it->getM()->size()%10;
    ++beginSpecies[species];
  }

  array<int,101> beginSpeciesCounts = {};
  int cum = 0;
  int record = 0;
  int holder = 0;
  for (int i = 0; i < 100; i++) {
    cum += beginSpecies[i];
    beginSpeciesCounts[i+1] = cum;
    if (beginSpecies[i] > record) {
      record = beginSpecies[i];
      holder = i;
    }
  }
  m_speciesCounts.push_back(beginSpeciesCounts);
  m_topSpeciesCounts.push_back(holder);
  m_xAxis.push_back(m_gen+1);

  // if (stepbystep) {
  //   drawScreenImage(0);
  //   setMenu(7);
  // } else {
  //   setMenu(10);
  // }
}

void EvolveClimber::simulate() {
  for (vector<Muscle>::iterator it = m.begin(); it != m.end(); ++it)
  {
    it->applyForce(&n);
  }
  for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
  {
    it->applyGravity();
    it->applyForces();
    it->hitWalls();
    it->doMath(&n);
  }
  for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
  {
    it->realizeMathValues();
  }
  averageNodeNausea = totalNodeNausea/n.size();
  simulationTimer++;
  timer++;
}

void EvolveClimber::kill()
{
  for (int j = 0; j < 500; j++) {
    float f = float(j)/1000;
    float rand = (pow(rFloat(-1, 1), 3)+1)/2; //cube function
    slowDies = (f <= rand);
    int j2;
    int j3;
    if (slowDies) {
      j2 = j;
      j3 = 999-j;
    } else {
      j2 = 999-j;
      j3 = j;
    }
    c2.at(j2).setAlive(true);
    c2.at(j3).setAlive(true);
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
  justGotBack = true;
  for (vector<Creature>::iterator it = c2.begin(); it != c2.begin() + 500; ++it)
  {
    int j2 = it->getAlive() ? it - c2.begin() : 999-(it - c2.begin());
    Creature cj = c2.at(j2);
    Creature cj2 = c2.at(999-j2);
    
    c2.at(j2) = cj.copyCreature(cj.getId()+1000);        //duplicate
    
    c2.at(999-j2) = cj.modified(cj2.getId()+1000);   //mutated offspring 1
    n = *c2.at(999-j2).getN();
    m = *c2.at(999-j2).getM();
    toStableConfiguration(n.size(), m.size());
    adjustToCenter(n.size());
  }
  for (vector<Creature>::iterator it = c2.begin(); it != c2.end(); ++it)
  {
    c.at(it->getId()-(m_gen*1000)-1001) = it->copyCreature(-1);
  }
  // drawScreenImage(3);
  ++m_gen;
  --m_genToDo;
  // if (stepbystep) {
  //   setMenu(13);
  // } else {
  //   setMenu(1);
  // }
}

void EvolveClimber::setAverages() {
  averageX = 0;
  averageY = 0;
  for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
  {
    averageX += it->getX();
    averageY += it->getY();
  }
  averageX = averageX/n.size();
  averageY = averageY/n.size();
}

void EvolveClimber::setGlobalVariables(vector<Creature>::iterator thisCreature) {
  n.clear();
  m.clear();
  vector<Node>* c_n = thisCreature->getN();
  vector<Muscle>* c_m = thisCreature->getM();
  for (vector<Node>::iterator it = c_n->begin(); it != c_n->end(); ++it)
  {
    n.push_back(it->copyNode());
  }
  for (vector<Muscle>::iterator it = c_m->begin(); it != c_m->end(); ++it)
  {
    m.push_back(it->copyMuscle());
  }
  id = thisCreature->getId();
  timer = 0;
  camZoom = 0.01;
  camX = 0;
  camY = 0;
  cTimer = thisCreature->getCreatureTimer();
  simulationTimer = 0;
  energy = baselineEnergy;
  totalNodeNausea = 0;
  averageNodeNausea = 0;
}

void EvolveClimber::setFitness(vector<Creature>::iterator it){
  // it->setD(averageX*0.2); // Multiply by 0.2 because a meter is 5 units for some weird reason.
  it->setD(averageX); // Multiply by 0.2 because a meter is 5 units for some weird reason.
}

void EvolveClimber::onClickCreate()
{
    m_gen = 0;
    creatures = 0;
    for (int y = 0; y < 25; y++) {
      for (int x = 0; x < 40; x++) {
        n.clear();
        m.clear();
        int nodeNum = rInt(3,6);
        int muscleNum = rInt(nodeNum-1, nodeNum*3-6);
        for (int i = 0; i < nodeNum; ++i) {
            Node newNode(rFloat(-1, 1), rFloat(-1, 1), 0, 0, 0.4, rFloat(0, 1), rFloat(0,1), 
          floor(rFloat(0,operationCount)),floor(rFloat(0,nodeNum)),floor(rFloat(0,nodeNum))); //replaced all nodes' sizes with 0.4, used to be random(0.1,1), random(0,1)
          n.push_back(newNode);
        }
        for (int i = 0; i < muscleNum; ++i) {
          int tc1 = 0;
          int tc2 = 0;
          int taxon = getNewMuscleAxon(nodeNum);
          if (i < nodeNum-1) {
            tc1 = i;
            tc2 = i+1;
          } else {
            tc1 = rInt(0, nodeNum);
            tc2 = tc1;
            while (tc2 == tc1) {
              tc2 = rInt(0, nodeNum);
            }
          }
          float s = 0.8;
          if (i >= 10) {
            s *= 1.414;
          }
          float len = rFloat(0.5,1.5);
          Muscle newMuscle(taxon, tc1, tc2, len, rFloat(0.02, 0.08));
          m.push_back(newMuscle);
        }
        toStableConfiguration(nodeNum, muscleNum);
        adjustToCenter(nodeNum);
        float heartbeat = rFloat(40.0f, 80.0f);

        vector<Node> newN(n);
        vector<Muscle> newM(m);
        Creature newCreature(y*40+x+1, newN, newM, 0, true, heartbeat, 1.0);
        newCreature.checkForOverlap();
        newCreature.checkForLoneNodes();
        newCreature.checkForBadAxons();
        c.push_back(newCreature);
        // drawCreature(c[y*40+x], x*3+5.5, y*2.5+3, 0);
      }
    }
}

void EvolveClimber::toStableConfiguration(int nodeNum, int muscleNum) {
  for (int j = 0; j < 200; ++j) {
    for (vector<Muscle>::iterator it = m.begin(); it != m.begin() + muscleNum; ++it)
    {
      it->applyForce(&n);
    }
    for (vector<Node>::iterator it = n.begin(); it != n.begin() + nodeNum; ++it)
    {
      it->applyForces();
    }
  }
  for (vector<Node>::iterator it = n.begin(); it != n.begin() + nodeNum; ++it)
    {
      it->setVx(0);
      it->setVy(0);
    }
}

void EvolveClimber::adjustToCenter(int nodeNum) {
  float avx = 0;
  float lowY = -1000;
  for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
  {
    avx += it->getX();
    if (it->getY()+it->getM()/2 > lowY) {
        lowY = it->getY()+it->getM()/2;
    }
  }
  avx /= nodeNum;
  for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
  {
    it->incrementX(-avx);
    it->incrementY(-lowY);
  }
}
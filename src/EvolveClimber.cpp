#include <stdio.h>
#include <iostream>

#include "EvolveClimber.h"
#include "HelperFunctions.h"

using namespace EC;

EvolveClimber::EvolveClimber()
: m_stepbystep(false)
, m_stepbystepslow(false)
, m_creatures(0)
, m_minBar(-10)
, m_maxBar(100)
, m_barLen(m_maxBar-m_minBar)
, m_gen(-1)
, m_SEED(0)
, m_barCounts(m_barLen)
, m_speciesCounts(101, 500)
, m_percentile(29)
, m_topSpeciesCounts(10)
{
    srand(m_SEED);
}

void EvolveClimber::startASAP()
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
    // setMenu(6);
  }
  std::cout << "here" << std::endl;
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
    m_gen = 1;
    creatures = 0;
    for (int y = 0; y < 25; y++) {
      for (int x = 0; x < 40; x++) {
        n.clear();
        m.clear();
        int nodeNum = rInt(3,6);
        int muscleNum = rInt(nodeNum-1, nodeNum*3-6);
        for (int i = 0; i < nodeNum; ++i) {
            Node newNode(rInt(-1, 1), rInt(-1, 1), 0, 0, 0.4, rInt(0, 1), rInt(0,1), 
          floor(rInt(0,operationCount)),floor(rInt(0,nodeNum)),floor(rInt(0,nodeNum))); //replaced all nodes' sizes with 0.4, used to be random(0.1,1), random(0,1)
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
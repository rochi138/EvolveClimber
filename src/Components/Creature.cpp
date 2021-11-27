#include <algorithm>
#include <iostream>

#define _USE_MATH_DEFINES
 
#include <cmath>

#include "Creature.h"
#include "../consts.h"
#include "../HelperFunctions.h"

using namespace std;

namespace EC
{
    Creature::Creature(int tid, vector<Node> tn, vector<Muscle> tm, float td, bool talive, float tct, float tmut) {
        id = tid;
        m = tm;
        n = tn;
        d = td;
        alive = talive;
        creatureTimer = tct;
        mutability = tmut;
    }       
    Creature Creature::modified(int id) {
        Creature modifiedCreature(id, 
        vector<Node>(), vector<Muscle>(), 0, true, creatureTimer+r()*16*mutability, min(mutability*rFloat(0.8, 1.25), 2.0f));
        int n_size = n.size();
        for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it) {
            modifiedCreature.n.push_back(it->modifyNode(mutability,n_size));
        }
        for (vector<Muscle>::iterator it = m.begin(); it != m.end(); ++it) {
            modifiedCreature.m.push_back(it->modifyMuscle(mutability,n_size));
        }
        if (rFloat(0, 1) < bigMutationChance*mutability || n.size() <= 2) { //Add a node
        modifiedCreature.addRandomNode();
        }
        if (rFloat(0, 1) < bigMutationChance*mutability) { //Add a muscle
        modifiedCreature.addRandomMuscle(-1, -1);
        }
        if (rFloat(0, 1) < bigMutationChance*mutability && modifiedCreature.n.size() >= 4) { //Remove a node
        modifiedCreature.removeRandomNode();
        }
        if (rFloat(0, 1) < bigMutationChance*mutability && modifiedCreature.m.size() >= 2) { //Remove a muscle
        modifiedCreature.removeRandomMuscle();
        }
        modifiedCreature.checkForOverlap();
        modifiedCreature.checkForLoneNodes();
        modifiedCreature.checkForBadAxons();
        return modifiedCreature;
    }
    void Creature::checkForOverlap() {
        vector<int> bads(0);
        for (vector<Muscle>::iterator i = m.begin(); i != m.end(); ++i)
        {
            for (vector<Muscle>::iterator j = i+1; j != m.end(); ++j)
            {
                if ( i->getC1() == j->getC1() && i->getC2() == j->getC2() )
                    bads.push_back(i - m.begin());
                else if ( i->getC1() == j->getC2() && i->getC2() == j->getC1() )
                    bads.push_back(i - m.begin());
                else if ( i->getC1() == i->getC2() )
                    bads.push_back(i - m.begin());
            }
        }
        for (int i = bads.size()-1; i >= 0; --i) {
            int b = bads.at(i);
            if (b < m.size()) {
                m.erase(m.begin() + b);
            }
        }
    }
    void Creature::checkForLoneNodes() {
        int n_size = n.size();
        if (n_size >= 3) {
            for (int i = 0; i < n_size; i++)
            {
                int connections = 0;
                int connectedTo = -1;
                for (vector<Muscle>::iterator j = m.begin(); j != m.end(); ++j)
                {
                    if (j->getC1() == i || j->getC2() == i)
                    {
                        connections++;
                        connectedTo = j - m.begin();
                    }
                }
                if (connections <= 1) {
                    int newConnectionNode = floor(rFloat(0, n_size));
                    while (newConnectionNode == i || newConnectionNode == connectedTo) {
                        newConnectionNode = floor(rFloat(0, n_size));
                    }
                    addRandomMuscle(i, newConnectionNode);
                }
            }
        }
    }
    void Creature::checkForBadAxons(){
        int n_size = n.size();
        for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
        {
            if(it->getAxon1() >= n_size){
                it->setAxon1(rand() % n_size);
            }
            if(it->getAxon2() >= n_size){
                it->setAxon2(rand() % n_size);
            }
        }

        for (vector<Muscle>::iterator it = m.begin(); it != m.end(); ++it)
        {
            if(it->getAxon() >= n_size){
                it->setAxon(getNewMuscleAxon(n_size));
            }
        }

        for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
        {
            it->setSafeInput(operationAxons[it->getOperation()] == 0);
        }

        int iterations = 0;
        bool didSomething = false;
        
        while(iterations < 1000){
            didSomething = false;
            for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
            {
                if (!it->getSafeInput())
                {
                    vector<Node>::iterator n_begin = n.begin();
                    if((operationAxons[it->getOperation()] == 1 && (n_begin + it->getAxon1())->getSafeInput()) ||
                    (operationAxons[it->getOperation()] == 2 && (n_begin + it->getAxon1())->getSafeInput() && (n_begin + it->getAxon2())->getSafeInput())){
                        it->setSafeInput(true);
                        didSomething = true;
                    }
                }
            }
            if(!didSomething){
                iterations = 10000;
            }
        }

        for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
        {
            if(!it->getSafeInput()){ // This node doesn't get its input from a safe place.  CLEANSE IT.
                it->setOperation(0);
                it->setValue(rFloat(0,1));
            }
        }
    }
    void Creature::addRandomNode() {
        int parentNode = floor(rFloat(0, n.size()));
        float ang1 = rFloat(0, 2*M_PI);
        float distance = sqrt(rFloat(0, 1));
        float x = n.at(parentNode).getX()+cos(ang1)*0.5*distance;
        float y = n.at(parentNode).getY()+sin(ang1)*0.5*distance;
        
        int newNodeCount = n.size()+1;
        
        Node newNode(x, y, 0, 0, 0.4, rFloat(0, 1), rFloat(0,1), floor(rFloat(0,operationCount)),
        floor(rFloat(0,newNodeCount)),floor(rFloat(0,newNodeCount))); //random(0.1,1),random(0,1)
        n.push_back(newNode);
        int nextClosestNode = 0;
        float record = 100000;

        for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
        {
            int i = it - n.begin();
            if ( i != parentNode)
            {
                if (dist(it->getX()-x, it->getY()-y) < record) {
                    record = dist(it->getX()-x, it->getY()-y);
                    nextClosestNode = i;
                }
            }
        }
        addRandomMuscle(parentNode, n.size()-1);
        addRandomMuscle(nextClosestNode, n.size()-1);
    }
    void Creature::addRandomMuscle(int tc1, int tc2) {
        int axon = getNewMuscleAxon(n.size());
        if (tc1 == -1) {
            tc1 = rand() % n.size();
            tc2 = tc1;
            while (tc2 == tc1 && n.size () >= 2) {
                tc2 = rand() % n.size();
            }
        }
        float len = rFloat(0.5, 1.5);
        if (tc1 != -1) {
            float dx = n.at(tc1).getX() - n.at(tc2).getX();
            float dy = n.at(tc1).getY() - n.at(tc2).getY();
            len = sqrt(dx*dx+dy*dy);
        }
        Muscle newMuscle(axon, tc1, tc2, len, rFloat(0.02, 0.08));
        m.push_back(newMuscle);
    }
    void Creature::removeRandomNode() {
        int choice = rand() % n.size();
        n.erase(n.begin() + choice);
        int i = 0;
        while (i < m.size ()) {
            if (m.at(i).getC1() == choice || m.at(i).getC2() == choice) {
                m.erase(m.begin() + i);
            }
            else {
                ++i;
            }
        }
        for (vector<Muscle>::iterator it = m.begin(); it != m.end(); ++it)
        {
            if(it->getC1() >= choice)   
            {
                it->setC1(it->getC1()-1);
            }
            if(it->getC2() >= choice)   
            {
                it->setC2(it->getC2()-1);
            }
        }
    }
    void Creature::removeRandomMuscle() {
        int choice = floor(rFloat(0, m.size()));
        m.erase(m.begin() + choice);
    }
    Creature Creature::copyCreature(int newID) {
        vector<Node> n2;
        vector<Muscle> m2;

        for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it)
        {
            n2.push_back(it->copyNode());
        }
        for (vector<Muscle>::iterator it = m.begin(); it != m.end(); ++it)
        {
            m2.push_back(it->copyMuscle());
        }
        if (newID == -1) {
            newID = id;
        }
        Creature newCreature(newID, n2, m2, d, alive, creatureTimer, mutability);
        return newCreature;
    }
}

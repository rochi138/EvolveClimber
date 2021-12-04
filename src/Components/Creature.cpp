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
        vector<Node> mod_n;
        vector<Muscle> mod_m;
        int n_size = n.size();
        for (vector<Node>::iterator it = n.begin(); it != n.end(); ++it) {
            mod_n.push_back(it->modifyNode(mutability,n_size));
        }
        for (vector<Muscle>::iterator it = m.begin(); it != m.end(); ++it) {
            mod_m.push_back(it->modifyMuscle(mutability,n_size));
        }

        Creature modifiedCreature(id, mod_n, mod_m, 0.0f, true, creatureTimer+r()*16.0f*mutability, min(mutability*rFloat(0.8f, 1.25f), 2.0f));
        if (rFloat(0.0f, 1.0f) < bigMutationChance*mutability || n.size() <= 2) { //Add a node
        modifiedCreature.addRandomNode();
        }
        if (rFloat(0.0f, 1.0f) < bigMutationChance*mutability) { //Add a muscle
        modifiedCreature.addRandomMuscle(-1, -1);
        }
        if (rFloat(0.0f, 1.0f) < bigMutationChance*mutability && modifiedCreature.n.size() >= 4) { //Remove a node
        modifiedCreature.removeRandomNode();
        }
        if (rFloat(0.0f, 1.0f) < bigMutationChance*mutability && modifiedCreature.m.size() >= 2) { //Remove a muscle
        modifiedCreature.removeRandomMuscle();
        }
        modifiedCreature.checkForOverlap();
        modifiedCreature.checkForLoneNodes();
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
                    int newConnectionNode = floor(rFloat(0.0f, (float)n_size));
                    while (newConnectionNode == i || newConnectionNode == connectedTo) {
                        newConnectionNode = floor(rFloat(0.0f, (float)n_size));
                    }
                    addRandomMuscle(i, newConnectionNode);
                }
            }
        }
    }
    void Creature::addRandomNode() {
        int parentNode = floor(rFloat(0.0f, (float)n.size()));
        float ang1 = rFloat(0.0f, 2*M_PI);
        float distance = sqrt(rFloat(0.0f, 1.0f));
        float x = n.at(parentNode).getX()+cos(ang1)*0.5f*distance;
        float y = n.at(parentNode).getY()+sin(ang1)*0.5f*distance;
        
        Node newNode(x, y, 0.0f, 0.0f, 0.4f, rFloat(0.0f, 1.0f)); //random(0.1,1),random(0,1)
        n.push_back(newNode);
        int nextClosestNode = 0;
        float record = 100000.0f;

        for (vector<Node>::iterator it = n.begin(); it != n.end()-1; ++it)
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
        if (nextClosestNode == n.size() -1)
            std::cout << "nextClosestNode" << std::endl;
        addRandomMuscle(parentNode, n.size()-1);
        addRandomMuscle(nextClosestNode, n.size()-1);
    }
    void Creature::addRandomMuscle(int tc1, int tc2) {
        if (tc1 == -1) {
            tc1 = rInt(0, n.size());
            tc2 = tc1;
            while (tc2 == tc1 && n.size() >= 2) {
                tc2 = rInt(0, n.size());
            }
        }

        float rlength1 = rFloat(0.5f,1.5f);
        float rlength2 = rFloat(0.5f,1.5f);
        float rtime1 = rFloat(0.0f,1.0f);
        float rtime2 = rFloat(0.0f,1.0f);

        if (tc1 != -1) {
            float distance = dist(n.at(tc1).getX(), n.at(tc1).getY(), n.at(tc2).getX(), n.at(tc2).getY());
            float ratio = rFloat(0.01f,0.2f);
            rlength1 = distance*(1.0f-ratio);
            rlength2 = distance*(1.0f+ratio);
        }

        // if (rlength1 == 0.0f || rlength2 == 0.0f)
		// {
		// 	std::cout << "addRandomMuscle" << std::endl;
        //     std::cout << "n.size" << n.size() << std::endl;
        //     std::cout << "tc1: "<< tc1 << std::endl;
        //     std::cout << "tc2: "<< tc2 << std::endl;
        //     std::cout << "rlength1: "<< rlength1 << std::endl;
        //     std::cout << "rlength2: "<< rlength2 << std::endl;
		// }

        Muscle newMuscle(rInt(1,3),tc1,tc2,rtime1,rtime2, min(rlength1,rlength2),max(rlength1,rlength2),isItContracted(rtime1,rtime2),rFloat(0.02f,0.08f));
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
        int choice = floor(rFloat(0.0f, (float)m.size()));
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

#pragma once

#include "Muscle.h"
#include "Node.h"

#include <vector>

using namespace std;

namespace EC
{
    class Creature {
        vector<Node> n;
        vector<Muscle> m;
        float d;
        int id;
        bool alive;
        float creatureTimer;
        float mutability;
        
        public:
        Creature(int tid, vector<Node> tn, vector<Muscle> tm, float td, bool talive, float tct, float tmut);
        Creature modified(int id);

        void checkForOverlap();
        void checkForLoneNodes();
        void addRandomNode();
        void addRandomMuscle(int tc1, int tc2);
        void removeRandomNode();
        void removeRandomMuscle();
        Creature copyCreature(int newID);

        bool getAlive() { return alive; }
        float getD() { return d; }
        int getId() { return id; }
        float getCreatureTimer() { return creatureTimer; }
        vector<Node>* getN() { return &n; }
        vector<Muscle>* getM() { return &m; }

        void setAlive(bool b) { alive = b; }
        void setD(float f) { d = f; }
    };
}

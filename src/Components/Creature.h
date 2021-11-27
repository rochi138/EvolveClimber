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

        private:
        void checkForOverlap();
        void checkForLoneNodes();
        void checkForBadAxons();
        void addRandomNode();
        void addRandomMuscle(int tc1, int tc2);
        void removeRandomNode();
        void removeRandomMuscle();
        Creature copyCreature(int newID);
    };
}

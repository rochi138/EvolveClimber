#pragma once

#include "Muscle.h"
#include "Node.h"

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
        
        Creature(int tid, vector<Node> tn, vector<Muscle> tm, float td, bool talive, float tct, float tmut) {
            id = tid;
            m = tm;
            n = tn;
            d = td;
            alive = talive;
            creatureTimer = tct;
            mutability = tmut;
        }
    };
}

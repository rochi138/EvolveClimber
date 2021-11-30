#pragma once

#include "consts.h"
#include "Components/Creature.h"

#include <algorithm>
#include <array>
#include <experimental/coroutine>
#include <iostream>
#include "imgui.h"

namespace EC
{
    class EvolveClimber
    {
        public:
        EvolveClimber();

        bool getRunCoroutine() { return m_genToDo > 0 || m_alap; }
        int getGen() { return m_gen; };
        int* getGenToDoInput() { return &m_genToDoInput; }
        int* getRunUntilGen() { return &m_runUntilGen; }

        void genCoroutine();
        void onClickCreate();
        void onClickASAP();
        void onClickALAP() { m_alap = true; }
        void onClickStop() { m_alap = false; }
        void onClickDoXGens();
        void onClickRunUntil();
        void testGen();
        void kill();
        void reproduce();

        void toStableConfiguration(int nodeNum, int muscleNum);
        void adjustToCenter(int nodeNum);

        vector<vector<float>>* getPercentile() { return &m_percentile; }
        vector<float>* getXAxis() { return &m_xAxis; }

        private:        
        bool m_alap;
        bool m_stepbystep;
        bool m_stepbystepslow;
        int m_creatures;
        int m_gen;
        int m_genToDo;
        int m_genToDoInput;
        int m_runUntilGen;
        int m_SEED;

        // array lengths cannot be variables
        vector<vector<float>> m_percentile;
        vector<array<int,110>> m_barCounts;
        vector<array<int, 101>> m_speciesCounts;
        vector<float> m_xAxis;
        vector<int> m_topSpeciesCounts;
        vector<Creature> c;
        vector<Creature> c2;
        vector<Node> n;
        vector<Muscle> m;
        vector<Creature> m_creatureDatabase;

        void compileGenData();
        void runGenASAP();
        void simulate();
        void setAverages();
        void setGlobalVariables(vector<Creature>::iterator thisCreature);
        void setFitness(vector<Creature>::iterator it);
    };
}

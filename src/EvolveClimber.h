#pragma once

#include "Components/Creature.h"

#include <array>
#include <vector>
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

        void onClickCreate();
        void onClickASAP();
        void onClickALAP() { m_alap = true; }
        void onClickStop() { m_alap = false; }
        void onClickDoXGens();
        void onClickRunUntil();
        void testGen();
        void compileGenData();
        void kill();
        void reproduce();

        void toStableConfiguration(vector<Node> &n, vector<Muscle> &m);
        void adjustToCenter(vector<Node> &n);

        vector<vector<float>>* getPercentile() { return &m_percentile; }
        vector<float>* getXAxis() { return &m_xAxis; }

        private:        
        bool m_alap;
        bool m_stepbystep;
        bool m_stepbystepslow;
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
        vector<Creature> m_creaturePopulation;
        vector<Creature> c2;
        vector<Creature> m_creatureDatabase;

        
        void simulate(vector<Node> &n, vector<Muscle> &m);
        float calcAverages(vector<Node> &n);
        // void setGlobalVariables(vector<Creature>::iterator thisCreature);
    };
}

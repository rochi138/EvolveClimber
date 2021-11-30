#pragma once

#include "consts.h"
#include "Components/Creature.h"

#include <algorithm>
#include <array>
#include "imgui.h"

namespace EC
{
    class EvolveClimber
    {
        public:
        EvolveClimber();

        int getGen() { return m_gen; };

        void onClickCreate();
        void startASAP();
        void kill();
        void reproduce();

        void toStableConfiguration(int nodeNum, int muscleNum);
        void adjustToCenter(int nodeNum);

        vector<vector<float>>* getPercentile() { return &m_percentile; }
        vector<float>* getXAxis() { return &m_xAxis; }

        private:        
        bool m_stepbystep;
        bool m_stepbystepslow;
        int m_creatures;
        int m_gen;
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
        void simulate();
        void setAverages();
        void setGlobalVariables(vector<Creature>::iterator thisCreature);
        void setFitness(vector<Creature>::iterator it);
    };
}

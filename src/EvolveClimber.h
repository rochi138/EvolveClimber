#pragma once

#include "consts.h"
#include "Components/Creature.h"

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

        void toStableConfiguration(int nodeNum, int muscleNum);
        void adjustToCenter(int nodeNum);

        private:        
        bool m_stepbystep;
        bool m_stepbystepslow;
        int m_creatures;
        int m_minBar;
        int m_maxBar;
        int m_barLen;
        int m_gen;
        int m_SEED;

        vector<float> m_percentile;
        vector<int> m_barCounts;
        vector<int> m_speciesCounts;
        vector<int> m_topSpeciesCounts;
        vector<Creature> c;
        vector<Node> n;
        vector<Muscle> m;

        void simulate();
        void setAverages();
        void setGlobalVariables(vector<Creature>::iterator thisCreature);
        void setFitness(vector<Creature>::iterator it);
    };
}

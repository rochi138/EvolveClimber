#pragma once

#include "consts.h"

#include "imgui.h"

namespace EC
{
    class EvolveClimber
    {
        private:
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

        public:
        EvolveClimber();

        int getGen() { return m_gen; };

        void onClickCreate();

        void toStableConfiguration(int nodeNum, int muscleNum);
        void adjustToCenter(int nodeNum);
    };
}

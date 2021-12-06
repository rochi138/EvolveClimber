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

        vector<Creature>* getCreatureDatabase() { return &m_creatureDatabase; }
        vector<Creature>* getCreaturePopulation() { return &m_creaturePopulation; }
        vector<Creature>* getCreatureSorted() { return &m_creaturePopulationSorted; }
        int getGen() { return m_gen; };
        int* getGenToDoInput() { return &m_genToDoInput; }
        int* getMaxTime() { return &m_maxTime; }
        bool getRunCoroutine() { return m_genToDo > 0 || m_alap; }
        int* getRunUntilGen() { return &m_runUntilGen; }
        int* getSeed() { return &m_SEED; }
        vector<array<int, 101>>* getSpeciesCounts() { return &m_speciesCounts; }
        vector<int>* getTopSpecies() { return &m_topSpeciesCounts; }
        int* getSelectionFunction() { return &m_selectionFunction; }

        void onClickCreate();
        void onClickASAP();
        void onClickALAP() { m_alap = true; }
        void onClickStop() { m_alap = false; m_genToDo = 0; }
        void onClickDoXGens();
        void onClickRunUntil();
        void onClickSeed() { srand(m_SEED); }
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
        int m_maxTime;
        int m_runUntilGen;
        int m_SEED;
        int m_selectionFunction;

        // array lengths cannot be variables
        vector<vector<float>> m_percentile;
        vector<array<int,110>> m_barCounts;
        vector<array<int, 101>> m_speciesCounts;
        vector<array<int, 101>> m_speciesCum;
        vector<float> m_xAxis;
        vector<int> m_topSpeciesCounts;
        vector<Creature> m_creaturePopulation;
        vector<Creature> m_creaturePopulationSorted;
        vector<Creature> m_creatureDatabase;

        
        void simulate(vector<Node> &n, vector<Muscle> &m);
        float calcAverages(vector<Node> &n);
        // void setGlobalVariables(vector<Creature>::iterator thisCreature);
    };
}

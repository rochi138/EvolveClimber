#include <stdio.h>
#include <iostream>

#include "EvolveClimber.h"

using namespace EC;

EvolveClimber::EvolveClimber()
: m_minBar(-10)
, m_maxBar(100)
, m_barLen(m_maxBar-m_minBar)
, m_gen(-1)
, m_SEED(0)
, m_barCounts(m_barLen)
, m_speciesCounts(101, 500)
, m_percentile(29)
, m_topSpeciesCounts(10)
{
    srand(m_SEED);
}

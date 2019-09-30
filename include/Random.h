#pragma once

#include <map>
#include <chrono>
#include <random>


class Random
{
public:

  static void init();

  static int dice(int min, int max);

  //std::random_shuffle(mRecords.begin(), mRecords.end(), Random::myrandom);
  static int myrandom (int i) { return dice(0, i); }

protected:

  static std::default_random_engine generator;

  static std::map<
    std::pair<int, int>,
    std::uniform_int_distribution<int>
  > m_dists;

};

#include "Random.h"


std::default_random_engine Random::generator(0);
std::map<
  std::pair<int, int>,
  std::uniform_int_distribution<int>
> Random::m_dists;

void Random::init()
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  generator = std::default_random_engine(seed);
}


int Random::dice(int a, int b)
{
  auto key = std::make_pair(a, b);
  if (m_dists.find(key) == m_dists.end())
  {
    m_dists[key] = std::uniform_int_distribution<int>(a, b);
  }

  return m_dists[key](generator);

  //std::uniform_int_distribution<int> distribution(a, b);
  //auto dice = std::bind ( distribution, generator );
  //return dice();
}

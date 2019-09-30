#pragma once


class RenderQueueAnimator
{
public:

  RenderQueueAnimator(int t0, int t1)
  {
    m_tMin = t0;
    m_tMax = t1;
  }

  ~RenderQueueAnimator() {}

  void advance(float dt)
  {
    m_timer += dt;
  }

  int getFrame()
  {
    int r = m_tMax - m_tMin;
    if (r <= 0) return m_tMin;
    return m_tMin + (int)(m_timer * m_rate) % r;
  }

  float m_timer = 0.f;
  float m_rate = 12.f;
  int m_tMin = 0;
  int m_tMax = 0;
};

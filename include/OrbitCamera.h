
class OrbitCamera2
{
public:
  OrbitCamera2() { zoom(0); }
  ~OrbitCamera2() {}

  bool move = false;
  bool orbit = false;

  //float heading = 0.7853982f;
  float heading = 0.0f;
  //float pitch = 1.047198f;
  float pitch = 1.18;

  glm::vec3 pivot;

  double mouseBeginMoveX = 0;
  double mouseBeginMoveY = 0;

  glm::vec3 worldMoveBeginClick;
  glm::vec3 worldMoveBeginPivot;

  float beginHeading = 0.0f;
  float beginPitch = 0.0f;

  glm::vec3 getPos()
  {
    return pivot +
      radius *
      glm::vec3(
        sinf(heading) * cosf(pitch),
        cosf(heading) * cosf(pitch),
        sinf(pitch)
      );
  }

  void moveIt(double dx, double dy)
  {
    double worldx = -dx * cos(heading) + dy * sin(heading);
    double worldy = dx * sin(heading) + dy * cos(heading);
    pivot.x += -0.01 * worldx;
    pivot.y += -0.01 * worldy;
  }

  void zoom(int i)
  {
    zoomStep += i;
    if (zoomStep < 1) zoomStep = 1;
    if (zoomStep > 10) zoomStep = 10;
    targetRadius = 10.f + 0.5f * zoomStep * zoomStep;
  }

  void update(float dt)
  {
    float factor = 2.5f; // Zoom speed factor
    if (radius < targetRadius)
    {
      radius += factor * radius * dt;
      if (radius > targetRadius) radius = targetRadius;
    }
    else if (radius > targetRadius)
    {
      radius -= factor * radius * dt;
      if (radius < targetRadius) radius = targetRadius;
    }
  }


protected:
  float radius = 20.f;
  float targetRadius = radius;
  int zoomStep = 8;
};

#include "graphics.h"


// http://cgvr.informatik.uni-bremen.de/teaching/cg_literatur/lighthouse3d_view_frustum_culling/index.html
class ViewFrustum
{
public:
  ViewFrustum();
  ~ViewFrustum();
  // void setProj(glm::mat4 Proj);
  // void setOrigin(glm::vec3 x);
  void setCamInternals(float angle, float ratio, float nearD, float farD);
  void setCamDef(glm::vec3 p, glm::vec3 l, glm::vec3 u); // LOokAt def

  int testSphere(glm::vec3 p, float r);

  void runTests();

protected:
  enum {
    TOP = 0, BOTTOM, LEFT,
    RIGHT, NEARP, FARP
  };

  //glm::vec4[4] m_plane;

  struct Plane {
    Plane() : Plane(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f))
    {}
    Plane(glm::vec3 n, glm::vec3 p)
    {
      normal = n;
      point = p;
      plane = glm::vec4(n.x, n.y, n.z, -glm::dot(n, p));
    }
    glm::vec3 normal;
    glm::vec3 point;
    glm::vec4 plane;
    // Signed distance
    float distance(glm::vec3 x)
    {
      return glm::dot(normal, x) + plane[3];
      // glm::vec3 p = x - point;
      // float sn = -glm::dot(normal, p);
      // // float sd =  glm::dot(normal, normal);
      // // float sb =  sn / sd;
      // // glm::vec3 b = x + sb * normal;
      // // return glm::distance(x, b);
      // return sn;
    }
  };
  Plane pl[6];

  //glm::vec3 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
  float nearD, farD, ratio, angle, tang;
  float nw, nh, fw, fh;
};

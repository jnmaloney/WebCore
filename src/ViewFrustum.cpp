#include "ViewFrustum.h"
#include <iostream>


ViewFrustum::ViewFrustum()
{

}


ViewFrustum::~ViewFrustum()
{

}


void ViewFrustum::setCamInternals(float angle, float ratio, float nearD, float farD)
{
  // store the information
	this->ratio = ratio;
	this->angle = angle;
	this->nearD = nearD;
	this->farD = farD;

	// compute width and height of the near and far plane sections
	//tang = (float)tan(glm::radians(angle) * 0.5);
  tang = tanf(angle * 0.5f);
	nh = nearD * tang;
	nw = nh * ratio;
	fh = farD  * tang;
	fw = fh * ratio;
}


void ViewFrustum::setCamDef(glm::vec3 p, glm::vec3 l, glm::vec3 u)
{
  glm::vec3 dir, nc, fc, X, Y, Z;

  // compute the Z axis of camera
  // this axis points in the opposite direction from
  // the looking direction
  Z = p - l;
  Z = glm::normalize(Z);

  // X axis of camera with given "up" vector and Z axis
  X = glm::cross(u, Z);
  X = glm::normalize(X);

  // the real "up" vector is the cross product of Z and X
  Y = glm::cross(Z, X);

  // compute the centers of the near and far planes
  nc = p - Z * nearD;
  fc = p - Z * farD;

  // // Long form compute corners
  // glm::vec3 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
  //
  // // compute the 4 corners of the frustum on the near plane
  // ntl = nc + Y * nh - X * nw;
  // ntr = nc + Y * nh + X * nw;
  // nbl = nc - Y * nh - X * nw;
  // nbr = nc - Y * nh + X * nw;
  //
  // // compute the 4 corners of the frustum on the far plane
  // ftl = fc + Y * fh - X * fw;
  // ftr = fc + Y * fh + X * fw;
  // fbl = fc - Y * fh - X * fw;
  // fbr = fc - Y * fh + X * fw;

  // Alternative compute 8 corners
	pl[NEARP] = Plane(-Z, nc);
	pl[FARP] = Plane(Z, fc);

	glm::vec3 aux, normal;

	aux = (nc + Y*nh) - p;
	aux = glm::normalize(aux);
	normal = glm::cross(aux, X);
	pl[TOP] = Plane(normal, nc+Y*nh);

	aux = (nc - Y*nh) - p;
  aux = glm::normalize(aux);
	normal = glm::cross(X, aux);
  // std::cout << X[0] << " "
  //           << X[1] << " "
  //           << X[2] << std::endl;
  // std::cout << aux[0] << " "
  //           << aux[1] << " "
  //           << aux[2] << std::endl;
  // std::cout << normal[0] << " "
  //           << normal[1] << " "
  //           << normal[2] << std::endl;
	pl[BOTTOM] = Plane(normal, nc-Y*nh);

	aux = (nc - X*nw) - p;
  aux = glm::normalize(aux);
	normal = glm::cross(aux, Y);
	pl[LEFT] = Plane(normal, nc-X*nw);

	aux = (nc + X*nw) - p;
  aux = glm::normalize(aux);
	normal = glm::cross(Y, aux);
	pl[RIGHT] = Plane(normal, nc+X*nw);

  // TEST
  // std::cout << p.x << " " << p.y << " " << p.z << std::endl;
  // // std::cout << pl[LEFT].distance(p) << std::endl;
  // // std::cout << pl[RIGHT].distance(p) << std::endl;
  // // std::cout << pl[TOP].distance(p) << std::endl;
  // // std::cout << pl[BOTTOM].distance(p) << std::endl;
  // // std::cout << pl[LEFT].distance(l) << std::endl;
  // // std::cout << pl[RIGHT].distance(l) << std::endl;
  // // std::cout << pl[TOP].distance(l) << std::endl;
  // // std::cout << pl[BOTTOM].distance(l) << std::endl;
  //
  // std::cout << pl[1].plane[0] << " "
  //           << pl[1].plane[1] << " "
  //           << pl[1].plane[2] << " "
  //           << pl[1].plane[3] << std::endl;
}


int ViewFrustum::testSphere(glm::vec3 p, float radius)
{
  int INSIDE = 1;
  int INTERSECT = 0;
  int OUTSIDE = -1;

	float distance;
	int result = INSIDE;

	//for (int i=0; i < 6; i++)
  for (int i = 0; i < 4; i++)
  {
		distance = pl[i].distance(p);
		if (distance < -radius)
			return OUTSIDE;
		else if (distance < radius)
			result = INTERSECT;
	}
	return result;
}


void ViewFrustum::runTests()
{
  Plane p;
  p = Plane(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f));
  std::cout << p.distance(glm::vec3(0.f, 0.f, -2.f)) << std::endl;
  std::cout << p.distance(glm::vec3(0.f, 0.f, 0.f)) << std::endl;
  std::cout << p.distance(glm::vec3(0.f, 0.f, 2.f)) << std::endl;
}

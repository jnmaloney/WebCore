#pragma once


#include "BulletCollision/CollisionShapes/btBox2dShape.h"
#include "BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.h"
#include "BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.h"
#include "BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.h"

#include "BulletCollision/CollisionShapes/btBox2dShape.h"
#include "BulletCollision/CollisionShapes/btConvex2dShape.h"
#include "BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.h"

#include "btBulletDynamicsCommon.h"

#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include <vector>


class PhysicsLevel
{
public:
  PhysicsLevel();
  ~PhysicsLevel();

  void init();

  void addTile(int x_min, int x_max, int y_min, int y_max);
  void addTile(int x_min, int x_max, int y_min, int y_max, int t);

  void addDynamic(int x, int y);

  void getDynamicPosition(float*x, float*y);

  void step(double dt);

  void addDynamicImpulse(int d);
  void dynamicGravityReduce();
  void dynamicZoom();
  void normalGravity();

  void jumpDynamic();
  void jumpDynamicHold(float dt);

  void addTrigger(int x_min, int x_max, int y_min, int y_max);
  bool isTrigger(int i);

  btCollisionObject* addPickup(int x_min, int x_max, int y_min, int y_max, void* user_ptr);
  void removeCollisionObject(btCollisionObject* ob);

  void contactPoints(bool*, bool*, bool*, bool*);

  btScalar getDynamicYDir();

  int getNumGhosts();
  void getGhostInfo(int j, void** out_ptr, int* out_index1, int* out_index2);

  bool digDown(float* x, float* y);
  void removeAt(float x, float y);
  void digAt(float x, float y, std::vector<int>& in_oldBrokenTiles, std::vector<int>& out_newBrokenTiles);

protected:

  // Without RLE
  void addTile_(int x_min, int x_max, int y_min, int y_max, int t);

  // Return normal if body exists in manifold...
  btCollisionObject* getContactNormal(btPersistentManifold* manifold, btCollisionObject* body, btVector3* out_normal);

  //keep the collision shapes, for deletion/cleanup
	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
	btBroadphaseInterface* m_broadphase;
	btCollisionDispatcher* m_dispatcher;
	btConstraintSolver* m_solver;
	btDefaultCollisionConfiguration* m_collisionConfiguration;
	btDiscreteDynamicsWorld* m_dynamicsWorld;

	//data for picking objects
	// class btRigidBody* m_pickedBody;
	// class btTypedConstraint* m_pickedConstraint;
	// int m_savedState;
	// btVector3 m_oldPickingPos;
	// btVector3 m_hitPos;
	// btScalar m_oldPickingDist;

  //keep the collision shapes, for deletion/cleanup
  btConvex2dConvex2dAlgorithm::CreateFunc* m_convexAlgo2d;
  btVoronoiSimplexSolver* m_simplexSolver;
  btMinkowskiPenetrationDepthSolver* m_pdSolver;
  btBox2dBox2dCollisionAlgorithm::CreateFunc* m_box2dbox2dAlgo;

  btRigidBody* m_dynamicBody;
  btGhostObject* m_dynamicGhost;
  btGhostObject* m_specialGhost;

  btAlignedObjectArray<btGhostObject*> m_ghostObjects;

  bool m_rle = false;
  int m_rle_x_min;
  int m_rle_x_max;
  int m_rle_y_min;
  int m_rle_y_max;
};

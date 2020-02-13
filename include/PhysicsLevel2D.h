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


class PhysicsLevel2D
{
public:
  PhysicsLevel2D();
  ~PhysicsLevel2D();

  void init();
  void init(float gravity);

  void step(double dt);

  // A fixed, immovable square
  void addTile(int x_min, int x_max, int y_min, int y_max);
  void addTile(int x_min, int x_max, int y_min, int y_max, int t);

  // Add the player object
  void addDynamic(int x, int y, int w, int h);
  void getDynamicPosition(float*x, float*y);
  void addDynamicImpulse(int d);
  void dynamicGravityReduce();
  void dynamicZoom();
  void normalGravity();
  void jumpDynamic();
<<<<<<< HEAD
  void jumpDynamicWall(int i);
=======
>>>>>>> 51cef8f22afefb184093a34d45f0818a38d0d2d5
  void jumpDynamicHold(float dt);
  void contactPoints(bool*, bool*, bool*, bool*);
  btScalar getDynamicYDir();

<<<<<<< HEAD
  // TODO
  void freezeDynamic() {}
  void unfreezeDynamic() {}
  void jumpDynamic(float x) {}
  void addDynamicImpulse(float d, int mode) {}
  void jumpLaunchDynamic(float d) {}
  static std::vector<float> contactTop;
  static std::vector<float> contactBottom;
  static std::vector<float> contactLeft;
  static std::vector<float> contactRight;
  static int mCallbacksThisFrame;

=======
>>>>>>> 51cef8f22afefb184093a34d45f0818a38d0d2d5
  // A space that tracks being touched by objects
  void addTrigger(int x_min, int x_max, int y_min, int y_max);
  bool isTrigger(int i);

  // Special tracking items Ghost/Dynamiic
  btCollisionObject* addPickup(int x_min, int x_max, int y_min, int y_max, void* user_ptr);
  void removeCollisionObject(btCollisionObject* ob);

  // Ghosts
  int getNumGhosts();
  void getGhostInfo(int j, void** out_ptr, int* out_index1, int* out_index2);

  // Editing tiles
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
	btDiscreteDynamicsWorld* m_dynamicsWorld = 0;

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

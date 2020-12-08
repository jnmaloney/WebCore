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

  void init(float gravity);

  void step(double dt);

  // A fixed, immovable square
  // void addTile(int x_min, int x_max, int y_min, int y_max);
  // void addTile(int x_min, int x_max, int y_min, int y_max, int t);
  void addConvex(void* shape, int flags);

  // Add the player object
  btCollisionObject* addDynamic(int x_min, int x_max, int y_min, int y_max, void* user_ptr);
  btCollisionObject* addPickup(int x_min, int x_max, int y_min, int y_max, void* user_ptr);
  //btRigidBody* body,

  // Special tracking items Ghost/Dynamiic
  btCollisionObject* addGhost(int x_min, int x_max, int y_min, int y_max, void* user_ptr);
  void removeCollisionObject(btCollisionObject* ob);

  // Ghosts
  int getNumGhosts();
  void getGhostInfo(int j, void** out_ptr, int* out_index1, int* out_index2);

  class PhysicsGlobal
  {
  public:
    //keep the collision shapes, for deletion/cleanup
    btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
    btBroadphaseInterface* m_broadphase;
    btCollisionDispatcher* m_dispatcher;
    btConstraintSolver* m_solver;
    btDefaultCollisionConfiguration* m_collisionConfiguration;

    //keep the collision shapes, for deletion/cleanup
    btConvex2dConvex2dAlgorithm::CreateFunc* m_convexAlgo2d;
    btVoronoiSimplexSolver* m_simplexSolver;
    btMinkowskiPenetrationDepthSolver* m_pdSolver;
    btBox2dBox2dCollisionAlgorithm::CreateFunc* m_box2dbox2dAlgo;

    void init();
  private:
    bool m_init = false;
  };

protected:

  // Return normal if body exists in manifold...
  btCollisionObject* getContactNormal(btPersistentManifold* manifold, btCollisionObject* body, btVector3* out_normal);

	btDiscreteDynamicsWorld* m_dynamicsWorld = 0;
  btAlignedObjectArray<btRigidBody*> m_dynamicObjects;
  btAlignedObjectArray<btGhostObject*> m_ghostObjects;
};

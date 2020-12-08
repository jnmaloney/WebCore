#define USE_BULLET 1
#ifdef USE_BULLET
#include "PhysicsLevel2D.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>


// TODO Game params.
const int GROUND_1 = 1;
const int GROUND_2 = 2;
const int PLAYER = 4;
const int TRIGGER = 8;
const int CONTACT_1 = 16;
const int CONTACT_2 = 32;
//const int PICKUP = 16;


// TODO statics
// std::vector<float> PhysicsLevel2D::contactTop = {0, 0};
// std::vector<float> PhysicsLevel2D::contactBottom = {0, 0};
// std::vector<float> PhysicsLevel2D::contactLeft = {0, 0};
// std::vector<float> PhysicsLevel2D::contactRight = {0, 0};
// int PhysicsLevel2D::mCallbacksThisFrame = 0;
// void addPtTop(float pt)
// {
//   if (pt < PhysicsLevel2D::contactTop[0])
//   {
//     PhysicsLevel2D::contactTop[0] = pt;
//   }
//   if (pt > PhysicsLevel2D::contactTop[1])
//   {
//     PhysicsLevel2D::contactTop[1] = pt;
//   }
// }

// void addPtBottom(float pt)
// {
//   if (pt < PhysicsLevel2D::contactBottom[0])
//   {
//     PhysicsLevel2D::contactBottom[0] = pt;
//   }
//   if (pt > PhysicsLevel2D::contactBottom[1])
//   {
//     PhysicsLevel2D::contactBottom[1] = pt;
//   }
// }

// void addPtLeft(float pt)
// {
//   if (pt < PhysicsLevel2D::contactLeft[0])
//   {
//     PhysicsLevel2D::contactLeft[0] = pt;
//   }
//   if (pt > PhysicsLevel2D::contactLeft[1])
//   {
//     PhysicsLevel2D::contactLeft[1] = pt;
//   }
// }

// void addPtRight(float pt)
// {
//   if (pt < PhysicsLevel2D::contactRight[0])
//   {
//     PhysicsLevel2D::contactRight[0] = pt;
//   }
//   if (pt > PhysicsLevel2D::contactRight[1])
//   {
//     PhysicsLevel2D::contactRight[1] = pt;
//   }
// }


void btNearCallback_custom(btBroadphasePair& collisionPair, btCollisionDispatcher& dispatcher, const btDispatcherInfo& dispatchInfo)
{
  btCollisionObject* colObj0 = (btCollisionObject*)collisionPair.m_pProxy0->m_clientObject;
  btCollisionObject* colObj1 = (btCollisionObject*)collisionPair.m_pProxy1->m_clientObject;

  // if (PhysicsLevel2D::mCallbacksThisFrame == 0)
  // {
  //   PhysicsLevel2D::contactTop[0] = FLT_MAX;
  //   PhysicsLevel2D::contactTop[1] = FLT_MIN;
  //   PhysicsLevel2D::contactBottom[0] = FLT_MAX;
  //   PhysicsLevel2D::contactBottom[1] = FLT_MIN;
  //   PhysicsLevel2D::contactLeft[0] = FLT_MAX;
  //   PhysicsLevel2D::contactLeft[1] = FLT_MIN;
  //   PhysicsLevel2D::contactRight[0] = FLT_MAX;
  //   PhysicsLevel2D::contactRight[1] = FLT_MIN;
  // }
  // ++PhysicsLevel2D::mCallbacksThisFrame;

  if (dispatcher.needsCollision(colObj0, colObj1))
  {
    btCollisionObjectWrapper obj0Wrap(0, colObj0->getCollisionShape(), colObj0, colObj0->getWorldTransform(), -1, -1);
    btCollisionObjectWrapper obj1Wrap(0, colObj1->getCollisionShape(), colObj1, colObj1->getWorldTransform(), -1, -1);

    //dispatcher will keep algorithms persistent in the collision pair
    if (!collisionPair.m_algorithm)
    {
      collisionPair.m_algorithm = dispatcher.findAlgorithm(&obj0Wrap, &obj1Wrap, 0/*, BT_CONTACT_POINT_ALGORITHMS*/);
    }

    if (collisionPair.m_algorithm)
    {
      btManifoldResult contactPointResult(&obj0Wrap, &obj1Wrap);

      if (dispatchInfo.m_dispatchFunc == btDispatcherInfo::DISPATCH_DISCRETE)
      {
        //discrete collision detection query
        collisionPair.m_algorithm->processCollision(&obj0Wrap, &obj1Wrap, dispatchInfo, &contactPointResult);
      }
      else
      {
        //continuous collision detection query, time of impact (toi)
        btScalar toi = collisionPair.m_algorithm->calculateTimeOfImpact(colObj0, colObj1, dispatchInfo, &contactPointResult);
        if (dispatchInfo.m_timeOfImpact > toi)
          dispatchInfo.m_timeOfImpact = toi;
      }
		}
  }
}


void PhysicsLevel2D::PhysicsGlobal::init()
{
	if (m_init) return;

  // Set up the bullet world
	m_simplexSolver = new btVoronoiSimplexSolver();
	m_pdSolver = new btMinkowskiPenetrationDepthSolver();
	m_convexAlgo2d = new btConvex2dConvex2dAlgorithm::CreateFunc(m_simplexSolver, m_pdSolver);
	m_box2dbox2dAlgo = new btBox2dBox2dCollisionAlgorithm::CreateFunc();
	m_broadphase = new btDbvtBroadphase();	//m_broadphase = new btSimpleBroadphase();
	m_solver = new btSequentialImpulseConstraintSolver;
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

  m_dispatcher->setNearCallback(&btNearCallback_custom);
	m_dispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE, CONVEX_2D_SHAPE_PROXYTYPE, m_convexAlgo2d);
	m_dispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE, CONVEX_2D_SHAPE_PROXYTYPE, m_convexAlgo2d);
	m_dispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE, BOX_2D_SHAPE_PROXYTYPE, m_convexAlgo2d);
	m_dispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE, BOX_2D_SHAPE_PROXYTYPE, m_box2dbox2dAlgo);

	m_init = true;
}


PhysicsLevel2D::PhysicsGlobal g_global;


PhysicsLevel2D::PhysicsLevel2D()
{

}


PhysicsLevel2D::~PhysicsLevel2D()
{

}


void PhysicsLevel2D::init(float gravity)
{
  g_global.init();

	m_dynamicsWorld = new btDiscreteDynamicsWorld(g_global.m_dispatcher, g_global.m_broadphase, g_global.m_solver, g_global.m_collisionConfiguration);
	m_dynamicsWorld->setGravity(btVector3(0, gravity, 0));

	//
	// Set Ghost Callback (register with collision world)
	//
	g_global.m_broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
}


void PhysicsLevel2D::addDynamic(int x, int y, int w, int h)
{
	btCollisionShape* boxShape = new btBoxShape(btVector3(btScalar(0.5*w), btScalar(0.5*h), btScalar(100.)));

	//m_collisionShapes.push_back(boxShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(x, y, 0));

	//We can also use DemoApplication::localCreateRigidBody, but for clarity it is provided here:
	{
		btScalar mass(1.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			boxShape->calculateLocalInertia(mass, localInertia);

		// using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, boxShape, localInertia);
		rbInfo.m_friction = btScalar(0);
		btRigidBody* body = new btRigidBody(rbInfo);
    body->setUserPointer( (void*)1 );

		body->setLinearFactor(btVector3(1, 1, 0));
		body->setAngularFactor(btVector3(0, 0, 0));

		//	add the body to the dynamics world
		m_dynamicsWorld->addRigidBody(body);
		//m_dynamicsWorld->addCollisionObject(body);

		//m_dynamicBody = body;
		//m_dynamicBody->setActivationState(DISABLE_DEACTIVATION);

		//body->setCollisionFlags(body->getCollisionFlags()| GROUND_1);
		body->getBroadphaseHandle()->m_collisionFilterGroup = CONTACT_2;
		body->getBroadphaseHandle()->m_collisionFilterMask = GROUND_2;
	}


	// if (m_dynamicGhost == 0)
	// {
	// 	btGhostObject* g = new btPairCachingGhostObject();
	// 	m_ghostObjects.push_back(g);
	// 	g->setCollisionFlags( g->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	// 	g->setCollisionShape(boxShape);
	// 	//g->setWorldTransform(groundTransform);
	// 	g->setActivationState(DISABLE_DEACTIVATION);

	// 	m_dynamicsWorld->addCollisionObject(g);

	// 	m_dynamicGhost = g;

	// 	//m_dynamicGhost->setCollisionFlags(m_dynamicGhost->getCollisionFlags() | TRIGGER);
	// 	m_dynamicGhost->getBroadphaseHandle()->m_collisionFilterGroup = PLAYER;
	// 	m_dynamicGhost->getBroadphaseHandle()->m_collisionFilterMask = TRIGGER;
	// }

	// if (m_specialGhost == 0)
	// {
	// 	btCollisionShape* tinyBoxShape = new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(100.)));

	// 	btGhostObject* g = new btPairCachingGhostObject();
	// 	m_ghostObjects.push_back(g);
	// 	g->setCollisionFlags( g->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	// 	g->setCollisionShape(tinyBoxShape);
	// 	//g->setWorldTransform(groundTransform);
	// 	g->setActivationState(DISABLE_DEACTIVATION);

	// 	m_dynamicsWorld->addCollisionObject(g);

	// 	m_specialGhost = g;

	// 	g->getBroadphaseHandle()->m_collisionFilterGroup = CONTACT_2;
	// 	g->getBroadphaseHandle()->m_collisionFilterMask = GROUND_2;
	// }
}


void PhysicsLevel2D::getDynamicPosition(btRigidBody* body, float* x, float* y)
{
	if (body)
	{
		btTransform bodyWorldTransform;
		body->getMotionState()->getWorldTransform(bodyWorldTransform);
		btVector3 bodyOrigin = bodyWorldTransform.getOrigin();
		*x = bodyOrigin.x();
		*y = bodyOrigin.y();
	}
}


void PhysicsLevel2D::step(double dt)
{
  // if (PhysicsLevel2D::mCallbacksThisFrame == 0)
  // {
  //   PhysicsLevel2D::contactTop[0] = FLT_MAX;
  //   PhysicsLevel2D::contactTop[1] = FLT_MIN;
  //   PhysicsLevel2D::contactBottom[0] = FLT_MAX;
  //   PhysicsLevel2D::contactBottom[1] = FLT_MIN;
  //   PhysicsLevel2D::contactLeft[0] = FLT_MAX;
  //   PhysicsLevel2D::contactLeft[1] = FLT_MIN;
  //   PhysicsLevel2D::contactRight[0] = FLT_MAX;
  //   PhysicsLevel2D::contactRight[1] = FLT_MIN;
  // }
  // PhysicsLevel2D::mCallbacksThisFrame = 0; // Collision

	if (m_dynamicsWorld)
	{
		m_dynamicsWorld->stepSimulation(dt, 0);
	}

	// Ghost of player - update position
	// if (m_dynamicGhost)
	// {
	// 	m_dynamicGhost->setWorldTransform(m_dynamicBody->getWorldTransform());
	// }

	// if (m_specialGhost)
	// {
	// 	m_specialGhost->setWorldTransform(m_dynamicBody->getWorldTransform());
	// }
}


void PhysicsLevel2D::addDynamicImpulse(btRigidBody* body, int d)
{
	double x0 = body->getLinearVelocity().x();
	double x1 = 100 * d;
	double x = 16 * (x1 - x0) / 30.0;
	double y = 0;
	double z = 0;
	body->applyCentralImpulse(btVector3(x, y, z));
}


void PhysicsLevel2D::jumpDynamic(btRigidBody* body)
{
	double x = 0;
  double y = -6400 / 30.0;
	double z = 0;
	body->applyCentralImpulse(btVector3(x, y, z));
}


void PhysicsLevel2D::addTrigger(int x_min, int x_max, int y_min, int y_max)
{
	double w = 0.5 * (x_max - x_min);
	double h = 0.5 * (y_max - y_min);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(x_min + w, y_min + h, 0));

	btCollisionShape* boxShape = new btBoxShape(btVector3(btScalar(0.5*w), btScalar(0.5*h), btScalar(100.)));

	btGhostObject* g = new btPairCachingGhostObject();
	m_ghostObjects.push_back(g);
	g->setCollisionFlags(g->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	g->setCollisionShape(boxShape);
	g->setWorldTransform(groundTransform);

	g->setActivationState(DISABLE_DEACTIVATION);

	m_dynamicsWorld->addCollisionObject(g);
}


bool PhysicsLevel2D::isTrigger(btRigidBody* body, int i)
{
	for (int j = 0; j < m_ghostObjects[i]->getNumOverlappingObjects(); ++j)
	{
		if (m_ghostObjects[i]->getOverlappingObject(j) == m_dynamicBody)
		{
			return 1;
		}
	}
	return 0;
}


void PhysicsLevel2D::contactPoints(bool* ground,	bool* ceiling,	bool* wallLeft,	bool* wallRight)
{
	int numManifolds = m_dispatcher->getNumManifolds();
	for (int i = 0; i < numManifolds; ++i)
	{
		btPersistentManifold* contactManifold =  m_dispatcher->getManifoldByIndexInternal(i);
		btVector3 normal;
		if (getContactNormal(contactManifold, m_dynamicBody, &normal))
		{
			// if (normal.dot(worldUp) > UPWARD_NORMAL_THRESHOLD)
			// {
			//
			// }

			//ImGui::Text("%.1f, %.1f, %.1f", normal.x(), normal.y(), normal.z());

			//break;
			if (normal.y() == -1)
			{
				*ground = true;
			}
			if (normal.y() == 1)
			{
				*ceiling = true;
			}
			if (normal.x() == -1)
			{
				*wallRight = true;
			}
			if (normal.x() == 1)
			{
				*wallLeft = true;
			}
		}
	}
}


btCollisionObject* PhysicsLevel2D::getContactNormal(btPersistentManifold* manifold, btCollisionObject* body, btVector3* out_normal)
{
	if (manifold->getNumContacts() == 0) return 0;

	btCollisionObject* returnBody;

	const btCollisionObject* objectA = static_cast<const btCollisionObject*>(manifold->getBody0());
	const btCollisionObject* objectB = static_cast<const btCollisionObject*>(manifold->getBody1());

	bool otherBody = 0;
  btScalar sign = 1;
	if (objectA == body)
	{
		otherBody = 1;
		returnBody = (btCollisionObject*)(manifold->getBody1());
	}

	if (objectB == body)
	{
		otherBody = 1;
		sign = -1;
		returnBody = (btCollisionObject*)(manifold->getBody0());
	}

	if (otherBody == 0) return 0;

	if (out_normal)
		*out_normal = sign * manifold->getContactPoint(0).m_normalWorldOnB;

	return returnBody;
}


btScalar PhysicsLevel2D::getDynamicYDir()
{
	return m_dynamicBody->getLinearVelocity().y();
}


btCollisionObject* PhysicsLevel2D::addPickup(int x_min, int x_max, int y_min, int y_max, void* user_ptr)
{
	int w = x_max - x_min;
	int h = y_max - y_min;

	int x = x_min + 0.5 * w;
	int y = y_min + 0.5 * y;

	btCollisionShape* boxShape = new btBoxShape(btVector3(btScalar(0.5*w), btScalar(0.5*h), btScalar(100.)));

	m_collisionShapes.push_back(boxShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(x, y, 0));

	//We can also use DemoApplication::localCreateRigidBody, but for clarity it is provided here:
	{
		btScalar mass(1.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			boxShape->calculateLocalInertia(mass, localInertia);

		// using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, boxShape, localInertia);
		rbInfo.m_friction = btScalar(1.0);
		btRigidBody* body = new btRigidBody(rbInfo);

		body->setLinearFactor(btVector3(1, 1, 0));
		body->setAngularFactor(btVector3(0, 0, 0));

		//	add the body to the dynamics world
		m_dynamicsWorld->addRigidBody(body);

		body->setActivationState(DISABLE_DEACTIVATION);
		//body->setCollisionFlags(body->getCollisionFlags()| GROUND_2 | TRIGGER);
		body->getBroadphaseHandle()->m_collisionFilterGroup = CONTACT_1 | TRIGGER;
		body->getBroadphaseHandle()->m_collisionFilterMask = GROUND_1 | PLAYER;

		//((btCollisionObject*)body)->setUserIndex(1);
		((btCollisionObject*)body)->setUserPointer(user_ptr);
		return body;
	}
}


btCollisionObject* PhysicsLevel2D::addEnemy(int x_min, int x_max, int y_min, int y_max, void* user_ptr)
{
	int w = x_max - x_min;
	int h = y_max - y_min;

	int x = x_min + 0.5 * w;
	int y = y_min + 0.5 * y;

	btCollisionShape* boxShape = new btBoxShape(btVector3(btScalar(0.5*w), btScalar(0.5*h), btScalar(100.)));

	m_collisionShapes.push_back(boxShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(x, y, 0));

	// localCreateRigidBody:
	{
		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			boxShape->calculateLocalInertia(mass, localInertia);

		// using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, boxShape, localInertia);
		rbInfo.m_friction = btScalar(0.0);
		btRigidBody* body = new btRigidBody(rbInfo);

		body->setLinearFactor(btVector3(1, 1, 0));
		body->setAngularFactor(btVector3(0, 0, 0));

		//	add the body to the dynamics world
		m_dynamicsWorld->addRigidBody(body);

		body->setActivationState(DISABLE_DEACTIVATION);
		//body->setCollisionFlags(body->getCollisionFlags()| GROUND_2 | TRIGGER);
		body->getBroadphaseHandle()->m_collisionFilterGroup = CONTACT_1 | TRIGGER;
		body->getBroadphaseHandle()->m_collisionFilterMask = GROUND_1 | PLAYER;

		//((btCollisionObject*)body)->setUserIndex(1);
		((btCollisionObject*)body)->setUserPointer(user_ptr);
		return body;
	}
}


int PhysicsLevel2D::getNumGhosts()
{
	if (m_dynamicGhost == 0) return 0;
	return m_dynamicGhost->getNumOverlappingObjects();
}


void PhysicsLevel2D::getGhostInfo(int j, void** out_ptr, int* out_index1, int* out_index2)
{
	btCollisionObject* o = m_dynamicGhost->getOverlappingObject(j);
	*out_ptr = o->getUserPointer();
	//*out_index1 = o->getUserIndex();
	//*out_index2 = 0;
	//*out_index2 = o->getUserIndex2();
}


void PhysicsLevel2D::removeCollisionObject(btCollisionObject* ob)
{
	m_dynamicsWorld->removeCollisionObject(ob);
}


#endif

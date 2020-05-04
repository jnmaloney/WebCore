#include "PhysicsLevel.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>


const int GROUND_1 = 1;
const int GROUND_2 = 2;
const int PLAYER = 4;
const int TRIGGER = 8;
const int CONTACT_1 = 16;
const int CONTACT_2 = 32;
//const int PICKUP = 16;



PhysicsLevel::PhysicsLevel()
{

}


PhysicsLevel::~PhysicsLevel()
{

}


void PhysicsLevel::init()
{
	if (m_dynamicsWorld)
	{
		delete m_dynamicsWorld;
		m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
		m_dynamicsWorld->setGravity(btVector3(0, 420, 0));
		m_dynamicBody = 0;
		m_dynamicGhost = 0;
		m_specialGhost = 0;
		return;
	}

  // Set up the bullet world

	///collision configuration contains default setup for memory, collision setup
	m_collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	m_simplexSolver = new btVoronoiSimplexSolver();
	m_pdSolver = new btMinkowskiPenetrationDepthSolver();

	m_convexAlgo2d = new btConvex2dConvex2dAlgorithm::CreateFunc(m_simplexSolver, m_pdSolver);
	m_box2dbox2dAlgo = new btBox2dBox2dCollisionAlgorithm::CreateFunc();

	m_dispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE, CONVEX_2D_SHAPE_PROXYTYPE, m_convexAlgo2d);
	m_dispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE, CONVEX_2D_SHAPE_PROXYTYPE, m_convexAlgo2d);
	m_dispatcher->registerCollisionCreateFunc(CONVEX_2D_SHAPE_PROXYTYPE, BOX_2D_SHAPE_PROXYTYPE, m_convexAlgo2d);
	m_dispatcher->registerCollisionCreateFunc(BOX_2D_SHAPE_PROXYTYPE, BOX_2D_SHAPE_PROXYTYPE, m_box2dbox2dAlgo);

	m_broadphase = new btDbvtBroadphase();	//m_broadphase = new btSimpleBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
	m_solver = sol;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
  //m_dynamicsWorld->setGravity(btVector3(0, -100, 0));
	m_dynamicsWorld->setGravity(btVector3(0, 225, 0));
	//m_dynamicsWorld->setGravity(btVector3(0, 420, 0));

  //
  // Build the pieces
  //

  // First, load the Texture and build Shapes from the PNG

  // Use the Tiled map to build the Collision scene

  // Drop in a Player Character

	//
	// Set Ghost Callback (register with collision world)
	//
	m_broadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
}


void PhysicsLevel::addTile(int x_min, int x_max, int y_min, int y_max)
{
	addTile(x_min, x_max, y_min, y_max, 0);
}


void PhysicsLevel::addTile(int x_min, int x_max, int y_min, int y_max, int t)
{
	// //
	// // Use run-length to save on collision shapes
	// //
	// if (m_rle == false)
	// {
	// 	m_rle = true;
	// 	m_rle_x_min = x_min;
	// 	m_rle_x_max = x_max;
	// 	m_rle_y_min = y_min;
	// 	m_rle_y_max = y_max;
	// }
	// else
	// {
	// 	if (x_min == m_rle_x_max &&
	// 		  y_min == m_rle_y_min &&
	// 			y_max == m_rle_y_max)
	// 	{
	// 		m_rle_x_max = x_max;
	// 	}
	// 	else
	// 	{
	// 		addTile_(m_rle_x_min, m_rle_x_max, m_rle_y_min, m_rle_y_max);
	// 		//addTile_(x_min, x_max, y_min, y_max);
	// 		m_rle_x_min = x_min;
	// 		m_rle_x_max = x_max;
	// 		m_rle_y_min = y_min;
	// 		m_rle_y_max = y_max;
	// 	}
	// }
	//
	// Use run-length to save on collision shapes

			m_rle_x_min = x_min;
			m_rle_x_max = x_max;
			m_rle_y_min = y_min;
			m_rle_y_max = y_max;
	addTile_(x_min, x_max, y_min, y_max, t);
}


void PhysicsLevel::addTile_(int x_min, int x_max, int y_min, int y_max, int t)
{
	//
	// Recycle
	//
	x_min = m_rle_x_min;
	x_max = m_rle_x_max;
	y_min = m_rle_y_min;
	y_max = m_rle_y_max;

	double w = 0.5 * (x_max - x_min);
	double h = 0.5 * (y_max - y_min);

	//std::cout << x_min << " " << y_min << "    " << w << " " << h << std::endl;

  ///create a few basic rigid bodies
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(w), btScalar(h), btScalar(100.)));
	//	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),50);

	m_collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(x_min + w, y_min + h, 0));

	//We can also use DemoApplication::localCreateRigidBody, but for clarity it is provided here:
	{
		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass, localInertia);

		// using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

	  //	add the body to the dynamics world
    m_dynamicsWorld->addRigidBody(body);

		//body->setCollisionFlags(body->getCollisionFlags()| GROUND_1 | GROUND_2);
		body->getBroadphaseHandle()->m_collisionFilterGroup = GROUND_1 | GROUND_2;
		body->getBroadphaseHandle()->m_collisionFilterMask = CONTACT_1 | CONTACT_2;
		//body->getBroadphaseHandle()->m_collisionFilterGroup = GROUND_2;

		body->setUserIndex(t);
  }
}


void PhysicsLevel::addDynamic(int x, int y)
{
	if (m_dynamicBody)
	{
		m_dynamicsWorld->removeRigidBody(m_dynamicBody);

		m_dynamicBody = 0;
	}
	// int w = 19;
	// int h = 34;

	int w = 10; //14;
	int h = 28;

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
		rbInfo.m_friction = btScalar(0);
		btRigidBody* body = new btRigidBody(rbInfo);
		// btGhostObject* body = new btPairCachingGhostObject();
		// body->setCollisionShape(boxShape);
		// body->setWorldTransform(groundTransform);

		body->setLinearFactor(btVector3(1, 1, 0));
		body->setAngularFactor(btVector3(0, 0, 0));

		//	add the body to the dynamics world
		m_dynamicsWorld->addRigidBody(body);
		//m_dynamicsWorld->addCollisionObject(body);

		m_dynamicBody = body;
		m_dynamicBody->setActivationState(DISABLE_DEACTIVATION);

		//body->setCollisionFlags(body->getCollisionFlags()| GROUND_1);
		body->getBroadphaseHandle()->m_collisionFilterGroup = CONTACT_2;
		body->getBroadphaseHandle()->m_collisionFilterMask = GROUND_2;
	}


	if (m_dynamicGhost == 0)
	{
		btGhostObject* g = new btPairCachingGhostObject();
		m_ghostObjects.push_back(g);
		g->setCollisionFlags( g->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		g->setCollisionShape(boxShape);
		//g->setWorldTransform(groundTransform);
		g->setActivationState(DISABLE_DEACTIVATION);

		m_dynamicsWorld->addCollisionObject(g);

		m_dynamicGhost = g;

		//m_dynamicGhost->setCollisionFlags(m_dynamicGhost->getCollisionFlags() | TRIGGER);
		m_dynamicGhost->getBroadphaseHandle()->m_collisionFilterGroup = PLAYER;
		m_dynamicGhost->getBroadphaseHandle()->m_collisionFilterMask = TRIGGER;
	}

	if (m_specialGhost == 0)
	{
		btCollisionShape* tinyBoxShape = new btBoxShape(btVector3(btScalar(1.0), btScalar(1.0), btScalar(100.)));

		btGhostObject* g = new btPairCachingGhostObject();
		m_ghostObjects.push_back(g);
		g->setCollisionFlags( g->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		g->setCollisionShape(tinyBoxShape);
		//g->setWorldTransform(groundTransform);
		g->setActivationState(DISABLE_DEACTIVATION);

		m_dynamicsWorld->addCollisionObject(g);

		m_specialGhost = g;

		g->getBroadphaseHandle()->m_collisionFilterGroup = CONTACT_2;
		g->getBroadphaseHandle()->m_collisionFilterMask = GROUND_2;
	}
}


void PhysicsLevel::getDynamicPosition(float* x, float* y)
{
	if (m_dynamicBody)
	{
		btTransform bodyWorldTransform;
		m_dynamicBody->getMotionState()->getWorldTransform(bodyWorldTransform);
		btVector3 bodyOrigin = bodyWorldTransform.getOrigin();
		*x = bodyOrigin.x();
		*y = bodyOrigin.y();
	}
}


void PhysicsLevel::step(double dt)
{
	if (m_dynamicsWorld)
	{
		m_dynamicsWorld->stepSimulation(dt, 0);
	}

	// Ghost of player - update position
	if (m_dynamicGhost)
	{
		m_dynamicGhost->setWorldTransform(m_dynamicBody->getWorldTransform());
	}

	if (m_specialGhost)
	{
		m_specialGhost->setWorldTransform(m_dynamicBody->getWorldTransform());
	}
}


void PhysicsLevel::addDynamicImpulse(int d)
{
	// d *= 2;
	double x0 = m_dynamicBody->getLinearVelocity().x();
	double x1 = 100 * d;
	double x = 16 * (x1 - x0) / 30.0;
	double y = 0;
	double z = 0;
	// ?? applyCentralImpulse
	m_dynamicBody->applyCentralImpulse(btVector3(x, y, z));
}


void PhysicsLevel::jumpDynamic()
{
	double x = 0;
	//double y = 5200;
	double y = -3900;
	double z = 0;
	// y *= 2;
	//m_dynamicBody->applyCentralForce(btVector3(x, y, z));
	m_dynamicBody->applyCentralImpulse(btVector3(x, y / 30.0, z));
}


void PhysicsLevel::jumpDynamicHold(float dt)
{
	// double y0 = m_dynamicBody->getLinearVelocity().y();
	// double y1 = 100 * d;
	// double x = 0;
	// double y = 16 * (x1 - x0) / 30.0;
	// double z = 0;
	// m_dynamicBody->applyCentralImpulse(btVector3(x, y, z));

	double x = 0;
	double y = -21000 * dt;
	double z = 0;
	m_dynamicBody->applyCentralImpulse(btVector3(x, y / 30.0, z));

}


void PhysicsLevel::addTrigger(int x_min, int x_max, int y_min, int y_max)
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


bool PhysicsLevel::isTrigger(int i)
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


void PhysicsLevel::contactPoints(bool* ground,	bool* ceiling,	bool* wallLeft,	bool* wallRight)
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


btCollisionObject* PhysicsLevel::getContactNormal(btPersistentManifold* manifold, btCollisionObject* body, btVector3* out_normal)
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


btScalar PhysicsLevel::getDynamicYDir()
{
	return m_dynamicBody->getLinearVelocity().y();
}


btCollisionObject* PhysicsLevel::addPickup(int x_min, int x_max, int y_min, int y_max, void* user_ptr)
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


int PhysicsLevel::getNumGhosts()
{
	if (m_dynamicGhost == 0) return 0;
	return m_dynamicGhost->getNumOverlappingObjects();
}


void PhysicsLevel::getGhostInfo(int j, void** out_ptr, int* out_index1, int* out_index2)
{
	btCollisionObject* o = m_dynamicGhost->getOverlappingObject(j);
	*out_ptr = o->getUserPointer();
	//*out_index1 = o->getUserIndex();
	//*out_index2 = 0;
	//*out_index2 = o->getUserIndex2();
}


void PhysicsLevel::removeCollisionObject(btCollisionObject* ob)
{
	m_dynamicsWorld->removeCollisionObject(ob);
}


bool PhysicsLevel::digDown(float* x, float* y)
{
	// int numManifolds = m_dispatcher->getNumManifolds();
	// for (int i = 0; i < numManifolds; ++i)
	// {
	// 	btPersistentManifold* contactManifold =  m_dispatcher->getManifoldByIndexInternal(i);
	// 	btVector3 normal;
	// 	btCollisionObject* c = getContactNormal(contactManifold, m_dynamicBody, &normal);
	// 	if (c)
	// 	{
	// 		if (normal.y() == -1)
	// 		{
	// 			*x = c->getWorldTransform().getOrigin().x();
	// 			*y = c->getWorldTransform().getOrigin().y();
	// 			m_dynamicsWorld->removeCollisionObject(c);
	// 			return true;
	// 		}
	// 	}
	// }

	return false;
}


void PhysicsLevel::removeAt(float x, float y)
{
	// btTransform tfm;
	// tfm.setOrigin(btVector3(x, y, 0));
	// m_specialGhost->setWorldTransform(tfm);
	//
	// step(0.01);
	//
	// while (m_specialGhost->getNumOverlappingObjects())
	// {
 	// 	btCollisionObject* o = m_specialGhost->getOverlappingObject(0);
	// 	m_dynamicsWorld->removeCollisionObject(o);
	// }
}


void PhysicsLevel::digAt(float x, float y, std::vector<int>& in_oldBrokenTiles, std::vector<int>& out_newBrokenTiles)
{
	//
	// Dig tiles (break first, remove second)
	//

	btTransform tfm;
	tfm.setOrigin(btVector3(x, y, 0));
	m_specialGhost->setWorldTransform(tfm);

	step(0.001);

	int i = 0;
	while (i < m_specialGhost->getNumOverlappingObjects())
	{
 		btCollisionObject* o = m_specialGhost->getOverlappingObject(i);
		int x = o->getUserIndex();
		if (std::find(in_oldBrokenTiles.begin(), in_oldBrokenTiles.end(), x) != in_oldBrokenTiles.end())
		{
			m_dynamicsWorld->removeCollisionObject(o);
			out_newBrokenTiles.push_back(x);
		}
		else
		{
			out_newBrokenTiles.push_back(x);
			++i;
		}
	}
}


void PhysicsLevel::dynamicGravityReduce()
{
	// if (m_dynamicBody->getLinearVelocity().y() > 0)
	// {
	// 	m_dynamicBody->applyCentralForce(btVector3(0, -210, 0));
	// }
	if (m_dynamicBody->getLinearVelocity().y() > 0)
	{
		m_dynamicBody->setGravity(btVector3(0, 210, 0));
	}
	else
	{
		m_dynamicBody->setGravity(btVector3(0, 420, 0));
	}
}


void PhysicsLevel::dynamicZoom()
{
	// if (m_dynamicBody->getLinearVelocity().y() > 0)
	// {
	// 	m_dynamicBody->applyCentralForce(btVector3(0, -630, 0));
	// }
	m_dynamicBody->setGravity(btVector3(0, -420, 0));
}


void PhysicsLevel::normalGravity()
{
	m_dynamicBody->setGravity(btVector3(0, 420, 0));
}

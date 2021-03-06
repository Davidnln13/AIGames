#pragma once
#include "Collisions.h"
/**
* Description: Our types of Bodies that we can have
*/
enum Type
{
	Dynamic,
	Static
};

/**
* Description: Our types of shapes our bodies can ahve, Circles or Boxes
*/
enum Shape
{
	Box,
	Circle
};

/**
* Description: Physic body, this is the main class for moveable objects, classes that wish to move
* will have a physicbody variable
*/
class PhysicsBody
{
public:
	//Constructor takes the type of body and the shape it will use
	PhysicsBody(Type type, Shape shape, void* data);
	~PhysicsBody();

	void update(float dt); //Update the physics body position and colliders
	void draw(sf::RenderWindow& window); //Draw the collider of the physics object
	void applyGravity(float gravity); //Applies gravity to the velocity of the physics body
	bool operator==(const PhysicsBody &b);//Equals operator

	//Setter methods
	//Set the velocity of the physics object
	void setVelocity(Vector2f vel);
	void setFriction(float f);
	void setRestitution(float resti);
	void setInitialRotation(float angle);
	void addForce(Vector2f force);

	//Set the scalar for gravity
	void setGravityScalar(float val);
	//Sets up a box shape physics shape
	void setBoxParameters(Vector2f startPos, Vector2f size, float mass, bool useGravity);
	//Sets up a circle shape physics object
	void setCircleParameters(Vector2f startPos, float radius, float mass, bool useGravity);

	//Public variables
	std::string tag = "";
	bool isSensor = false; //Bool to hold wheter the body should bounce off other objects, this will be useful for trigger events
	Vector2f position, velocity, size, acceleration;
	float radius, e, mass, gravityScalar, friction; //Radius, restitution, mass, gravity scalar & friction
	float inv_mass;
	//Angular components
	float orientation, angularVelocity, torque;
	bool useGravity; //Boolean to use gravity or not
	Shape shape; //The shape of the physics Object (box, circle)
	Type type; //The type of the physics Object (dynamic, static)
	//The collider our physics object will use, this will be set using Shape
	CollisionBox * bCollider; 
	CollisionCircle * cCollider;
	void* objectData; //This is a pointer to an object that this physics object belongs to
	int mask; //The layer we are on
	std::vector<int> bitmasks; //we add masks to our bitmask that we want to avoid collisions with
	bool collisionResolved; //Bool to hold whetevr collisions were resolved or not
};
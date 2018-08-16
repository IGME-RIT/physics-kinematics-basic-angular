#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

/*
File Name : Gameobject.h
Copyright � 2018
Original authors : Sanketh Bhat
Written under the supervision of David I.Schwartz, Ph.D., and
supported by a professional development seed grant from the B.Thomas
Golisano College of Computing & Information Sciences
(https ://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.

Description:
Basic game object class with kinematic properties
*/




#include "GLIncludes.h";

class GameObject
{
	const glm::vec3 GRAVITY = glm::vec3(0, -.001f, 0); // Low gravity for slower motion

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	//Rotational Variables
	
	glm::vec3 angP;
	glm::vec3 angA;
	
	float inertia;
	float mass;

	glm::mat4 translation;
	glm::mat4 rotation;
	glm::mat4 scale;
	glm::mat4 transformation; //Model matrix
	glm::quat currentRot;

public:
	glm::vec3 totalForce;
	glm::vec3 torque;
	glm::vec3 angV;
	VertexBuffer base;
	glm::mat4 MVP;

	void update( float dt, glm::mat4 PV);

	void addForces();

	void calcTransform();

	void eulerIntegration(float dt);

	void setupCircle(float r, float n);

	void setupSq(float size);

	void rotate(glm::vec3 angle);

	void setRotation(glm::vec3 angle);

	glm::vec3 Position()
	{
		return position;
	}

	glm::vec3 Position(glm::vec3 p)
	{
		position = p;
		return position;
	}

	glm::vec3 Velocity()
	{
		return velocity;
	}

	glm::vec3 Velocity(glm::vec3 v)
	{
		velocity = v;
		return velocity;
	}

	glm::vec3 Acceleration()
	{
		return acceleration;

	}

	glm::vec3 Acceleration(glm::vec3 a)
	{
		acceleration = a;
		return acceleration;
	}

	GameObject( glm::mat4 mvp);
	~GameObject();
};

#endif _GAME_OBJECT_H
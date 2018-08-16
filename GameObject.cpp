/*
File Name : GameObject.cpp
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
References: RK2 and RK4 integration by Srinivasan Thiagarajan
*/

#include "GameObject.h"



void GameObject::update(float dt, glm::mat4 PV)
{
	//Summing all forces acting on the object
	addForces();

	//Calculating position based off kinematics equations
	eulerIntegration(dt);

	//translating object
	translation = glm::translate(glm::vec3(position));


	//Setting rotation
	setRotation(angP);

	//Calculating model matrix and then updating the objects MVP
	calcTransform();
	MVP = PV * transformation;

	//Zeroing force and acceleration
	totalForce = acceleration = torque=angA= glm::vec3();


}

void GameObject::addForces()
{
	//totalForce += GRAVITY * mass; //Gravitational force


	if (position.y < -1)
	{
		position.y=-1;

		if (velocity.y < 0)
			totalForce += velocity*-100.f; // Bounce force
	}

	acceleration = totalForce / mass; //Force=m * a so a = F/m
	angA = torque/inertia; //Torque= I*ang.a so ang.a =T/I

}

//Calculates Transformation matrix -> T * R * S
void GameObject::calcTransform()
{
	transformation = translation * rotation * scale;
	
}

void GameObject::eulerIntegration(float dt)
{
	//LINEAR

	//Kinematic equation x= v*dt+ 0.5(a *dt^2)
	position += velocity * dt + 0.5f*(acceleration * dt*dt);

	//Updating velocity
	velocity += acceleration * dt;

	//ROTATIONAL

	//Same equation as the linear one, except the variables are switched to their angular counterparts
	angP += angV * dt + 0.5f*(angA*dt*dt);

	angV += angA * dt;//Updating velocity 

}


//Sets up the vertices in the vertex buffer
void GameObject::setupCircle( float r , float n)
{

	float radius = r;


	VertexFormat center(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	std::vector<VertexFormat> vertices;

	float theta = 360.0f / n;

	//Circle vertex generation
	//In this example we are not implementing the proper the code for indices. We are just going to produce redundant information in the buffer.
	//since we are only having a small number of objects on the screen currently, this redundancy should not matter.
	for (int i = 0; i < n; i++)
	{
		//In every iteration, the center, the point at angle theta and at angle (theta+delta) are fed into the buffer.
		vertices.push_back(center);
		vertices.push_back(VertexFormat(glm::vec3(radius * cos(glm::radians(i*theta)), radius * sin(glm::radians(i*theta)), 0.0f), glm::vec4(0.7f, 0.20f, 0.0f, 1.0f)));
		vertices.push_back(VertexFormat(glm::vec3(radius * cos(glm::radians((i + 1)*theta)), radius * sin(glm::radians((i + 1)*theta)), 0.0f), glm::vec4(0.7f, 0.20f, 0.0f, 1.0f)));
	}

	base.initBuffer(n * 3, &vertices[0]);
}

//Sets up the vertices in the vertex buffer
void GameObject::setupSq(float size)
{
	std::vector<VertexFormat> vertices;
	float side = 1.0f*size;
	//Rectangle vertex generation
	//In this example we are not implementing the proper the code for indices. We are just going to produce redundant information in the buffer.
	//since we are only having a small number of objects on the screen currently, this redundancy should not matter.
	
	
	vertices.push_back(VertexFormat(glm::vec3(-size, size, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))); //Top left
	vertices.push_back(VertexFormat(glm::vec3(size, size, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))); //Top Right
	vertices.push_back(VertexFormat(glm::vec3(size, -size, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))); //Bottom Right
	

	vertices.push_back(VertexFormat(glm::vec3(-size, size, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))); //Top left
	vertices.push_back(VertexFormat(glm::vec3(size, -size, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))); //Bottom Right
	vertices.push_back(VertexFormat(glm::vec3(-size, -size, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))); //Bottom left
	
	
	base.initBuffer(6, &vertices[0]);
}

//Rotates by x,y and z radians
void GameObject::rotate(glm::vec3 angle)
{
	glm::quat qDelta = glm::quat(angle);

	currentRot *= qDelta;

	rotation = glm::toMat4(currentRot);

	calcTransform();
}

// Sets rotation by x, y and z radians
void GameObject::setRotation(glm::vec3 angle)
{
	currentRot = glm::quat(angle);

	rotation = glm::toMat4(currentRot);

	calcTransform();
}


//Initalizing values
GameObject::GameObject(glm::mat4 mvp)
{
	velocity = totalForce = acceleration = position = glm::vec3();

	translation=rotation=scale=transformation= glm::mat4();

	angA = angP = angV = glm::vec3();

	mass =inertia= 1.0f;

	MVP = mvp;
}


GameObject::~GameObject()
{
}

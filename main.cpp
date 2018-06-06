/*
File Name: main.cpp
Copyright © 2018
Original authors: Srinivasan Thiagarajan, Sanketh Bhat
Refactored by Sanketh Bhat
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Description:
This is the skeleton for a basic 2D engine in OpenGL.
*/


#include "GLRender.h"
#include "GameObject.h"


#pragma region program specific Data members
// We change this variable upon detecting collision
float timestep = 0.016;


// vector of scene bodies
std::vector<GameObject*> bodies;
#pragma endregion



// Functions called between every frame.
#pragma region util_functions



void update()
{

	for each (GameObject *body in bodies)
		body->update(timestep, PV);
}


// This function is used to handle key inputs.
// It is a callback funciton. i.e. glfw takes the pointer to this function (via function pointer) and calls this function every time a key is pressed in the during event polling.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Sets the current window to a close flag when ESC is pressed
	if (key == GLFW_KEY_ESCAPE && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
	{
		glfwSetWindowShouldClose(window,1);
	}

	
}
#pragma endregion

void main()
{
	// Initializes most things needed before the main loop
	init();

	// Sends the funtion as a funtion pointer along with the window to which it should be applied to.
	glfwSetKeyCallback(window, key_callback);

	
	// Enter the main loop.
	while (!glfwWindowShouldClose(window))
	{

		// Call to update() which will update the gameobjects.
		update();

		// Call the render function(s).
		renderScene();

		//Rendering each body after the scene
		for each (GameObject *body in bodies)
			renderBody(body);

		// Swaps the back buffer to the front buffer
		// Remember, you're rendering to the back buffer, then once rendering is complete, you're moving the back buffer to the front so it can be displayed.
		glfwSwapBuffers(window);

		// Checks to see if any events are pending and then processes them.
		glfwPollEvents();


	}

	//Cleans shaders and the program and frees up GLFW memory
	cleanup();

	return;
}
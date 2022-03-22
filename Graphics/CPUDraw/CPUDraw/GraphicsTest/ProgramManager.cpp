#include "ProgramManager.h"


bool ProgramManager::Initialise()
{
	if (!glfwInit())
		return false;

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CPU Graphics", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL())
		return false;


	glfwSwapInterval(1);

	simpleShader = new ShaderProgram("Plain.vert", "Plain.frag");
	simpleShader->UseProgram();

	image = new ImageRenderer(WINDOW_WIDTH / PIXEL_SCALE, WINDOW_HEIGHT / PIXEL_SCALE);

	glEnableVertexAttribArray(0);

	return true;

}

void ProgramManager::Run()
{
	while (!glfwWindowShouldClose(window))
	{
		Draw();
		image->Draw(simpleShader);

		glfwSwapBuffers(window);

		glfwPollEvents();
		UpdateMouseState();
	}
}


void ProgramManager::UpdateMouseState()
{
	double mouseXDouble, mouseYDouble;	//Some platforms allow sub-pixel cursor position...
	glfwGetCursorPos(window, &mouseXDouble, &mouseYDouble);
	//...but we're going to clobber it if it exists.
	mouseX = int(mouseXDouble) / PIXEL_SCALE;
	mouseY = int(mouseYDouble) / PIXEL_SCALE;

	mouseLeftDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
	mouseRightDown = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
}

void ProgramManager::ShutDown()
{
	delete simpleShader;
	delete image;
	glfwTerminate();
}

void ProgramManager::Draw()
{

	//This is where you put your custom stuff - do what you will to the contents of 'image'.
	image->Clear();

	//Pixle follows the mouse
	//image->SetPixel(mouseX, mouseY, 1, 0, 0);

	//Spread pixels around mouse
	//image->SetPixel(mouseX - 10, mouseY, 1, 0, 1);
	//image->SetPixel(mouseX, mouseY - 10, 1, 0, 1);
	//image->SetPixel(mouseX + 10, mouseY, 1, 0, 1);
	//image->SetPixel(mouseX, mouseY + 10, 1, 0, 1);

	//Creates pixel when left click is down
	//if (mouseLeftDown == true)
	//{
	//	image->SetPixel(mouseX, mouseY, 1, 0, 0);
	//}

}

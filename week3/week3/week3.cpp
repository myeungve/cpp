#include <glfw3.h>
#include <algorithm>
#include <math.h>
#define PI 3.141592

const int width = 1200;
const int height = 675;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Myeong-Bae Seung", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* White background */
		std::fill_n(pixels, width*height * 3, 1.0f);
		
		/* Draw Thick line */
		for (int i = 0; i <= 25; i++)
		{
			drawLine(125 - i, 400 + i, 325 - i, 400 + (0.5 * sqrt(2) * 250) + i, 1.0f, 0.75f, 0.0f);
		}

		/* Draw Square (Empty) */
		drawLine(475, 400, 675, 400, 1.0f, 0.75f, 0.0f);
		drawLine(475, 600, 675, 600, 1.0f, 0.75f, 0.0f);
		for (int i = 0; i <= 200; i++)
		{
			drawPixel(475, 400 + i, 1.0f, 0.75f, 0.0f);
			drawPixel(675, 400 + i, 1.0f, 0.75f, 0.0f);
		}
		
		/* Draw Square (Filled) */
		for (int i = 0; i <= 200; i++)
		{
			drawLine(850, 400 + i, 1050, 400 + i, 1.0f, 0.75f, 0.0f);
		}
		
		/* Draw Triangle */
		drawLine(100, 100, 350, 100, 1.0f, 0.75f, 0.0f);
		drawLine(100, 100, 225, 100 + (0.5 * sqrt(3) * 250), 1.0f, 0.75f, 0.0f);
		drawLine(225, 100 + (0.5 * sqrt(3) * 250), 350, 100, 1.0f, 0.75f, 0.0f);

		/* Draw Pentagon */
		drawLine(500, 100, 650, 100, 1.0f, 0.75f, 0.0f);
		drawLine(500 - (150 * cos(72 * PI / 180)), 100 + (150 * sin(72 * PI / 180)), 500, 100, 1.0f, 0.75f, 0.0f);
		drawLine(500 - (150 * cos(72 * PI / 180)), 100 + (150 * sin(72 * PI / 180)), 500 + (150 * 0.5 * (1 + sqrt(5)) * cos(72 * PI / 180)), 100 + (150 * 0.5 * (1 + sqrt(5)) * sin(72 * PI / 180)), 1.0f, 0.75f, 0.0f);
		drawLine(500 + (150 * 0.5 * (1 + sqrt(5)) * cos(72 * PI / 180)), 100 + (150 * 0.5 * (1 + sqrt(5)) * sin(72 * PI / 180)), 650 + (150 * cos(72 * PI / 180)), 100 + (150 * sin(72 * PI / 180)), 1.0f, 0.75f, 0.0f);
		drawLine(650, 100, 650 + (150 * cos(72 * PI / 180)), 100 + (150 * sin(72 * PI / 180)), 1.0f, 0.75f, 0.0f);
		
		/* Draw Circle */
		for (int i = 0; i <= 1200; i++)
		{
			for (int j = 0; j <= 675; j++)
			{
				if ((i - 950)*(i - 950) + (j - 200)*(j - 200) - 100 * 100 <= 0)
				{
					drawPixel(i, j, 1.0f, 0.75f, 0.0f);

					if ((i - 950)*(i - 950) + (j - 200)*(j - 200) - 99 * 99 <= 0)
					{
						drawPixel(i, j, 1.0f, 1.0f, 1.0f);
					}
				}
			}
		}
		
		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	delete[] pixels;

	glfwTerminate();
	return 0;
}
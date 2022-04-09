#include "lib/glad.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include "lib/utils.h"
#include "lib/shaderClass.h"
#include "lib/VAO.h"
#include "lib/VBO.h"
#include "lib/EBO.h"
float currScale = 0.5;

inline float deg2rad(float x)
{
  return x * M_PI / 180;
}

int
main() {

  int n = 8;
  float deg = 360 / 8;
  float rad = deg2rad(deg);
  float r = 0.3;
  
  GLfloat vertices[6*n+1] = {0};
  vertices[0] = vertices[1] = vertices[2] = 0;
  vertices[6] = -1 *  sin(deg2rad(deg)) * r;
  vertices[7] = -1 *  cos(deg2rad(deg)) * r;
  vertices[8] = 0.0;

  for (int i=12; i<6*n+1; i+=6)
    {
      vertices[i] = vertices[6] * cos(rad) - vertices[7] * sin(rad);
      vertices[i+1] = vertices[6] * sin(rad) + vertices[7] * cos(rad);
      vertices[i+2] = .0f;
      vertices[i+3] = 1.0;
      vertices[i+4] = 0.0;
      vertices[i+5] = 0.0;
      rad+=deg2rad(deg);
    }
  GLuint indices[] =
    {
      0, 1, 2,
      0, 2, 3,
      0, 3, 4,
      0, 4, 5,
      0, 5, 6,
      0, 6, 7,
      0, 7, 8,
      0, 8, 1
    };
  glfwSetErrorCallback(errCallback);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow* window = glfwCreateWindow(800, 800, "kgvUTS", nullptr, nullptr);
  glfwSetKeyCallback(window, keyCallback);

  glfwMakeContextCurrent(window);
  gladLoadGL();
  glViewport(0, 0, 800, 800);
  
  Shader shaderProgram("src/default.vert", "src/default.frag");
  
  VAO VAO1;
  VAO1.Bind();
  
  VBO VBO1(vertices, sizeof(float) * 9 * 6);
  EBO EBO1(indices, sizeof(unsigned int) * 8 * 3);
  
  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
  VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();
  
  GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
  
  while(!glfwWindowShouldClose(window))
    {
      glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      VAO VAO1;
      VAO1.Bind();
  
      VBO VBO1(vertices, sizeof(float) * 9 * 6);
      EBO EBO1(indices, sizeof(unsigned int) * 8 * 3);

      srand(glfwGetTime());
      for (int i=3; i<6*n+1; i+=6)
	{
	  vertices[i] = rand() % 256 / 256.0;
	  vertices[i+1] = rand() % 256 / 256.0;
	  vertices[i+2] = rand() % 256 / 256.0;
	    
	}
      VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
      VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  
      VAO1.Unbind();
      VBO1.Unbind();
      EBO1.Unbind();

        int minus = glfwGetKey(window, GLFW_KEY_MINUS);
      if (minus == GLFW_PRESS)
	{
	  currScale -= 0.01;
	}
      int plus = glfwGetKey(window, GLFW_KEY_EQUAL);
      if (plus == GLFW_PRESS)
	{
	  currScale += 0.01;
	}
      int enter = glfwGetKey(window, GLFW_KEY_ENTER);
      if (enter == GLFW_PRESS)
	{
	        VAO VAO1;
		VAO1.Bind();
  
		VBO VBO1(vertices, sizeof(float) * 9 * 6);
		EBO EBO1(indices, sizeof(unsigned int) * 8 * 3);

		srand(time(NULL));
		for (int i=3; i<6*n+1; i+=6)
		  {
		    vertices[i] = rand() % 256 / 256.0;
		    vertices[i+1] = rand() % 256 / 256.0;
		    vertices[i+2] = rand() % 256 / 256.0;
	    
		  }
		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  
		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();

	}
      shaderProgram.Activate();
    
      glUniform1f(uniID, currScale);
      VAO1.Bind();
      glDrawElements(GL_TRIANGLES, 3*8, GL_UNSIGNED_INT, 0);
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  
  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  shaderProgram.Delete();
  
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

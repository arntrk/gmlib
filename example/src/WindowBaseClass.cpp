#include "WindowBaseClass.h"

#include <string>
#include <iostream>

WindowBaseClass *WindowBaseClass::instance = nullptr;


WindowBaseClass::WindowBaseClass(WindowBaseClass *wnd) : window(nullptr) 
{ 
  /* Initialize the library */
  if (!glfwInit())
      throw "glefInit error";
  
  instance = wnd; 

}


void WindowBaseClass::resize_callback(GLFWwindow *window, int width, int height)
{
  if (instance != nullptr)
  {
    instance->resize(width, height);
  }
}

void WindowBaseClass::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (instance != nullptr)
  {
    if (action == GLFW_PRESS)
    {
      instance->keypress(key, scancode, mods);
    }
    else if (action == GLFW_RELEASE)
    {
      instance->keyrelease(key, scancode, mods);
    }
    else if (action == GLFW_REPEAT)
    {

    }   
  }    
}

bool WindowBaseClass::CreateWindow(std::string title, int width, int height)
{
  if (window != nullptr) return false;


  /* make function for custome settings to be called before this run function */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  // doing OpenGL 3.X then shaders must be loaded 
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (!window)
  {
      glfwTerminate();
      return false;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  /* Initializing OpenGL extensions */
  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialise GLEW" << std::endl;

    return EXIT_FAILURE;
  }

  return true;
}


int WindowBaseClass::Run()
{
    if (window != nullptr)
    {
      /* Setting the key events callback function */
      glfwSetKeyCallback(window, key_callback);

      /* Setting the resize window callback function */
      glfwSetWindowSizeCallback(window, resize_callback);

      /* call specialized initalization function (virtual) */
      initialize();

      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window))
      {
          /* Execute the virtual render function */
          render();

          /* Swap front and back buffers */
          glfwSwapBuffers(window);

          /* Poll for and process events */
          glfwPollEvents();
      }

      glfwTerminate();
    }
    else
    {
      std::cout << "Exiting: No window created" << std::endl;
    }

    return 0;
}


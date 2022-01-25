#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <BSplineBasis.h>
#include <KnotVector.h>
#include <myWindowClass.h>




int main()
{
  myWindowClass myWindow;

  myWindow.CreateWindow("B-Spline Basis functions", 1024, 768);

  return myWindow.Run();;
}

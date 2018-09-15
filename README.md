# SplineBasis

This project were created to test catch unit test libary, by testing the implementation of BSplineBasis

The BSplineBasis functions and the unit test are the only important with this project, at current stage 


requirements:
  - builds on linux
  - glfw library    http://www.glfw.org/
  - glew library    http://glew.sourceforge.net/


how to build:
  - make [spline]
    -- builds application witch renders the b-basis functions with OpenGL

  - make test
    -- builds and executes the unit tests 


files:
  - bin/spline
      -- executable file running on Linux (ubuntu) -- make 
  - bin/tests
      -- executable file running unit tests (ubuntu) -- make test

  - main.cpp 
      -- Execute Wrapper class for GLFW window functionality

  - Include/BSplineBasis.h
      -- This contains the implementation of B-spline basis functions by using Functors Design Principle
      -- Note: from C++11 this can be implemented as a lambda function

  - Include/KnotVector.h
      -- Implemented only to ensure that knots vector is ordered by increasing values [duplicate values is allowed]
      -- Note: this needs rework/redesign to be production ready
  
  - Include/WindowBasisClass.h
      -- Basis class for GLFW wrapper class for handling window management
  
  - src/WindowBasisClass.cpp
      -- implements window handling using GLFW library

  - Include/myWindowClass.h
      -- implements the setup and rendring using OpenGL
  
  - src/myWindowClass.cpp
      -- in the initialize function you can manipulate the knot vector and n variable 

  - Include/OpenGLShader.hpp
      -- C++ Lambda functions to use OpenGL shaders [note: crashes if no render context have been created]
      -- needs try catch to avoid crash when no rendering context is created

  - test.cpp
      -- contains all test cases to check the implementation of BSplineBasis
    
  - catch.cpp
      -- used for speeding up building of tests

  - Test/catch.hpp
      -- unit test library for C++11 or newer 
  
  - Makefile 
      -- old fashion make file 


BSplineBasis.h
  This is the implementation of a B-Spline basis, which is a blending function
  It is implemented with a Functor Design Prinsiple, which after C++11 can be replaced with lambdas

  Note: all calculated basis function sums up to 1.0 for any t inside [start, end]
        for the knot vector given below start=0.0 and end=1.0, study the unit test to see that this is tested

  for more info: https://en.wikipedia.org/wiki/B-spline


KnotVector.h----------
  This class is not considered finished, was made in a hurry to ensure that values are stored in increasing value

    Example:
       KnotVector<double>(0.0, 1.0, 4)

       creates a knot vector: 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0

       The value 4 indicates a that start and stop has a multiplicity of 4, for use with 4 order BSplineBasis

       aditional knots kan be added between the start and stop values













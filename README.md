# SplineBasis

This project were created to test catch unit test libary, by testing the implementation of BSplineBasis

The BSplineBasis functions and the unit test are the only important with this project, at current stage 


## requirements
  - builds on linux
  - glfw library    http://www.glfw.org/
  - glew library    http://glew.sourceforge.net/


## how to build
  - Prepare and build library
    ```
    $ conan install . -if build
    $ conan build . -bf build
    ```
  - Prepare and build with tests
    ```
    $ conan install . -if build -o tests=True
    $ conan build . -bf build
    ```
  - Prepare and build with examples
    ```
    $ conan install . -if build -o examples=True
    $ conan build . -bf build
    ```

## Create and upload conan package
  - Create package
    ```
    $ conan create . demo/stable
    ```
    The values `demo` and `stable` can be changed to any desired text, whitch affects the package name.
    The package name will be `gmlib/0.0.2@demo/stable`, when these values descibed above. The package can now be used on by you.
  
  - Upload package
    ```
    $ conan upload gmlib/0.0.2@demo/stable -r <some-remote> --all
    ```
    `<some-remote>` is the name of your conan remote package repostetory. This step is needed if other people shall use the same package.

    -- builds application witch renders the b-basis functions with OpenGL


## files

  - `include/BSplineBasis.h`
    This contains the implementation of B-spline basis functions by using Functors Design Principle  
    Note: from C++11 this can be implemented as a lambda function will be done in next version

  - `include/KnotVector.h`  
    Implemented only to ensure that knots vector is ordered by increasing values [duplicate values is allowed]  
    Note: this needs rework/redesign to be production ready
  
  - `tests/test.cpp`  
    contains all test cases to check the implementation of BSplineBasis
    
  - `tests/catch.cpp`  
    used for speeding up building of tests

  - `example/BSplineBasis.cpp`  
    Execute Wrapper class for GLFW window functionality

  - `example/include/WindowBasisClass.h`  
    Basis class for GLFW wrapper class for handling window management 

  - `example/include/myWindowClass.h`  
    implements the setup and rendring using OpenGL

  - `include/OpenGLShader.hpp`  
    C++ Lambda functions to use OpenGL shaders [note: crashes if no render context have been created]  
    needs try catch to avoid crash when no rendering context is created

  - `example/src/WindowBasisClass.cpp`  
    implements window handling using GLFW library

  - `example/src/myWindowClass.cpp`  
    in the initialize function you can manipulate the knot vector and n variable 
## Usage 
### BSplineBasis function and BSpline Curve
  
This is the implementation of a [B-Spline basis](https://en.wikipedia.org/wiki/B-spline), which is a blending function. It is implemented with a Functor Design Prinsiple, which after C++11 can be replaced with lambdas (will be done in next version).

The following example show how to calculate BSpline Curve, using BSpilneBasis defined in the intervall `[0.0, 1.0]`.

```cpp
  // create knot vector of order 4,
  //     0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0
  cad::KnotVector<double> knots(0.0, 1.0, 4);

  // vector of some point class -- not implemented
  // number of points must be order + num internal knot values
  std::vector<Point<double,3>> P{ 
      {0.0, 0.0, 0.0},
      ...
      {3.0, 2.0, 1.0}
  };

  // storage for calulated result
  cad::BSplineBasis<double>::Result result;
  
  // define BSplineBasis object
  cad::BSplineBasis<double> basis;
  
  // using result calculating BSpline Curve
  for (double t = knots.start(), t<=knots.stop(); t+=step) {
    // some point class -- not implemented
    Point<double,3> pnt;
    
    result = basis(t, knots);
    
    for (int i=0; i<result.basis.size(); ++i) 
    {
      // result.i is the first non 0 basis function
      int ii = i + result.i;
      // BSpline Curve position for a given t
      pnt = P[ii] * result.basis[i];
    }
  }
```

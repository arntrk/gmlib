#include "myWindowClass.h"

#include "BSplineBasis.h"
#include "KnotVector.h"

#include "OpenGLShader.hpp"

#include <string>
#include <iostream>


struct Point {
  GLfloat x;
  GLfloat y;
  GLfloat z;
};

std::vector<Point> vertices = {
  { -0.5f, -0.5f,  0.0f },
  {  0.5f, -0.5f,  0.0f },
  {  0.0f,  0.5f,  0.0f }
};


void myWindowClass::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void myWindowClass::keypress(int key, int scancode, int mods)
{
    switch (key)
    {
      case GLFW_KEY_ESCAPE:
        closeWindow();
        break;
    }
}


void myWindowClass::keyrelease(int key, int scancode, int mods)
{

}

/**
 * @brief Initializing OpenGL 
 * 
 */
void myWindowClass::initialize()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


    /**
     * Prepare Vertex shader
     */
    GLuint vertexShader = CreateVertexShader();

    CompileShader(vertexShader, std::string(vertexShaderSource));

    auto successVertex = GetCompileStatus(vertexShader);

    if (!successVertex)
    {
        std::cout << GetCompileErrorMessage(vertexShader) << std::endl;
    }


    /**
     * Prepare Fragment shader
     */
    GLuint fragmentShader = CreateFragmentShader();

    CompileShader(fragmentShader, std::string(fragmentShaderSource));

    auto successFragment = GetCompileStatus(fragmentShader);

    if (!successFragment)
    {
        std::cout << GetCompileErrorMessage(fragmentShader) << std::endl;
    }


    /**
     * Attach shaders and Link Program
     */
    if (successVertex && successFragment)
    {
        shaderProgram = CreateProgram();

        AttachShader(shaderProgram, vertexShader);
        AttachShader(shaderProgram, fragmentShader);

        GLint success = LinkProgram(shaderProgram);

        if (!success)
        {
            std::cout << GetLinkErrorMessage(shaderProgram) << std::endl;
        }
    }

    DeleteShader(vertexShader);
    DeleteShader(fragmentShader);


    /* knot vector of order 4 in interval [-0.5, 0.5] 
     *  --> { -0.5, -0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5 }  
     */
    cad::KnotVector<float> knots(-0.5, 0.5, 4);

    // insert points in the interval [-0.5, 0.5], multiplicity is allowed
    //knots.insert(-0.375);
    //knots.insert(-0.25);
    //knots.insert(-0.125);
    knots.insert(0.0);
    //knots.insert(0.125);
    //knots.insert(0.25);
    //knots.insert(0.375);
    
    /**
     * Preparing Vertex Arrays with points to rendered (points from knot vector)
     */
    std::vector<Point> point;

    int order = knots.getOrder();

    /* Creating a Point for each knots omiting multiple points at start and end */
    for (int i = order-1; i < (knots.size() - order + 1); ++i)
        point.push_back({knots[i], 0.0, 0.0});

    // storing number of points to be created Vertex Array
    pointSize = point.size();

    // creating Vertex Array of points in video memory based on point variable
    glGenVertexArrays(1, &pointsVAO);
    glGenBuffers(1, &pointsVBO);

    glBindVertexArray(pointsVAO);

    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * point.size(), &point[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

    glEnableVertexAttribArray(0);

    /**
     * Prepare to create Vertex Arrays for each b-spline basis curve
     */

    std::vector<std::vector<Point>> basisFunc;

    // prepare space for n b-spline basis curves (n = number of knots - order)
    basisFunc.resize(knots.size() - order);

    // declearing bspline basis function and result vector
    cad::BSplineBasis<float> basis;
    cad::BSplineBasis<float>::Result result;

    int n = 400;
    /**
     * calculating basis functions for t in [start, stop] 
     * with a resolution of n values inside the interval
     */
    for (int i = 0; i < n; ++i)
    {
        Point p;
        p.z = 0.0;

        // calculate next t to evaluate
        float t = (knots.getStop() - knots.getStart()) / (n - 1);
        p.x = knots[0] + t * i;

        // calculate basis functions for t, k gives the index to the first curve to be added to
        result = basis(p.x, knots);
        
        // add all results into respective basisfunc variable
        /**
         * Add result to the basisFunc[result.i+j] --> each is a curve in the interval
         * result.i is the first curve to add results to
         */
        for (unsigned int j = 0; j < result.basis.size(); ++j)
        {
            p.y = result.basis[j];
            basisFunc[result.i + j].push_back(p);
        }
    }

    // creating Vertex Array for each b-spline basis function in video memory
    VBO.resize(basisFunc.size());
    VAO.resize(basisFunc.size());

    for (unsigned int j = 0; j < basisFunc.size(); ++j)
    {
        VAO[j] = 0;
        VBO[j] = 0;
        curveSize.push_back(basisFunc[j].size());
        if (basisFunc[j].size() > 1)
        {
            glGenVertexArrays(1, &VAO[j]);
            glGenBuffers(1, &VBO[j]);

            glBindVertexArray(VAO[j]);

            glBindBuffer(GL_ARRAY_BUFFER, VBO[j]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * basisFunc[j].size(), &basisFunc[j][0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

            glEnableVertexAttribArray(0);
        }
    }

    // ubind vertex array buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void myWindowClass::render()
{
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    for (unsigned int j = 0; j < VBO.size(); ++j)
    {
      if (VAO[j] != 0)
      {
        // draw Vertex Array for each b-spline basis curve
        glBindVertexArray(VAO[j]);
        glDrawArrays(GL_LINE_STRIP, 0, curveSize[j]);
        glBindVertexArray(0);
      }
    }

    // draw Vertex Array of knots 
    glBindVertexArray(pointsVAO);
    glPointSize(6.0f);
    glDrawArrays(GL_POINTS, 0, pointSize);

    // reset binding to vertex array buffers in video memory
    glBindVertexArray(0);


    // Base class will swapbuffers
}

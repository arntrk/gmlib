#ifndef myWindowClass_H
#define myWindowClass_H

#include "WindowBaseClass.h"

#include <vector>

class myWindowClass : public WindowBaseClass 
{
    public:
        myWindowClass() : WindowBaseClass(this) { shaderProgram = 0; }

    protected:
        void resize(int width, int height) override;
        void keypress(int key, int scancode, int mods) override;
        void keyrelease(int key, int scancode, int mods) override;

        void render() override;
        void initialize() override;

    private:
        // shader program
        GLuint shaderProgram;

        // VBO and VAO to render
        std::vector<GLuint> VBO;
        std::vector<GLuint> VAO;
        std::vector<int> curveSize;
        GLuint pointsVBO;
        GLuint pointsVAO;
        int pointSize;
};

#endif // myWindowClass_H

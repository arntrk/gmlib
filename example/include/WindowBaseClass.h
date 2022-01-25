#ifndef WindowBaseClass_H
#define WindowBaseClass_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#ifndef GLFW_TRUE
const int GLFW_TRUE = 1;
#endif

#include <string>

class WindowBaseClass 
{
    public:
        bool CreateWindow(std::string title, int width, int height);
        int Run();

    protected:
        /* make sure that this class cannot be used directly */
        WindowBaseClass(WindowBaseClass *wnd);

        virtual void resize(int width, int hight) {}
        virtual void keypress(int key, int scancode, int mods) {}
        virtual void keyrelease(int key, int scancode, int mods) {}
        virtual void initialize() { }
        virtual void render() { }

        /* special functions to be used by the class inherit this base class */
        void closeWindow() { glfwSetWindowShouldClose(window, GLFW_TRUE); }

    private:
        WindowBaseClass();                             /* prevent call to default constuctort */
        WindowBaseClass(const WindowBaseClass &cpy);  /* prevent this object to be copied    */

        /* the window pointer */
        GLFWwindow *window;

        /* GLFW callback function must be static 
         * the instance must be set to correct class instance
         * to be able to call the correct virtal functions  
         */
        static WindowBaseClass *instance;

        static void resize_callback(GLFWwindow *window, int width, int height);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif // WindowBaseClass_H

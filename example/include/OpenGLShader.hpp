
#define GLEW_STATIC
#include <GL/glew.h>


const GLchar *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main( )\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main( )\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}";

#include <string>

/**
 * @brief These following lamda functions will not work without a OpenGL rendering context
 * 
 */


auto CreateVertexShader = []() -> GLuint {
  return glCreateShader(GL_VERTEX_SHADER);
};

auto CreateFragmentShader = []() -> GLuint {
  return glCreateShader(GL_FRAGMENT_SHADER);
};


auto CompileShader = [](const GLuint shader, const std::string &src) {
    const GLchar *source = src.c_str();
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
};

auto GetCompileStatus = [](const GLuint shader) -> GLint {
  GLint status = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  return status;
};

auto GetCompileErrorMessage = [](const GLuint shader) -> std::string {
  GLchar infoLog[512];
  glGetShaderInfoLog(shader, 512, nullptr, infoLog);
  return std::string(infoLog);
};


auto CreateProgram = []() -> GLuint {
  return glCreateProgram();
};

auto AttachShader = [](GLuint program, GLuint shader) {
  glAttachShader(program, shader);
};

auto LinkProgram = [](GLuint program) -> GLint {
  GLint success = 0;
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  return success;
};
  
auto GetLinkErrorMessage = [](GLuint program) -> std::string {
  GLchar infoLog[512];
  glGetShaderInfoLog(program, 512, NULL, infoLog);
  return std::string(infoLog);
};

auto DeleteShader = [](GLuint shader) {
  glDeleteShader(shader);
} ;



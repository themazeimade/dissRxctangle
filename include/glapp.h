
#include <memory>
#include <shader.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct DestroyglfwWin{

    void operator()(GLFWwindow* ptr){
         glfwDestroyWindow(ptr);
    }

};

class glapp {
private:
  std::unique_ptr<GLFWwindow,DestroyglfwWin> windowApp;

  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);

  unsigned int VertexBuffer;
  unsigned int ElementBuffer;
  unsigned int VertexArrayObject;

  std::unique_ptr<Shader> shaders;
  unsigned int vertexShader;
  unsigned int fragmentShader;
  unsigned int shaderProgram;

  void initVertexBuffer();
  void initElementBuffer();
  void initShaders();
  void initFragmentShader();
  void initVertexShader();
  void initShaderProgram();
  void deleteShader();

public:
  glapp(){};
  ~glapp() {
    glfwTerminate();
    deleteShader();
  }
  void processInput();
  void initWindow();
  void initContext();
  void glAppStart();
  void initOpenGL();
  void initBuffers();
  GLFWwindow *getpWindow();
};

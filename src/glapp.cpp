#include <geometry.h>
#include <glapp.h>
#include <iostream>

void glapp::initWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  windowApp.reset(glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL));
  if (windowApp == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    return;
  }

  glfwMakeContextCurrent(windowApp.get());

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }

  glViewport(0, 0, 800, 600);

  glfwSetFramebufferSizeCallback(windowApp.get(), framebuffer_size_callback);
}

void glapp::framebuffer_size_callback(GLFWwindow *window, int width,
                                      int height) {
  glViewport(0, 0, width, height);
}

void glapp::processInput() {
  if (glfwGetKey(windowApp.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(windowApp.get(), true);
}

void glapp::glAppStart() {
  while (!glfwWindowShouldClose(windowApp.get())) {

    processInput();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VertexArrayObject);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
    /*glDrawArrays(GL_TRIANGLES, 0, 3);*/

    glfwSwapBuffers(windowApp.get());
    glfwPollEvents();
  }
}

void glapp::initContext() {
  initWindow();
  initOpenGL();
}

void glapp::initBuffers() {
  initVertexBuffer();
  initElementBuffer();
}

void glapp::initVertexBuffer() {
  // VB and VAO
  glGenBuffers(1, &VertexBuffer);
  glGenVertexArrays(1, &VertexArrayObject);

  glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
  glBindVertexArray(VertexArrayObject);

  // Vertex Attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // this test vertex (triangle)
  /*float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};*/

  glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle::vertices),
               rectangle::vertices, GL_STATIC_DRAW);
}

void glapp::initElementBuffer() {
  // VB and VAO
  glGenBuffers(1, &ElementBuffer);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBuffer);

  // Vertex Attributes

  // this test vertex (triangle)

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangle::indices),
               rectangle::indices, GL_STATIC_DRAW);
}

void glapp::initVertexShader() {
  // vertexShader compilation

  const char *vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";

  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // check shader success

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
}

void glapp::initFragmentShader() {
  // fragment shader compilation

  const char *fragmentShaderSource =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\0";

  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // check fragment shader success
  int success;
  char infoLog[512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
}

void glapp::initShaderProgram() {
  // shader Program instatiation

  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  /*glUseProgram(shaderProgram);*/
}

void glapp::deleteShader() {
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void glapp::initOpenGL() {
  initBuffers();
  initVertexShader();
  initFragmentShader();
  initShaderProgram();
}

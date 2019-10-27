#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static unsigned int CompileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string & vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


int main()
{
   if(!glfwInit())
   {
       std::cout << "Failed to initialize GLFW" << std::endl;
       return -1;
   }

   GLFWwindow* window = glfwCreateWindow(854, 500, "Engine", nullptr, nullptr);
   glfwMakeContextCurrent(window);

   // initialize glew
   if (glewInit() != GLEW_OK)
   {
       std::cout << "Error!" << std::endl;
   }

   float positions[6] = {
       -0.5f, -0.5f,
        0.0f,  0.5f,
        0.5f, -0.5f
   };

   unsigned int buffer;
   // create
   glGenBuffers(1, &buffer);
   // select it
   glBindBuffer(GL_ARRAY_BUFFER, buffer);
   glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

   std::string vertexShader =
       "#version 330 core\n"
       "\n"
       "layout(location = 0) in vec4 position;\n"
       "\n"
       "void main()\n"
       "{\n"
       "    gl_Position = position;\n"
       "}\n";

   std::string fragmentShader =
       "#version 330 core\n"
       "\n"
       "layout(location = 0) out vec4 color;\n"
       "\n"
       "void main()\n"
       "{\n"
       "    color = vec4(1.0, 0.0, 0.0, 1.0);\n"
       "}\n";

   unsigned int shader = CreateShader(vertexShader, fragmentShader);
   glUseProgram(shader);

   while (!glfwWindowShouldClose(window))
   {
       glClearColor(1, 0, 1, 1);
       glClear(GL_COLOR_BUFFER_BIT);

       glDrawArrays(GL_TRIANGLES, 0, 3);

       glfwSwapBuffers(window);
       glfwPollEvents();
   }
   glDeleteProgram(shader);
   glfwDestroyWindow(window);
   glfwTerminate();
   return 0;
}
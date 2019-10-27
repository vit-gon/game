#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

int main()
{
   if(!glfwInit())
   {
       cout << "Failed to initialize GLFW" << endl;
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
   

   while (!glfwWindowShouldClose(window))
   {
       glClearColor(1, 0, 1, 1);
       glClear(GL_COLOR_BUFFER_BIT);

       glDrawArrays(GL_TRIANGLES, 0, 3);

       glfwSwapBuffers(window);
       glfwPollEvents();
   }
   glfwDestroyWindow(window);
   glfwTerminate();
   return 0;
}
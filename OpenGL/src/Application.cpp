#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    
    {
        //Vertex buffer
        float positions[16] = {
            100.0f, 100.0f, 0.0f, 0.0f,  //0
            200.0f, 100.0f, 1.0f, 0.0f,   //1
            200.0f, 200.0f, 1.0f, 1.0f,   //2
            100.0f, 200.0f, 0.0f, 1.0f   //3
        };

        //Index buffer
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        IndexBuffer ib(indices, 6);
        VertexBuffer vb(positions, 16 * sizeof(float));
        VertexBufferLayout layout;
        VertexArray va;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

        glm::mat4 mvp = proj * view * model;

        shader.SetUniformMat4f("u_MVP", mvp);

        Texture texture("res/textures/image.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        Renderer renderer;
        while (!glfwWindowShouldClose(window))
        {
            shader.Bind();
            shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

            renderer.Draw(va, ib, shader);
       
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
#include <iostream>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <shader.h>

using namespace std;

GLfloat triangulo[] = {       	-0.5f, -0.5f, 0.0f, 0.2, 0.9, 0.3,
                                 0.5f, -0.5f, 0.0f, 0.9, 0.1, 0.8,
                                 0.0f,  0.5f, 0.0f, 0.5, 0.3, 0.2
                       };

int main()
{
    if(!glfwInit())
    {
        cout << "No se pudo iniciar GLFW" << endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Ejemplo OpenGL", nullptr, nullptr);

    if(!window)
    {
        cout << "No se pudo abrir la ventana." << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = true;

    if(glewInit() != GLEW_OK)
    {
        cout << "No se pudo iniciar GLEW." << endl;
        glfwTerminate();
        return -1;
    }

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangulo), triangulo, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);



    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    GLuint shader = crearShader("vertex.glsl", "fragment.glsl");

    bool running = true;

    glViewport(0, 0, 640, 480);

    while(running)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        running = false;

        glfwPollEvents();

        glClearColor(.5, .5, .5, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glBindVertexArray(VAO);
        glUniform1f(glGetUniformLocation(shader, "time"), glfwGetTime());
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

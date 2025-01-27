//
//  projecao2d.cpp
//  glutOpenGL
//
//  Created by Gilberto Fernandes Junior on 21/01/25.
//

#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

const int SCR_WIDTH = 600;
const int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void desenhaTriangulo() {
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(-0.5f, -0.5f);
    glEnd();
}

int main(int argc, char** argv) {
    // Inicialização GLFW
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Atividade 4 - Projeção 2D", NULL, NULL);
   
    if (!window) {
        std::cerr << "Falha ao criar janela GLFW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float time = static_cast<float>(glfwGetTime());

        // Quadrante Superior Esquerdo (Estático)
        glViewport(0, SCR_HEIGHT/2, SCR_WIDTH/2, SCR_HEIGHT/2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1.0f, 0.0f, 0.0f);
        desenhaTriangulo();

        // Quadrante Superior Direito: Horizontal
        glViewport(SCR_WIDTH/2, SCR_HEIGHT/2, SCR_WIDTH/2, SCR_HEIGHT/2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float xOffset = 0.5f * sin(time);
        glOrtho(-1.0 + xOffset, 1.0 + xOffset, -1.0, 1.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(0.0f, 1.0f, 0.0f);
        desenhaTriangulo();

        // Quadrante Inferior Esquerdo: Vertical
        glViewport(0, 0, SCR_WIDTH/2, SCR_HEIGHT/2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float yOffset = 0.5f * sin(time);
        glOrtho(-1.0, 1.0, -1.0 + yOffset, 1.0 + yOffset, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(0.0f, 0.0f, 1.0f);
        desenhaTriangulo();

        // Quadrante Inferior Direito: Zoom e depois diminui
        glViewport(SCR_WIDTH/2, 0, SCR_WIDTH/2, SCR_HEIGHT/2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        float scale = fabs(sin(time)) * 2.0f + 0.001f;
        glOrtho(-1.0/scale, 1.0/scale, -1.0/scale, 1.0/scale, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1.0f, 1.0f, 0.0f);
        desenhaTriangulo();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void drawHouse() {

    // Desenha o quadrado principal da casa
    glColor3f(0.502f, 0.502f, 0.502f);
    glBegin(GL_QUADS);
    glVertex2f(-0.25f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.0f);
    glVertex2f(-0.25f, 0.0f);
    glEnd();

    // Desenha a chaminé
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.15f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.6f);
    glVertex2f(-0.15f, 0.6f);
    glEnd();

    // Desenha o telhado da casa
    glColor3f(0.7f, 0.2f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.25f, 0.0f);
    glVertex2f(0.50f, 0.0f);
    glVertex2f(0.125f, 0.5f);
    glEnd();

    // Desenha a porta
    glColor3f(0.529f, 0.808f, 0.980f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1f, -0.5f);
    glVertex2f(0.1f, -0.5f);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(-0.1f, -0.1f);
    glEnd();

    // Desenha a janela
    glColor3f(0.529f, 0.808f, 0.980f);
    glBegin(GL_QUADS);
    glVertex2f(0.2f, -0.3f); 
    glVertex2f(0.4f, -0.3f);
    glVertex2f(0.4f, -0.1f);  
    glVertex2f(0.2f, -0.1f);
    glEnd();


}

int main() {
    // Inicializa o GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL versão 2.1 (compatibilidade)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // Modo legado

    GLFWwindow* window = glfwCreateWindow(800, 600, "Casa Desenhada", NULL, NULL);
    if (window == NULL) {
        std::cout << "Falha ao criar a janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Falha ao inicializar o GLAD" << std::endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        // Configura a cor de fundo e limpa o buffer
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Desenha a casinha
        drawHouse();

        // Troca os buffers para exibir o que foi desenhado
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
#include <GLFW/glfw3.h>
#include <iostream>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void drawHouse() {

    // Desenha o quadrado principal da casa
    glColor3f(0.502f, 0.502f, 0.502f);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.0f);
    glVertex2f(-0.5f, 0.0f);
    glEnd();

    // Desenha a chaminé
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.4f, 0.0f);
    glVertex2f(-0.25f, 0.0f);
    glVertex2f(-0.25f, 0.4f);
    glVertex2f(-0.4f, 0.4f);
    glEnd();

    // Desenha o telhado da casa
    glColor3f(0.7f, 0.2f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.55f, 0.0f);
    glVertex2f(0.55f, 0.0f);
    glVertex2f(0.0f, 0.5f);
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

    // Desenha as divisórias da janela
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.3f, -0.1f);
    glVertex2f(0.2f, -0.2f);
    glVertex2f(0.4f, -0.2f);
    glEnd();
}

int main() {
    // Inicializa o GLFW
    if (!glfwInit()) {
        std::cerr << "Erro ao inicializar o GLFW!" << std::endl;
        return -1;
    }

    // Cria uma janela OpenGL
    GLFWwindow* window = glfwCreateWindow(800, 600, "Desenho de Casinha", nullptr, nullptr);
    if (!window) {
        std::cerr << "Erro ao criar janela GLFW!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Configura a viewport e a projeção
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Configura a matriz de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a projeção ortográfica
    if (width >= height) {
        float aspect = (float)width / (float)height;
        glOrtho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    } else {
        float aspect = (float)height / (float)width;
        glOrtho(-1.0f, 1.0f, -1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Loop principal de renderização
    while (!glfwWindowShouldClose(window)) {
        // Define a cor de fundo
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Desenha a casinha
        drawHouse();

        // Troca os buffers e verifica eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Finaliza e fecha o GLFW
    glfwTerminate();
    return 0;
}
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

// Variáveis globais para transformações
float translateX = 0.0f, translateY = 0.0f;
float scale = 1.0f;
float rotation = 0.0f;

// Constantes da tela
const float SCREEN_WIDTH = 1.0f;
const float SCREEN_HEIGHT = 1.0f;

// Função para desenhar um quadrado
void drawSquare(float x, float y, float size, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x - size, y - size);
    glVertex2f(x + size, y - size);
    glVertex2f(x + size, y + size);
    glVertex2f(x - size, y + size);
    glEnd();
}

// Callback do teclado para transformações
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // Translação
        if (key == GLFW_KEY_UP && translateY + 0.1f < SCREEN_HEIGHT) translateY += 0.05f;
        if (key == GLFW_KEY_DOWN && translateY - 0.1f > -SCREEN_HEIGHT) translateY -= 0.05f;
        if (key == GLFW_KEY_LEFT && translateX - 0.1f > -SCREEN_WIDTH) translateX -= 0.05f;
        if (key == GLFW_KEY_RIGHT && translateX + 0.1f < SCREEN_WIDTH) translateX += 0.05f;
        // Escala
        if (key == GLFW_KEY_W) scale += 0.05f;
        if (key == GLFW_KEY_S && scale > 0.1f) scale -= 0.05f;
        // Rotação
        if (key == GLFW_KEY_A) rotation += 5.0f;
        if (key == GLFW_KEY_D) rotation -= 5.0f;
    }
}

// Função para desenhar uma árvore hierárquica animada
void drawTree(float branchLength, int depth) {
    if (depth == 0) return;

    glPushMatrix();
    glColor3f(0.4f, 0.2f, 0.0f); // Cor do tronco
    glBegin(GL_QUADS);
    glVertex2f(-0.02f, 0.0f);
    glVertex2f(0.02f, 0.0f);
    glVertex2f(0.02f, branchLength);
    glVertex2f(-0.02f, branchLength);
    glEnd();

    glTranslatef(0.0f, branchLength, 0.0f);
    glRotatef(sin(glfwGetTime() + depth) * 15.0f, 0.0f, 0.0f, 1.0f);

    drawTree(branchLength * 0.7f, depth - 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, branchLength, 0.0f);
    glRotatef(-sin(glfwGetTime() + depth) * 15.0f, 0.0f, 0.0f, 1.0f);
    drawTree(branchLength * 0.7f, depth - 1);
    glPopMatrix();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Transformacoes e Arvore Hierarquica", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        // Aplicação das transformações
        glTranslatef(translateX, translateY, 0.0f);
        glScalef(scale, scale, 1.0f);
        glRotatef(rotation, 0.0f, 0.0f, 1.0f);

        drawSquare(0.0f, 0.0f, 0.1f, 1.0f, 1.0f, 1.0f);
        drawTree(0.5f, 5); // Desenha a árvore com profundidade 5

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

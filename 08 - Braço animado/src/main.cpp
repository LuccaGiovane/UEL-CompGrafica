#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

// Variáveis globais
const float BASE_SIZE = 0.1f;
const float ARM_LENGTH = 0.3f;
const float ARM_WIDTH = 0.05f;

// Função para desenhar um retângulo
void drawRectangle(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x - width / 2, y);
    glVertex2f(x + width / 2, y);
    glVertex2f(x + width / 2, y + height);
    glVertex2f(x - width / 2, y + height);
    glEnd();
}

// Função para desenhar o braço mecânico
void drawMechanicalArm() {
    // Base fixa
    drawRectangle(0.0f, 0.0f, BASE_SIZE, BASE_SIZE, 1.0f, 0.0f, 0.0f);

    // Braço inferior
    glPushMatrix();
    float angleLowerArm = sin(glfwGetTime()) * 45.0f;
    glTranslatef(0.0f, BASE_SIZE, 0.0f);
    glRotatef(angleLowerArm, 0.0f, 0.0f, 1.0f);
    drawRectangle(0.0f, 0.0f, ARM_WIDTH, ARM_LENGTH, 0.0f, 1.0f, 0.0f);

    // Braço superior
    glPushMatrix();
    float angleUpperArm = sin(glfwGetTime() + 1.0f) * 45.0f;
    glTranslatef(0.0f, ARM_LENGTH, 0.0f);
    glRotatef(angleUpperArm, 0.0f, 0.0f, 1.0f);
    drawRectangle(0.0f, 0.0f, ARM_WIDTH, ARM_LENGTH, 0.0f, 0.0f, 1.0f);
    glPopMatrix();

    glPopMatrix();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Bra\xC3\xA7o Mec\xC3\xA2nico Hier\xC3\xA1rquico", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        drawMechanicalArm();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

const float BASE_DIM = 0.12f;
const float SEGMENT_LENGTH = 0.28f;
const float SEGMENT_WIDTH = 0.06f;


void renderRectangle(float posX, float posY, float width, float height, 
                     float red, float green, float blue) {
    /* === Function to draw rectangle === */

    glColor3f(red, green, blue);
    glBegin(GL_QUADS);

    glVertex2f(posX - width / 2, posY);
    glVertex2f(posX + width / 2, posY);
    glVertex2f(posX + width / 2, posY + height);
    glVertex2f(posX - width / 2, posY + height);

    glEnd();
}


void renderArmSystem() {
    /* === Function to draw the arm === */

    float angleLowerSegment = sin(glfwGetTime() * 1.0f) * 55.0f;
    float angleUpperSegment = sin(glfwGetTime() * 1.5f + 0.5f) * 45.0f;

    //Draw base
    renderRectangle(0.0f, 0.0f, BASE_DIM, BASE_DIM, 0.9f, 0.1f, 0.1f);

    //Draw lower part rectangle
    glPushMatrix();
    glTranslatef(0.0f, BASE_DIM, 0.0f);
    glRotatef(angleLowerSegment, 0.0f, 0.0f, 1.0f);
    renderRectangle(0.0f, 0.0f, SEGMENT_WIDTH, SEGMENT_LENGTH, 0.1f, 0.9f, 0.1f);

    //Draw upper part rectangle
    glPushMatrix();
    glTranslatef(0.0f, SEGMENT_LENGTH, 0.0f);
    glRotatef(angleUpperSegment, 0.0f, 0.0f, 1.0f);
    renderRectangle(0.0f, 0.0f, SEGMENT_WIDTH, SEGMENT_LENGTH, 0.1f, 0.1f, 0.9f);
    glPopMatrix();

    glPopMatrix();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Erro ao inicializar GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "1COP028 - Braço Mecânico", NULL, NULL);
    if (!mainWindow) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(mainWindow);

    while (!glfwWindowShouldClose(mainWindow)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        renderArmSystem();

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(mainWindow);
    glfwTerminate();

    return 0;
}

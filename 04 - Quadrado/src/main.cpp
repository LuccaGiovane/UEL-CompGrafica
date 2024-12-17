#include <GLFW/glfw3.h>
#include <cstdlib>
#include <ctime>

//Var globais
float squareX = 0.0f, squareY = 0.0f;   
float squareSize = 0.1f;               
float r = 1.0f, g = 1.0f, b = 1.0f;    

//Altura e largura da tela
const float SCREEN_WIDTH = 1.0f;       
const float SCREEN_HEIGHT = 1.0f;      

// Callback do teclado
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_UP && squareY + squareSize < SCREEN_HEIGHT) squareY += 0.05f;
        if (key == GLFW_KEY_DOWN && squareY - squareSize > -SCREEN_HEIGHT) squareY -= 0.05f;
        if (key == GLFW_KEY_LEFT && squareX - squareSize > -SCREEN_WIDTH) squareX -= 0.05f;
        if (key == GLFW_KEY_RIGHT && squareX + squareSize < SCREEN_WIDTH) squareX += 0.05f;
    }
}

// Callback do mouse
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        r = static_cast<float>(rand()) / RAND_MAX;
        g = static_cast<float>(rand()) / RAND_MAX;
        b = static_cast<float>(rand()) / RAND_MAX;
    }
}

// Função para desenhar o quadrado
void drawSquare(float x, float y, float size) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x - size, y - size);
    glVertex2f(x + size, y - size);
    glVertex2f(x + size, y + size);
    glVertex2f(x - size, y + size);
    glEnd();
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Quadrado Interativo", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        drawSquare(squareX, squareY, squareSize);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

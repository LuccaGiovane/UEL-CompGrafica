#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>  // Para sin e cos

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _APPLE_
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Shapes", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Definindo vértices para as formas
    const int numSegments = 32;
    const float radius = 0.25f; // Raio dos círculos para formar o "8"
    const float rectangleWidth = 0.6f; // Largura do retângulo
    const float rectangleHeight = 0.5f; // Altura do retângulo ajustada

    std::vector<float> verticesCirculo1, verticesCirculo2, verticesSemicirculo;

    // Círculo 1
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        verticesCirculo1.push_back(x - radius); // Centralizado no ponto (-radius, 0)
        verticesCirculo1.push_back(y);
        verticesCirculo1.push_back(0.0f);
    }

    // Círculo 2
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        verticesCirculo2.push_back(x + radius); // Centralizado no ponto (radius, 0)
        verticesCirculo2.push_back(y);
        verticesCirculo2.push_back(0.0f);
    }

    // Retângulo (ajustado para não ultrapassar os círculos)
    float verticesRetangulo[] = {
        -rectangleWidth / 8, -rectangleHeight / 2+0.2, 0.0f, // Inferior esquerdo
         rectangleWidth / 8, -rectangleHeight / 2+0.2, 0.0f, // Inferior direito
         rectangleWidth / 8,  rectangleHeight / 2, 0.0f, // Superior direito
        -rectangleWidth / 8,  rectangleHeight / 2, 0.0f  // Superior esquerdo
    };

    // Semicírculo no topo do retângulo
    for (int i = 0; i <= numSegments / 2; i++) {
        float theta = M_PI * float(i) / float(numSegments / 2);
        float x = (rectangleWidth / 8) * cosf(theta);
        float y = (rectangleWidth / 8) * sinf(theta);
        verticesSemicirculo.push_back(x);
        verticesSemicirculo.push_back(y + rectangleHeight / 2); // Posiciona no topo do retângulo
        verticesSemicirculo.push_back(0.0f);
    }

    // Funções para configurar e desenhar cada forma
    unsigned int VAO1, VBO1, VAO2, VBO2, VAO3, VBO3, VAO4, VBO4;

    // Círculo 1
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, verticesCirculo1.size() * sizeof(float), verticesCirculo1.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Círculo 2
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, verticesCirculo2.size() * sizeof(float), verticesCirculo2.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Retângulo
    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);
    glBindVertexArray(VAO3);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRetangulo), verticesRetangulo, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Semicírculo
    glGenVertexArrays(1, &VAO4);
    glGenBuffers(1, &VBO4);
    glBindVertexArray(VAO4);
    glBindBuffer(GL_ARRAY_BUFFER, VBO4);
    glBufferData(GL_ARRAY_BUFFER, verticesSemicirculo.size() * sizeof(float), verticesSemicirculo.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Loop de renderização
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Desenhar Círculo 1
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments);

        // Desenhar Círculo 2
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments);

        // Desenhar Retângulo
        glBindVertexArray(VAO3);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // Desenhar Semicírculo
        glBindVertexArray(VAO4);
        glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments / 2 + 1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glDeleteVertexArrays(1, &VAO3);
    glDeleteBuffers(1, &VBO3);
    glDeleteVertexArrays(1, &VAO4);
    glDeleteBuffers(1, &VBO4);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

<div align="center">
  <h1>UEL - Computação Gráfica 💻🎨</h1>
  
 <a href="" target="_blank">![License](https://img.shields.io/badge/license-MIT-blue.svg)</a><br>
 ![C++](https://img.shields.io/badge/C%2B%2B-Green)
 ![C](https://img.shields.io/badge/C-grey)
 ![Python](https://img.shields.io/badge/Python-3.8%2B-magenta.svg)
</div>

Bem-vindo ao repositório **UEL-CompGrafica**! Este repositório é dedicado à disciplina de **Computação Gráfica** do curso de **Ciência da Computação** da **Universidade Estadual de Londrina**.<br>

## 📚 Sobre o Repositório

Aqui você encontrará todos os exercícios propostos durante as aulas de Computação Gráfica.<br>

### 📂 Estrutura
```bash
UEL-CompGrafica/
│
├── 01 - Teste/
├── 02 - Casinha/
├── 03 - DDA e Bresenhan/
├── 04 - Quadrado/
├── 05 - Quadrado Parte 2/
├── 06 - Rotação e escala/
├── 07 - Arvore/
├── 08 - Braço animado/
├── 09 - Triangulos/
│
└── README.md    
```

<br>

## 👨🏻‍💻 Exercícios feitos

- **[01 - Teste](https://github.com/LuccaGiovane/UEL-CompGrafica/tree/main/01%20-%20Teste)** É apenas um teste para verificar se a instalação dos programas necessários para a plotagem etc estava funcionando. <br>
- **[02 - Casinha](https://github.com/LuccaGiovane/UEL-CompGrafica/tree/main/02%20-%20Casinha)** Desenho de uma casa feito em C++ utilizando OPENGL.<br>
- **[03 - DDA e Bresenhan](https://github.com/LuccaGiovane/UEL-CompGrafica/tree/main/03%20-%20DDA%20e%20Bresenham)** Programa feito em Python que ao inserir os dados de pontos em uma GUI, traça uma reta utilizando os algoritmos DDA ou Bresenhan, além de desenhar circunferências utilizando também o algoritmo de Bresenhan.<br>
- **[04 - Quadrado](https://github.com/LuccaGiovane/UEL-CompGrafica/tree/main/04%20-%20Quadrado)** Programa feito em C++ utilizando OPENGL que desenha um quadrado na tela. O quadrado se move via setinhas do teclado e ao clicar na tela com o botao esquerdo do mouse ele aleatoriamente muda de cor.
- **[05 - Quadrado Parte 2](https://github.com/LuccaGiovane/UEL-CompGrafica/blob/main/05%20-%20Quadrado%20parte%202/src/main.cpp)** Programa feito em C++ utilizando OPENGL que desenha um quadrado na tela. O quadrado se move via setinhas do teclado e ao clicar na tela com o botao esquerdo do mouse ele aleatoriamente muda de cor. Além disso, são desenhados eixos cartesianos para referência visual.
- **[06 - Rotação e escala](https://github.com/LuccaGiovane/UEL-CompGrafica/tree/main/06%20-%20Rota%C3%A7%C3%A3o%20e%20escala)** Programa feito em C++ cria uma janela usando GLFW e exibe um retângulo branco que pode ser transformado interativamente. O usuário pode mover o retângulo com as setas do teclado, escalá-lo com as teclas 'W' e 'S' e rotacioná-lo com 'A' e 'D'. As transformações são aplicadas dinamicamente usando `glTranslatef`, `glScalef` e `glRotatef`.
- **[07 - Arvore](https://github.com/LuccaGiovane/UEL-CompGrafica/tree/main/07%20-%20Arvore)** Programa feito em C++ cria uma janela usando GLFW e desenha uma tentativa de árvore hierárquica usando recursão. O usuário pode mover, escalar e rotacionar a árvore com o teclado. O tronco é representado por um retângulo marrom, e os galhos são gerados recursivamente, oscilando levemente com base no tempo para simular um efeito de movimento.
- **[08 - Braço animado](https://github.com/LuccaGiovane/UEL-CompGrafica/blob/main/08%20-%20Bra%C3%A7o%20animado/src/main.cpp)** Programa feito em C++ cria uma janela usando GLFW e desenha um braço mecânico animado composto por uma base fixa e dois segmentos articulados. Os segmentos oscilam dinamicamente com base no tempo usando funções senoidais para simular um movimento natural. Cada parte do braço tem uma cor distinta e as transformações são aplicadas hierarquicamente com `glPushMatrix()` e `glPopMatrix()` para manter a estrutura articulada.
- **[09 - Triangulos](https://github.com/LuccaGiovane/UEL-CompGrafica/blob/main/09%20-%20Triangulos/src/main.cpp)** Programa feito em C++ cria uma janela com quatro quadrantes distintos e exibe um triângulo em cada um, aplicando diferentes transformações dinâmicas usando projeção ortogonal. No quadrante superior esquerdo, o triângulo permanece estático; no superior direito, ele oscila horizontalmente; no inferior esquerdo, ele se move verticalmente; e no inferior direito, ele aumenta e diminui de tamanho periodicamente. Essas transformações são baseadas no tempo (`glfwGetTime()`), criando um efeito animado.

import matplotlib.pyplot as plt

def dda_line(x1, y1, x2, y2):
    """
    Algoritmo DDA para desenhar uma reta entre (x1, y1) e (x2, y2)
    """
    x1 = float(x1)
    y1 = float(y1)
    x2 = float(x2)
    y2 = float(y2)
    pontos = []
    dx = x2 - x1
    dy = y2 - y1

    passos = int(max(abs(dx), abs(dy)))

    x_inc = dx / passos
    y_inc = dy / passos

    x = x1
    y = y1
    pontos.append((round(x), round(y)))
    for i in range(passos):
        x += x_inc
        y += y_inc
        pontos.append((round(x), round(y)))
    return pontos

def bresenham_line(x1, y1, x2, y2):
    """
    Algoritmo de Bresenham para desenhar uma reta entre (x1, y1) e (x2, y2)
    Funciona para todas as inclinações
    """
    pontos = []
    dx = abs(x2 - x1)
    dy = abs(y2 - y1)

    x = x1
    y = y1

    sx = -1 if x1 > x2 else 1
    sy = -1 if y1 > y2 else 1

    if dy <= dx:
        err = dx / 2.0
        while x != x2:
            pontos.append((x, y))
            err -= dy
            if err < 0:
                y += sy
                err += dx
            x += sx
    else:
        err = dy / 2.0
        while y != y2:
            pontos.append((x, y))
            err -= dx
            if err < 0:
                x += sx
                err += dy
            y += sy
    pontos.append((x2, y2))
    return pontos

def bresenham_circle(xc, yc, r):
    """
    Algoritmo de Bresenham para desenhar uma circunferência centrada em (xc, yc) com raio r
    """
    x = 0
    y = r
    p = 3 - 2 * r
    pontos = []

    def plot_circle_points(xc, yc, x, y):
        # Plotando todos os oito octantes
        pontos.extend([
            (xc + x, yc + y),
            (xc - x, yc + y),
            (xc + x, yc - y),
            (xc - x, yc - y),
            (xc + y, yc + x),
            (xc - y, yc + x),
            (xc + y, yc - x),
            (xc - y, yc - x),
        ])

    plot_circle_points(xc, yc, x, y)

    while y >= x:
        x += 1
        if p <= 0:
            p = p + 4 * x + 6
        else:
            y -= 1
            p = p + 4 * (x - y) + 10
        plot_circle_points(xc, yc, x, y)
    return pontos

# Testando o Algoritmo DDA
x1, y1 = 2, 2
x2, y2 = 15, 10
pontos_dda = dda_line(x1, y1, x2, y2)

# Plotando a reta usando o algoritmo DDA
x_coords, y_coords = zip(*pontos_dda)
plt.figure()
plt.title("Algoritmo DDA - Reta")
plt.plot(x_coords, y_coords, 'ro')
plt.xlabel("Eixo X")
plt.ylabel("Eixo Y")
plt.grid(True)
plt.show()

# Testando o Algoritmo de Bresenham para Retas
x1_b, y1_b = 10, 5
x2_b, y2_b = 3, 20
pontos_bresenham = bresenham_line(x1_b, y1_b, x2_b, y2_b)

# Plotando a reta usando o algoritmo de Bresenham
x_coords_b, y_coords_b = zip(*pontos_bresenham)
plt.figure()
plt.title("Algoritmo de Bresenham - Reta")
plt.plot(x_coords_b, y_coords_b, 'ro')
plt.xlabel("Eixo X")
plt.ylabel("Eixo Y")
plt.grid(True)
plt.show()

# Testando o Algoritmo de Bresenham para Circunferências
xc, yc, r = 10, 10, 8
pontos_circulo = bresenham_circle(xc, yc, r)

# Removendo pontos duplicados
pontos_circulo = list(set(pontos_circulo))

# Plotando a circunferência usando o algoritmo de Bresenham
x_coords_c, y_coords_c = zip(*pontos_circulo)
plt.figure()
plt.title("Algoritmo de Bresenham - Circunferência")
plt.plot(x_coords_c, y_coords_c, 'ro')
plt.xlabel("Eixo X")
plt.ylabel("Eixo Y")
plt.axis('equal')  # Garantindo escala igual nos eixos
plt.grid(True)
plt.show()

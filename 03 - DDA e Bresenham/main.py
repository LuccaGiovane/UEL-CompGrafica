import tkinter as tk
from tkinter import simpledialog, messagebox, font
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

def dda_line(x1, y1, x2, y2):
    """
    Implementa o algoritmo DDA para traçado de retas.
    """
    points = []

    dx = x2 - x1
    dy = y2 - y1

    steps = max(abs(dx), abs(dy))

    if steps == 0:
        return [(x1, y1)]

    x_inc = dx / steps
    y_inc = dy / steps

    x = x1
    y = y1

    for _ in range(int(steps) + 1):
        points.append((round(x), round(y)))
        x += x_inc
        y += y_inc

    return points

def bresenham_line(x1, y1, x2, y2):
    """
    Implementa o algoritmo de Bresenham para traçado de retas.
    """
    points = []

    dx = abs(x2 - x1)
    dy = abs(y2 - y1)

    x, y = x1, y1

    sx = 1 if x2 > x1 else -1
    sy = 1 if y2 > y1 else -1

    if dy <= dx:
        err = 2 * dy - dx
        for _ in range(dx + 1):
            points.append((x, y))
            if err >= 0:
                y += sy
                err -= 2 * dx
            x += sx
            err += 2 * dy
    else:
        err = 2 * dx - dy
        for _ in range(dy + 1):
            points.append((x, y))
            if err >= 0:
                x += sx
                err -= 2 * dy
            y += sy
            err += 2 * dx

    return points

def bresenham_circle(xc, yc, r):
    """
    Implementa o algoritmo de Bresenham para traçado de circunferências.
    """
    points = []
    x = 0
    y = r
    d = 3 - 2 * r

    def plot_circle_points(xc, yc, x, y):
        return [
            (xc + x, yc + y),
            (xc - x, yc + y),
            (xc + x, yc - y),
            (xc - x, yc - y),
            (xc + y, yc + x),
            (xc - y, yc + x),
            (xc + y, yc - x),
            (xc - y, yc - x),
        ]

    while y >= x:
        points.extend(plot_circle_points(xc, yc, x, y))
        x += 1
        if d > 0:
            y -= 1
            d = d + 4 * (x - y) + 10
        else:
            d = d + 4 * x + 6

    #remover os ptos duplicados
    unique_points = list(set(points))
    return unique_points

def plot_points(points, title, color='blue'):
    """
    Plota os pontos utilizando matplotlib.
    """
    if not points:
        messagebox.showwarning("Aviso", "Nenhum ponto para plotar.")
        return

    x_coords, y_coords = zip(*points)
    
    fig, ax = plt.subplots(figsize=(6,6))
    # pixels sao representados como "quadradinhos"
    ax.scatter(x_coords, y_coords, c=color, marker='s')
    ax.set_title(title)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.grid(True)
    ax.set_aspect('equal')
    plt.show()

def get_line_points(root):
    """
    Solicita ao usuário os pontos para traçado de reta.
    """
    try:
        x1 = float(simpledialog.askstring("Entrada", "Digite x1:", parent=root))
        y1 = float(simpledialog.askstring("Entrada", "Digite y1:", parent=root))
        x2 = float(simpledialog.askstring("Entrada", "Digite x2:", parent=root))
        y2 = float(simpledialog.askstring("Entrada", "Digite y2:", parent=root))
        return x1, y1, x2, y2
    except (TypeError, ValueError):
        messagebox.showerror("Erro", "Entrada inválida. Por favor, insira números válidos.")
        return None

def get_circle_parameters(root):
    """
    Solicita ao usuário os parâmetros para traçado de circunferência.
    """
    try:
        xc = float(simpledialog.askstring("Entrada", "Digite o centro x (xc):", parent=root))
        yc = float(simpledialog.askstring("Entrada", "Digite o centro y (yc):", parent=root))
        r = float(simpledialog.askstring("Entrada", "Digite o raio (r):", parent=root))
        if r < 0:
            messagebox.showerror("Erro", "O raio deve ser não negativo.")
            return None
        return xc, yc, r
    except (TypeError, ValueError):
        messagebox.showerror("Erro", "Entrada inválida. Por favor, insira números válidos.")
        return None

def executar_dda(root):
    """
    Executa o algoritmo DDA para traçado de retas.
    """
    pontos = get_line_points(root)
    if pontos:
        x1, y1, x2, y2 = pontos
        dda_points = dda_line(x1, y1, x2, y2)
        plot_points(dda_points, f'DDA Reta: ({x1},{y1}) -> ({x2},{y2})', color='red')

def executar_bresenham_line(root):
    """
    Executa o algoritmo de Bresenham para traçado de retas.
    """
    pontos = get_line_points(root)
    if pontos:
        x1, y1, x2, y2 = pontos
        bresenham_points = bresenham_line(int(round(x1)), int(round(y1)), int(round(x2)), int(round(y2)))
        plot_points(bresenham_points, f'Bresenham Reta: ({x1},{y1}) -> ({x2},{y2})', color='green')

def executar_bresenham_circle(root):
    """
    Executa o algoritmo de Bresenham para traçado de circunferências.
    """
    params = get_circle_parameters(root)
    if params:
        xc, yc, r = params
        bresenham_points = bresenham_circle(int(round(xc)), int(round(yc)), int(round(r)))
        plot_points(bresenham_points, f'Bresenham Circunferência: Centro=({xc},{yc}), Raio={r}', color='blue')

def main():
    # Interface gráfica principal
    root = tk.Tk()
    root.title("Algoritmos de Traçado de Gráficos")
    root.configure(bg='#F0F0F0')

    
    root.geometry('400x400')
    root.resizable(False, False)

    # Título
    titulo_font = font.Font(family='Helvetica', size=20, weight='bold')
    titulo_label = tk.Label(root, text="Traçado de Gráficos", bg='#F0F0F0', font=titulo_font)
    titulo_label.pack(pady=20)

    # Botões
    button_font = font.Font(family='Helvetica', size=12)

    dda_button = tk.Button(root, text="DDA para Retas", command=lambda: executar_dda(root),
                           width=25, height=2, bg='lightblue', font=button_font)
    dda_button.pack(pady=10)

    bresenham_line_button = tk.Button(root, text="Bresenham para Retas", command=lambda: executar_bresenham_line(root),
                                      width=25, height=2, bg='lightgreen', font=button_font)
    bresenham_line_button.pack(pady=10)

    bresenham_circle_button = tk.Button(root, text="Bresenham para Circunferências",
                                        command=lambda: executar_bresenham_circle(root),
                                        width=25, height=2, bg='lightcoral', font=button_font)
    bresenham_circle_button.pack(pady=10)

    # Botão Sair
    sair_button = tk.Button(root, text="Sair", command=root.quit,
                            width=25, height=2, bg='lightgray', font=button_font)
    sair_button.pack(pady=20)

    root.mainloop()

if __name__ == "__main__":
    main()

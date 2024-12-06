import tkinter as tk
from tkinter import messagebox, font
import matplotlib.pyplot as plt

def dda_line(x1, y1, x2, y2):
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

    unique_points = list(set(points))
    return unique_points

def plot_points(points, title, color='blue'):
    if not points:
        messagebox.showwarning("Aviso", "Nenhum ponto para plotar.")
        return

    x_coords, y_coords = zip(*points)
    fig, ax = plt.subplots(figsize=(6,6))
    ax.scatter(x_coords, y_coords, c=color, marker='s')
    ax.set_title(title)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.grid(True)
    ax.set_aspect('equal')
    plt.show()

def mostrar_frame_retas_dda(frame_retas, frame_circulo, dda_button_retas, bresenham_button_retas):
    frame_circulo.pack_forget()
    frame_retas.pack(pady=10)
    dda_button_retas.grid(row=0, column=0, padx=5)
    bresenham_button_retas.grid_remove()#gambiarra pq aparecia os 2 botao da reta kkkk

def mostrar_frame_retas_bresenham(frame_retas, frame_circulo, dda_button_retas, bresenham_button_retas):
    frame_circulo.pack_forget()
    frame_retas.pack(pady=10)
    bresenham_button_retas.grid(row=0, column=0, padx=5)
    dda_button_retas.grid_remove()#mesma gambiarra so que pro dda

def mostrar_frame_circulo(frame_retas, frame_circulo):
    frame_retas.pack_forget()
    frame_circulo.pack(pady=10)

def executar_dda(x1_entry, y1_entry, x2_entry, y2_entry):
    try:
        x1 = float(x1_entry.get())
        y1 = float(y1_entry.get())
        x2 = float(x2_entry.get())
        y2 = float(y2_entry.get())
    except ValueError:
        messagebox.showerror("Erro", "Entrada inválida. Por favor, insira números válidos.")
        return
    dda_points = dda_line(x1, y1, x2, y2)
    plot_points(dda_points, f'DDA Reta: ({x1},{y1}) -> ({x2},{y2})', color='red')

def executar_bresenham_line(x1_entry, y1_entry, x2_entry, y2_entry):
    try:
        x1 = float(x1_entry.get())
        y1 = float(y1_entry.get())
        x2 = float(x2_entry.get())
        y2 = float(y2_entry.get())
    except ValueError:
        messagebox.showerror("Erro", "Entrada inválida. Por favor, insira números válidos.")
        return
    bresenham_points = bresenham_line(int(round(x1)), int(round(y1)), int(round(x2)), int(round(y2)))
    plot_points(bresenham_points, f'Bresenham Reta: ({x1},{y1}) -> ({x2},{y2})', color='green')

def executar_bresenham_circle(xc_entry, yc_entry, r_entry):
    try:
        xc = float(xc_entry.get())
        yc = float(yc_entry.get())
        r = float(r_entry.get())
        if r < 0:
            messagebox.showerror("Erro", "O raio deve ser não negativo.")
            return
    except ValueError:
        messagebox.showerror("Erro", "Entrada inválida. Por favor, insira números válidos.")
        return
    bresenham_points = bresenham_circle(int(round(xc)), int(round(yc)), int(round(r)))
    plot_points(bresenham_points, f'Bresenham Circunferência: Centro=({xc},{yc}), Raio={r}', color='blue')

def main():
    root = tk.Tk()
    root.title("Atividade 2 - Algoritmos de traçado de retas e circunferências")
    root.configure(bg='#F0F0F0')
    root.geometry('400x650')
    root.resizable(False, False)

    #titlo e meus dados
    titulo_font = font.Font(family='Helvetica', size=20, weight='bold')
    titulo_label = tk.Label(root, text="Algoritmos de Traçado", bg='#F0F0F0', font=titulo_font)
    titulo_label.pack(pady=20)

    autor_font = font.Font(family='Helvetica', size=12)
    autor_label = tk.Label(root, text="Lucca G. Gomes\n201900560202", bg='#F0F0F0', font=autor_font)
    autor_label.pack(pady=5)

    button_font = font.Font(family='Helvetica', size=12)

    #entrada para retas
    frame_retas = tk.Frame(root, bg='#F0F0F0')
    tk.Label(frame_retas, text="Insira os valores para a Reta:", bg='#F0F0F0').pack(pady=5)
    entrada_retas_frame = tk.Frame(frame_retas, bg='#F0F0F0')
    entrada_retas_frame.pack()

    tk.Label(entrada_retas_frame, text="X1:", bg='#F0F0F0').grid(row=0, column=0, padx=5, pady=5)
    x1_entry = tk.Entry(entrada_retas_frame)
    x1_entry.grid(row=0, column=1, padx=5, pady=5)

    tk.Label(entrada_retas_frame, text="Y1:", bg='#F0F0F0').grid(row=0, column=2, padx=5, pady=5)
    y1_entry = tk.Entry(entrada_retas_frame)
    y1_entry.grid(row=0, column=3, padx=5, pady=5)

    tk.Label(entrada_retas_frame, text="X2:", bg='#F0F0F0').grid(row=1, column=0, padx=5, pady=5)
    x2_entry = tk.Entry(entrada_retas_frame)
    x2_entry.grid(row=1, column=1, padx=5, pady=5)

    tk.Label(entrada_retas_frame, text="Y2:", bg='#F0F0F0').grid(row=1, column=2, padx=5, pady=5)
    y2_entry = tk.Entry(entrada_retas_frame)
    y2_entry.grid(row=1, column=3, padx=5, pady=5)

    executar_retas_frame = tk.Frame(frame_retas, bg='#F0F0F0')
    executar_retas_frame.pack(pady=10)


    dda_button_retas = tk.Button(executar_retas_frame, text="Plotar DDA",
                                 command=lambda: executar_dda(x1_entry, y1_entry, x2_entry, y2_entry),
                                 width=10, bg='lightblue', font=button_font)

    bresenham_button_retas = tk.Button(executar_retas_frame, text="Plotar Bresenham",
                                       command=lambda: executar_bresenham_line(x1_entry, y1_entry, x2_entry, y2_entry),
                                       width=15, bg='lightgreen', font=button_font)

    
    
    #entrada para circunferência
    frame_circulo = tk.Frame(root, bg='#F0F0F0')
    tk.Label(frame_circulo, text="Insira os valores para a Circunferência:", bg='#F0F0F0').pack(pady=5)
    entrada_circulo_frame = tk.Frame(frame_circulo, bg='#F0F0F0')
    entrada_circulo_frame.pack()

    tk.Label(entrada_circulo_frame, text="XC:", bg='#F0F0F0').grid(row=0, column=0, padx=5, pady=5)
    xc_entry = tk.Entry(entrada_circulo_frame)
    xc_entry.grid(row=0, column=1, padx=5, pady=5)

    tk.Label(entrada_circulo_frame, text="YC:", bg='#F0F0F0').grid(row=1, column=0, padx=5, pady=5)
    yc_entry = tk.Entry(entrada_circulo_frame)
    yc_entry.grid(row=1, column=1, padx=5, pady=5)

    tk.Label(entrada_circulo_frame, text="Raio:", bg='#F0F0F0').grid(row=2, column=0, padx=5, pady=5)
    r_entry = tk.Entry(entrada_circulo_frame)
    r_entry.grid(row=2, column=1, padx=5, pady=5)

    tk.Button(frame_circulo, text="Plotar Circunferência",
              command=lambda: executar_bresenham_circle(xc_entry, yc_entry, r_entry),
              width=20, bg='lightcoral', font=button_font).pack(pady=10)



    # Botões principais
    dda_button = tk.Button(root, text="DDA para Retas",
                           command=lambda: mostrar_frame_retas_dda(frame_retas, frame_circulo, dda_button_retas, bresenham_button_retas),
                           width=25, height=2, bg='lightblue', font=button_font)
    dda_button.pack(pady=10)

    bresenham_line_button = tk.Button(root, text="Bresenham para Retas",
                                      command=lambda: mostrar_frame_retas_bresenham(frame_retas, frame_circulo, dda_button_retas, bresenham_button_retas),
                                      width=25, height=2, bg='lightgreen', font=button_font)
    bresenham_line_button.pack(pady=10)

    bresenham_circle_button = tk.Button(root, text="Bresenham para Circunferências",
                                        command=lambda: mostrar_frame_circulo(frame_retas, frame_circulo),
                                        width=25, height=2, bg='lightcoral', font=button_font)
    bresenham_circle_button.pack(pady=10)

    sair_button = tk.Button(root, text="Sair", command=root.quit,
                            width=25, height=2, bg='lightgray', font=button_font)
    sair_button.pack(pady=20)

    # so pra nao mostrar nada alem dos botoes no inicio
    root.mainloop()

if __name__ == "__main__":
    main()

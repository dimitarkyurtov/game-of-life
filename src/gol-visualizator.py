import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import sys
import math

def read(filename, N):
    frames = []
    with open(filename, 'r') as file:
        lines = file.readlines()
        for i in range(0, len(lines)):
            matrix = np.array([int(cell) for cell in lines[i].strip()])
            matrix = np.array(matrix).reshape(N, N)
            frames.append(matrix)
    return frames

def animate(frames, N):
    fig, ax = plt.subplots()
    
    def update(frame):
        ax.clear()
        ax.set_xticks(np.arange(-0.5, N, 1), minor=True)
        ax.set_yticks(np.arange(-0.5, N, 1), minor=True)
        ax.grid(which="minor", color='gray', linestyle='-', linewidth=1.5)
        ax.tick_params(which='both', bottom=False, left=False, labelbottom=False, labelleft=False)
        ax.imshow(1 - frame, cmap='gray', interpolation='nearest')

    ani = animation.FuncAnimation(fig, update, frames=frames, interval=300)
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python animate_game_of_life.py <filename>")
        sys.exit(1)
    
    filename = sys.argv[1]
    N = 1

    with open(filename, 'r') as file:
        lines = file.readlines()
        N = round(math.sqrt(len(lines[0]) - 1))
    
    frames = read(filename, N)
    animate(frames, N)

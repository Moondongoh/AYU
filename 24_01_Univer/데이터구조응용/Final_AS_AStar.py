import random
import tkinter as tk
from tkinter import messagebox
import heapq

class PuzzleState:
    def __init__(self, state, parent, move, depth, cost):
        self.state = state
        self.parent = parent
        self.move = move
        self.depth = depth
        self.cost = cost

    def __lt__(self, other):
        return self.cost < other.cost

def calculate_manhattan_distance(state):
    distance = 0
    for i in range(3):
        for j in range(3):
            if state[i][j] != 0:
                x, y = divmod(state[i][j] - 1, 3)
                distance += abs(x - i) + abs(y - j)
    return distance

def solve_puzzle(start_state):
    goal_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
    visited = set()
    pq = []
    start_node = PuzzleState(start_state, None, None, 0, calculate_manhattan_distance(start_state))
    heapq.heappush(pq, start_node)

    while pq:
        node = heapq.heappop(pq)
        visited.add(tuple(map(tuple, node.state)))

        if node.state == goal_state:
            moves = []
            while node.parent is not None:
                moves.append(node.move)
                node = node.parent
            moves.reverse()
            return moves

        for direction in ((-1, 0), (1, 0), (0, -1), (0, 1)):
            i, j = next((i, j) for i in range(3) for j in range(3) if node.state[i][j] == 0)
            if 0 <= i + direction[0] < 3 and 0 <= j + direction[1] < 3:
                new_state = [row[:] for row in node.state]
                new_state[i][j], new_state[i + direction[0]][j + direction[1]] = new_state[i + direction[0]][j + direction[1]], new_state[i][j]
                if tuple(map(tuple, new_state)) not in visited:
                    child_node = PuzzleState(new_state, node, direction, node.depth + 1,
                                             node.depth + 1 + calculate_manhattan_distance(new_state))
                    heapq.heappush(pq, child_node)

    return None

def shuffle_puzzle(state):
    for _ in range(100):
        i, j = next((i, j) for i in range(3) for j in range(3) if state[i][j] == 0)
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        random.shuffle(directions)
        for direction in directions:
            if 0 <= i + direction[0] < 3 and 0 <= j + direction[1] < 3:
                state[i][j], state[i + direction[0]][j + direction[1]] = state[i + direction[0]][j + direction[1]], state[i][j]
                break
    return state

class PuzzleGUI:
    def __init__(self, master):
        self.master = master
        master.title("8-Puzzle Solver")

        self.puzzle_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
        self.buttons = []

        for i in range(3):
            row = []
            for j in range(3):
                button = tk.Button(master, width=10, height=5, command=lambda r=i, c=j: self.move_tile(r, c))
                button.grid(row=i, column=j, padx=5, pady=5)
                row.append(button)
            self.buttons.append(row)

        self.shuffle_button = tk.Button(master, text="Shuffle", command=self.shuffle_puzzle)
        self.shuffle_button.grid(row=3, column=0, padx=5, pady=5)

        self.solve_button = tk.Button(master, text="Solve", command=self.solve_puzzle)
        self.solve_button.grid(row=3, column=2, padx=5, pady=5)

        self.update_puzzle()

    def update_puzzle(self):
        for i in range(3):
            for j in range(3):
                if self.puzzle_state[i][j] != 0:
                    self.buttons[i][j].config(text=str(self.puzzle_state[i][j]))
                else:
                    self.buttons[i][j].config(text="")

    def move_tile(self, row, col):
        if self.puzzle_state[row][col] != 0:
            directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
            for direction in directions:
                new_row, new_col = row + direction[0], col + direction[1]
                if 0 <= new_row < 3 and 0 <= new_col < 3 and self.puzzle_state[new_row][new_col] == 0:
                    self.puzzle_state[row][col], self.puzzle_state[new_row][new_col] = self.puzzle_state[new_row][new_col], self.puzzle_state[row][col]
                    self.update_puzzle()
                    break

    def shuffle_puzzle(self):
        self.puzzle_state = shuffle_puzzle(self.puzzle_state)
        self.update_puzzle()
        print("퍼즐이 섞였습니다.")

    def solve_puzzle(self):
        solution = solve_puzzle(self.puzzle_state)
        if solution is None:
            messagebox.showinfo("No Solution", "퍼즐을 풀 수 없습니다!")
        else:
            for direction in solution:
                i, j = next((i, j) for i in range(3) for j in range(3) if self.puzzle_state[i][j] == 0)
                new_i, new_j = i + direction[0], j + direction[1]
                self.puzzle_state[i][j], self.puzzle_state[new_i][new_j] = self.puzzle_state[new_i][new_j], self.puzzle_state[i][j]
                self.update_puzzle()
                move_str = {(-1, 0): 'Up', (1, 0): 'Down', (0, -1): 'Left', (0, 1): 'Right'}[direction]
                print(f"이동: {move_str}")
                self.master.update()
                self.master.after(500)
            messagebox.showinfo("Solved", "퍼즐이 해결되었습니다!")

root = tk.Tk()
puzzle_gui = PuzzleGUI(root)
root.mainloop()
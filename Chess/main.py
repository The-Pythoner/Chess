import ctypes as ct
c = ct.cdll.LoadLibrary("./main.so")

import pygame as pg
import numpy as np
pg.init()

c.is_in.argtypes = [ct.c_int, ct.c_int]
c.is_turn.argtypes = [ct.c_int, ct.c_bool]

c.get_moves.argtypes = [np.ctypeslib.ndpointer(dtype=np.uint8),
np.ctypeslib.ndpointer(dtype=np.uint8), np.ctypeslib.ndpointer(dtype=np.uint8), ct.c_int, ct.c_bool]

pg.display.set_caption("Chess")
pg.display.set_icon(pg.image.load("Images/p_7.png"))
screen = pg.display.set_mode((1080, 720))

# VARS
sq_sz = 90
turn = True
selected = [-1, -1]

array = np.array([
[8, 9, 10, 11, 12, 10, 9, 8],
[7, 7, 7, 7, 7, 7, 7, 7],
[0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0],
[1, 1, 1, 1, 1, 1, 1, 1],
[2, 3, 4, 5, 6, 4, 3, 2]], dtype=np.uint8)

moves = np.zeros((127, 5), dtype=np.uint8)

history = array.reshape((1, 8, 8)).copy()

# IMAGES
board = pg.image.load("Images/board.png")
pieces = [pg.image.load(f"Images/p_{i+1}.png") for i in range(12)]
back = pg.image.load("Images/back.png")
screen.blit(back, (720+60, 720-60-120))
blue = pg.image.load("Images/blue.png")

# FUNCTIONS
def draw(array, moves):
	screen.blit(board, (0, 0))

	for i in range(8):
		for j in range(8):
			if array[i, j] != 0:
				screen.blit(pieces[array[i, j]-1], (j*sq_sz, i*sq_sz))

	for move in moves:
		if move[0] != 0:
			if move[1] == selected[0] and move[2] == selected[1]:
				screen.blit(blue, (move[4]*sq_sz, move[3]*sq_sz))

		else:
			break

	pg.display.flip()

running = True

c.get_moves(array, moves, history, history.shape[0], turn)
draw(array, moves)

while running:
	for event in pg.event.get():
		if event.type == pg.QUIT:
			running = False
			pg.quit()

		if event.type == pg.MOUSEBUTTONDOWN:
			if event.pos[0] < 720:
				i = event.pos[1]//sq_sz
				j = event.pos[0]//sq_sz

				if c.is_turn(array[i, j], turn):
					selected = [i, j]

				else:
					for move in moves:
						if move[0] != 0:
							if (move[1] == selected[0] and move[2] == selected[1] and
							move[3] == i and move[4] == j):
								array[move[3], move[4]] = array[move[1], move[2]]
								array[move[1], move[2]] = 0

								if move[0] == 2:
									array[move[1], move[4]] = 0

								elif move[0] == 3:
									array[move[1], 3] = array[move[1], 0]
									array[move[1], 0] = 0

								elif move[0] == 4:
									array[move[1], 5] = array[move[1], 7]
									array[move[1], 7] = 0

								history = np.vstack((history, array.reshape((1, 8, 8)).copy()))

								turn = not turn
								c.get_moves(array, moves, history, history.shape[0], turn)

						else:
							break

					selected = [-1, -1]

			else:
				if history.shape[0] > 1:
					array = history[-2].copy()
					history = history[:-1]
					turn = not turn
					c.get_moves(array, moves, history, history.shape[0], turn)

			draw(array, moves)
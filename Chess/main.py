from get_moves import *

import pygame as pg
pg.init()

pg.display.set_caption("Chess")
pg.display.set_icon(pg.image.load("Images/p_1.png"))
screen = pg.display.set_mode((1080, 720))

# variables
sq_sz = 90
selected = [-1, -1]
turn = True

array = np.array([
[-2, -3, -4, -5, -6, -4, -3, -2],
[-1, -1, -1, -1, -1, -1, -1, -1],
[0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0],
[1, 1, 1, 1, 1, 1, 1, 1],
[2, 3, 4, 5, 6, 4, 3, 2]], dtype=np.int8)
history = np.zeros((0, 8, 8), dtype=np.int8)

moves = get_moves(array, turn, history)[0]

# loading images
pieces = [pg.image.load(f"Images/p_{i}.png") for i in range(1, 13)]
board = pg.image.load("Images/board.png")
blue = pg.image.load("Images/blue.png")
back = pg.image.load("Images/back.png")
back_rect = pg.Rect((720+60, 720-60-120, 240, 120))

screen.blit(back, back_rect)

running = True
clock = pg.time.Clock()
fps = 15

while running:
	clock.tick(fps)

	# displaying
	screen.blit(board, (0, 0))

	for i in range(8):
		for j in range(8):
			p = array[i, j]

			if p > 0:
				screen.blit(pieces[p-1], (j*sq_sz, i*sq_sz))

			elif p < 0:
				screen.blit(pieces[-p+5], (j*sq_sz, i*sq_sz))

	for move in moves:
		if move[0] != 2:
			if move[1] == selected[0] and move[2] == selected[1]:
				screen.blit(blue, (move[4]*sq_sz, move[3]*sq_sz))

		else:
			if move[1] == selected[0] and move[2] == selected[1]:
				screen.blit(blue, (move[3]*sq_sz, move[1]*sq_sz))

	pg.display.flip()

	for event in pg.event.get():
		if event.type == pg.QUIT:
			running = False

		elif event.type == pg.MOUSEBUTTONDOWN:
			x = event.pos[0]
			y = event.pos[1]
			j = int(x/sq_sz)
			i = int(y/sq_sz)

			if is_in(i, j):
				j = int(event.pos[0]/sq_sz)
				i = int(event.pos[1]/sq_sz)

				if is_turn(array[i, j], turn):
					selected = [i, j]

				else:
					for move in moves:
						if move[0] != 2:
							if (move[1] == selected[0] and move[2] == selected[1] and
							move[3] == i and move[4] == j):
								history = np.vstack((history, array.reshape((1, 8, 8))))
								array[move[3], move[4]] = array[move[1], move[2]]
								array[move[1], move[2]] = 0

								if abs(array[move[3], move[4]]) == 1 and move[3] in [0, 7]:
									array[move[3], move[4]] *= 5

								if move[0] == 1:
									array[move[1], move[4]] = 0

								turn = not turn
								moves = get_moves(array, turn, history)[0]

								selected = [-1, -1]

						else:
							if (move[1] == selected[0] and move[2] == selected[1] and
							move[1] == i and move[3] == j):
								history = np.vstack((history, array.reshape((1, 8, 8))))
								array[move[1], move[3]] = array[move[1], move[2]]
								array[move[1], move[5]] = array[move[1], move[4]]
								array[move[1], move[2]] = 0
								array[move[1], move[4]] = 0

								turn = not turn
								moves = get_moves(array, turn, history)[0]

								selected = [-1, -1]

			else:
				if back_rect.collidepoint((x, y)):
					if history.shape[0] > 0:
						array = history[-1]
						history = history[:-1]
						turn = not turn
						moves = get_moves(array, turn, history)[0]

pg.quit()
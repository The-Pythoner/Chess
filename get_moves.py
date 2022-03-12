from numba import jit

import numpy as np

@jit(nopython=True)
def is_turn(p, turn):
	return (p > 0 and turn) or (p < 0 and not turn)

@jit(nopython=True)
def is_in(i, j):
	return i < 8 and i >= 0 and j < 8 and j >= 0

@jit(nopython=True)
def get_moves(array, turn, history):
	moves = np.zeros((0, 6), dtype=np.int8)

	for i in range(8):
		for j in range(8):
			p = array[i, j]

			# pawn
			if abs(p) == 1 and is_turn(p, turn):
				if turn:
					k = -1

				else:
					k = 1

				if is_in(i+k, j):
					if array[i+k, j] == 0:
						moves = np.vstack((moves, np.array(
						[0, i, j, i+k, j, 0], dtype=np.int8).reshape((1, 6))))

						if (i == 6 and turn) or (i == 1 and not turn):
							if array[i+k*2, j] == 0:
								moves = np.vstack((moves, np.array(
								[0, i, j, i+k*2, j, 0], dtype=np.int8).reshape((1, 6))))

				if is_in(i+k, j-1):
					if is_turn(array[i+k, j-1], not turn):
						moves = np.vstack((moves, np.array(
						[0, i, j, i+k, j-1, 0], dtype=np.int8).reshape((1, 6))))

					if (is_turn(array[i, j-1], not turn) and
					array[i, j-1] == k and
					array[i+k*2, j-1] == 0):
						if (history[-1, i, j-1] == 0 and
						is_turn(history[-1, i+k*2, j-1], not turn) and
						history[-1, i+k*2, j-1] == k):
							moves = np.vstack((moves, np.array(
							[1, i, j, i+k, j-1, 0], dtype=np.int8).reshape((1, 6))))

				if is_in(i+k, j+1):
					if is_turn(array[i+k, j+1], not turn):
						moves = np.vstack((moves, np.array(
						[0, i, j, i+k, j+1, 0], dtype=np.int8).reshape((1, 6))))

					if (is_turn(array[i, j+1], not turn) and
					array[i, j+1] == k and
					array[i+k*2, j+1] == 0):
						if (history[-1, i, j+1] == 0 and
						is_turn(history[-1, i+k*2, j+1], not turn) and
						history[-1, i+k*2, j+1] == k):
							moves = np.vstack((moves, np.array(
							[1, i, j, i+k, j+1, 0], dtype=np.int8).reshape((1, 6))))

			# knight
			elif abs(p) == 3 and is_turn(p, turn):
				for k in [-2, -1, 1, 2]:
					for l in [-2, -1, 1, 2]:
						if abs(k) != abs(l) and is_in(i+k, j+l):
							if not is_turn(array[i+k, j+l], turn):
								moves = np.vstack((moves, np.array(
								[0, i, j, i+k, j+l, 0], dtype=np.int8).reshape((1, 6))))

			# king
			elif abs(p) == 6 and is_turn(p, turn):
				for k in [-1, 0, 1]:
					for l in [-1, 0, 1]:
						if (k != 0 or l != 0) and is_in(i+k, j+l):
							if not is_turn(array[i+k, j+l], turn):
								moves = np.vstack((moves, np.array(
								[0, i, j, i+k, j+l, 0], dtype=np.int8).reshape((1, 6))))

				# castling
				right_cast = True
				left_cast = True

				if turn:
					k = 7

				else:
					k = 0

				if abs(array[k, 4]) != 6 or not is_turn(array[k, 4], turn):
					right_cast = False
					left_cast = False

				if abs(array[k, 0]) != 2 or not is_turn(array[k, 0], turn):
					left_cast = False

				if abs(array[k, 7]) != 2 or not is_turn(array[k, 7], turn):
					right_cast = False

				for h in range(history.shape[0]):
					if abs(history[h, k, 4]) != 6 or not is_turn(history[h, k, 4], turn):
						right_cast = False
						left_cast = False

					if abs(history[h, k, 0]) != 2 or not is_turn(history[h, k, 0], turn):
						left_cast = False

					if abs(history[h, k, 7]) != 2 or not is_turn(history[h, k, 7], turn):
						right_cast = False

				if right_cast:
					if array[i+1, j] == 0 and array[i+2, j] == 0:
						moves = np.vstack((moves, np.array(
						[2, i, j, j+2, j+3, j+1], dtype=np.int8).reshape((1, 6))))

				if left_cast:
					if array[i-1, j] == 0 and array[i-2, j] == 0 and array[i-3, j] == 0:
						moves = np.vstack((moves, np.array(
						[2, i, j, j-2, j-4, j-1], dtype=np.int8).reshape((1, 6))))

			# rook or queen
			if abs(p) in [2, 5] and is_turn(p, turn):
				for k in [-1, 1]:
					for l in range(1, 8):
						if is_in(i+k*l, j):
							if not is_turn(array[i+k*l, j], turn):
								moves = np.vstack((moves, np.array(
								[0, i, j, i+k*l, j, 0], dtype=np.int8).reshape((1, 6))))

								if array[i+k*l, j] != 0:
									break

							else:
								break

						else:
							break

					for l in range(1, 8):
						if is_in(i, j+k*l):
							if not is_turn(array[i, j+k*l], turn):
								moves = np.vstack((moves, np.array(
								[0, i, j, i, j+k*l, 0], dtype=np.int8).reshape((1, 6))))

								if array[i, j+k*l] != 0:
									break

							else:
								break

						else:
							break

			# bishop or queen
			if abs(p) in [4, 5] and is_turn(p, turn):
				for k in [-1, 1]:
					for l in [-1, 1]:
						for m in range(1, 8):
							if is_in(i+k*m, j+l*m):
								if not is_turn(array[i+k*m, j+l*m], turn):
									moves = np.vstack((moves, np.array(
									[0, i, j, i+k*m, j+l*m, 0], dtype=np.int8).reshape((1, 6))))

									if array[i+k*m, j+l*m] != 0:
										break

								else:
									break

							else:
								break

	return moves
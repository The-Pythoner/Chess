#include <stdio.h>

_Bool is_in(char i, char j) {
	return i >= 0 && i < 8 && j >= 0 && j < 8;
}

_Bool is_turn(unsigned char p, _Bool turn) {
	return (p < 7 && p != 0 && turn) || (p > 6 && !turn);
}

void get_moves_(unsigned char* array, unsigned char* moves, unsigned char* history, int hi_sz, _Bool turn) {
	unsigned char i, j, mlen = 0;
	char k, l, m;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {

			// WHITE PAWN
			if (*(array+i*8+j) == 1 && turn) {
				if (is_in(i-1, j)) {
					if (*(array+i*8+j-8) == 0) {
						*(moves+mlen*5) = 1;
						*(moves+mlen*5+1) = i;
						*(moves+mlen*5+2) = j;
						*(moves+mlen*5+3) = i-1;
						*(moves+mlen*5+4) = j;
						mlen++;

						if (i-1 == 0) {
							*(moves+mlen*5-5) = 2;
						}

						if (i == 6) {
							if (*(array+i*8+j-16) == 0) {
								*(moves+mlen*5) = 1;
								*(moves+mlen*5+1) = i;
								*(moves+mlen*5+2) = j;
								*(moves+mlen*5+3) = i-2;
								*(moves+mlen*5+4) = j;
								mlen++;
							}
						}
					}
				}

				if (is_in(i-1, j-1)) {
					if (is_turn(*(array+i*8+j-8-1), !turn)) {
						*(moves+mlen*5) = 1;
						*(moves+mlen*5+1) = i;
						*(moves+mlen*5+2) = j;
						*(moves+mlen*5+3) = i-1;
						*(moves+mlen*5+4) = j-1;
						mlen++;

						if (i-1 == 0) {
							*(moves+mlen*5-5) = 2;
						}
					}

					// PAWN SPECIAL KILL
					if (i == 3) {
						if (*(array+i*8+j-1) == 7 && *(array+i*8+j-16-1) == 0) {
							if (*(history+hi_sz*64-128+i*8+j-1) == 0 && *(history+hi_sz*64-128+i*8+j-16-1) == 7) {
								*(moves+mlen*5) = 3;
								*(moves+mlen*5+1) = i;
								*(moves+mlen*5+2) = j;
								*(moves+mlen*5+3) = i-1;
								*(moves+mlen*5+4) = j-1;
								mlen++;
							}
						}
					}
				}

				if (is_in(i-1, j+1)) {
					if (is_turn(*(array+i*8+j-8+1), !turn)) {
						*(moves+mlen*5) = 1;
						*(moves+mlen*5+1) = i;
						*(moves+mlen*5+2) = j;
						*(moves+mlen*5+3) = i-1;
						*(moves+mlen*5+4) = j+1;
						mlen++;

						if (i-1 == 0) {
							*(moves+mlen*5-5) = 2;
						}
					}

					// PAWN SPECIAL KILL
					if (i == 3) {
						if (*(array+i*8+j+1) == 7 && *(array+i*8+j-16+1) == 0) {
							if (*(history+hi_sz*64-128+i*8+j+1) == 0 && *(history+hi_sz*64-128+i*8+j-16+1) == 7) {
								*(moves+mlen*5) = 3;
								*(moves+mlen*5+1) = i;
								*(moves+mlen*5+2) = j;
								*(moves+mlen*5+3) = i-1;
								*(moves+mlen*5+4) = j+1;
								mlen++;
							}
						}
					}
				}
			}

			// BLACK PAWN
			if (*(array+i*8+j) == 7 && !turn) {
				if (is_in(i+1, j)) {
					if (*(array+i*8+j+8) == 0) {
						*(moves+mlen*5) = 1;
						*(moves+mlen*5+1) = i;
						*(moves+mlen*5+2) = j;
						*(moves+mlen*5+3) = i+1;
						*(moves+mlen*5+4) = j;
						mlen++;

						if (i+1 == 7) {
							*(moves+mlen*5-5) = 2;
						}

						if (i == 1) {
							if (*(array+i*8+j+16) == 0) {
								*(moves+mlen*5) = 1;
								*(moves+mlen*5+1) = i;
								*(moves+mlen*5+2) = j;
								*(moves+mlen*5+3) = i+2;
								*(moves+mlen*5+4) = j;
								mlen++;
							}
						}
					}
				}

				if (is_in(i+1, j-1)) {
					if (is_turn(*(array+i*8+j+8-1), !turn)) {
						*(moves+mlen*5) = 1;
						*(moves+mlen*5+1) = i;
						*(moves+mlen*5+2) = j;
						*(moves+mlen*5+3) = i+1;
						*(moves+mlen*5+4) = j-1;
						mlen++;

						if (i+1 == 7) {
							*(moves+mlen*5-5) = 2;
						}
					}

					// PAWN SPECIAL KILL
					if (i == 4) {
						if (*(array+i*8+j-1) == 1 && *(array+i*8+j+16-1) == 0) {
							if (*(history+hi_sz*64-128+i*8+j-1) == 0 && *(history+hi_sz*64-128+i*8+j+16-1) == 1) {
								*(moves+mlen*5) = 3;
								*(moves+mlen*5+1) = i;
								*(moves+mlen*5+2) = j;
								*(moves+mlen*5+3) = i+1;
								*(moves+mlen*5+4) = j-1;
								mlen++;
							}
						}
					}
				}

				if (is_in(i+1, j+1)) {
					if (is_turn(*(array+i*8+j+8+1), !turn)) {
						*(moves+mlen*5) = 1;
						*(moves+mlen*5+1) = i;
						*(moves+mlen*5+2) = j;
						*(moves+mlen*5+3) = i+1;
						*(moves+mlen*5+4) = j+1;
						mlen++;

						if (i+1 == 7) {
							*(moves+mlen*5-5) = 2;
						}
					}

					// PAWN SPECIAL KILL
					if (i == 4) {
						if (*(array+i*8+j+1) == 1 && *(array+i*8+j+16+1) == 0) {
							if (*(history+hi_sz*64-128+i*8+j+1) == 0 && *(history+hi_sz*64-128+i*8+j+16+1) == 1) {
								*(moves+mlen*5) = 3;
								*(moves+mlen*5+1) = i;
								*(moves+mlen*5+2) = j;
								*(moves+mlen*5+3) = i+1;
								*(moves+mlen*5+4) = j+1;
								mlen++;
							}
						}
					}
				}
			}

			// KNIGHT
			if ((*(array+i*8+j) == 3 && turn) || (*(array+i*8+j) == 9 && !turn)) {
				for (k = -2; k < 3; k++) {
					for (l = -2; l < 3; l++) {
						if (k != 0 && l != 0 && k != l && k != -l && is_in(i+k, j+l)) {
							if (!is_turn(*(array+i*8+j+k*8+l), turn)) {
								*(moves+mlen*5) = 1;
								*(moves+mlen*5+1) = i;
								*(moves+mlen*5+2) = j;
								*(moves+mlen*5+3) = i+k;
								*(moves+mlen*5+4) = j+l;
								mlen++;
							}
						}
					}
				}
			}

			// ROOK AND QUEEN
			if (((*(array+i*8+j) == 2 || *(array+i*8+j) == 5) && turn) ||
			((*(array+i*8+j) == 8 || *(array+i*8+j) == 11) && !turn)) {
				for (k = -1; k < 2; k += 2) {
					for (l = 1; l < 8; l++) {
						if (is_in(i+k*l, j)) {
							if (!is_turn(*(array+i*8+j+k*l*8), turn)) {
								*(moves+mlen*5) = 1;
								*(moves+mlen*5+1) = i;
								*(moves+mlen*5+2) = j;
								*(moves+mlen*5+3) = i+k*l;
								*(moves+mlen*5+4) = j;
								mlen++;

								if (*(array+i*8+j+k*l*8) != 0) {
									break;
								}

							} else {
								break;
							}

						} else {
							break;
						}
					}

					for (l = 1; l < 8; l++) {
						if (is_in(i, j+k*l)) {
							if (!is_turn(*(array+i*8+j+k*l), turn)) {
								*(moves+mlen*5) = 1;
								*(moves+mlen*5+1) = i;
								*(moves+mlen*5+2) = j;
								*(moves+mlen*5+3) = i;
								*(moves+mlen*5+4) = j+k*l;
								mlen++;

								if (*(array+i*8+j+k*l) != 0) {
									break;
								}
								
							} else {
								break;
							}

						} else {
							break;
						}
					}
				}
			}

			// BISHOP AND QUEEN
			if (((*(array+i*8+j) == 4 || *(array+i*8+j) == 5) && turn) ||
			((*(array+i*8+j) == 10 || *(array+i*8+j) == 11) && !turn)) {
				for (k = -1; k < 2; k += 2) {
					for (l = -1; l < 2; l += 2) {
						for (m = 1; m < 8; m++) {
							if (is_in(i+k*m, j+l*m)) {
								if (!is_turn(*(array+i*8+j+k*m*8+l*m), turn)) {
									*(moves+mlen*5) = 1;
									*(moves+mlen*5+1) = i;
									*(moves+mlen*5+2) = j;
									*(moves+mlen*5+3) = i+k*m;
									*(moves+mlen*5+4) = j+l*m;
									mlen++;

									if (*(array+i*8+j+k*m*8+l*m) != 0) {
										break;
									}

								} else {
									break;
								}

							} else {
								break;
							}
						}
					}
				}
			}

			// KING
			if ((*(array+i*8+j) == 6 && turn) || (*(array+i*8+j) == 12 && !turn)) {
				for (k = -1; k < 2; k++) {
					for (l = -1; l < 2; l++) {
						if (is_in(i+k, j+l)) {
							if ((k != 0 || l != 0) && !is_turn(*(array+i*8+j+k*8+l), turn)) {
								*(moves+mlen*5) = 1;
								*(moves+mlen*5+1) = i;
								*(moves+mlen*5+2) = j;
								*(moves+mlen*5+3) = i+k;
								*(moves+mlen*5+4) = j+l;
								mlen++;
							}
						}
					}
				}

				// CASTLING
				if (j == 4) {
					if (i == 7 && turn) {
						if (*(array+56) == 2) {
							if (*(array+56+1) == 0 && *(array+56+2) == 0 && *(array+56+3) == 0) {
								*(moves+mlen*5) = 4;
								*(moves+mlen*5+1) = 7;
								*(moves+mlen*5+2) = 4;
								*(moves+mlen*5+3) = 7;
								*(moves+mlen*5+4) = 2;
								mlen++;
							}
						}

						if (*(array+56+7) == 2) {
							if (*(array+56+5) == 0 && *(array+56+6) == 0) {
								*(moves+mlen*5) = 5;
								*(moves+mlen*5+1) = 7;
								*(moves+mlen*5+2) = 4;
								*(moves+mlen*5+3) = 7;
								*(moves+mlen*5+4) = 6;
								mlen++;
							}
						}
					}

					if (i == 0 && !turn) {
						if (*(array) == 8) {
							if (*(array+1) == 0 && *(array+2) == 0 && *(array+3) == 0) {
								*(moves+mlen*5) = 4;
								*(moves+mlen*5+1) = 0;
								*(moves+mlen*5+2) = 4;
								*(moves+mlen*5+3) = 0;
								*(moves+mlen*5+4) = 2;
								mlen++;
							}
						}

						if (*(array+7) == 8) {
							if (*(array+5) == 0 && *(array+6) == 0) {
								*(moves+mlen*5) = 5;
								*(moves+mlen*5+1) = 0;
								*(moves+mlen*5+2) = 4;
								*(moves+mlen*5+3) = 0;
								*(moves+mlen*5+4) = 6;
								mlen++;
							}
						}
					}
				}
			}
		}
	}
}

void play(unsigned char* array, unsigned char* move, _Bool turn) {
	*(array+(*(move+3))*8+(*(move+4))) = *(array+(*(move+1))*8+(*(move+2)));
	*(array+(*(move+1))*8+(*(move+2))) = 0;

	if (*move == 2) {
		*(array+(*(move+3))*8+(*(move+4))) = 5+((int) !turn)*6;
	} else if (*move == 3) {
		*(array+(*(move+1))*8+(*(move+4))) = 0;
	} else if (*move == 4) {
		*(array+(*(move+1))*8+3) = *(array+(*(move+1))*8);
		*(array+(*(move+1))*8) = 0;
	} else if (*move == 5) {
		*(array+(*(move+1))*8+5) = *(array+(*(move+1))*8+7);
		*(array+(*(move+1))*8+7) = 0;
	}
}

void get_moves(unsigned char* array, unsigned char* moves, unsigned char* history, int hi_sz, _Bool turn) {
	unsigned char moves_[127][5], moves_opp[127][5], i, j, mlen = 0;
	_Bool is_move;

	for (i = 0; i < 127; i++) {
		for (j = 0; j < 5; j++) {
			moves_[i][j] = 0;
			moves_opp[i][j] = 0;
		}
	}

	get_moves_(array, &moves_[0][0], history, hi_sz, turn);

	for (i = 0; i < 127; i++) {
		if (moves_[i][0] != 0) {
			if (moves_[i][0] < 4) {
				*(moves+mlen*5) = moves_[i][0];
				*(moves+mlen*5+1) = moves_[i][1];
				*(moves+mlen*5+2) = moves_[i][2];
				*(moves+mlen*5+3) = moves_[i][3];
				*(moves+mlen*5+4) = moves_[i][4];
				mlen++;
			} else if (moves_[i][0] == 4) {
				get_moves_(array, &moves_opp[0][0], history, hi_sz, !turn);
				is_move = (_Bool) 1;

				for (j = 0; j < 127; j++) {
					if (moves_opp[j][3] == moves_[i][1] && moves_opp[j][4] > 1 && moves_opp[j][4] < 5) {
						is_move = (_Bool) 0;
					}
				}

				if (is_move) {
					*(moves+mlen*5) = moves_[i][0];
					*(moves+mlen*5+1) = moves_[i][1];
					*(moves+mlen*5+2) = moves_[i][2];
					*(moves+mlen*5+3) = moves_[i][3];
					*(moves+mlen*5+4) = moves_[i][4];
					mlen++;
				}
				
			} else {
				get_moves_(array, &moves_opp[0][0], history, hi_sz, !turn);
				is_move = (_Bool) 1;

				for (j = 0; j < 127; j++) {
					if (moves_opp[j][3] == moves_[i][1] && moves_opp[j][4] > 3 && moves_opp[j][4] < 7) {
						is_move = (_Bool) 0;
					}
				}

				if (is_move) {
					*(moves+mlen*5) = moves_[i][0];
					*(moves+mlen*5+1) = moves_[i][1];
					*(moves+mlen*5+2) = moves_[i][2];
					*(moves+mlen*5+3) = moves_[i][3];
					*(moves+mlen*5+4) = moves_[i][4];
					mlen++;
				}
			}

		} else {
			break;
		}
	}
}
#include <stdio.h>

_Bool is_in(char i, char j) {
	return i >= 0 && i < 8 && j >= 0 && j < 8;
}

_Bool is_turn(unsigned char p, _Bool turn) {
	return (p < 7 && p != 0 && turn) || (p > 6 && !turn);
}

void get_moves_(unsigned char* array, unsigned char* moves, _Bool turn) {
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
			}
		}
	}
}

void get_moves(unsigned char* array, unsigned char* moves, _Bool turn) {
	get_moves_(array, moves, turn);
}
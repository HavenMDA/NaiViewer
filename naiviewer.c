#include <raylib.h>

#include <time.h>

#include <stdlib.h>

#include <stdio.h>

#include <ctype.h>

#include "dict.h"

/* Compilation command for Raspberry Pi: gcc naiviewer.c -o naiviewer -lraylib -lGLESv2 -lEGL -lm -lpthread -ldl -lX11 */

struct Ruletype {
	
	int bsfkl;
	
};

void rparse(int (* bconds)[117], int (* sconds)[117], int (* fconds)[117], int (* kconds)[117], int (* lconds)[117], int * naive, int * gennum, struct Ruletype * ruletype) {
	
	printf("Rule: ");
	
	int lastdigit = -1;
	
	int currentlynegating = 0;
	
	int nn;
	
	char c = getchar();
	
	char letters[] = "cekainyqjrtwz";
	
	int lengths[9] = {0, 2, 6, 10, 13, 10, 6, 2, 0};
	
	while ((c != '/')) {
		
		if (c == 'N') {
			
			*naive = 1;
			
			goto bend;
			
		}
		
		if (c == 'R') goto randgen;
		
		if (c == 'B') goto bend;
		
		if (isdigit(c)) {
			
			currentlynegating = 0;
			
			nn = c - '0';
			
			if (lastdigit >= 0) {
				
				for (int n = 0; n < 13; n++) {
					
					(*bconds)[lastdigit * 13 + n] = 1;
					
				}
				
			}
			
			for (int n = 0; n < 13; n++) {
				
				(*bconds)[nn * 13 + n] = 2;
				
			}
			
			lastdigit = nn;
			
			(*bconds)[nn] = 1;
			
		}
		
		if (isalpha(c)) {
			
			int i = -1;
			
			lastdigit = -1;
			
			for (int n = 0; n < 13; n++) {
				
				if (letters[n] == c) {
					
					i = n;
					
					break;
					
				}
				
			}
			
			for (int n = 0; n < 13; n++) {
				
				if (currentlynegating) {
					
					if (n == i) {
						
						(*bconds)[nn * 13 + n] = 0;
						
					}
					
				} else {
					
					if ((*bconds)[nn * 13 + n] == 2) {
						
						(*bconds)[nn * 13 + n] = 0;
						
					}
					
					if (((*bconds)[nn * 13 + n] == 0) && (n == i)) {
						
						(*bconds)[nn * 13 + n] = 1;
						
					}
					
				}
				
			}
			
		}
		
		if (c == '-') {
			
			lastdigit = -1;
			
			currentlynegating = 1;
			
			for (int n = 0; n < 13; n++) {
				
				if ((*bconds)[nn * 13 + n] == 2) {
					
					(*bconds)[nn * 13 + n] = 1;
					
				}
				
			}
			
		}
		
		if (c == '\n') {
			
			for (int n = 39; n < 52; n++) {
				
				(*bconds)[n] = 1;
				
			}
			
			for (int n = 26; n < 52; n++) {
				
				(*sconds)[n] = 1;
				
			}
			
			return;
			
		}
		
		bend:;
		
		c = getchar();
		
	}
	
	lastdigit = -1;
	
	currentlynegating = 0;
	
	c = getchar();
	
	while ((c != '\n') && (c != '/')) {
		
		if (c == 'S') goto send;
		
		if (isdigit(c)) {
			
			currentlynegating = 0;
			
			nn = c - '0';
			
			if (lastdigit >= 0) {
				
				for (int n = 0; n < 13; n++) {
					
					(*sconds)[lastdigit * 13 + n] = 1;
					
				}}
			
			for (int n = 0; n < 13; n++) {
				
				(*sconds)[nn * 13 + n] = 2;
				
			}
			
			lastdigit = nn;
			
			(*sconds)[nn] = 1;
			
		}
		
		if (isalpha(c)) {
			
			lastdigit = -1;
			
			int i = -1;
			
			for (int n = 0; n < 13; n++) {
				
				if (letters[n] == c) {
					
					i = n;
					
					break;
					
				}
				
			}
			
			for (int n = 0; n < 13; n++) {
				
				if (currentlynegating) {
					
					if (n == i) {
						
						(*sconds)[nn * 13 + n] = 0;
						
					}
					
				} else {
					
					if ((*sconds)[nn * 13 + n] == 2) {
						
						(*sconds)[nn * 13 + n] = 0;
						
					}
					
					if (((*sconds)[nn * 13 + n] == 0) && (n == i)) {
						
						(*sconds)[nn * 13 + n] = 1;
						
					}
					
				}
				
			}
			
		}
		
		if (c == '-') {
			
			lastdigit = -1;
			
			currentlynegating = 1;
			
			for (int n = 0; n < 13; n++) {
				
				if ((*sconds)[nn * 13 + n] == 2) {
					
					(*sconds)[nn * 13 + n] = 1;
					
				}
				
			}
			
		}
		
		send:;
		
		c = getchar();
		
		continue;
		
		randgen:;
		
		srand(time(NULL));
		
		*naive = rand() % 2;
		
		if (*naive) {
			
			printf("N");
			
		}
		
		printf("B");
		
		for (int n = 3; n < 9; n++) {
			
			for (int c = 0; c < lengths[n]; c++) {
				
				(*bconds)[n * 13 + c] = rand() % 2;
				
			}
			
		}
		
		(*bconds)[42] = 1;
		
		(*bconds)[43] = 1;
		
		for (int n = 0; n < 9; n++) {
			
			for (int c = 0; c < lengths[n]; c++) {
				
				if ((*bconds)[n * 13 + c]) {
					
					printf("%d", n);
					
					break;
					
				}
				
			}
			
			for (int c = 0; c < lengths[n]; c++) {
				
				if ((*bconds)[n * 13 + c]) {
					
					printf("%c", letters[c]);
					
				}
				
			}
			
		}
		
		printf("/S");
		
		for (int n = 0; n < 9; n++) {
			
			for (int c = 0; c < lengths[n]; c++) {
				
				(*sconds)[n * 13 + c] = rand() % 2;
				
			}
			
		}
		
		for (int n = 0; n < 9; n++) {
			
			for (int c = 0; c < lengths[n]; c++) {
				
				if ((*sconds)[n * 13 + c]) {
					
					printf("%d", n);
					
					break;
					
				}
				
			}
			
			for (int c = 0; c < lengths[n]; c++) {
				
				if ((*sconds)[n * 13 + c]) {
					
					printf("%c", letters[c]);
					
				}
				
			}
			
		}
		
		printf("\n");
		
		(*ruletype).bsfkl = 0;
		
		return;
		
	}
	
	*gennum = 0;
	
	if (c == '\n') {
		
		(*ruletype).bsfkl = 0;
		
		*gennum = 2;
		
		return;
		
	}
	
	c = getchar();
	
	if (c == 'G') goto generations;
	
	if (c == 'F') goto bsfkl;
	
	generations:;
	
	c = getchar();
	
	while (c != '\n') {
		
		if (c == '/') goto gend;
		
		*gennum *= 10;
		
		*gennum += (c - '0');
		
		gend:;
		
		c = getchar();
		
	}
	
	if (!(*gennum) || (*gennum == 1)) {
		
		 *gennum = 2;
		 
	}
	
	(*ruletype).bsfkl = 0;
	
	return;
	
	bsfkl:;
	
	(*ruletype).bsfkl = 1;
	
	c = getchar();
	
	while ((c != '/')) {
		
		if (isdigit(c)) {
			
			currentlynegating = 0;
			
			nn = c - '0';
			
			if (lastdigit >= 0) {
				
				for (int n = 0; n < 13; n++) {
					
					(*fconds)[lastdigit * 13 + n] = 1;
					
				}}
			
			for (int n = 0; n < 13; n++) {
				
				(*fconds)[nn * 13 + n] = 2;
				
			}
			
			lastdigit = nn;
			
			(*fconds)[nn] = 1;
			
		}
		
		if (isalpha(c)) {
			
			lastdigit = -1;
			
			int i = -1;
			
			for (int n = 0; n < 13; n++) {
				
				if (letters[n] == c) {
					
					i = n;
					
					break;
					
				}
				
			}
			
			for (int n = 0; n < 13; n++) {
				
				if (currentlynegating) {
					
					if (n == i) {
						
						(*fconds)[nn * 13 + n] = 0;
						
					}
					
				} else {
					
					if ((*fconds)[nn * 13 + n] == 2) {
						
						(*fconds)[nn * 13 + n] = 0;
						
					}
					
					if (((*fconds)[nn * 13 + n] == 0) && (n == i)) {
						
						(*fconds)[nn * 13 + n] = 1;
						
					}
					
				}
				
			}
			
		}
		
		if (c == '-') {
			
			lastdigit = -1;
			
			currentlynegating = 1;
			
			for (int n = 0; n < 13; n++) {
				
				if ((*fconds)[nn * 13 + n] == 2) {
					
					(*fconds)[nn * 13 + n] = 1;
					
				}
				
			}
			
		}
		
		fend:;
		
		c = getchar();
		
	}
	
	c = getchar();
	
	while ((c != '/')) {
		
		if (c == 'K') goto kend;
		
		if (isdigit(c)) {
			
			currentlynegating = 0;
			
			nn = c - '0';
			
			if (lastdigit >= 0) {
				
				for (int n = 0; n < 13; n++) {
					
					(*kconds)[lastdigit * 13 + n] = 1;
					
				}}
			
			for (int n = 0; n < 13; n++) {
				
				(*kconds)[nn * 13 + n] = 2;
				
			}
			
			lastdigit = nn;
			
			(*kconds)[nn] = 1;
			
		}
		
		if (isalpha(c)) {
			
			lastdigit = -1;
			
			int i = -1;
			
			for (int n = 0; n < 13; n++) {
				
				if (letters[n] == c) {
					
					i = n;
					
					break;
					
				}
				
			}
			
			for (int n = 0; n < 13; n++) {
				
				if (currentlynegating) {
					
					if (n == i) {
						
						(*kconds)[nn * 13 + n] = 0;
						
					}
					
				} else {
					
					if ((*kconds)[nn * 13 + n] == 2) {
						
						(*kconds)[nn * 13 + n] = 0;
						
					}
					
					if (((*kconds)[nn * 13 + n] == 0) && (n == i)) {
						
						(*kconds)[nn * 13 + n] = 1;
						
					}
					
				}
				
			}
			
		}
		
		if (c == '-') {
			
			lastdigit = -1;
			
			currentlynegating = 1;
			
			for (int n = 0; n < 13; n++) {
				
				if ((*kconds)[nn * 13 + n] == 2) {
					
					(*kconds)[nn * 13 + n] = 1;
					
				}
				
			}
			
		}
		
		kend:;
		
		c = getchar();
		
	}
	
	c = getchar();
	
	while ((c != '\n')) {
		
		if (c == 'L') goto lend;
		
		if (isdigit(c)) {
			
			currentlynegating = 0;
			
			nn = c - '0';
			
			if (lastdigit >= 0) {
				
				for (int n = 0; n < 13; n++) {
					
					(*lconds)[lastdigit * 13 + n] = 1;
					
				}}
			
			for (int n = 0; n < 13; n++) {
				
				(*lconds)[nn * 13 + n] = 2;
				
			}
			
			lastdigit = nn;
			
			(*lconds)[nn] = 1;
			
		}
		
		if (isalpha(c)) {
			
			lastdigit = -1;
			
			int i = -1;
			
			for (int n = 0; n < 13; n++) {
				
				if (letters[n] == c) {
					
					i = n;
					
					break;
					
				}
				
			}
			
			for (int n = 0; n < 13; n++) {
				
				if (currentlynegating) {
					
					if (n == i) {
						
						(*lconds)[nn * 13 + n] = 0;
						
					}
					
				} else {
					
					if ((*lconds)[nn * 13 + n] == 2) {
						
						(*lconds)[nn * 13 + n] = 0;
						
					}
					
					if (((*lconds)[nn * 13 + n] == 0) && (n == i)) {
						
						(*lconds)[nn * 13 + n] = 1;
						
					}
					
				}
				
			}
			
		}
		
		if (c == '-') {
			
			lastdigit = -1;
			
			currentlynegating = 1;
			
			for (int n = 0; n < 13; n++) {
				
				if ((*lconds)[nn * 13 + n] == 2) {
					
					(*lconds)[nn * 13 + n] = 1;
					
				}
				
			}
			
		}
		
		lend:;
		
		c = getchar();
		
	}
	
	*gennum = 3;
	
}

void advance(int (* world)[200][200], int bconds[117], int sconds[117], int fconds[117], int kconds[117], int lconds[117], int colorized, int naive, int gennum, struct Ruletype ruletype) {
	
	int neigh[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
	
	int next[200][200] = {0};
	
	for (int y = 0; y < 200; y++) {
		
		for (int x = 0; x < 200; x++) {
			
			int count = 0;
			
			int binary = 0;
			
			int second = 0;
			
			for (int n = 0; n < 8; n++) {
				
				int augx = x + neigh[n][1];
				
				int augy = y + neigh[n][0];
				
				binary *= 2;
				
				second *= 2;
				
				if ((augx >= 200) || (augy >= 200) || (augx < 0) || (augy < 0)) {
					
					continue;
					
				}
				
				if ((*world)[y + neigh[n][0]][x + neigh[n][1]]) {
					
					if (!(ruletype.bsfkl)) {
						
						if (gennum > 2) {
							
							if ((*world)[y + neigh[n][0]][x + neigh[n][1]] == 1) {
								
								binary++;
								
								count++;
								
							}
							
						} else {
							
							binary++;
							
							count++;
							
						}
						
					} else {
						
						if ((*world)[y + neigh[n][0]][x + neigh[n][1]] == 1) {
							
							binary++;
							
						}
						
						if ((*world)[y + neigh[n][0]][x + neigh[n][1]] == 2) {
							
							second++;
							
						}
						
					}
					
				}
				
			}
			
			if (!(ruletype.bsfkl)) {
				
				if (!(*world)[y][x] && bconds[dict[binary]]) { /* Birth */
					
					if (naive) {
						
						if (colorized) {
							
							(*world)[y][x] = count + 1;
							
						} else {
							
							(*world)[y][x] = 1;
							
						}
						
						continue; /* Prevents cell states from being overwritten more than once in naive rules */
							
					} else {
						
						if (colorized) {
							
							next[y][x] = count + 1;
							
						} else {
							
							next[y][x] = 1;
							
						}
						
					}
					
				} else if ((*world)[y][x] && !(sconds[dict[binary]])) { /* Death */
					
					if (gennum == 2) { /* Two-state rules */
						
						if (naive) {
							
							(*world)[y][x] = 0;
							
							continue; /* Prevents cell states from being overwritten more than once in naive rules */
							
						} else {
							
							next[y][x] = 0;
							
						}
						
					} else { /* Generations rules */
						
						if (naive) {
							
							naive_dying:;
							
							(*world)[y][x]++;
							
							(*world)[y][x] %= gennum;
							
							/* The two lines above increment all dying cells and kill cells in their last stage of death */
							
							continue; /* Prevents cell states from being overwritten more than once in naive rules */
							
						} else {
							
							dying:;
							
							next[y][x] = (*world)[y][x] + 1;
							
							next[y][x] %= gennum;
							
						}
						
					}
					
				} else if ((*world)[y][x] && sconds[dict[binary]]) { /* Survival */
					
					if (gennum == 2) {
						
						if (naive) {
							
							if (colorized) {
								
								(*world)[y][x] = count + 1;
								
							} else {
								
								(*world)[y][x] = 1;
								
							}
							
							continue;
							
						} else {
							
							if (colorized) {
								
								next[y][x] = count + 1;
								
							} else {
								
								next[y][x] = 1;
								
							}
							
						}
						
					} else {
						
						if (naive) {
							
							if ((*world)[y][x] == 1) {
								
								(*world)[y][x] = 1;
								
							} else {
								
								goto naive_dying;
								
							}
							
							continue;
							
						} else {
							
							if ((*world)[y][x] == 1) {
								
								next[y][x] = 1;
								
							} else {
								
								goto dying;
								
							}
							
						}
						
					}
					
				}
				
			} else {
				
				if (((*world)[y][x] == 0) && (bconds[dict[binary]] && fconds[dict[second]])) {
					
					if (naive) {
						
						(*world)[y][x] = 1;
						
						continue;
						
					} else {
						
						next[y][x] = 1;
						
					}
					
				} else if (((*world)[y][x] == 1) && kconds[dict[second]]) {
					
					if (naive) {
						
						(*world)[y][x] = 0;
						
						continue;
						
					} else {
						
						next[y][x] = 0;
						
					}
					
				} else if (((*world)[y][x] == 1) && sconds[dict[binary]]) {
					
					if (naive) {
						
						(*world)[y][x] = 1;
						
						continue;
						
					} else {
						
						next[y][x] = 1;
						
					}
					
				} else if (((*world)[y][x] == 1) && (!kconds[dict[second]] && !sconds[dict[binary]])) {
					
					if (naive) {
						
						(*world)[y][x] = 2;
						
						continue;
						
					} else {
						
						next[y][x] = 2;
						
					}
					
				} else if (((*world)[y][x] == 2) && lconds[dict[binary]]) {
					
					if (naive) {
						
						(*world)[y][x] = 0;
						
						continue;
						
					} else {
						
						next[y][x] = 0;
						
					}
				
				} else if (((*world)[y][x] == 2) && !lconds[dict[binary]]) {
					
					if (naive) {
						
						(*world)[y][x] = 2;
						
						continue;
						
					} else {
						
						next[y][x] = 2;
						
					}
					
				}
				
			}
			
		}
		
	}
	
	if (!naive) {
		
		for (int y = 0; y < 200; y++) {
			
			for (int x = 0; x < 200; x++) {
				
				(*world)[y][x] = next[y][x];
				
			}
			
		}
		
	}
	
}

void show(int world[200][200], int cursorpos[2], int selection[2][2], int colorized, int gennum, struct Ruletype ruletype) {
	
	int xstart, xend, xinc, ystart, yend, yinc;
	
	int g, k, r, f;
	
	Color cursor = {255, 0, 0, 128};
	
	Color redcursor = {0, 0, 255, 255};
	
	Color StateOne = {0, 128, 255, 255};
	
	Color StateTwo = {255, 0, 0, 255};
	
	Color colors[10] = {BLACK, GRAY, WHITE, RED, GREEN, BLUE, ORANGE, PURPLE, YELLOW, PINK};
	
	for (int y = 0; y < 200; y++) {
		
		for (int x = 0; x < 200; x++) {
			
			if (world[y][x]) {
				
				if (!(ruletype.bsfkl)) {
					
					if (colorized) {
						
						DrawRectangle(x * 5, y * 5, 5, 5, colors[world[y][x]]);
						
					} else {
						
						g = gennum - 2;
						
						k = world[y][x] - 1;
						
						if (gennum == 2) {
							
							f = 0;
							
						} else {
							
							f = 255 / g;
							
						}
						
						r = 255 - (k * f);
							
						Color gencolor = {r, r, 255, 255};
						
						DrawRectangle(x * 5, y * 5, 5, 5, gencolor);
						
					}
					
				} else {
					
					if (world[y][x] == 1) {
						
						DrawRectangle(x * 5, y * 5, 5, 5, StateOne);
						
					}
					
					if (world[y][x] == 2) {
						
						DrawRectangle(x * 5, y * 5, 5, 5, StateTwo);
						
					}
					
				}
				
			}
			
			if ((cursorpos[0] == y) && (cursorpos[1] == x)) {
				
				if ((world[y][x] == 3) || (world[y][x] == 6) || (world[y][x] == 7) || (world[y][x] == 8) || (world[y][x] == 9)) {
					
					DrawRectangle(x * 5, y * 5, 5, 5, redcursor); /* Makes the cursor stand out from red colors */
					
				} else {
					
					DrawRectangle(x * 5, y * 5, 5, 5, cursor);
					
				}
				
			}
			
		}
		
	}
	
	if ((selection[0][0] == selection[1][0]) && (selection[0][1] == selection[1][1])) return;
	
	xstart = selection[0][1] + 1;
	
	ystart = selection[0][0] + 1;
	
	xend = selection[1][1];
	
	yend = selection[1][0];
	
	xinc = (xstart <= xend) ? 1 : -1;
	
	yinc = (ystart <= yend) ? 1 : -1;
	
	Color select = {0, 255, 0, 128};
	
	for (int y = ystart; y != yend; y += yinc) {
		
		for (int x = xstart; x != xend; x += xinc) {
			
			DrawRectangle(x * 5, y * 5, 5, 5, select);
			
		}
		
	}
	
}

void delete(int (* world)[200][200], int selection[2][2]) {
	
	int xstart, xend, xinc, ystart, yend, yinc;
	
	if ((selection[0][0] == selection[1][0]) && (selection[0][1] == selection[1][1])) {
		
		xstart = 0;
		
		xend = 200;
		
		ystart = 0;
		
		yend = 200;
		
		xinc = 1;
		
		yinc = 1;
		
	} else {
		
		xstart = selection[0][1] + 1;
		
		ystart = selection[0][0] + 1;
		
		xend = selection[1][1];
		
		yend = selection[1][0];
		
		xinc = (xstart <= xend) ? 1 : -1;
		
		yinc = (ystart <= yend) ? 1 : -1;
		
	}
	
	for (int y = ystart; y != yend; y += yinc) {
		
		for (int x = xstart; x != xend; x += xinc) {
			
			(*world)[y][x] = 0;
			
		}
		
	}
	
}

void makerle(int world[200][200], int selection[2][2], char (* rle)[40201], int (* fullsize)) {
	
	for (int n = 0; n < 40201; n++) {
		
		(*rle)[n] = 0;
		
	}
	
	int xstart, xend, xinc, ystart, yend, yinc;
	
	int n = 0;
	
	if ((selection[0][0] == selection[1][0]) && (selection[0][1] == selection[1][1])) {
		
		xstart = 0;
		
		xend = 200;
		
		ystart = 0;
		
		yend = 200;
		
		*fullsize = 1;
		
	} else {
		
		xstart = (selection[0][1] <= selection[1][1]) ? selection[0][1] + 1 : selection[1][1] + 1;
		
		ystart = (selection[0][0] <= selection[1][0]) ? selection[0][0] + 1 : selection[1][0] + 1;
		
		xend = (selection[0][1] <= selection[1][1]) ? selection[1][1] : selection[0][1];
		
		yend = (selection[0][0] <= selection[1][0]) ? selection[1][0] : selection[0][0];
		
		*fullsize = 0;
		
	}
	
	for (int y = ystart; y != yend; y++) {
		
		for (int x = xstart; x != xend; x++) {
			
			switch (world[y][x]) {
				
				case 0:
					
					(*rle)[n] = 'b';
					
					break;
					
				case 1:
				
				case 2:
				
				case 3:
				
				case 4:
				
				case 5:
				
				case 6:
				
				case 7:
				
				case 8:
				
				case 9:
					
					(*rle)[n] = 'o';
					
					break;
					
			}
			
			n++;
			
		}
		
		(*rle)[n] = '$';
		
		n++;
		
	}
	
	n--;
	
	(*rle)[n] = '!';
	
	SetClipboardText(*rle);
	
}

void makeworld(const char rle[], int (* world)[200][200], int cursorpos[2], int fullsize) {
	
	int x, y;
	
	if (fullsize) {
		
		x = 0;
		
		y = 0;
		
	} else {
		
		x = cursorpos[1];
		
		y = cursorpos[0];
		
	}
	
	int n = 0;
	
	int nn;
	
	int run = 0;
	
	int value = 0;
	
	while (rle[n]) {
		
		switch (rle[n]) {
			
			case '0':
			
			case '1':
			
			case '2':
			
			case '3':
			
			case '4':
			
			case '5':
			
			case '6':
			
			case '7':
			
			case '8':
			
			case '9':
				
				run *= 10;
				
				run += (rle[n] - '0');
				
				goto digit;
				
			case 'b':
				
				value = 0;
				
				break;
				
			case 'o':
				
				value = 1;
				
				break;
				
			case '$':
				
				nn = (run == 0) ? 1 : run;
				
				x = cursorpos[1];
				
				for (int m = 0; m < nn; m++) {
					
					y++;
					
				}
				
				run = 0;
				
				goto digit;
				
			case '!':
				
				return;
				
			default:
				
				goto digit;
				
		}
		
		nn = (run == 0) ? 1 : run;
		
		for (int m = 0; m < nn; m++) {
			
			(*world)[y][x] = value;
			
			x++;
			
		}
		
		run = 0;
		
		digit:;
		
		n++;
		
	}
	
}

int main(void) {
	
	int world[200][200] = {0};
	
	int cursorpos[2] = {100, 100};
	
	int selection[2][2] = {{100, 100}, {100, 100}};
	
	int phase = 0;
	
	int eventcounter = 0;
	
	int fullsize = 1;
	
	int mod = 10; /* Prevents the event listener from responding too frequently and making the program run too fast. */
	
	int tpressed = 0;
	
	char rle[40201] = {0};
	
	struct Ruletype ruletype;
	
	srand(time(NULL));
	
	ruleswitch:;
	
	int colorized = 0;
	
	int bconds[117] = {0};
	
	int sconds[117] = {0};
	
	int fconds[117] = {0};
	
	int kconds[117] = {0};
	
	int lconds[117] = {0};
	
	int naive = 0;
	
	int gennum = 2;
	
	rparse(&bconds, &sconds, &fconds, &kconds, &lconds, &naive, &gennum, &ruletype);
	
	InitWindow(1000, 1000, "NaiViewer");
	
	while (!WindowShouldClose()) {
		
		int x = GetMouseX() / 5;
		
		int y = GetMouseY() / 5;
		
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			
			world[y][x] = 1;
			
			cursorpos[0] = y;
			
			cursorpos[1] = x;
			
			if (!phase) {
				
				selection[0][0] = y;
				
				selection[0][1] = x;
				
				selection[1][0] = y;
				
				selection[1][1] = x;
				
			} else {
				
				selection[1][0] = y;
				
				selection[1][1] = x;
				
			}
			
		}
		
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			
			world[y][x] = 0;
			
			cursorpos[0] = y;
			
			cursorpos[1] = x;
			
			if (!phase) {
				
				selection[0][0] = y;
				
				selection[0][1] = x;
				
				selection[1][0] = y;
				
				selection[1][1] = x;
				
			} else {
				
				selection[1][0] = y;
				
				selection[1][1] = x;
				
			}
			
		}
		
		if (IsKeyPressed(KEY_ENTER)) {
			
			world[cursorpos[0]][cursorpos[1]]++;
			
			world[cursorpos[0]][cursorpos[1]] %= 2;
			
		}
		
		if (IsKeyPressed(KEY_BACKSPACE)) {
			
			delete(&world, selection);
			
		}
		
		if (IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT)) {
			
			phase++;
			
			phase %= 2;
			
		}
		
		if (IsKeyPressed(KEY_EQUAL)) advance(&world, bconds, sconds, fconds, kconds, lconds, colorized, naive, gennum, ruletype);
		
		if (IsKeyPressed(KEY_UP) || (IsKeyDown(KEY_W) && !(eventcounter % mod))) {
			
			cursorpos[0]--;
			
			if (!phase) {
				
				if ((selection[0][0] == selection[1][0]) && (selection[0][1] == selection[1][1])) {
					
					selection[0][0] = cursorpos[0];
					
					selection[0][1] = cursorpos[1];
					
					selection[1][0] = cursorpos[0];
					
					selection[1][1] = cursorpos[1];
					
				}
				
			} else {
				
				selection[1][0] = cursorpos[0];
				
				selection[1][1] = cursorpos[1];
				
			}
			
		}
		
		if (IsKeyPressed(KEY_DOWN) || (IsKeyDown(KEY_S) && !(eventcounter % mod))) {
			
			cursorpos[0]++;
			
			if (!phase) {
				
				if ((selection[0][0] == selection[1][0]) && (selection[0][1] == selection[1][1])) {
					
					selection[0][0] = cursorpos[0];
					
					selection[0][1] = cursorpos[1];
					
					selection[1][0] = cursorpos[0];
					
					selection[1][1] = cursorpos[1];
					
				}
				
			} else {
				
				selection[1][0] = cursorpos[0];
				
				selection[1][1] = cursorpos[1];
				
			}
			
		}
		
		if (IsKeyPressed(KEY_LEFT) || (IsKeyDown(KEY_A) && !(eventcounter % mod))) {
			
			cursorpos[1]--;
			
			if (!phase) {
				
				if ((selection[0][0] == selection[1][0]) && (selection[0][1] == selection[1][1])) {
					
					selection[0][0] = cursorpos[0];
					
					selection[0][1] = cursorpos[1];
					
					selection[1][0] = cursorpos[0];
					
					selection[1][1] = cursorpos[1];
					
				}
				
			} else {
				
				selection[1][0] = cursorpos[0];
				
				selection[1][1] = cursorpos[1];
				
			}
			
		}
		
		if (IsKeyPressed(KEY_RIGHT) || (IsKeyDown(KEY_D) && !(eventcounter % mod))) {
			
			cursorpos[1]++;
			
			if (!phase) {
				
				if ((selection[0][0] == selection[1][0]) && (selection[0][1] == selection[1][1])) {
					
					selection[0][0] = cursorpos[0];
					
					selection[0][1] = cursorpos[1];
					
					selection[1][0] = cursorpos[0];
					
					selection[1][1] = cursorpos[1];
					
				}
				
			} else {
				
				selection[1][0] = cursorpos[0];
				
				selection[1][1] = cursorpos[1];
				
			}
			
		}
		
		if (IsKeyPressed(KEY_C)) makerle(world, selection, &rle, &fullsize);
		
		if (IsKeyPressed(KEY_I)) {
			
			int xstart, xend, xinc, ystart, yend, yinc;
			
			if ((selection[0][0] == selection[1][0]) && (selection[0][1] == selection[1][1])) {
				
				xstart = 0;
				
				xend = 200;
				
				ystart = 0;
				
				yend = 200;
				
				xinc = 1;
				
				yinc = 1;
				
			} else {
				
				xstart = selection[0][1] + 1;
				
				ystart = selection[0][0] + 1;
				
				xend = selection[1][1];
				
				yend = selection[1][0];
				
				xinc = (xstart <= xend) ? 1 : -1;
				
				yinc = (ystart <= yend) ? 1 : -1;
				
			}
			
			for (int y = ystart; y != yend; y += yinc) {
				
				for (int x = xstart; x != xend; x += xinc) {
					
					if (world[y][x]) {
						
						world[y][x] = 0;
						
					} else {
						
						world[y][x] = 1;
						
					}
					
				}
				
			}
			
		}
		
		if (IsKeyPressed(KEY_K) && (gennum == 2)) colorized++;
		
		if (IsKeyPressed(KEY_Q)) break;
		
		if (IsKeyPressed(KEY_R)) {
			
			int xstart, xend, xinc, ystart, yend, yinc;
			
			if ((selection[0][0] == selection[1][0]) && (selection[0][1] == selection[1][1])) {
				
				xstart = 0;
				
				xend = 200;
				
				ystart = 0;
				
				yend = 200;
				
				xinc = 1;
				
				yinc = 1;
				
			} else {
				
				xstart = selection[0][1] + 1;
				
				ystart = selection[0][0] + 1;
				
				xend = selection[1][1];
				
				yend = selection[1][0];
				
				xinc = (xstart <= xend) ? 1 : -1;
				
				yinc = (ystart <= yend) ? 1 : -1;
				
			}
			
			for (int y = ystart; y != yend; y += yinc) {
				
				for (int x = xstart; x != xend; x += xinc) {
					
					world[y][x] = rand() % 2;
					
				}
				
			}
			
		}
		
		if (IsKeyPressed(KEY_T)) {
			
			tpressed = 1;
			
			break;
			
		}
		
		if (IsKeyPressed(KEY_V)) {
			
			makeworld(GetClipboardText(), &world, cursorpos, fullsize);
			
		}
		
		if (IsKeyPressed(KEY_X)) {
			
			makerle(world, selection, &rle, &fullsize);
			
			delete(&world, selection);
			
		}
		
		if (IsKeyPressed(KEY_ZERO)) {
			
			selection[0][0] = cursorpos[0];
			
			selection[0][1] = cursorpos[1];
			
			selection[1][0] = cursorpos[0];
			
			selection[1][1] = cursorpos[1];
			
			phase = 0;
			
		}
		
		cursorpos[0] %= 200;
		
		cursorpos[1] %= 200;
		
		colorized %= 2;
		
		if (IsKeyDown(KEY_SPACE)) advance(&world, bconds, sconds, fconds, kconds, lconds, colorized, naive, gennum, ruletype);
		
		eventcounter++;
		
		BeginDrawing();
		
		ClearBackground(BLACK);
		
		show(world, cursorpos, selection, colorized, gennum, ruletype);
		
		EndDrawing();
		
	}
	
	CloseWindow();
	
	if (tpressed) {
		
		tpressed = 0;
		
		goto ruleswitch;
		
	}
	
	return 0;
	
}

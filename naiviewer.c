#include <raylib.h>

#include <time.h>

#include <stdlib.h>

#include <stdio.h>

#include <ctype.h>

#include "dict.h"

/* Compilation command for Raspberry Pi: gcc naiviewer.c -o naiviewer -lraylib -lGLESv2 -lEGL -lm -lpthread -ldl -lX11 */

struct Conds {
	
	int bconds[117];
	
	int sconds[117];
	
	int fconds[117];
	
	int kconds[117];
	
	int lconds[117];
	
	int gennum;
	
};

struct Ruletype {
	
	int naive;
	
	int bsfkl;
	
};

void rparse(struct Conds * conds, struct Ruletype * ruletype) {
	
	printf("Rule: ");
	
	int lastdigit = -1;
	
	int currentlynegating = 0;
	
	int nn;
	
	char c = getchar();
	
	char letters[] = "cekainyqjrtwz";
	
	int lengths[9] = {0, 2, 6, 10, 13, 10, 6, 2, 0};
	
	while ((c != '/')) {
		
		if (c == 'N') {
			
			((*ruletype).naive) = 1;
			
			goto bend;
			
		}
		
		if (c == 'R') goto randgen;
		
		if (c == 'B') goto bend;
		
		if (isdigit(c)) {
			
			currentlynegating = 0;
			
			nn = c - '0';
			
			if (lastdigit >= 0) {
				
				for (int n = 0; n < 13; n++) {
					
					((*conds).bconds)[lastdigit * 13 + n] = 1;
					
				}
				
			}
			
			for (int n = 0; n < 13; n++) {
				
				((*conds).bconds)[nn * 13 + n] = 2;
				
			}
			
			lastdigit = nn;
			
			((*conds).bconds)[nn] = 1;
			
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
						
						((*conds).bconds)[nn * 13 + n] = 0;
						
					}
					
				} else {
					
					if (((*conds).bconds)[nn * 13 + n] == 2) {
						
						((*conds).bconds)[nn * 13 + n] = 0;
						
					}
					
					if ((((*conds).bconds)[nn * 13 + n] == 0) && (n == i)) {
						
						((*conds).bconds)[nn * 13 + n] = 1;
						
					}
					
				}
				
			}
			
		}
		
		if (c == '-') {
			
			lastdigit = -1;
			
			currentlynegating = 1;
			
			for (int n = 0; n < 13; n++) {
				
				if (((*conds).bconds)[nn * 13 + n] == 2) {
					
					((*conds).bconds)[nn * 13 + n] = 1;
					
				}
				
			}
			
		}
		
		if (c == '\n') {
			
			for (int n = 39; n < 52; n++) {
				
				((*conds).bconds)[n] = 1;
				
			}
			
			for (int n = 26; n < 52; n++) {
				
				((*conds).sconds)[n] = 1;
				
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
					
					((*conds).sconds)[lastdigit * 13 + n] = 1;
					
				}}
			
			for (int n = 0; n < 13; n++) {
				
				((*conds).sconds)[nn * 13 + n] = 2;
				
			}
			
			lastdigit = nn;
			
			((*conds).sconds)[nn] = 1;
			
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
						
						((*conds).sconds)[nn * 13 + n] = 0;
						
					}
					
				} else {
					
					if (((*conds).sconds)[nn * 13 + n] == 2) {
						
						((*conds).sconds)[nn * 13 + n] = 0;
						
					}
					
					if ((((*conds).sconds)[nn * 13 + n] == 0) && (n == i)) {
						
						((*conds).sconds)[nn * 13 + n] = 1;
						
					}
					
				}
				
			}
			
		}
		
		if (c == '-') {
			
			lastdigit = -1;
			
			currentlynegating = 1;
			
			for (int n = 0; n < 13; n++) {
				
				if (((*conds).sconds)[nn * 13 + n] == 2) {
					
					((*conds).sconds)[nn * 13 + n] = 1;
					
				}
				
			}
			
		}
		
		send:;
		
		c = getchar();
		
		continue;
		
		randgen:;
		
		srand(time(NULL));
		
		((*ruletype).naive) = rand() % 2;
		
		if (((*ruletype).naive)) {
			
			printf("N");
			
		}
		
		printf("B");
		
		for (int n = 3; n < 9; n++) {
			
			for (int c = 0; c < lengths[n]; c++) {
				
				((*conds).bconds)[n * 13 + c] = rand() % 2;
				
			}
			
		}
		
		((*conds).bconds)[42] = 1;
		
		((*conds).bconds)[43] = 1;
		
		for (int n = 0; n < 9; n++) {
			
			for (int c = 0; c < lengths[n]; c++) {
				
				if (((*conds).bconds)[n * 13 + c]) {
					
					printf("%d", n);
					
					break;
					
				}
				
			}
			
			for (int c = 0; c < lengths[n]; c++) {
				
				if (((*conds).bconds)[n * 13 + c]) {
					
					printf("%c", letters[c]);
					
				}
				
			}
			
		}
		
		printf("/S");
		
		for (int n = 0; n < 9; n++) {
			
			for (int c = 0; c < lengths[n]; c++) {
				
				((*conds).sconds)[n * 13 + c] = rand() % 2;
				
			}
			
		}
		
		for (int n = 0; n < 9; n++) {
			
			for (int c = 0; c < lengths[n]; c++) {
				
				if (((*conds).sconds)[n * 13 + c]) {
					
					printf("%d", n);
					
					break;
					
				}
				
			}
			
			for (int c = 0; c < lengths[n]; c++) {
				
				if (((*conds).sconds)[n * 13 + c]) {
					
					printf("%c", letters[c]);
					
				}
				
			}
			
		}
		
		printf("\n");
		
		(*ruletype).bsfkl = 0;
		
		return;
		
	}
	
	((*conds).gennum) = 0;
	
	if (c == '\n') {
		
		(*ruletype).bsfkl = 0;
		
		((*conds).gennum) = 2;
		
		return;
		
	}
	
	c = getchar();
	
	if (c == 'G') goto generations;
	
	if (c == 'F') goto bsfkl;
	
	generations:;
	
	c = getchar();
	
	while (c != '\n') {
		
		if (c == '/') goto gend;
		
		((*conds).gennum) *= 10;
		
		((*conds).gennum) += (c - '0');
		
		gend:;
		
		c = getchar();
		
	}
	
	if (!(((*conds).gennum)) || (((*conds).gennum) == 1)) {
		
		 ((*conds).gennum) = 2;
		 
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
					
					((*conds).fconds)[lastdigit * 13 + n] = 1;
					
				}}
			
			for (int n = 0; n < 13; n++) {
				
				((*conds).fconds)[nn * 13 + n] = 2;
				
			}
			
			lastdigit = nn;
			
			((*conds).fconds)[nn] = 1;
			
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
						
						((*conds).fconds)[nn * 13 + n] = 0;
						
					}
					
				} else {
					
					if (((*conds).fconds)[nn * 13 + n] == 2) {
						
						((*conds).fconds)[nn * 13 + n] = 0;
						
					}
					
					if ((((*conds).fconds)[nn * 13 + n] == 0) && (n == i)) {
						
						((*conds).fconds)[nn * 13 + n] = 1;
						
					}
					
				}
				
			}
			
		}
		
		if (c == '-') {
			
			lastdigit = -1;
			
			currentlynegating = 1;
			
			for (int n = 0; n < 13; n++) {
				
				if (((*conds).fconds)[nn * 13 + n] == 2) {
					
					((*conds).fconds)[nn * 13 + n] = 1;
					
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
					
					((*conds).kconds)[lastdigit * 13 + n] = 1;
					
				}}
			
			for (int n = 0; n < 13; n++) {
				
				((*conds).kconds)[nn * 13 + n] = 2;
				
			}
			
			lastdigit = nn;
			
			((*conds).kconds)[nn] = 1;
			
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
						
						((*conds).kconds)[nn * 13 + n] = 0;
						
					}
					
				} else {
					
					if (((*conds).kconds)[nn * 13 + n] == 2) {
						
						((*conds).kconds)[nn * 13 + n] = 0;
						
					}
					
					if ((((*conds).kconds)[nn * 13 + n] == 0) && (n == i)) {
						
						((*conds).kconds)[nn * 13 + n] = 1;
						
					}
					
				}
				
			}
			
		}
		
		if (c == '-') {
			
			lastdigit = -1;
			
			currentlynegating = 1;
			
			for (int n = 0; n < 13; n++) {
				
				if (((*conds).kconds)[nn * 13 + n] == 2) {
					
					((*conds).kconds)[nn * 13 + n] = 1;
					
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
					
					((*conds).lconds)[lastdigit * 13 + n] = 1;
					
				}}
			
			for (int n = 0; n < 13; n++) {
				
				((*conds).lconds)[nn * 13 + n] = 2;
				
			}
			
			lastdigit = nn;
			
			((*conds).lconds)[nn] = 1;
			
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
						
						((*conds).lconds)[nn * 13 + n] = 0;
						
					}
					
				} else {
					
					if (((*conds).lconds)[nn * 13 + n] == 2) {
						
						((*conds).lconds)[nn * 13 + n] = 0;
						
					}
					
					if ((((*conds).lconds)[nn * 13 + n] == 0) && (n == i)) {
						
						((*conds).lconds)[nn * 13 + n] = 1;
						
					}
					
				}
				
			}
			
		}
		
		if (c == '-') {
			
			lastdigit = -1;
			
			currentlynegating = 1;
			
			for (int n = 0; n < 13; n++) {
				
				if (((*conds).lconds)[nn * 13 + n] == 2) {
					
					((*conds).lconds)[nn * 13 + n] = 1;
					
				}
				
			}
			
		}
		
		lend:;
		
		c = getchar();
		
	}
	
	((*conds).gennum) = 3;
	
}

void advance(int (* world)[200][200], struct Conds conds, struct Ruletype ruletype, int colorized) {
	
	int xx, yy;
	
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
				
				if ((ruletype.naive) && ((augx >= 200) || (augy >= 200) || (augx < 0) || (augy < 0))) {
					
					continue;
					
				}
				
				if (ruletype.naive) {
					
					xx = x + neigh[n][1];
					
					yy = y + neigh[n][0];
					
				} else {
					
					xx = x + neigh[n][1] + 200;
					
					yy = y + neigh[n][0] + 200;
					
					xx %= 200;
					
					yy %= 200;
					
				}
				
				if ((*world)[yy][xx]) {
					
					if (!(ruletype.bsfkl)) {
						
						if ((conds.gennum) > 2) {
							
							if ((*world)[yy][xx] == 1) {
								
								binary++;
								
								count++;
								
							}
							
						} else {
							
							binary++;
							
							count++;
							
						}
						
					} else {
						
						if ((*world)[yy][xx] == 1) {
							
							binary++;
							
						}
						
						if ((*world)[yy][xx] == 2) {
							
							second++;
							
						}
						
					}
					
				}
				
			}
			
			if (!(ruletype.bsfkl)) {
				
				if (!(*world)[y][x] && (conds.bconds)[dict[binary]]) { /* Birth */
					
					if ((ruletype.naive)) {
						
						if (colorized) {
							
							(*world)[y][x] = count + 1;
							
						} else {
							
							(*world)[y][x] = 1;
							
						}
						
						continue; /* Prevents cell states from being overwritten more than once in (ruletype.naive) rules */
							
					} else {
						
						if (colorized) {
							
							next[y][x] = count + 1;
							
						} else {
							
							next[y][x] = 1;
							
						}
						
					}
					
				} else if ((*world)[y][x] && !((conds.sconds)[dict[binary]])) { /* Death */
					
					if ((conds.gennum) == 2) { /* Two-state rules */
						
						if ((ruletype.naive)) {
							
							(*world)[y][x] = 0;
							
							continue; /* Prevents cell states from being overwritten more than once in (ruletype.naive) rules */
							
						} else {
							
							next[y][x] = 0;
							
						}
						
					} else { /* Generations rules */
						
						if ((ruletype.naive)) {
							
							naive_dying:;
							
							(*world)[y][x]++;
							
							(*world)[y][x] %= (conds.gennum);
							
							/* The two lines above increment all dying cells and kill cells in their last stage of death */
							
							continue; /* Prevents cell states from being overwritten more than once in (ruletype.naive) rules */
							
						} else {
							
							dying:;
							
							next[y][x] = (*world)[y][x] + 1;
							
							next[y][x] %= (conds.gennum);
							
						}
						
					}
					
				} else if ((*world)[y][x] && (conds.sconds)[dict[binary]]) { /* Survival */
					
					if ((conds.gennum) == 2) {
						
						if ((ruletype.naive)) {
							
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
						
						if ((ruletype.naive)) {
							
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
				
				if (((*world)[y][x] == 0) && ((conds.bconds)[dict[binary]] && (conds.fconds)[dict[second]])) {
					
					if ((ruletype.naive)) {
						
						(*world)[y][x] = 1;
						
						continue;
						
					} else {
						
						next[y][x] = 1;
						
					}
					
				} else if (((*world)[y][x] == 1) && (conds.kconds)[dict[second]]) {
					
					if ((ruletype.naive)) {
						
						(*world)[y][x] = 0;
						
						continue;
						
					} else {
						
						next[y][x] = 0;
						
					}
					
				} else if (((*world)[y][x] == 1) && (conds.sconds)[dict[binary]]) {
					
					if ((ruletype.naive)) {
						
						(*world)[y][x] = 1;
						
						continue;
						
					} else {
						
						next[y][x] = 1;
						
					}
					
				} else if (((*world)[y][x] == 1) && (!(conds.kconds)[dict[second]] && !(conds.sconds)[dict[binary]])) {
					
					if ((ruletype.naive)) {
						
						(*world)[y][x] = 2;
						
						continue;
						
					} else {
						
						next[y][x] = 2;
						
					}
					
				} else if (((*world)[y][x] == 2) && (conds.lconds)[dict[binary]]) {
					
					if ((ruletype.naive)) {
						
						(*world)[y][x] = 0;
						
						continue;
						
					} else {
						
						next[y][x] = 0;
						
					}
				
				} else if (((*world)[y][x] == 2) && !(conds.lconds)[dict[binary]]) {
					
					if ((ruletype.naive)) {
						
						(*world)[y][x] = 2;
						
						continue;
						
					} else {
						
						next[y][x] = 2;
						
					}
					
				}
				
			}
			
		}
		
	}
	
	if (!(ruletype.naive)) {
		
		for (int y = 0; y < 200; y++) {
			
			for (int x = 0; x < 200; x++) {
				
				(*world)[y][x] = next[y][x];
				
			}
			
		}
		
	}
	
}

void show(int world[200][200], int cursorpos[2], int selection[2][2], int colorized, struct Conds conds, struct Ruletype ruletype) {
	
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
						
						g = (conds.gennum) - 2;
						
						k = world[y][x] - 1;
						
						if ((conds.gennum) == 2) {
							
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
	
	int mod = 40; /* Prevents the event listener from responding too frequently and making the program run too fast. */
	
	int drawmod = 2;
	
	char rle[40201] = {0};
	
	struct Conds conds;
	
	struct Ruletype ruletype;
	
	srand(time(NULL));
	
	int colorized = 0;
	
	for (int n = 0; n < 117; n++) {
		
		conds.bconds[n] = 0;
		
		conds.sconds[n] = 0;
		
		conds.fconds[n] = 0;
		
		conds.kconds[n] = 0;
		
		conds.lconds[n] = 0;
		
	}
	
	ruletype.naive = 0;
	
	ruletype.bsfkl = 0;
	
	conds.gennum = 2;
	
	rparse(&conds, &ruletype);
	
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
		
		if (IsKeyPressed(KEY_EQUAL)) advance(&world, conds, ruletype, colorized);
		
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
		
		if (IsKeyPressed(KEY_COMMA)) {
			
			world[cursorpos[0]][cursorpos[1]] += (conds.gennum - 1);
			
			world[cursorpos[0]][cursorpos[1]] %= conds.gennum;
			
		}
		
		if (IsKeyPressed(KEY_PERIOD)) {
			
			world[cursorpos[0]][cursorpos[1]] += 1;
			
			world[cursorpos[0]][cursorpos[1]] %= conds.gennum;
			
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
		
		if (IsKeyPressed(KEY_K) && (conds.gennum == 2)) colorized++;
		
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
					
					world[y][x] = rand() % conds.gennum;
					
				}
				
			}
			
		}
		
		if (IsKeyPressed(KEY_T)) {
			
			colorized = 0;
			
			for (int n = 0; n < 117; n++) {
				
				conds.bconds[n] = 0;
				
				conds.sconds[n] = 0;
				
				conds.fconds[n] = 0;
				
				conds.kconds[n] = 0;
				
				conds.lconds[n] = 0;
				
			}
			
			ruletype.naive = 0;
			
			ruletype.bsfkl = 0;
			
			conds.gennum = 2;
			
			rparse(&conds, &ruletype);
			
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
		
		cursorpos[0] += 200;
		
		cursorpos[1] += 200;
		
		cursorpos[0] %= 200;
		
		cursorpos[1] %= 200;
		
		colorized %= 2;
		
		if (IsKeyDown(KEY_SPACE) && !(eventcounter % drawmod)) advance(&world, conds, ruletype, colorized);
		
		eventcounter++;
		
		BeginDrawing();
		
		ClearBackground(BLACK);
		
		show(world, cursorpos, selection, colorized, conds, ruletype);
		
		EndDrawing();
		
	}
	
	CloseWindow();
	
	return 0;
	
}

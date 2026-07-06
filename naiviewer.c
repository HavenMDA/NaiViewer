#include <raylib.h>

#include <time.h>

#include <stdlib.h>

#include <stdio.h>

#include <ctype.h>

#include "dict.h"

/* Compilation command for Raspberry Pi: gcc naiviewer.c -o naiviewer -lraylib -lGLESv2 -lEGL -lm -lpthread -ldl -lX11 */

void rparse(int (* bconds)[117], int (* sconds)[117]) {
	
	printf("Rule: ");
	
	int lastdigit = -1;
	
	int currentlynegating = 0;
	
	int nn;
	
	char c = getchar();
	
	char letters[] = "cekainyqjrtwz";
	
	while ((c != '/')) {
		
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
		
		bend:
		
		c = getchar();
		
	}
	
	lastdigit = -1;
	
	currentlynegating = 0;
	
	while (c != '\n') {
		
		if (c == '/') goto send;
		
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
		
		send:
		
		c = getchar();
		
	}
	
}

void advance(int (* world)[200][200], int bconds[117], int sconds[117], int colorized) {
	
	int neigh[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
	
	for (int y = 0; y < 200; y++) {
		
		for (int x = 0; x < 200; x++) {
			
			int count = 0;
			
			int binary = 0;
			
			for (int n = 0; n < 8; n++) {
				
				int augx = x + neigh[n][1];
				
				int augy = y + neigh[n][0];
				
				binary *= 2;
				
				if ((augx >= 200) || (augy >= 200) || (augx < 0) || (augy < 0)) {
					
					continue;
					
				}
				
				if ((*world)[y + neigh[n][0]][x + neigh[n][1]]) {
					
					binary++;
					
					count++;
					
				}
				
			}
			
			if ((*world)[y][x] && !sconds[dict[binary]]) {
				
				(*world)[y][x] = 0;
				
				continue;
				
			}
			
			if (!(*world)[y][x] && bconds[dict[binary]]) {
				
				if (colorized) {
					
					(*world)[y][x] = count + 1;
					
				} else {
					
					(*world)[y][x] = 1;
					
				}
				
				continue;
				
			}
			
			if ((*world)[y][x] && sconds[dict[binary]]) {
				
				if (colorized) {
					
					(*world)[y][x] = count + 1;
					
				} else {
					
					(*world)[y][x] = 1;
					
				}
				
				continue;
				
			}
			
		}
		
	}
	
}

void show(int world[200][200], int cursorpos[2], int selection[2][2], int colorized) {
	
	int xstart, xend, xinc, ystart, yend, yinc;
	
	Color cursor = {255, 0, 0, 128};
	
	Color redcursor = {0, 0, 255, 255};
	
	Color colors[10] = {BLACK, GRAY, WHITE, RED, GREEN, BLUE, ORANGE, PURPLE, YELLOW, PINK};
	
	for (int y = 0; y < 200; y++) {
		
		for (int x = 0; x < 200; x++) {
			
			if (world[y][x]) {
				
				if (colorized) {
					
					DrawRectangle(x * 5, y * 5, 5, 5, colors[world[y][x]]);
					
				} else {
					
					DrawRectangle(x * 5, y * 5, 5, 5, WHITE);
					
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
	
	// 11, 13 -> 15, 11
	
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
		
		digit:
		
		n++;
		
	}
	
}

int main(void) {
	
	int world[200][200] = {0};
	
	int cursorpos[2] = {100, 100};
	
	int selection[2][2] = {{100, 100}, {100, 100}};
	
	int phase = 0;
	
	int bconds[117] = {0};
	
	int sconds[117] = {0};
	
	int colorized = 0;
	
	int eventcounter = 0;
	
	int fullsize = 1;
	
	int mod = 10; /* Prevents the event listener from responding too frequently and making the program run too fast. */
	
	int tpressed = 0;
	
	char rle[40201] = {0};
	
	srand(time(NULL));
	
	ruleswitch:
	
	rparse(&bconds, &sconds);
	
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
		
		if (IsKeyPressed(KEY_EQUAL)) advance(&world, bconds, sconds, colorized);
		
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
		
		if (IsKeyPressed(KEY_K)) colorized++;
		
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
			
			selection[0][0] = 100;
			
			selection[0][1] = 100;
			
			selection[1][0] = 100;
			
			selection[1][1] = 100;
			
			phase = 0;
			
		}
		
		cursorpos[0] %= 200;
		
		cursorpos[1] %= 200;
		
		colorized %= 2;
		
		if (IsKeyDown(KEY_SPACE) && !(eventcounter % mod)) advance(&world, bconds, sconds, colorized);
		
		eventcounter++;
		
		BeginDrawing();
		
		ClearBackground(BLACK);
		
		show(world, cursorpos, selection, colorized);
		
		EndDrawing();
		
	}
	
	CloseWindow();
	
	if (tpressed) {
		
		tpressed = 0;
		
		goto ruleswitch;
		
	}
	
	return 0;
	
}

#include <stdio.h>
#include <stdlib.h>  
#include <math.h>

#define ROWS 25
#define COLS 60

char canvas[ROWS][COLS];

// 1. Fills the canvas grid with background dots
void initializeCanvas() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            canvas[i][j] = '.'; 
        }
    }
}

// 2. Clears the screen buffer completely and prints the frame
void displayCanvas() {
    #ifdef _WIN32
        system("cls");  
    #else
        printf("\033[H\033[J"); 
    #endif
    
    for (int j = 0; j < COLS + 2; j++) printf("-");
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        printf("|"); 
        for (int j = 0; j < COLS; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("|\n"); 
    }

    for (int j = 0; j < COLS + 2; j++) printf("-");
    printf("\n");
}

// 3. Draws a  rectangle
void drawRectangle(int r, int c, int h, int w, char symbol) {
    for (int i = r; i < r + h; i++) {
        for (int j = c; j < c + w; j++) {
            if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
                if (i == r || i == r + h - 1 || j == c || j == c + w - 1) {
                    canvas[i][j] = symbol;
                }
            }
        }
    }
}

// 4. Draws a DIAGONAL line using Bresenham's Algorithm
void drawLine(int r1, int c1, int r2, int c2, char symbol) {
    int dr = abs(r2 - r1), sr = r1 < r2 ? 1 : -1;
    int dc = abs(c2 - c1), sc = c1 < c2 ? 1 : -1;
    int err = (dc > dr ? dc : -dr) / 2, e2;

    while (1) {
        if (r1 >= 0 && r1 < ROWS && c1 >= 0 && c1 < COLS) {
            canvas[r1][c1] = symbol;
        }
        if (r1 == r2 && c1 == c2) break;
        e2 = err;
        if (e2 > -dc) { err -= dr; c1 += sc; }
        if (e2 <  dr) { err += dc; r1 += sr; }
    }
}

// 5. Draws a circle using distance formula
void drawCircle(int centerRow, int centerCol, int radius, char symbol) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            double dist = sqrt(pow(i - centerRow, 2) + pow(j - centerCol, 2));
            if (dist < radius) {
                canvas[i][j] = symbol;
            }
        }
    }
}

// 6. Draws a right-angled triangle
void drawTriangle(int r, int c, int size, char symbol) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
            if ((r + i) >= 0 && (r + i) < ROWS && (c + j) >= 0 && (c + j) < COLS) {
                canvas[r + i][c + j] = symbol;
            }
        }
    }
}

int main() {
    int choice;
    initializeCanvas(); 

    while (1) {
        displayCanvas(); 
        
        printf("\n=== 2D GRAPHICS EDITOR (SEPARATE OUTPUTS VERSION) ===\n");
        printf("1. Draw Rectangle (*)\n");
        printf("2. Draw Diagonal Line (#)\n");
        printf("3. Draw Circle (O)\n");
        printf("4. Draw Triangle (^)\n");
        printf("5. Erase/Delete an Area\n");
        printf("6. Modify/Overwrite an Area\n"); 
        printf("7. Reset Canvas\n");
        printf("8. Exit Program\n");
        printf("Enter choice (1-8): ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            continue; 
        }

        if (choice == 8) {
            printf("Exiting\n");
            break; 
        }

        int r, c, h, w, r2, c2, radius, size;
        char newSymbol;

        switch (choice) {
            case 1:
                printf("Enter row, col, height, width: ");
                scanf("%d %d %d %d", &r, &c, &h, &w);
                initializeCanvas(); // <-- Wipes old shapes right before drawing the new one
                drawRectangle(r, c, h, w, '*');
                break;
            case 2:
                printf("Enter r1, c1, r2, c2: ");
                scanf("%d %d %d %d", &r, &c, &r2, &c2);
                initializeCanvas(); // <-- Wipes old shapes right before drawing the new one
                drawLine(r, c, r2, c2, '#');
                break;
            case 3:
                printf("Enter center-row, center-col, radius: ");
                scanf("%d %d %d", &r, &c, &radius);
                initializeCanvas(); // <-- Wipes old shapes right before drawing the new one
                drawCircle(r, c, radius, 'O');
                break;
            case 4:
                printf("Enter top-row, top-col, size: ");
                scanf("%d %d %d", &r, &c, &size);
                initializeCanvas(); // <-- Wipes old shapes right before drawing the new one
                drawTriangle(r, c, size, '^');
                break;
            case 5:
                printf("Enter row, col, height, width to erase: ");
                scanf("%d %d %d %d", &r, &c, &h, &w);
                for(int i=r; i<r+h; i++) {
                    for(int j=c; j<c+w; j++) {
                        if(i>=0 && i<ROWS && j>=0 && j<COLS) canvas[i][j] = '.';
                    }
                }
                break;
            case 6:
                printf("Enter row, col, height, width to modify: ");
                scanf("%d %d %d %d", &r, &c, &h, &w);
                printf("Enter new character symbol: ");
                scanf(" %c", &newSymbol); 
                drawRectangle(r, c, h, w, newSymbol); 
                break;
            case 7:
                initializeCanvas(); 
                break;
            default:
                break;
        }
    }
    return 0;
}

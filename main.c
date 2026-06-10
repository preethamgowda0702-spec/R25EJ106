#include <stdio.h>
#include <math.h>

#define ROWS 30
#define COLS 80

char rectCanvas[ROWS][COLS];
char lineCanvas[ROWS][COLS];
char circleCanvas[ROWS][COLS];
char triangleCanvas[ROWS][COLS];

void clearSpecificCanvas(char canvas[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            canvas[i][j] = '.'; 
        }
    }
}

void initializeAllCanvases() {
    clearSpecificCanvas(rectCanvas);
    clearSpecificCanvas(lineCanvas);
    clearSpecificCanvas(circleCanvas);
    clearSpecificCanvas(triangleCanvas);
}

// Internal print function without the clear-screen sequence
void renderCanvasGrid(char canvas[ROWS][COLS], const char* canvasTitle) {
    printf("=== %s WINDOW ===\n", canvasTitle);

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
    printf("\n\n");
}

void displaySpecificCanvas(char canvas[ROWS][COLS], const char* canvasTitle) {
    printf("\033[H\033[J"); // Clears screen
    renderCanvasGrid(canvas, canvasTitle);
}

void displayAllCanvasesTogether() {
    printf("\033[H\033[J");
    printf("==================== VIEWING ALL CANVAS OBJECTS ====================\n\n");
    renderCanvasGrid(rectCanvas, "RECTANGLE CANVAS (1)");
    renderCanvasGrid(lineCanvas, "LINE CANVAS (2)");
    renderCanvasGrid(circleCanvas, "CIRCLE CANVAS (3)");
    renderCanvasGrid(triangleCanvas, "TRIANGLE CANVAS (4)");
}

void drawRectangle(int r, int c, int h, int w, char symbol) {
    for (int i = r; i < r + h; i++) {
        for (int j = c; j < c + w; j++) {
            if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
                rectCanvas[i][j] = symbol; 
            }
        }
    }
}

void drawLine(int r, int c, int len, char symbol) {
    for (int i = 0; i < len; i++) {
        if (r >= 0 && r < ROWS && (c + i) >= 0 && (c + i) < COLS) {
            lineCanvas[r][c + i] = symbol; 
        }
    }
}

void drawCircle(int centerX, int centerY, int radius, char symbol) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            double dist = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));
            if (dist < radius) {
                if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
                    circleCanvas[i][j] = symbol; 
                }
            }
        }
    }
}

void drawTriangle(int r, int c, int size, char symbol) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
            if ((r + i) >= 0 && (r + i) < ROWS && (c + j) >= 0 && (c + j) < COLS) {
                triangleCanvas[r + i][c + j] = symbol; 
            }
        }
    }
}

int main() {
    int choice;
    int currentView = 1; 
    initializeAllCanvases(); 

    while (1) {
        if (currentView == 1) displaySpecificCanvas(rectCanvas, "RECTANGLE CANVAS");
        else if (currentView == 2) displaySpecificCanvas(lineCanvas, "LINE CANVAS");
        else if (currentView == 3) displaySpecificCanvas(circleCanvas, "CIRCLE CANVAS");
        else if (currentView == 4) displaySpecificCanvas(triangleCanvas, "TRIANGLE CANVAS");
        else if (currentView == 8) displayAllCanvasesTogether();
        
        printf("\n=== MULTI-CANVAS GRAPHICS CONTROL PANEL ===\n");
        if (currentView == 8) {
            printf("Current Screen Active: ALL WINDOWS SPLIT VIEW\n");
        } else {
            printf("Current Screen Active: Canvas %d\n", currentView);
        }
        printf("1. Draw Rectangle (*) \n");
        printf("2. Draw Line (#)  \n");
        printf("3. Draw Circle (O) \n");
        printf("4. Draw Triangle (^) \n");
        printf("5. Switch Active Display View Window\n");
        printf("6. Reset All Canvases\n");
        printf("7. Exit Program\n");
        printf("8. View All Canvas Objects Simultaneously\n"); 
        printf("Enter choice (1-8): ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            continue; 
        }

        if (choice == 7) {
            printf("Exiting\n");
            break; 
        }

        int r, c, h, w, len, radius, size;

        switch (choice) {
            case 1:
                printf("Enter row, col, height, width: ");
                scanf("%d %d %d %d", &r, &c, &h, &w);
                drawRectangle(r, c, h, w, '*');
                currentView = 1; 
                break;
            case 2:
                printf("Enter row, col, length: ");
                scanf("%d %d %d", &r, &c, &len);
                drawLine(r, c, len, '#');
                currentView = 2; 
                break;
            case 3:
                printf("Enter center-row, center-col, radius: ");
                scanf("%d %d %d", &r, &c, &radius);
                drawCircle(r, c, radius, 'O');
                currentView = 3; 
                break;
            case 4:
                printf("Enter top-row, top-col, size: ");
                scanf("%d %d %d", &r, &c, &size);
                drawTriangle(r, c, size, '^');
                currentView = 4; 
                break;
            case 5:
                printf("Choose canvas window to display (1=Rect, 2=Line, 3=Circle, 4=Triangle): ");
                int targetView;
                scanf("%d", &targetView);
                if (targetView >= 1 && targetView <= 4) {
                    currentView = targetView;
                }
                break;
            case 6:
                initializeAllCanvases(); 
                if (currentView == 8) currentView = 1;
                break;
            case 8:
                currentView = 8; 
                break;
        }
    }
    return 0;
}
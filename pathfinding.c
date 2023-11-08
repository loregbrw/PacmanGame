#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 5
#define COLS 5

typedef struct {
    int x, y;
} Point;

typedef struct Node {
    int x,y;
    bool visited;
    // int rating;
    int value;
    struct Node* parent;
    
} Node_T;

typedef struct {
    Point position;
} Ghost;

typedef struct {
    Point position;
} Pacman;

// // Função para calcular a distância de Manhattan entre dois pontos.
// int rate(Point a, Point b) {
//     return abs(a.x - b.x) + abs(a.y - b.y);
// }

int ox = -1, oy = -1, lastx = -1, lasty = -1;
bool flood(Node_T map[ROWS][COLS], int x, int y, int xd, int yd) {
    //Primeira execucao
    if (ox == -1){
        ox = x;
    }
    if (oy == -1){
        oy = y;
    }

    if (map[y][x].visited) {
        return false;
    }

    if (y >= ROWS || x >= COLS || x < 0 || y < 0){
        return false;
    }

    if (map[y][x].value == 1) {
        return false;
    }

    map[y][x].parent = &map[oy][ox];

    //Encontrado
    if (x == xd && y == yd ) {
        //Cordenadas destion/ultimo
        lastx = x;
        lasty = y;

        return true;
    }
    
    map[y][x].visited = true;
    
    ox = x;
    oy = y;

    if (flood(map, x+1, y, xd, yd)) {        
        return true;
    }
    if (flood(map, x, y+1, xd, yd)) {        
        return true;
    }
    if (flood(map, x-1, y, xd, yd)) {        
        return true;
    }
    if (flood(map, x, y-1, xd, yd)) {        
        return true;
    }


    return false;
    
}


int main() {
    int map[ROWS][COLS] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    Ghost ghosts;
    ghosts.position.x = 1;
    ghosts.position.y = 2;

    Pacman pacman;
    pacman.position.x = 4;
    pacman.position.y = 4;
    
    Node_T new_map[ROWS][COLS];

    for (int i = 0 ; i < ROWS; i++) {
        for (int j = 0 ; j < ROWS; j++) {
            new_map[i][j].x = j;
            new_map[i][j].y = i;
            new_map[i][j].value = map[i][j];
            new_map[i][j].visited = false;
        }
    }

    printf("%s\n\n", flood(new_map, ghosts.position.x, ghosts.position.y, pacman.position.x, pacman.position.y) ? "Encontrado" : "Nao encontrado");

    puts("Found path");

    Node_T * curr = &new_map[lasty][lastx];

    while (1) {
        printf("X: %d Y: %d\n", curr->x, curr->y);

        if (curr == curr->parent) {
            break;
        }

        curr = curr->parent;
    } 

    return 0;
}
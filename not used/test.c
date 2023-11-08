#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    int x, y, value1, value2;
} Character;

typedef struct
{
    int x,y;
    struct Node* parent;
    int g, h;
} Node;

int distanceCharacters(Character* a, Character* b) // retorna a distância entre dois characters
{
    return abs(a->x - b->x) + abs(a->y - b->y); // abs = valor absoluto
}

findPath(int matrix[20][20], Node start, Node end)
{
    Node* openList[400];
    int openListSize = 0;

    bool closedList[20][20] = {0};

    openList[0] = &start;
    openListSize = 1;

    while (openListSize > 0)
    {
        int currentIdx = 0;

        for (int i = 1; i < openListSize; i++) {
            if ((openList[i]->g + openList[i]->h) < (openList[currentIdx]->g + openList[currentIdx]->h))
            {
                currentIdx = i;
            }

        Node* current = openList[currentIdx];

        openList[currentIdx] = openList[openListSize - 1];
        openListSize--;

        closedList[current->x][current->y] = true;

        if (current == &end)
        {
            Node* pathNode = current;
            while (pathNode != NULL) {
                printf("Caminho: (%d, %d)\n", pathNode->x, pathNode->y);
                pathNode = pathNode->parent;
            }
            return;
        }

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++) {
            int newX = current->x + dx[i];
            int newY = current->y + dy[i];

            if (newX >= 0 && newX < 20 && newY >= 0 && newY < 20)
            {
                if (matrix[newX][newY] == 0 && !closedList[newX][newY])
                {
                    Node* neighbor = (Node*)malloc(sizeof(Node));
                    neighbor->x = newX;
                    neighbor->y = newY;
                    neighbor->parent = current;
                    neighbor->g = current->g + 1;
                    neighbor->h = calculateHeuristic(neighbor, &end);
                    openList[openListSize] = neighbor;
                    openListSize++;
                }
            }


    }



}

void ghostsMovements(Character* character)
{
    // pathfinding
}

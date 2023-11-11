// #include <stdio.h>
// #include "terminal.h"

// int pacman_animacao_um[20][20];

//     void printWall(int x, int y) 
//     {
//         int up = 0, down = 0, left = 0, right = 0;

//         if (x != 19)
//         {
//             if (pacman_animacao_um[y][x+1] == 1) {right = 1;}
//         }
//         if (x != 0)
//         {
//             if (pacman_animacao_um[y][x-1] == 1) {left = 1;}
//         }
//         if (y != 19)
//         {
//             if (pacman_animacao_um[y+1][x] == 1) {down = 1;}
//         }
//         if (y != 0)
//         {
//             if (pacman_animacao_um[y-1][x] == 1) {up = 1;}
//         }
//         if (up && down && right)
//         {
//             printf("%c%c", 204, 205);
//         }
//         else if (left && up && right)
//         {
//             printf("%c%c", 202, 205);
//         }
//         else if (left && down && right)
//         {
//             printf("%c%c", 203, 205);
//         }
//         else if (up && left && down)
//         {
//             printf("%c ", 185);
//         }
//         else if (up && right && down)
//         {
//             printf("%c%c", 204, 205);
//         }
//         else if (left && up)
//         {
//             printf("%c ", 188);
//         }
//         else if (left && down)
//         {
//             printf("%c ", 187);
//         }
//         else if (up && right)
//         {
//             printf("%c%c", 200, 205);
//         }
//         else if (right && down)
//         {
//             printf("%c%c", 201, 205);
//         }
//         else if (up || down)
//         {
//             printf("%c ", 186);
//         }
//         else if (left || right)
//         {
//             if (left && !right)
//             {
//                 printf("%c ", 205);
//             }
//             else
//             {
//                 printf("%c%c", 205, 205);
//             }
//         }
//         else 
//         {
//             printf("o ");
//         } 
//     }

//     void defineGameOver() // redefine o fundo para a tela de game over
//     {
//     FILE *matrix = fopen("./animacao1.txt", "r");

//     int line = 0, col = 0;
//     char c;

//     while ((c = fgetc(matrix)) != EOF)
//     {
//         if (c == '\r')
//         {
//             continue;
//         }
//         if (c == '\n')
//         {
//             col = 0;
//             line++;
//             continue;
//         }
//         pacman_animacao_um[line][col++] = c - '0';
//     }
//     fclose(matrix);
//     }

// int main(){
//     defineGameOver();
//     configureTerminal();

//     HIDE_CURSOR();
//     MOVE_HOME();

//     for (int i = 0; i < 20; i++)
//     {
//         for (int  j = 0; j < 20; j++)
//         {
//             if (pacman_animacao_um[i][j] == 0)
//             {
//                 printf("  ");
//             }
//             if (pacman_animacao_um[i][j] == 1)
//             {
//                 FOREGROUND_COLOR(2, 40, 97);
//                 printWall(j, i);
//                 RESET_FOREGROUND();
//             }
//             if (pacman_animacao_um[i][j] == 2)
//             {
//                 FOREGROUND_COLOR(250, 177, 7);
//                 printf("%c ", 254);
//                 RESET_FOREGROUND();
//             }
//             if (pacman_animacao_um[i][j] == 3)
//             {
//                 FOREGROUND_COLOR(14, 204, 176);
//                 printf("%c ", 254);
//                 RESET_FOREGROUND();
//             }
//         }
//         printf("\n");
//     }
//     ERASE_LEND();

//     fflush(stdout); 
//     system("pause");
// }

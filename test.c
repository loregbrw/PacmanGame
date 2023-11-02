#include <stdio.h>

typedef struct
{
    int x, y;
} Personagem;

void test_change(Personagem* pers)
{
    pers->x += 1;
}

int main(void)
{
    Personagem eu;
    eu.x = 1;

    test_change(&eu);

    printf("%i", eu.x);
    return 0;
}
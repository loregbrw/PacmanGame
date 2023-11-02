#ifndef EVENTS_H
#define EVENTS_H

void moveUp (Character character);
void moveLeft (Character character)
void moveDown (Character character)
void moveRight (Character character)

void changePositions (Character character, int new_x, int new_y);

int getInput();
int commands(int input);

#endif
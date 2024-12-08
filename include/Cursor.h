#ifndef BOILER_CURSOR
#define BOILER_CURSOR

typedef struct {
    int x;
    int y;
} Cursor;

void Cursor_MoveRight();
void Cursor_MoveLeft();
void Cursor_MoveUp();
void Cursor_MoveDown();

#endif
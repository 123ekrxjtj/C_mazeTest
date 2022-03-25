#include <stdio.h>
#include <stdlib.h>

#define MAZE_SIZE 6
#define MAX_SIZE 100
#define TRUE 1
#define FALSE 0
typedef struct
{
    short r;
    short c;
} element;

typedef struct
{
    element stack[100];
    int top;
} StackType;

int isFull(StackType *s)
{
    if (s->top < MAX_SIZE)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

int is_empty(StackType *s)
{
    if (s->top == -1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void push(StackType *s, element newEle)
{
    if (!isFull(s))
    {
        s->stack[++(s->top)] = newEle;
    }
    else
    {
        printf("Stack is full\n");
    }
}

element pop(StackType *s)
{
    if (!is_empty(s))
    {
        element res = s->stack[(s->top)--];
        return res;
    }
    else
    {
        printf("Stack is Empty\n");
        exit(1);
    }
}

element here = {1, 0}, entry = {1, 0};
char maze[][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '0', '0', '1', '1'},
    {'1', '1', '0', '1', '1', '1'},
    {'1', '1', '0', '1', '1', '1'},
    {'1', '0', '0', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'},
};

void init_stack(StackType *s)
{
    s->top = -1;
}

void push_loc(StackType *s, int r, int c)
{
    if (r < 0 || c < 0)
        return;
    if (maze[r][c] != '1' && maze[r][c] != '.')
    {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++)
    {
        for (int c = 0; c < MAZE_SIZE; c++)
        {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

int main(void)
{
    int r, c;
    StackType s;
    init_stack(&s);
    here = entry;
    while (maze[here.r][here.c] != 'x')
    {
        r = here.r;
        c = here.c;
        maze[r][c] = '.';
        maze_print(maze);
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);
        if (is_empty(&s))
        {
            printf("실패\n");
            return 0;
        }
        else
            here = pop(&s);
    }
    printf("성공\n");
    return 0;
}
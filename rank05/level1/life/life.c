#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
    int x;
    int y;
    int is_draw;
} pen;

char ** create_board(int width, int height)
{
    char** board  = malloc(sizeof (char*) * height);
    for (int i = 0;i < height; i++)
    {
        board[i] = calloc(sizeof(char), width);
        for (int  j = 0; j < width; j++)
        {
            board[i][j] = ' ';
        }
    }
    return board;
}

int count_neighboors(char **board,int y ,int  x, int height,int width)
{
    // int count = 0;
    // int x, y;
    // x = i - 1;
    // y = j;
    // if (x >= 0)
    // {
    //     if(board[x][y] == 'O')
    //         count++;
    // }

    // x = i - 1;
    // y = j - 1;
    // if (x >=0 && y >= 0)

    int count = 0;
	for (int i = -1; i <= 1; i++){
		for (int j = -1; j <= 1; j++){
			if (j == 0 && i == 0)
				continue ;
			int new_x = x + i;
			int new_y = y + j;
			if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height){
				if (board[new_y][new_x] == 'O')
					count++;
			}
		}
	}
	return (count);


}

void iter_game(char** board,int  height, int width)
{
    int count = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0;j < width; j++)
        {
            count = count_neighboors(board, i , j, height, width);
            if (board[i][j] == 'O')
            {
                if (count == 2|| count == 3)
                    continue;
                else
                    board[i][j] = ' ';
            }
            else
            {
                if (count == 3)
                    board[i][j] = 'O';
            }
        }
    }
}

void print_board(char **board, int height, int width)
{
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j  < width; j ++)
            putchar(board[i][j]);
        putchar('\n');
    }
}

int main (int ac, char **av)
{
    if (ac != 4)
    {
        return 1;
    }
    int width = atoi(av[1]);
    int height = atoi(av[2]);
    int iter = atoi(av[3]);
    char **board =create_board(width, height);
    char command;
    pen pen = {0, 0, 0};
    while (read(0, &command, 1))
    {
        if (command == 'w')
        {
            if (pen.x > 0)
                pen.x--;
            if (pen.is_draw)
                board[pen.x][pen.y] = 'O';
        }
        else if (command == 'a')
        {
            if (pen.y > 0)
                pen.y--;
            if (pen.is_draw)
                board[pen.x][pen.y] = 'O';
        }
        else if (command == 's')
        {
            if (pen.x < height - 1)
                pen.x++;
            if (pen.is_draw)
                board[pen.x][pen.y] = 'O';
        }
        else if (command == 'd')
        {
            if (pen.y < width - 1)
                pen.y ++;
            if (pen.is_draw)
                board[pen.x][pen.y] = 'O';
        }
        else if (command == 'x')
        {
            pen.is_draw = !pen.is_draw;
            if (pen.is_draw)
                 board[pen.x][pen.y] = 'O';
        }

    }

    // print_board(board, height, width);
    for (int i = 0; i <  iter; i ++)
        iter_game(board, height, width);
    print_board(board, height, width);
}
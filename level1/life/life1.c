#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


 
typedef struct s_board
{
	int		width;
	int		height;
	char	*cells;
}	t_board;
 
char	*get_cell(t_board *b, int x, int y);
void	mark(t_board *b, int x, int y);
void	process_command(t_board *b, char cmd, int *x, int *y, int *drawing);
void	read_input(t_board *b);
int		count_neighbors(t_board *b, int x, int y);
void	step(t_board *b);
void	print_board(t_board *b);

char	*get_cell(t_board *b, int x, int y)
{
	if (x < 0 || x >= b->width || y < 0 || y >= b->height)
		return (0);
	return (&b->cells[y * b->width + x]);
}

void	mark(t_board *b, int x, int y)
{
	char	*c;

	c = get_cell(b, x, y);
	if (c)
		*c = 1;
}

void	process_command(t_board *b, char cmd, int *x, int *y, int *drawing)
{
	if (cmd == 'w')
		(*y)--;
	else if (cmd == 's')
		(*y)++;
	else if (cmd == 'a')
		(*x)--;
	else if (cmd == 'd')
		(*x)++;
	else if (cmd == 'x')
	{
		*drawing = !(*drawing);
		if (*drawing)
			mark(b, *x, *y);
		return ;
	}
	else
		return ;
	if (*drawing)
		mark(b, *x, *y);
}

void	read_input(t_board *b)
{
	char	buf[4096];
	ssize_t	n;
	int		x;
	int		y;
	int		drawing;
	int		i;

	x = 0;
	y = 0;
	drawing = 0;
	while ((n = read(0, buf, sizeof(buf))) > 0)
	{
		i = 0;
		while (i < n)
		{
			process_command(b, buf[i], &x, &y, &drawing);
			i++;
		}
	}
}

int	count_neighbors(t_board *b, int x, int y)
{
	int		count;
	int		dx;
	int		dy;
	char	*c;

	count = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (!(dx == 0 && dy == 0))
			{
				c = get_cell(b, x + dx, y + dy);
				if (c && *c)
					count++;
			}
			dx++;
		}
		dy++;
	}
	return (count);
}

void	step(t_board *b)
{
	char	*next;
	int		x;
	int		y;
	int		n;
	char	*cur;

	next = malloc(sizeof(char) * b->width * b->height);
	if (!next)
		return ;
	y = 0;
	while (y < b->height)
	{
		x = 0;
		while (x < b->width)
		{
			n = count_neighbors(b, x, y);
			cur = get_cell(b, x, y);
			if (*cur)
				next[y * b->width + x] = (n == 2 || n == 3);
			else
				next[y * b->width + x] = (n == 3);
			x++;
		}
		y++;
	}
	free(b->cells);
	b->cells = next;
}

void	print_board(t_board *b)
{
	int		x;
	int		y;
	char	*c;

	y = 0;
	while (y < b->height)
	{
		x = 0;
		while (x < b->width)
		{
			c = &b->cells[y * b->width + x];
			if (*c)
				putchar('O');
			else
				putchar('.');
			x++;
		}
		putchar('\n');
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_board	b;
	int		iterations;
	int		i;

	if (argc != 4)
		return (1);
	b.width = atoi(argv[1]);
	b.height = atoi(argv[2]);
	iterations = atoi(argv[3]);
	if (b.width <= 0 || b.height <= 0 || iterations < 0)
		return (1);
	b.cells = calloc((size_t)b.width * (size_t)b.height, sizeof(char));
	if (!b.cells)
		return (1);
	read_input(&b);
	i = 0;
	while (i < iterations)
	{
		step(&b);
		i++;
	}
	print_board(&b);
	free(b.cells);
	return (0);
}
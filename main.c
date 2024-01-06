#include "includes/header.h"
// typedef struct s_data
// {
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// 	int		hight;
// 	int		width;
// 	int		color;
// 	double	move_right;
// 	double	move_left;
// 	double	zoom_hight;
// 	double	zoom_width;
// }  t_data ;
// creat a map with 1 = wall, 0 = empty 8x8 me will make a funy map with obstacles enjoi
int	map[] = {
	1, 1, 1, 1, 1, 1, 1, 1, // 1
	1, 0, 0, 0, 0, 0, 0, 1, // 2
	1, 0, 0, 0, 0, 0, 0, 1, // 3
	1, 0, 0, 0, 0, 0, 0, 1, // 4
	1, 0, 0, 0, 0, 0, 0, 1, // 5
	1, 0, 0, 0, 0, 0, 0, 1, // 6
	1, 0, 0, 0, 0, 0, 0, 1, // 7
	1, 1, 1, 1, 1, 1, 1, 1, // 8
};

// if you have (x, y) and you want to know the value of the map in this position you can use this function
int	getMapValue(int x, int y)
{
	return (map[y * 8 + x]);
}

void	 drawMap(t_data *data)
{
	int x;
	int y;

	x = 0;
	// each 64 pixel is a square in the map
	while (x < WIDTH / 2)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (getMapValue(x / 64, y / 64) == 1)
				mlx_pixel_put(data->mlx, data->mlx_win, x, y, RED);
			y++;
		}
		x++;
	}
}

void	drawInitPlayer(t_data *data)
{
	int x;
	int y;

	for (int i = data->y * 64 - 32 + 1; i < data->y * 64 + 32 - 1; i++)
	{
		for (int j = data->x * 64 - 32 + 1; j < data->x * 64 + 32 -1; j++)
			mlx_pixel_put(data->mlx, data->mlx_win, j, i, WHITE);
	}
}
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void drawPlayerCircle(t_data data) {
	int radius = 8; 
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x * x + y * y <= radius * radius) {
                my_mlx_pixel_put(&data, data.x + x, data.y + y, 0xFFFF00);
            }
        }
    }
}

void clearLineInFront(t_data data) {
    float lineLength = 5.0f; // Length of the line to clear in front of the player
    int boldness = 2; // Adjust this value to control the line's boldness

    for (int i = 0; i < lineLength; i++) {
        // Draw pixels around the original line to make it bolder
        for (int j = -boldness; j <= boldness; j++) {
            for (int k = -boldness; k <= boldness; k++) {
                my_mlx_pixel_put(&data, data.x + i * data.dx + j, data.y + i * data.dy + k, YELLOW);
            }
        }
    }
}

void	mlx_line_put(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	int dx;
	int dy;
	int x;
	int y;
	int i;
	int j;

	dx = x2 - x1;
	dy = y2 - y1;
	x = x1;
	y = y1;
	i = 0;
	j = 0;
	if (abs(dx) > abs(dy))
	{
		while (i < abs(dx))
		{
			x += dx > 0 ? 1 : -1;
			y += dy * abs(dx) / dx;
			my_mlx_pixel_put(data, x, y, color);
			i++;
		}
	}
	else
	{
		while (j < abs(dy))
		{
			x += dx * abs(dy) / dy;
			y += dy > 0 ? 1 : -1;
			my_mlx_pixel_put(data, x, y, color);
			j++;
		}
	}
}

void	drawRays3D(t_data *data)
{
	int r, mx, my, mp, dof;
	float rx, ry, ra, xo, yo;
	ra = data->angle;

	for (r = 0; r < 1; r++)
	{
		// --- Horizontal lines ---
		dof = 0;
		float aTan = -1 / tan(ra);
		if (ra > M_PI) { // looking up
			ry = (((int)data->y >> 6) << 6) - 0.0001;
			rx = (data->y - ry) * aTan + data->x;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < M_PI) { // looking down
			ry = (((int)data->y >> 6) << 6) + 64;
			rx = (data->y - ry) * aTan + data->x;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == M_PI) { // looking straight left or right
			rx = data->x;
			ry = data->y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * 8 + mx;
			if (mp > 0 && mp < 64 && map[mp] == 1) {
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
	}
	// draw line from player to wall
	mlx_line_put(data, data->x, data->y, rx, ry, GREEN);
}

void draw(t_data data)
{

	if(data.img != NULL)
		mlx_destroy_image(data.mlx, data.img);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, \
		&data.bits_per_pixel, &data.line_length, &data.endian);
	for(int x = 0; x < WIDTH / 2; x++) {
		for (int y = 0; y < HEIGHT; y++)
		{
			if (x % 64 == 0 || y % 64 == 0)
				my_mlx_pixel_put(&data, x, y, BLUE);
			else if (getMapValue((x) / 64, (y) / 64) == 1)
				my_mlx_pixel_put(&data, x, y, CYAN);
		}
	}
	drawPlayerCircle(data);
	clearLineInFront(data);
	drawRays3D(&data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	// return 0;
}

int	fun(int key, t_data *data)
{
	
	if (key == 53)
		quiteWindow();
	else if (key == 0)
	{
		data->x += data->dy;
		data->y -= data->dx;
	}
	else if (key == 2)
	{
		data->x -= data->dy;
		data->y += data->dx;
	}
	else if (key == 1)
	{
		data->x -= data->dx;
		data->y -= data->dy;
	}
	else if (key == 13)
	{
		data->x += data->dx;
		data->y += data->dy;
	}
	else if (key == 124)
	{
		data->angle += 0.2;
		if (data->angle > 2 * M_PI)
			data->angle -= 2 * M_PI;
		data->dx = cos(data->angle) * 15;
		data->dy = sin(data->angle) * 15;
	}
	else if (key == 123)
	{
		data->angle -= 0.2;
		if (data->angle < 0)
			data->angle += 2 * M_PI;
		data->dx = cos(data->angle) * 15;
		data->dy = sin(data->angle) * 15;
	}
	if (data->x < 0)
		data->x = 0;
	if (data->x > WIDTH / 2)
		data->x = WIDTH / 2;
	if (data->y < 0)
		data->y = 0;
	if (data->y > HEIGHT)
		data->y = HEIGHT;
	draw(*data);
	return (0);
}

// int fun(int a, t_data *x)
// {
	
// 	return 0;
// 	// t_data ptr
// }

int	main()
{
	t_data	data;
	data.img = NULL;
	init(&data);
	draw(data);
	// drawMap(&data);
	mlx_hook(data.mlx_win, 17, 0, quiteWindow, NULL);
	// mlx_loop_hook(data.mlx, fun, &data);
	// mlx_hook(data.mlx_win, 2, 0, movePlayer, &data);
	mlx_hook(data.mlx_win, 2, 0, fun, &data);
	mlx_loop(data.mlx);
}
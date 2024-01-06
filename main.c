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
// creat a map with 1 = wall, 0 = empty 16x12 
int	map[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1 , 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	1 , 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	1 , 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	1 , 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	1 , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.
};
// if you have (x, y) and you want to know the value of the map in this position you can use this function
int	getMapValue(int x, int y)
{
	return (map[y * 16 + x]);
}

void	 drawMap(t_data *data)
{
	int x;
	int y;

	x = 0;
	// each 64 pixel is a square in the map
	while (x < WIDTH)
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
    float lineLength = 15.0f; // Length of the line to clear in front of the player
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


void draw(t_data data)
{

	if(data.img != NULL)
		mlx_destroy_image(data.mlx, data.img);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, \
		&data.bits_per_pixel, &data.line_length, &data.endian);
	for(int x = 0; x < WIDTH; x++) {
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
		data->dx = cos(data->angle) * 5;
		data->dy = sin(data->angle) * 5;
	}
	else if (key == 123)
	{
		data->angle -= 0.2;
		if (data->angle < 0)
			data->angle += 2 * M_PI;
		data->dx = cos(data->angle) * 5;
		data->dy = sin(data->angle) * 5;
	}

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
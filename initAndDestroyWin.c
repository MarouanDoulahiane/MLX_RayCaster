#include "includes/header.h"


void	init(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "RayCaster");
	data->angle = 0;
	data->x = WIDTH / 2;
	data->y = HEIGHT / 2;
	data->dx = cos(data->angle) * 5;
	data->dy = sin(data->angle) * 5;
}

int	quiteWindow()
{
	printf("See u Soon Baby º_^\n");
	exit(0);
}
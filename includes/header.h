#ifndef HEADER_H
# define HEADER_H

// include libraries
#include <mlx.h>
#include <unistd.h>	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// define window size
# define WIDTH 1024
# define HEIGHT 512
// define map size
# define MAP_WIDTH 16
# define MAP_HEIGHT 12

// define colors
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define YELLOW 0xFFFF00
# define PURPLE 0xFF00FF
# define CYAN 0x00FFFF

// declare struct
typedef struct	s_data
{
	void	*mlx;
	void	*mlx_win;
	int		x;
	int		y;
	int		dx;
	int		dy;
	double		angle;
	int		bits_per_pixel;
	char	*addr;
	void	*img;
	int		line_length;
	int		endian;
	int		hight;
	int		width;
	int		color;
	double	move_right;
	double	move_left;
	double	zoom_hight;
	double	zoom_width;

}				t_data;

// declare functions
void	init(t_data *data);
int		quiteWindow();

#endif
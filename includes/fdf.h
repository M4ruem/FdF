
#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "../libft/libft.h"
# include <sys/stat.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

# define WIDTH 1000
# define HEIGHT 600
# define MENU_WIDTH 300
# define MENU_HEIGHT 300
# define WHITE 0xFFFFFF
# define ESCAPE 53
# define ERROR_MEMORY_ALLOCATION 2
# define ERROR_MAP_COLOURS 3
# define DEG_TO_RAD(angle) ((angle) * (M_PI / 180.0))
# define ISO_ANGLE 30.0

typedef struct s_data
{
	int x_difference;
	int y_difference;
	int x_sign;
	int y_sign;
	int error;
}			t_data;


typedef struct s_win
{
	void	*mlx;
	void	*window;
	int		height;
	int		width;
}			t_win;


typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
	int	colour;
}			t_coord;

typedef struct s_map
{
	int	width;
	int	height;
	int **depthGrid;
	int **color;
}			t_map;

typedef struct s_camera
{
	double	zoom;
	double	rotationX;  
	double	rotationY;  
	double	rotationZ;  
	int		xPositionAdjustment;
	int		yPositionAdjustment;
	double	layerDepth;  

}			t_camera;

typedef struct s_img
{
	t_win		win;
	t_map		map;
	void		*img;
	char		*addr;
	int			line_length;
	int			endian;
	int			height;
	int			width;
	t_camera	*cam;
	int			bits_per_pixel;
}			t_img;

int		validate_file_input(char *file, int arg_count);
t_win	initialize_window(int width, int height, char *title);
void	put_pixel_to_image(t_img image, int x, int y, int color);
void	plot_lines(t_coord p1, t_coord p2, t_img image);
t_img	initialize_image(int width, int height, t_win window);
int		handle_key_press(int key_code, t_img *image);
int		terminate_program(t_img *image);
void	draw_grid_lines(t_img image);
t_map	parse_map_from_file(char *file);
t_coord create_coordinate(int col, int row, t_map map);
int		*parse_hex_colors(char **color_str_array, t_map map_dimensions);
void	project_onto_plane(t_coord *c, t_img image);
void	free_2d_array(void **double_ptr);

#endif
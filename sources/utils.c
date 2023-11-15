#include "fdf.h"

t_win initialize_window(int width, int height, char *title)
{
	void *mlx_ptr;

	mlx_ptr = mlx_init();
	return ((t_win){mlx_ptr, mlx_new_window(mlx_ptr, width, height, title), width, height});
}

void put_pixel_to_image(t_img image, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < image.width && y < image.height)
		*(unsigned int *)(image.addr + (y * image.line_length + x * (image.bits_per_pixel / 8))) = color;
}

t_img initialize_image(int width, int height, t_win window)
{
	t_img new_image;

	new_image.win = window;
	new_image.img = mlx_new_image(window.mlx, width, height);
	new_image.addr = mlx_get_data_addr(new_image.img, &new_image.bits_per_pixel, &new_image.line_length, &new_image.endian);
	new_image.height = height;
	new_image.width = width;
	return (new_image);
}

int terminate_program(t_img *image)
{
	free_2d_array((void **) image->map.depthGrid);
	free_2d_array((void **) image->map.color);
	mlx_destroy_image(image->win.mlx, image->addr);
	mlx_destroy_window(image->win.mlx, image->win.window);
	exit(0);
}

int handle_key_press(int key_code, t_img *image)
{
	ft_memset(image->addr, 0, (image->height * image->width * 4));
	if (key_code == ESCAPE)
		terminate_program(image);
	return (0);
}


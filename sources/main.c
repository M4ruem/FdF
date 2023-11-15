#include "fdf.h"

static void	initialize_camera(t_camera *cam, t_map map)
{
    if (map.width <= 50 || map.height <= 50)
        cam->zoom = 10;
    else
        cam->zoom = 1;
    cam->layerDepth = 1;
    cam->xPositionAdjustment = 0;
    cam->yPositionAdjustment = 0;
}

t_win setup_window_and_image(t_img *image, char *filename, t_camera *cam)
{
    t_win fdf = initialize_window(WIDTH, HEIGHT, filename);
    if (!fdf.mlx || !fdf.window)
        exit(1);
    *image = initialize_image(WIDTH, HEIGHT, fdf);
    image->map = parse_map_from_file(filename);
    initialize_camera(cam, image->map);
    image->cam = cam;
    return fdf;
}

int main(int ac, char **av)
{
    t_win		fdf;
    t_img		image;
    t_camera	cam;

    if (validate_file_input(av[1], ac))
    {
        fdf = setup_window_and_image(&image, av[1], &cam);
        draw_grid_lines(image);
        mlx_hook(fdf.window, 2, 1L << 0, handle_key_press, &image);
        mlx_hook(fdf.window, 17, 1L << 17, terminate_program, &image);
        mlx_loop(fdf.mlx);
    }
    else
        return (1);
    return (0);
}


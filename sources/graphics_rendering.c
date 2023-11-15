#include "fdf.h"

t_coord create_coordinate(int col, int row, t_map map)
{
    t_coord coord;

    coord.colour = map.color[row][col];
    coord.x = col;
    coord.y = row;
    coord.z = map.depthGrid[row][col];
    return (coord);
}

void draw_horizontal_lines(t_img image, int current_row)
{
    int current_col;

    current_col = 0;
    while (current_col < image.map.width - 1)
    {
        plot_lines(
            create_coordinate(current_col, current_row, image.map),
            create_coordinate(current_col + 1, current_row, image.map),
            image);
        current_col++;
    }
}

void draw_vertical_lines(t_img image, int current_row)
{
    int current_col;

    current_col = 0;
    while (current_col < image.map.width)
    {
        plot_lines(
            create_coordinate(current_col, current_row, image.map),
            create_coordinate(current_col, current_row + 1, image.map),
            image);
        current_col++;
    }
}

void draw_grid_lines(t_img image)
{
    int current_row ;

    current_row = 0;
    while (current_row < image.map.height)
    {
        draw_horizontal_lines(image, current_row);
        if (current_row < image.map.height - 1)
            draw_vertical_lines(image, current_row);
        current_row++;
    }
    mlx_put_image_to_window(image.win.mlx, image.win.window, image.img, 0, 0);
}


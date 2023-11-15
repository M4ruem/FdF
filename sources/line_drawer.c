#include "fdf.h"

static int determine_sign(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

static int swap_dimensions_if_needed(t_data *data)
{
	int tmp;

	if (data->x_difference < data->y_difference)
	{
		tmp = data->x_difference;
		data->x_difference = data->y_difference;
		data->y_difference = tmp;
		return (1);
	}
	return (0);
}

static int absolute_value(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

static void initialize_line_data(t_data *data, t_coord start, t_coord end)
{
	data->x_difference = absolute_value(end.x - start.x);
	data->y_difference = absolute_value(end.y - start.y);
	data->x_sign = determine_sign(end.x - start.x);
	data->y_sign = determine_sign(end.y - start.y);
}

static void adjust_coordinates_based_on_error(t_coord* point, t_data* line_data, int should_swap) 
{
	while (line_data->error > 0)
	{
		line_data->error -= 2 * line_data->x_difference;
		point->x += line_data->x_sign * should_swap;
		point->y += line_data->y_sign * !should_swap;
	}
	
	line_data->error += 2 * line_data->y_difference;
	point->y += line_data->y_sign * should_swap;
	point->x += line_data->x_sign * !should_swap;
}

void plot_lines(t_coord start, t_coord end, t_img image)
{
	int i;
	int should_swap;
	t_data line_data;

	project_onto_plane(&start, image);
	project_onto_plane(&end, image);
	initialize_line_data(&line_data, start, end);
	should_swap = swap_dimensions_if_needed(&line_data);
	line_data.error = 2 * line_data.y_difference - line_data.x_difference;
	i = 0;
	while (i <= line_data.x_difference)
	{
		put_pixel_to_image(image, start.x, start.y, start.colour);
		adjust_coordinates_based_on_error(&start, &line_data, should_swap);
		i++;
	}
}


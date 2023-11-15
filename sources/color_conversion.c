#include "fdf.h"

static char *convert_to_uppercase(char *input_str) 
{
    char *cursor = input_str;

    while (*cursor) 
    {
        if (ft_isalpha(*cursor))
            *cursor = ft_toupper(*cursor);
        cursor++;
    }
    return (input_str);
}

static int extract_color_value(const char *color_str) 
{
    char **hex_parts;
    int color;

    hex_parts = ft_split(color_str, 'x');
    if (!ft_strchr(color_str, 'x'))
        return 0xFFFFFF;
    if (!hex_parts || !hex_parts[1]) 
    {
        free_2d_array((void **)hex_parts);
        return (-1);
    }
    color = ft_atoi_base(convert_to_uppercase(hex_parts[1]), "0123456789ABCDEF");
    free_2d_array((void **)hex_parts);
    return (color);
}

int *parse_hex_colors(char **color_str_array, t_map map_dimensions) 
{
    int *parsed_colors;
    int i;
    int color_value;

    parsed_colors = (int *)malloc(sizeof(int) * map_dimensions.width);
    i = 0;
    if (!parsed_colors)
        return (NULL);
    while (i < map_dimensions.width) 
    {
        color_value = extract_color_value(color_str_array[i]);
        if (color_value == -1) 
        {
            free(parsed_colors);
            return (NULL);
        }
        parsed_colors[i] = color_value;
        i++;
    }
    return (parsed_colors);
}

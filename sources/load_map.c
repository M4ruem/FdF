#include "fdf.h"

void	free_2d_array(void **double_ptr)
{
	int i = 0;

	if (!double_ptr)
		return ;
	while (double_ptr[i])
	{
		free(double_ptr[i]);
		i++;
	}
	free(double_ptr);
}

static t_map determine_map_dimensions(int fd)
{
	char	*line;
	char	**vals;
	t_map	map;

	line = get_next_line(fd);
	while (line)
	{
		if (map.height == 0)
		{
			vals = ft_split(line, ' ');
			int width_count = 0;
			while (vals[width_count])
				width_count++;
			map.width = width_count;
			free_2d_array((void **)vals);
		}
		map.height++;
		free(line);
		line = get_next_line(fd);
	}
	return (map);
}

static int *parse_line_values(char **values_str, t_map map, int y)
{
	int		*depthGrid;
	int		x = 0;

	map.color[y] = parse_hex_colors(values_str, map);
	depthGrid = (int *) malloc(sizeof(int) * map.width);
	if (!depthGrid)
		exit(ERROR_MEMORY_ALLOCATION);
	while (x < map.width)
	{
		depthGrid[x] = ft_atoi(values_str[x]);
		x++;
	}
	free_2d_array((void **)values_str);
	return (depthGrid);
}

static int safe_open_file(const char *file)
{
	int fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	return (fd);
}

static void allocate_map_memory(t_map *map)
{
	map->depthGrid = (int **) malloc(sizeof(int *) * (map->height + 1));
	map->color = (int **) malloc(sizeof(int *) * (map->height + 1));
	if (!map->depthGrid || !map->color)
	{
		if (map->depthGrid) free(map->depthGrid);
		if (map->color) free(map->color);
		exit(ERROR_MEMORY_ALLOCATION);
	}
}

t_map parse_map_from_file(char *file)
{
	int fd;
	char *line;
	int y = 0;
	t_map map;

	fd = safe_open_file(file);
	if (fd == -1) return (t_map){0};
	map = determine_map_dimensions(fd);
	close(fd);
	allocate_map_memory(&map);
	fd = safe_open_file(file);
	if (fd == -1) 
	{
		free(map.depthGrid);
		free(map.color);
		return (t_map){0};
	}
	while ((line = get_next_line(fd)) && y < map.height)
	{
		map.depthGrid[y] = parse_line_values(ft_split(line, ' '), map, y);
		free(line);
		y++;
	}
	map.color[y] = NULL;
	map.depthGrid[y] = NULL;
	close(fd);
	return map;
}

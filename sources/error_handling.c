#include "fdf.h" 

static void	display_error_message(char *message)
{
	ft_putendl_fd("\033[1;3;31m\n Invalid file entered.\n", 2);
	ft_putendl_fd(message, 2);
	exit(0);
}

static void	verify_file_extension(char *file)
{
	char *file_extension;

	file_extension = ft_strrchr(file, '.');
	if (!file_extension || strcmp(file_extension, ".fdf") != 0)
		display_error_message("Use \"./fdf [map].fdf\" to run this program.");
}

static int is_empty_file(char *file)
{
	struct stat file_stat;

	if (stat(file, &file_stat) != 0)
		return (0);
	return (file_stat.st_size == 0); 
}

int validate_file_input(char *file, int arg_count)
{
	int fd;

	if (arg_count != 2)
		display_error_message("Use \"./fdf [map].fdf\" to run this program.");
	verify_file_extension(file);
	if (is_empty_file(file))
		display_error_message("The provided .fdf file is empty.");
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		display_error_message("Use \"./fdf [map].fdf\" to run this program.");
	}
	close(fd);
	return (1);
}

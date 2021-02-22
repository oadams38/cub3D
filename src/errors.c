#include "../inc/cub3D.h"

void	*malloc_error()
{
	//perror("Memory allocation error:\n");
	ft_putstr("Memory allocation error:\n");
	return (NULL);
}

int		malloc_error_int()
{
	//perror("Memory allocation error:\n");
	ft_putstr("Memory allocation error:\n");
	return (0);
}

void	*duplicate_or_missing_param_error(char *param)
{
	//perror("Error: Map has duplicate parameter\n");
	printf("Error: Map has duplicate or missing parameter %s\n", param);
	return (NULL);
}

void	*wrong_map_char()
{
	//perror("Error: The map grid contains a wrong character\n");
	ft_putstr("Error: The map grid contains a wrong character\n");
	return (NULL);
}

void	*astar_search_malloc_fail(t_pathfinder **head)
{
	free_t_pathfinder(head);
	return (malloc_error());
}

int		walls_not_closed_error()
{
	printf("Error: Walls not closed");
	return (0);
}

int		missing_entry_error(char *missing_entry)
{
	printf("Error: missing %s", missing_entry);
	return (0);
}

int		missing_player_error()
{
	printf("Error: missing player initial position");
	return (0);
}

void	*missing_map_error()
{
	printf("Error: map missing\n");
	return (NULL);
}

int		wrong_rgb_error(char *subject)
{
	printf("Error: bad RGB values for the %s parameter\n", subject);
	return (0);
}

int		resolution_error()
{
	printf("Error: resolution is too low. We suggest a resolution over 600 x 600 to see something\n");
	return (0);
}

int		wrong_path_error(char *path, char *subject)
{
	printf("Error: path to %s \"%s\" doesn't exist\n", subject, path);
	return (0);
}
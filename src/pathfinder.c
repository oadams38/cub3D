#include "../inc/cub3D.h"
#include <math.h>

int				get_matrix_xy(int **mapdata, char c)
{
	int		axis;

	axis = 0;
	if (c == 'y')
	{
		while (mapdata[axis])
			axis++;
		return (axis);
	}
	else if (c == 'x')
	{
		while (mapdata[0][axis])
			axis++;
		return (axis);
	}
	else
		return (-1);
}

int				on_border(t_pathfinder **head, int	**mapdata)
{
	if ((*head)->y == 0 || mapdata[(*head)->y + 1] == NULL)
		return (1);
	if ((*head)->x == 0 || mapdata[0][(*head)->x + 1] == -1)
		return (1);
	return (0);
}

void			sort_list(t_pathfinder **head)
{
	t_pathfinder	*tmp_prev;
	t_pathfinder	*tmp;
	t_pathfinder	*tmp_next;

	if (!head || !*head)
		return ;
	tmp = (*head);
	tmp_prev = (*head);
	while (tmp)
	{
		tmp_next = tmp->next;
		if (tmp_next && ((tmp->cost > tmp_next->cost && tmp_next->all_discovered == 0) || (tmp->all_discovered == 1 && tmp_next->all_discovered == 0)))
		{
			if (tmp_prev == (*head) && tmp == (*head))
			{
				(*head) = tmp_next;
				tmp->next = tmp_next->next;
				tmp_next->next = tmp;
				tmp_prev = (*head);
			}
			else
			{
				tmp->next = tmp_next->next;
				tmp_next->next = tmp;
				tmp_prev->next = tmp_next;
			}
			tmp_prev = (*head);
			tmp = (*head);
		}
		else if (tmp_next)
		{
			tmp_prev = tmp;
			tmp = tmp_next;
			tmp_next = tmp_next->next;
		}
		else
			return;
	}
}

t_pathfinder	**update(t_pathfinder **head, int x, int y, int steps)
{
	t_pathfinder	*tmp;
	t_pathfinder	*new_item;

	tmp = (*head);
	while (tmp && (tmp->x != x || tmp->y != y))
		tmp = tmp->next;
	if (tmp && tmp->x == x && tmp->y == y)
	{
		tmp->steps = tmp->steps < steps ? steps : tmp->steps;
		tmp->cost = tmp->distance + (double)(tmp->steps / 2);
	}
	else
	{
		if ((new_item = ft_calloc(1, sizeof(*new_item))) == NULL)
			return (NULL);
		new_item->steps = steps;
		new_item->x = x;
		new_item->y = y;
		new_item->all_discovered = 0;
		new_item->distance = (sqrt(pow(x, 2) + pow(y, 2)));
		new_item->cost = (double)(new_item->steps / 2) + new_item->distance;
		new_item->next = (*head);
		(*head) = new_item;
	}
	return (head);
}

t_pathfinder	**update_adjacent_positions(t_pathfinder **head, int **mapdata)
{
	t_pathfinder	*tmp;
	t_pathfinder	**tmp_head;
	int				y;
	int				x;

	tmp = (*head);
	x = tmp->x;
	y = tmp->y;
	tmp_head = head;
	if ((mapdata[y][x + 1] != -1 && mapdata[y][x + 1] == 0) && 
		((tmp_head = update(head, x + 1, y, tmp->steps + 1)) == NULL))
		return (astar_search_malloc_fail(head));
	head = tmp_head;
	if ((x - 1 >= 0 && mapdata[y][x - 1] == 0) && 
		((tmp_head = update(head, x - 1, y, tmp->steps + 1)) == NULL))
		return (astar_search_malloc_fail(head));
	head = tmp_head;
	if ((mapdata[y + 1] && mapdata[y + 1][x] == 0) &&
		((tmp_head = update(head, x, y + 1, tmp->steps + 1)) == NULL))
		return (astar_search_malloc_fail(head));
	head = tmp_head;
	if ((y - 1 >= 0 && mapdata[y - 1][x] == 0) &&
		((tmp_head = update(head, x, y - 1, tmp->steps + 1)) == NULL))
		return (astar_search_malloc_fail(head));
	head = tmp_head;
	tmp->all_discovered = 1;

	return (head);
}

void			free_t_pathfinder(t_pathfinder **head)
{
	t_pathfinder	*tmp;

	while ((*head)->next)
	{
		tmp = (*head);
		(*head) = tmp->next;
		free((void*)tmp);
	}
	free((void*)(*head));
	free((void*)head);
}

t_pathfinder	*init_head(t_pathfinder **head, int y, int x)
{
	t_pathfinder	*tmp;

	if (!(tmp = ft_calloc(1, sizeof(t_pathfinder))))
		return (NULL);
	*head = tmp;
	tmp->y = y;
	tmp->x = x;
	tmp->steps = 0;
	tmp->distance = (sqrt(pow(x, 2) + pow(y, 2)));
	tmp->cost = (double)(tmp->steps / 2) + tmp->distance;
	tmp->all_discovered = 0;
	tmp->next = NULL;
	return (tmp);
}

int				find_player_border_path(int **map, int y, int x)
{
	t_pathfinder	**head;

	if (!(head = ft_calloc(1, sizeof(t_pathfinder*))))
		return (0);
	if (init_head(head, y, x) == NULL)
	{
		free((void*)head);
		return (malloc_error_int());
	}
	while (!on_border(head, map) && (*head)->all_discovered == 0)
	{
		if ((head = update_adjacent_positions(head, map)) == NULL)
			return (0);
		sort_list(head);
	}
	print_map(map, head);
	if ((*head)->all_discovered == 1)
	{
		free_t_pathfinder(head);
		return (0);
	}
	free_t_pathfinder(head);
	return (1);
}
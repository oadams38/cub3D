#include "../inc/cub3D.h"

int		start_minilibx()
{
	void	*mlx_ptr;
	// void	*win_ptr;

	mlx_ptr = mlx_init();
	mlx_new_window(mlx_ptr, 1920, 1080, "cub3D");
	//mlx_loop(mlx_ptr);
	return (1);
}
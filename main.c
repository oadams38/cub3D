#include "inc/cub3D.h"
#include "inc/libft_bonus.h"

int     main(int argc, char **argv)
{
    int     map_nb;
    t_mapdata  *ptr;

    map_nb = 0;
    if (argc > 1)
    {
        while (++map_nb < argc)
        {
			//MAYBE CHECK MAP FILE BEFORE SAVING DATA
            if ((ptr = get_map_data(argv[map_nb])) == NULL)
			{
				printf("Y'a erreur\n");
				return (0);
			}
			//
			if (check_mapdata(ptr))
			{
				printf("\nALL CLEAR");
				//start_minilibx();
			}
            free((void*)ptr);
        }
    }
    return (0);
}
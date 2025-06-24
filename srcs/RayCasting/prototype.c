// #include "../../includes/cub3d.h"
// #include <stdlib.h>
// #include <math.h>
// #include <stdio.h>

// #define MAP_SIZE 50


// int	close_win(t_data *data)
// {
// 	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 	exit(EXIT_SUCCESS);
// 	return (0);
// }

// char **generate_large_map(void)
// {
//     char **map = malloc(sizeof(char*) * (MAP_SIZE + 1));
//     if (!map)
//         return NULL;

//     for (int i = 0; i < MAP_SIZE; i++)
//     {
//         map[i] = malloc(MAP_SIZE + 1);
//         if (!map[i])
//         {
//             // libérer tout en cas d'erreur
//             for (int j = 0; j < i; j++)
//                 free(map[j]);
//             free(map);
//             return NULL;
//         }
//         for (int j = 0; j < MAP_SIZE; j++)
//         {
//             if (i == 0 || i == MAP_SIZE - 1 || j == 0 || j == MAP_SIZE - 1)
//                 map[i][j] = '1'; // mur autour
//             else
//                 map[i][j] = '0'; // espace vide
//         }
//         map[i][MAP_SIZE] = '\0';
//     }
//     map[MAP_SIZE] = NULL;
//     return map;
// }

// int main(void)
// {
//     t_data data;

//     ft_init_mlx(&data);

//     data.ceiling = (t_color){100, 100, 255};
//     data.floor = (t_color){80, 50, 30};

//     data.map.width = MAP_SIZE;
//     data.map.height = MAP_SIZE;
//     data.map.map = generate_large_map();

//     static t_position player = {
//         .x = MAP_SIZE / 2.0f,
//         .y = MAP_SIZE / 2.0f,
//         .angle = M_PI * 3 / 4,
//         .fov = M_PI / 3
//     };
//     data.map.play = &player;

//     data.textures.no_xpm = "./textures_test/wall.xpm";
//     data.textures.so_xpm = "./textures_test/blue_wall.xpm";
//     data.textures.ea_xpm = "./textures_test/green_wall.xpm";
//     data.textures.we_xpm = "./textures_test/red_wall.xpm";
//     ft_init_textures(&data);

//     // Hook pour le rendu (rafraîchissement)
//     mlx_loop_hook(data.mlx_ptr, (int (*)())render_game, &data);

//     mlx_hook(data.win_ptr, 17, 0, close_win, &data);
//     mlx_loop(data.mlx_ptr);

//     for (int i = 0; i < MAP_SIZE; i++)
//         free(data.map.map[i]);
//     free(data.map.map);

//     return 0;
// }


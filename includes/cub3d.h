/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:07:19 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/18 16:39:02 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//# include <mlx.h>
//# include <X11/X.h>
//# include <X11/keysym.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100

# define KEY_UP				65362
# define KEY_LEFT			65361
# define KEY_RIGHT			65363
# define KEY_DOWN			65364

# define KEY_Q				113
# define KEY_ESC			65307

typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct s_textures
{
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
}       t_textures;

typedef struct s_params
{
    t_textures  textures;
    t_color     floor;
    t_color     ceiling;
}           t_params;

typedef struct s_map
{
    int north;
    int south;
    int west;
    int east;
    int height;
    int width;
    char    **map;
}   t_map;

typedef struct s_data
{
    void    *win_ptr;
    void    *mlx_ptr;
    t_params params;
    t_map   map;
} t_data;


// INITIALISATION
char	**init_map(int fd, t_params *params, t_map *map);
void	init_data(t_data *data);

int     is_param_line(char *line, t_params *params);
int	    is_param_map(char *line);

// CHECK
int     check_map(t_map *map);

// PARSING MAP
char	**load_map(char **av, t_params *params, t_map *map);
char    **add_line_to_map(t_map *map, char *line);
int     is_param_map(char *line);

// PARSING TEXTURES AND COLOR
int     parse_color(char *line, t_color *color);
int     parse_texture(char *line, char **texture);

// UTILS
void	count_elements(t_map *map);
void	print_map(char **map);
#endif

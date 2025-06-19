/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:07:19 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/19 15:59:41 by opique           ###   ########.fr       */
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
# include <math.h>
# include <float.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define GREEN				"\033[0;32m"
# define ORANGE				"\033[1;33m"
# define MAGENTA			"\033[1;95m"
# define GREY				"\033[0;90m"
# define RESET				"\033[0m"

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

# define WIN_LEN			1500
# define WIN_HEIGHT			1000

# define NORTH				1
# define SOUTH              2
# define EAST               3
# define WEST               4

//Angle de vision a 60 degres pour reproduire la vision comme Wolfenstein
# define FOV				M_PI / 3
# define NUM_RAYS			60

typedef	struct s_cast
{
	float	dx;
	float	dy;
	float	rayx;
	float	rayy;
	float	distance;
	float	stepsize;
}	t_cast;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_position
{
	float	x;
	float	y;
}	t_position;

typedef struct s_image
{
	void	*xpm_ptr;
	int		or;
	float	x;
	float	y;
}	t_image;

typedef struct s_textures
{
	char	*no_xpm;
	char	*so_xpm;
	char	*we_xpm;
	char	*ea_xpm;
	t_image	no;
	t_image	so;
	t_image	ea;
	t_image	we;
	int no_check;
    int so_check;
    int we_check;
    int ea_check;
}	t_textures;

typedef struct s_map
{
    int 		north;
    int 		south;
    int 		west;
    int 		east;
    int 		height;
    int 		width;
    char    	**map;
	t_position	*play;
}   t_map;

typedef struct s_data
{
	void		*win_ptr;
	void		*mlx_ptr;
	t_map		map;
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	int 	check_f;
    int 	check_c;
}	t_data;


// INITIALISATION
char	**init_map(int fd, t_data *data, t_map *map);
void	init_data(t_data *data);

int     is_param_line(char *line, t_data *data);
int	    is_param_map(char *line);

// CHECK
int     check_map(t_map *map);
int		check_param(t_data *data);

// PARSING MAP
char	**load_map(char **av, t_data *data, t_map *map);
char    **add_line_to_map(t_map *map, char *line);
int     is_param_map(char *line);

// PARSING TEXTURES AND COLOR
int     parse_color(char *line, t_color *color);
int     parse_texture(char *line, char **texture);

//CLOSING MAPS
int     ft_error_close(char *message, t_data *data);

// UTILS
void	count_elements(t_map *map);
void	print_map(char **map);

#endif

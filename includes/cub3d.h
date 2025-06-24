/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:07:19 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/24 15:38:03 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define _USE_MATH_DEFINES

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

#define TILE_SIZE			64

# define NORTH				1
# define SOUTH              2
# define EAST               3
# define WEST               4

//Angle de vision a 60 degres pour reproduire la vision comme Wolfenstein
# define NUM_RAYS			WIN_LEN
# define TILE_SIZE			7

typedef struct s_cast
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
	int		orientation; // cardinal
	float	angle; // radians
	float	fov;
	float	fov_rad; // Pour la norme
}	t_position;

typedef struct s_rc
{
	float	distance;
	float	pr_hght;
	float	impact_x;
	float	dis_proj_plane;
	int		top_pixel;
	int		bttm_pixel;
	int		w_or;
}	t_rc;

typedef struct s_image
{
	void	*xpm_ptr;
	char	*data_addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		or;
	int		x;
	int		y;
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
	t_image	*all[4];
	int		no_check;
	int		so_check;
	int		we_check;
	int		ea_check;
}	t_textures;

typedef struct s_map
{
	int			north;
	int			south;
	int			west;
	int			east;
	int			height;
	int			width;
	char		**map;
	t_position	play;
}	t_map;

typedef struct s_data
{
	void		*win_ptr;
	void		*mlx_ptr;
	t_map		map;
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	int			check_f;
	int			check_c;
	int			last_mouse_x;
	t_image		screen;
}	t_data;


// INITIALISATION
void	init_data(t_data *data);
void	ft_init_mlx(t_data *data);
void	init_hook_loop(t_data *data);

int		is_param_line(char *line, t_data *data);
int		is_param_map(char *line);
void	ft_init_mlx(t_data *data);
t_image	ft_new_img(void *mlx, char *path, t_data *data, int or);
void	ft_init_textures(t_data *data);
int		check_char_map(t_map *map);

// CHECK
int		check_map(t_map *map);
int		check_param(t_data *data);
int		check_all(t_data *data, t_map *map);

// PARSING MAP
char	**load_map(int fd, t_map *map, char *first_line);
int		load_map_and_param(char **av, t_data *data, t_map *map);
char	**add_line_to_map(t_map *map, char *line);
int		check_char_map(t_map *map);
void	parse_player(t_map *map);
int     load_map_and_param(char av, t_data data, t_map *map);

// PARSING TEXTURES AND COLOR
char	*load_param(int fd, t_data *data);
int		parse_color(char *line, t_color *color);
int		parse_texture(char *line, char **texture);

// RAYCASTING ET 3D
void	render_game(t_data *data);
int		get_w_or(float dx, float dy);
float	get_impact_x(float rayx, float rayy, int w_or);
void	draw_column(t_data *data, t_rc *rc, int ray);

// DRAW MAP
void	load_textures(t_data *data);
void	draw_map(t_data *data);
t_image	ft_new_img(void *mlx, char *path, t_data *data, int or);
void	print_textures_for_player(t_data *data, char c, int x, int y);

//CLOSING MAPS
int		ft_error_close(char *message, t_data *data);
int		on_destroy(t_data *data);

// MOUVEMENT JOUEUR (CLAVIER)
int		handle_keypress(int keysum, t_data *data);
int		handle_mouse(int x, int y, t_data *data);

// UTILS
void	count_elements(t_map *map);
void	replace_spaces_by_walls(t_map *map);
void	print_map(char **map);
int		cub_extansion(char *filename);

/*
Récapitulatif des directions :
Est	= 0° =	0
Nord-Est =	45° =	π/4
Nord = 90° = π/2
Nord-Ouest = 135° = 3π/4
Ouest = 180° = π
Sud-Ouest = 225° = 5π/4
Sud = 270° = 3π/2
Sud-Est = 315° = 7π/4
*/

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:07:19 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/01 10:40:10 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/X.h>
# include <X11/keysym.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "structures.h"

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

# define NORTH				0
# define SOUTH              1
# define EAST               2
# define WEST               3

# define MINMAP_BOX			10 // Taille case pixel
# define MINMAP_SIZE		200 // Taille minimap

//Angle de vision a 60 degres pour reproduire la vision comme Wolfenstein
# define NUM_RAYS			WIN_LEN
# define GRAPH_SIZE         64
# define TILE_SIZE			2
# define SPEED				0.05f

// INITIALISATION
void			init_data(t_data *data);
void			ft_init_mlx(t_data *data);
void			init_hook_loop(t_data *data);
void			init_texture(t_data *data);
int				is_param_line(char *line, t_data *data);
int				is_param_prefix_only(char *line);
int				is_param_map(char *line);
void			ft_init_mlx(t_data *data);
t_image			ft_new_img(void *mlx, char *path, t_data *data, int or);
void			ft_init_textures(t_data *data);

// CHECK
int				check_map(t_map *map, t_data *data);
int				check_param(t_data *data);
int				check_all(t_data *data, t_map *map);
int				check_wall(t_map *map, t_data *data);
int				is_color_line(char *line, t_data *data);
int				is_texture_line(char *line, t_data *data);
int				parse_and_check(char *line, char *id, char **texture,
					int *check);

// PARSING MAP
char			**load_map(int fd, t_map *map, char *first_line, t_data *data);
int				load_map_and_param(char **av, t_data *data, t_map *map);
char			**add_line_to_map(t_map *map, char *line);
int				check_char_map(t_map *map);
void			parse_player(t_map *map);

// PARSING TEXTURES AND COLOR
char			*load_param(int fd, t_data *data);
int				parse_color(char *line, t_color *color, t_data *data);
int				parse_texture(char *line, char **texture);

// RAYCASTING ET 3D
void			render_game(t_data *data);
int				get_w_or(float dx, float dy);
float			get_dist_from_player(t_map *map, float rayAngle, t_rc *rc);
float			get_impact_x(float rayx, float rayy, int w_or);
void			draw_column(t_data *data, t_rc *rc, int ray);
float			normalize_angle(float angle);
int				loop_handler(t_data *data);
int				init_text_x(t_rc *rc, t_image *texture);
int				set_text_y(t_rc *rc, int y, t_image *texture);
void			run_dda(t_map *map, t_dda *dda, int *side);
void			init_ray_data(t_map *map, float ray_angle, t_cast *cast,
					t_dda *dda);


// DRAW MAP
void			load_textures(t_data *data);
void			draw_map(t_data *data);
t_image			ft_new_img(void *mlx, char *path, t_data *data, int or);
void			print_textures_for_player(t_data *data, char c, int x, int y);
void			put_pixel_to_image(t_image *img, int x, int y,
					unsigned int color);
unsigned int	get_text_pixel_color(t_image *img, int x, int y);

// MINIMAP
int				draw_minimap(t_data *data);

//CLOSING MAPS
int				ft_error_close(char *message, t_data *data);
int				on_destroy(t_data *data);

// MOUVEMENT JOUEUR (CLAVIER)
int				handle_keypress(int keysum, t_data *data);
int				handle_mouse(int x, int y, t_data *data);
int				handle_mouse_click(int but, int x, int y, t_data *data);
void			double_c(struct timeval cur_click, t_data *data,
					struct timeval *last);
int				first_c(struct timeval *last, struct timeval current_click,
					int *first_c);

// UTILS
void			count_elements(t_map *map);
void			replace_spaces_by_walls(t_map *map);
int				cub_extansion(char *filename);
int				rgb_to_int(t_color color);
void			free_map(char **map, int height);
void			ft_free_paths_textures(t_data *data);
int				print_color_error(char *msg, t_data *data, char *line);

#endif
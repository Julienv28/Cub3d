/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:41:20 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/30 13:21:25 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_minimap
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;
}	t_minimap;

typedef struct s_cast
{
	float	dx;
	float	dy;
	float	rayx;
	float	rayy;
	float	distance;
	float	stepsize;
    int		mapX;
    int		mapY;
    int		stepX;
    int		stepY;
    float	deltaX;
    float	deltaY;
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
	int		ori;
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
	bool		mouse_locked;
	bool		ignore_mouse_event;
	bool		need_redraw;
	t_image		screen;
	t_minimap	minimap;
}	t_data;

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
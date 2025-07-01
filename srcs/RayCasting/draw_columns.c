/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_columns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:04:04 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/01 17:24:56 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// static void	draw_wall_strip(t_data *data, t_rc *rc, int ray, int text_x)
// {
// 	int		y;
// 	int		text_y;
// 	int		color;
// 	t_image	*texture;
// 	float	step;
// 	float	tex_pos;

// 	texture = data->textures.all[rc->w_or];
// 	y = rc->top_pixel;
// 	while (y < rc->bttm_pixel)
// 	{
// 		text_y = set_text_y(rc, y, texture);
// 		color = get_text_pixel_color(texture, text_x, text_y);
// 		put_pixel_to_image(&data->screen, ray, y, color);
// 		y++;
// 	}
// }

static void	draw_wall_strip(t_data *data, t_rc *rc, int ray, int text_x)
{
	int		y;
	int		text_y;
	int		color;
	t_image	*texture;
	float	step;
	float	tex_pos;

	texture = data->textures.all[rc->w_or];

	int wall_height = rc->pr_hght;
	int draw_start = rc->top_pixel;
	int draw_end = rc->bttm_pixel;

	step = (float)texture->y / (float)wall_height;
	tex_pos = (draw_start - WIN_HEIGHT / 2 + wall_height / 2) * step;

	for (y = draw_start; y < draw_end; y++)
	{
		text_y = (int)tex_pos & (texture->y - 1);
		tex_pos += step;
		color = get_text_pixel_color(texture, text_x, text_y);
		put_pixel_to_image(&data->screen, ray, y, color);
	}
}

static void	draw_ceiling(t_data *data, t_rc *rc, int ray)
{
	int	y;
	int	color;

	y = 0;
	color = rgb_to_int(data->ceiling);
	while (y < rc->top_pixel)
	{
		put_pixel_to_image(&data->screen, ray, y, color);
		y++;
	}
}

static void	draw_floor(t_data *data, t_rc *rc, int ray)
{
	int	y;
	int	color;

	y = rc->bttm_pixel;
	color = rgb_to_int(data->floor);
	while (y < WIN_HEIGHT)
	{
		put_pixel_to_image(&data->screen, ray, y, color);
		y++;
	}
}

void	draw_column(t_data *data, t_rc *rc, int ray)
{
	t_image	*texture;
	int		text_x;

	if (rc->w_or < 0 || rc ->w_or > 3)
		return ;
	texture = data->textures.all[rc->w_or];
	if (texture == NULL)
		return ;
	text_x = init_text_x(rc, texture);
	draw_wall_strip(data, rc, ray, text_x);
	draw_ceiling(data, rc, ray);
	draw_floor(data, rc, ray);
}

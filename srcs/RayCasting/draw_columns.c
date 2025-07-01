/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_columns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:04:04 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/01 11:22:06 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// void	draw_column(t_data *data, t_rc *rc, int ray)
// {
// 	int				y;
// 	int				text_x;
// 	int				text_y;
// 	unsigned int	color;
// 	t_image			*texture;

// 	y = rc->top_pixel;
// 	if (rc->w_or < 0 || rc->w_or > 3)
// 		return ;
// 	texture = data->textures.all[rc->w_or];
// 	if (texture == NULL)
// 		return ;
// 	text_x = init_text_x(rc, texture);
// 	y = rc->top_pixel;
// 	while (++y < rc->bttm_pixel)
// 	{
// 		text_y = set_text_y(rc, y, texture);
// 		color = get_text_pixel_color(texture, text_x, text_y);
// 		put_pixel_to_image(&data->screen, ray, y, color);
// 	}
// 	y = 0;
// 	while (++y < rc->top_pixel)
// 		put_pixel_to_image(&data->screen, ray, y, rgb_to_int(data->ceiling));
// 	y = rc->bttm_pixel;
// 	while (++y < WIN_HEIGHT)
// 		put_pixel_to_image(&data->screen, ray, y, rgb_to_int(data->floor));
// }

static void	draw_wall_strip(t_data *data, t_rc *rc, int ray, int text_x)
{
	int		y;
	int		text_y;
	int		color;
	t_image	*texture;

	texture = data->textures.all[rc->w_or];
	y = rc->top_pixel;
	while (++y < rc->bttm_pixel)
	{
		text_y = set_text_y(rc, y, texture);
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
	while (++y < rc->top_pixel)
		put_pixel_to_image(&data->screen, ray, y, color);
}

static void	draw_floor(t_data *data, t_rc *rc, int ray)
{
	int	y;
	int	color;

	y = rc->bttm_pixel;
	color = rgb_to_int(data->floor);
	while (++y < WIN_HEIGHT)
		put_pixel_to_image(&data->screen, ray, y, color);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_columns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:22:28 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/23 14:57:30 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	init_text_x(t_rc *rc)
{
	int	texture;

	texture = (int)(rc->impact_x * TILE_SIZE);
	if (texture < 0)
		texture = 0;
	if (texture >= TILE_SIZE)
		texture = TILE_SIZE - 1;
	return (texture);
}

static int	set_text_y(t_rc *rc, int y)
{
	int	texture;

	texture = (int)(((float)(y - rc->top_pixel) / rc->pr_hght) * TILE_SIZE);
	if (texture < 0)
		texture = 0;
	if (texture >= TILE_SIZE)
		texture = TILE_SIZE - 1;
	return (texture);
}

void	draw_column(t_data *data, t_rc *rc, int ray)
{
	int	y;
	int	text_x;
	int	text_y;
	int	color;

	text_x = init_text_x(rc);
	y = rc->top_pixel;
	while (y < rc->bttm_pixel)
	{
		text_y = set_text_y(rc, y);
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, ray, y, color);
		y++;
	}
	y = 0;
	while (y < rc->top_pixel)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, ray, y, rgb_to_int(data->ceiling));
		y++;
	}
	y = rc->bttm_pixel;
	while (y < WIN_HEIGHT)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, ray, y, rgb_to_int(data->floor));
		y++;
	}
}

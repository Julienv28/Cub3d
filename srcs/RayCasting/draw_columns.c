/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_columns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:22:28 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/23 15:49:42 by juvitry          ###   ########.fr       */
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

unsigned int	get_text_pixel_color(t_image *img, int x, int y)
{
	char			*pixel;
	unsigned int	color;

	if (x < 0 || x >= img->x || y < 0 || y >= img->y)
		return (0xFF00FF);
	pixel = img->data_addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

int	rgb_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = color.r;
	g = color.g;
	b = color.b;
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	draw_column(t_data *data, t_rc *rc, int ray)
{
	int				y;
	int				text_x;
	int				text_y;
	unsigned int	color;
	t_image			*texture;

	text_x = init_text_x(rc);
	y = rc->top_pixel;
	texture = data->textures.all[rc->w_or];
	while (y < rc->bttm_pixel)
	{
		text_y = set_text_y(rc, y);
		color = get_text_pixel_color(texture, text_x, text_y);
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

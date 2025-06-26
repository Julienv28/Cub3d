/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_columns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:22:28 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/26 10:46:24 by juvitry          ###   ########.fr       */
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

void	put_pixel_to_image(t_image *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= img->x || y < 0 || y >= img->y)
		return ;
	dst = img->data_addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
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
	if (rc->w_or < 0 || rc->w_or > 3)
		return ;
	texture = data->textures.all[rc->w_or];
	if (texture == NULL)
		return ;
	while (y < rc->bttm_pixel)
	{
		text_y = set_text_y(rc, y);
		color = get_text_pixel_color(texture, text_x, text_y);
		put_pixel_to_image(&data->screen, ray, y, color);
		y++;
	}
	y = 0;
	while (y < rc->top_pixel)
	{
		put_pixel_to_image(&data->screen, ray, y, rgb_to_int(data->ceiling));
		y++;
	}
	y = rc->bttm_pixel;
	while (y < WIN_HEIGHT)
	{
		put_pixel_to_image(&data->screen, ray, y, rgb_to_int(data->floor));
		y++;
	}
}

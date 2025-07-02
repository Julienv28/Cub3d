/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_columns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:04:04 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/02 11:29:13 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_wall_column(t_data *data, t_image *texture, t_wall_draw wall)
{
	int				y;
	int				text_y;
	unsigned int	color;

	y = wall.draw_start;
	while (y < wall.draw_end)
	{
		text_y = (int)wall.tex_pos;
		if (text_y < 0)
			text_y = 0;
		if (text_y >= texture->y)
			text_y = texture->y - 1;
		color = get_text_pixel_color(texture, wall.text_x, text_y);
		put_pixel_to_image(&data->screen, wall.ray, y, color);
		wall.tex_pos += wall.step;
		y++;
	}
}

void	draw_wall_strip(t_data *data, t_rc *rc, int ray, int text_x)
{
	t_image		*texture;
	t_wall_draw	wall;

	texture = data->textures.all[rc->w_or];
	if (!texture)
		return ;
	wall.wall_height = rc->pr_hght;
	wall.step = (float)texture->y / wall.wall_height;
	wall.draw_start = rc->top_pixel;
	wall.draw_end = rc->bttm_pixel;
	wall.tex_pos = 0.0f;
	if (wall.draw_start < 0)
		wall.tex_pos = -wall.draw_start * wall.step;
	if (wall.draw_start < 0)
		wall.draw_start = 0;
	if (wall.draw_end > WIN_HEIGHT)
		wall.draw_end = WIN_HEIGHT;
	wall.ray = ray;
	wall.text_x = text_x;
	draw_wall_column(data, texture, wall);
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

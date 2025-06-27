/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:59:53 by opique            #+#    #+#             */
/*   Updated: 2025/06/27 11:01:27 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	put_pixel(t_data *data, int x, int y)
{
	char	*dst;

	if (!data->minimap.addr)
		return ;
	if (x < 0 || x >= WIN_LEN || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = data->minimap.addr + (y * data->minimap.line_length
			+ x * (data->minimap.bits_per_pixel / 8));
	*(unsigned int *)dst = data->minimap.color;
}

void	draw_player_minimap(t_data *data, int px, int py, int radius)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			dx = px + x;
			dy = py + y;
			if (x * x + y * y <= radius * radius)
				put_pixel(data, dx, dy);
			x++;
		}
		y++;
	}
}

static void	draw_map_minimap(t_data *data, int start_x, int start_y, int size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_pixel(data, start_x + x, start_y + y);
			x++;
		}
		y++;
	}
}

int	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	px;
	int	py;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (x < (int)ft_strlen(data->map.map[y])
				&& data->map.map[y][x] == '1')
				data->minimap.color = 0x000000;
			else
				data->minimap.color = 0xFFFFFF;
			draw_map_minimap(data, x * MINMAP_BOX, y * MINMAP_BOX, MINMAP_BOX);
			x++;
		}
		y++;
	}
	data->minimap.color = 0xFF0000;
	px = (int)(data->map.play.x * MINMAP_BOX);
	py = (int)(data->map.play.y * MINMAP_BOX);
	draw_player_minimap(data, px, py, 5);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->minimap.img_ptr, 0, 0);
	return (0);
}

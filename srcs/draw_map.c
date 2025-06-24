/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:00:19 by opique            #+#    #+#             */
/*   Updated: 2025/06/24 17:19:49 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_textures(t_data *data)
{
	void	*mlx;

	mlx = data->mlx_ptr;
	data->textures.no = ft_new_img(mlx, data->textures.no_xpm, data, NORTH);
	data->textures.so = ft_new_img(mlx, data->textures.so_xpm, data, SOUTH);
	data->textures.ea = ft_new_img(mlx, data->textures.ea_xpm, data, EAST);
	data->textures.we = ft_new_img(mlx, data->textures.we_xpm, data, WEST);
}

void	print_textures_for_player(t_data *data, char c, int x, int y)
{
	void	*img_ptr;

	img_ptr = NULL;
	if (c == 'N')
		img_ptr = data->textures.no.xpm_ptr;
	else if (c == 'S')
		img_ptr = data->textures.so.xpm_ptr;
	else if (c == 'E')
		img_ptr = data->textures.ea.xpm_ptr;
	else if (c == 'W')
		img_ptr = data->textures.we.xpm_ptr;
	if (img_ptr)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_ptr, x * TILE_SIZE, y * TILE_SIZE);
}

void	draw_map(t_data *data)
{
	int		x;
	int		y;
	t_map	*map;
	char	c;

	map = &data->map;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->map[y][x];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				print_textures_for_player(data, c, x, y);
			x++;
		}
		y++;
	}
}

void put_pixel(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIN_LEN || y < 0 || y >= WIN_HEIGHT)
        return;

    dst = data->minimap.addr + (y * data->minimap.line_length + x * (data->minimap.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


void	draw_rect(t_data *data, int start_x, int start_y, int size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_pixel(data, start_x + x, start_y + y, 0x00FFFF);
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
	int	dy;
	int	dx;
	int	color;

	y = 0;
	data->minimap.img_ptr = mlx_new_image(data->mlx_ptr, data->map.width * MINIMAP_SCALE, data->map.height * MINIMAP_SCALE);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img_ptr, &data->minimap.bits_per_pixel,
                                      &data->minimap.line_length, &data->minimap.endian);
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.map[y][x] == '1')
				color = 0x000000;
			else
				color = 0xFFFFFF;
			draw_rect(data, x * MINIMAP_SCALE, y * MINIMAP_SCALE, MINIMAP_SCALE);
			x++;
		}
		y++;
	}
	// Dessiner le joueur sur la minimap
	px = (int)(data->map.play.x * MINIMAP_SCALE);
	py = (int)(data->map.play.y * MINIMAP_SCALE);
	//draw_circle(data, px, py, 5, 0xFF0000);
	// Dessiner direction joueur (ligne devant joueur)
	dx = (int)(cosf(data->map.play.angle) * 15);
	dy = (int)(-sinf(data->map.play.angle) * 15);
	//draw_line(data, px, py, px + dx, py + dy, 0xFF0000);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->minimap.img_ptr, 0, 0);
	return (0);
}

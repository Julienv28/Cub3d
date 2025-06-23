/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:00:19 by opique            #+#    #+#             */
/*   Updated: 2025/06/23 15:10:44 by opique           ###   ########.fr       */
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
	void *img_ptr;

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

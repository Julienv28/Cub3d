/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:33:44 by opique            #+#    #+#             */
/*   Updated: 2025/06/30 15:13:51 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	count_cell(char cell, t_map *map)
{
	if (cell == 'N')
		map->north++;
	else if (cell == 'S')
		map->south++;
	else if (cell == 'E')
		map->east++;
	else if (cell == 'W')
		map->west++;
}

void	count_elements(t_map *map)
{
	int		y;
	int		x;
	int		len;

	map->east = 0;
	map->north = 0;
	map->south = 0;
	map->west = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		len = ft_strlen(map->map[y]);
		while (x < len)
		{
			count_cell(map->map[y][x], map);
			x++;
		}
		y++;
	}
}

int	cub_extansion(char *filename)
{
	int		len;
	int		res;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	res = ft_strcmp(filename + len - 4, ".cub");
	if (res == 0)
		return (1);
	else
		return (0);
}	

void	replace_spaces_by_walls(t_map *map)
{
	int	y;
	int	x;
	int	line_len;

	y = 0;
	while (y < map->height)
	{
		line_len = ft_strlen(map->map[y]);
		x = 0;
		while (x < line_len)
		{
			if (map->map[y][x] == ' ' || map->map[y][x] == '\t')
				map->map[y][x] = '1';
			x++;
		}
		y++;
	}
}

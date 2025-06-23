/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:33:44 by opique            #+#    #+#             */
/*   Updated: 2025/06/20 15:18:48 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	count_elements(t_map *map)
{
	int		y;
	int		x;
	char	cell;

    map->east = 0;
	map->north = 0;
	map->south = 0;
	map->west = 0;
    y = 0;
	while (y < map->height)
	{
        x = 0;
		while (x < map->width)
		{
            cell = map->map[y][x];
			if (cell == 'N')
				map->north++;
			else if (cell == 'S')
				map->south++;
			else if (cell == 'E')
				map->east++;
			else if (cell == 'W')
				map->west++;
            x++;
		}
        y++;
	}
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i] != NULL)
	{
		printf("%s\n", map[i]);
		i++;
	}
}

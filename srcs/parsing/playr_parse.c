/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playr_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:31:36 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/19 14:38:20 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parse_player(t_map *map)
{
	int		x;
	int		y;
	char	**maps;

	maps = map->map;
	y = 0;
	while (maps[y])
	{
		x = 0;
		while (maps[y][x])
		{
			if (maps[y][x] == 'N' || maps[y][x] == 'S' || maps[y][x] == 'E'
				|| maps[y][x] == 'W')
			{
				map->play->x = (float)x;
				map->play->y = (float)y;
				break ;
			}
			x++;
		}
		y++;
	}
}

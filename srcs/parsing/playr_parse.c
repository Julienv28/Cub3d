/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playr_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:31:36 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/20 14:11:55 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//fonction d'initialisation, il faudra ensuite faire un update au fur et a
// mesure du jeu aavec la fonction mlx_loop(); on verra ca apres.
static void	init_player_pos(char c, t_map *map)
{
	if (c == 'N')
		map->play->orientation = NORTH;
	if (c == 'S')
		map->play->orientation = SOUTH;
	if (c == 'E')
		map->play->orientation = EAST;
	if (c == 'W')
		map->play->orientation = WEST;
}

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
				init_player_pos(maps[x][y], map);
				break ;
			}
			x++;
		}
		y++;
	}
}

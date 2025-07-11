/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playr_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:31:36 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/01 17:33:46 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_player_pos(char c, t_map *map)
{
	if (c == 'N')
		map->play.orientation = NORTH;
	else if (c == 'S')
		map->play.orientation = SOUTH;
	else if (c == 'E')
		map->play.orientation = EAST;
	else if (c == 'W')
		map->play.orientation = WEST;
}

void	set_player_angle(t_position *play)
{
	if (play->orientation == NORTH)
		play->angle = 3 * M_PI_2;
	else if (play->orientation == SOUTH)
		play->angle = M_PI_2;
	else if (play->orientation == EAST)
		play->angle = 0;
	else if (play->orientation == WEST)
		play->angle = M_PI;
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
				map->play.x = (float)x;
				map->play.y = (float)y;
				init_player_pos(maps[y][x], map);
				set_player_angle(&map->play);
				map->play.fov = M_PI / 3;
				break ;
			}
			x++;
		}
		y++;
	}
}

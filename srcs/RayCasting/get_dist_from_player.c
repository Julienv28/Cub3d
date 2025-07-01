/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dist_from_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:58:36 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/01 10:38:01 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	get_dist_from_player(t_map *map, float rayAngle, t_rc *rc)
{
	t_cast	cast;
	t_dda	dda;
	int		side;

	init_ray_data(map, rayAngle, &cast, &dda);
	run_dda(map, &dda, &side);
	if (side == 0)
		cast.distance = dda.side_d_x - dda.delta_d_x;
	else
		cast.distance = dda.side_d_y - dda.delta_d_y;
	if (side == 0)
		rc->w_or = get_w_or(cast.dx, 0);
	else
		rc->w_or = get_w_or(0, cast.dy);
	rc->impact_x = get_impact_x(map->play.x + cast.distance * cast.dx,
			map->play.y + cast.distance * cast.dy, rc->w_or);
	return (cast.distance);
}

/*
float get_dist_from_player(t_map *map, float rayAngle, t_rc *rc)
{
	t_cast cast;
	int hit = 0;
	int map_x, map_y;
	int stepX, stepY;
	float delta_d_x, delta_d_y;
	float sideDistX, sideDistY;
	float posX = map->play.x;
	float posY = map->play.y;
	int	side;

	cast.dx = cosf(rayAngle);
	cast.dy = sinf(rayAngle);
	map_x = (int)posX;
	map_y = (int)posY;
	delta_d_x = fabsf(1 / cast.dx);
	delta_d_y = fabsf(1 / cast.dy);

	if (cast.dx < 0)
	{
		stepX = -1;
		sideDistX = (posX - map_x) * delta_d_x;
	}
	else
	{
		stepX = 1;
		sideDistX = (map_x + 1.0f - posX) * delta_d_x;
	}
	if (cast.dy < 0)
	{
		stepY = -1;
		sideDistY = (posY - map_y) * delta_d_y;
	}
	else
	{
		stepY = 1;
		sideDistY = (map_y + 1.0f - posY) * delta_d_y;
	}
	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += delta_d_x;
			map_x += stepX;
			side = 0;
		}
		else
		{
			sideDistY += delta_d_y;
			map_y += stepY;
			side = 1;
		}
		if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
			return (FLT_MAX);
		if (map->map[map_y][map_x] == '1')
			hit = 1;
	}
	if (side == 0)
		cast.distance = sideDistX - delta_d_x;
	else
		cast.distance = sideDistY - delta_d_y;
	rc->w_or = get_w_or((side == 0) ? cast.dx : 0, (side == 1) ? cast.dy : 0);
	rc->impact_x = get_impact_x(posX + cast.distance * cast.dx,
			posY + cast.distance * cast.dy,
			rc->w_or);
	return (cast.distance);
}*/

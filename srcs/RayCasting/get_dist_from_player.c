/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dist_from_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:58:36 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/30 12:52:56 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float get_dist_from_player(t_map *map, float rayAngle, t_rc *rc)
{
	t_cast cast;
	int hit = 0;
	int mapX, mapY;
	int stepX, stepY;
	float deltaDistX, deltaDistY;
	float sideDistX, sideDistY;
	float posX = map->play.x;
	float posY = map->play.y;

	// Direction du rayon
	cast.dx = cosf(rayAngle);
	cast.dy = sinf(rayAngle);
	// Case actuelle
	mapX = (int)posX;
	mapY = (int)posY;
	// Delta distances
	deltaDistX = fabsf(1 / cast.dx);
	deltaDistY = fabsf(1 / cast.dy);
	// Initialisation des pas et distances initiales
	if (cast.dx < 0)
	{
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0f - posX) * deltaDistX;
	}
	if (cast.dy < 0)
	{
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0f - posY) * deltaDistY;
	}
	int side; // 0 = X hit, 1 = Y hit
	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (mapX < 0 || mapX >= map->width || mapY < 0 || mapY >= map->height)
			return FLT_MAX;
		if (map->map[mapY][mapX] == '1')
			hit = 1;
	}
	// Calcul de la distance
	if (side == 0)
		cast.distance = sideDistX - deltaDistX;
	else
		cast.distance = sideDistY - deltaDistY;
	// Détermination de la direction du mur touché
	rc->w_or = get_w_or((side == 0) ? cast.dx : 0, (side == 1) ? cast.dy : 0);
	// Coordonnées d'impact
	rc->impact_x = get_impact_x(
		posX + cast.distance * cast.dx,
		posY + cast.distance * cast.dy,
		rc->w_or);
	return cast.distance;
}

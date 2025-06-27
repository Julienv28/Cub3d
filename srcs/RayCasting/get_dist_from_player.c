/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dist_from_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:58:36 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/27 11:20:00 by juvitry          ###   ########.fr       */
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

// static void	init_ray_values(t_cast *cast, t_map *map, float rayAngle,
// 			float *sideDistX, float *sideDistY)
// {
// 	float	posX = map->play.x;
// 	float	posY = map->play.y;
// 	int		mapX = (int)posX;
// 	int		mapY = (int)posY;

// 	cast->dx = cosf(rayAngle);
// 	cast->dy = sinf(rayAngle);
// 	cast->mapX = mapX;
// 	cast->mapY = mapY;
// 	cast->deltaX = fabsf(1 / cast->dx);
// 	cast->deltaY = fabsf(1 / cast->dy);
// 	if (cast->dx < 0)
// 	{
// 		cast->stepX = -1;
// 		*sideDistX = (posX - mapX) * cast->deltaX;
// 	}
// 	else
// 	{
// 		cast->stepX = 1;
// 		*sideDistX = (mapX + 1.0f - posX) * cast->deltaX;
// 	}
// 	if (cast->dy < 0)
// 	{
// 		cast->stepY = -1;
// 		*sideDistY = (posY - mapY) * cast->deltaY;
// 	}
// 	else
// 	{
// 		cast->stepY = 1;
// 		*sideDistY = (mapY + 1.0f - posY) * cast->deltaY;
// 	}
// }

// static void	perform_dda(t_map *map, t_cast *cast,
// 			float *sideDistX, float *sideDistY, int *side)
// {
// 	int	hit = 0;

// 	while (!hit)
// 	{
// 		if (*sideDistX < *sideDistY)
// 		{
// 			*sideDistX += cast->deltaX;
// 			cast->mapX += cast->stepX;
// 			*side = 0;
// 		}
// 		else
// 		{
// 			*sideDistY += cast->deltaY;
// 			cast->mapY += cast->stepY;
// 			*side = 1;
// 		}
// 		if (cast->mapX < 0 || cast->mapX >= map->width
// 			|| cast->mapY < 0 || cast->mapY >= map->height)
// 			break ;
// 		if (map->map[cast->mapY][cast->mapX] == '1')
// 			hit = 1;
// 	}
// }

// static void	finalize_ray_data(t_cast *cast, t_rc *rc, float posX, float posY, int side)
// {
// 	if (side == 0)
// 		cast->distance = (cast->mapX - (int)posX + (1 - cast->stepX) / 2) / cast->dx;
// 	else
// 		cast->distance = (cast->mapY - (int)posY + (1 - cast->stepY) / 2) / cast->dy;
// 	rc->w_or = get_w_or((side == 0) ? cast->dx : 0, (side == 1) ? cast->dy : 0);
// 	rc->impact_x = get_impact_x(
// 		posX + cast->distance * cast->dx,
// 		posY + cast->distance * cast->dy,
// 		rc->w_or);
// }

// float	get_dist_from_player(t_map *map, float rayAngle, t_rc *rc)
// {
// 	t_cast	cast;
// 	float	sidedistx;
// 	float	sidedisty;
// 	int		side;
// 	float	posx;
// 	float	posy;

// 	posx = map->play.x;
// 	posy = map->play.y;
// 	init_ray_values(&cast, map, rayAngle, &sidedistx, &sidedisty);
// 	perform_dda(map, &cast, &sidedistx, &sidedisty, &side);
// 	finalize_ray_data(&cast, rc, posx, posy, side);
// 	// printf("Ray %f hit at (%d, %d)\n", rayAngle, cast.mapX, cast.mapY);
// 	return (cast.distance);
// }

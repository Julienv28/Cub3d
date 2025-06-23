/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:06:25 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/23 11:53:51 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

static t_cast	*init_val_cast(t_cast *cast, t_map *map, float rayAngle)
{
	cast = malloc(sizeof(t_cast));
	if (!cast)
		return (NULL);
	cast->dx = cosf(rayAngle);
	cast->dy = sinf(rayAngle);
	cast->rayx = map->play->x;
	cast->distance = 0.0f;
	cast->rayy = map->play->y;
	cast->stepsize = 0.05f;
	return (cast);
}

float	get_dist_from_player(t_map *map, float rayAngle)
{
	t_cast	*cast;
	int		mapx;
	int		mapy;
	float	distance;

	cast = init_val_cast(cast, map, rayAngle);
	if (cast == NULL)
		return (0);
	while (cast->distance < 20.0f)
	{
		cast->rayx += cast->dx * cast->stepsize;
		cast->rayy += cast->dy * cast->stepsize;
		cast->distance += cast->stepsize;
		mapx = (int)cast->rayx;
		mapy = (int)cast->rayy;
		if (mapx < 0 || mapx >= map->width || mapy < 0 || mapy >= map->height)
			return (free(cast), FLT_MAX);
		if (map->map[mapy][mapx] == '1')
		{
			distance = cast->distance;
			return (free(cast), distance);
		}
	}
	return (free(cast), FLT_MAX);
}

float	*init_distaces(t_map *map)
{
	float	playerangle;
	float	rayangle;
	float	*distances;
	int		constante;
	int		ray;
	float	projected_height;
	int		top_pixel;
	int		bottom_pixel;

	ray = 0;
	distances = ft_calloc(sizeof(float), NUM_RAYS); // ATTENTION IL EST PAS FREE !
	playerangle = M_PI / 2;
	constante = WIN_HEIGHT * TILE_SIZE;
	while (ray < NUM_RAYS)
	{
		rayangle = playerangle - (map->play->fov / 2)
			+ (map->play->fov / NUM_RAYS) * ray;
		distances[ray] = get_dist_from_player(map, rayangle);
		distances[ray] *= cosf(rayangle - playerangle); //correctif de vision et eviter l'effet fish-eye
		if (distances[ray] == 0)
			distances[ray] = 0.0001;
		projected_height = constante / distances[ray];
		top_pixel = (WIN_HEIGHT / 2) - (projected_height / 2);
		bottom_pixel = (WIN_HEIGHT / 2) + (projected_height / 2);
		if (top_pixel < 0)
			top_pixel = 0;
		if (bottom_pixel > WIN_HEIGHT)
			bottom_pixel = WIN_HEIGHT;
		ray++;
	}
	return (distances);
}

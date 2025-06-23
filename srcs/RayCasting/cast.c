/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:06:25 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/23 12:55:06 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_cast	*init_val_cast(t_cast *cast, t_map *map, float rayAngle)
{
	cast = malloc(sizeof(t_cast));
	if (!cast)
		return (NULL);
	cast->dx = cosf(rayAngle);
	cast->dy = sinf(rayAngle);
	cast->rayx = map->play->x;
	cast->rayy = map->play->y;
	cast->stepsize = 0.05f;
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
	distance = 0.0f;
	while (cast->distance < 20.0f)
	{
		cast->rayx += cast->dx * cast->stepsize;
		cast->rayy += cast->dy * cast->stepsize;
		cast->distance += cast->stepsize;
		mapx = (int)cast->rayx;
		mapy = (int)cast->rayy;
		if (mapx < 0 || mapx >= map->width || mapy < 0 || mapy >= map->height)
			return (free(cast), FLT_MAX);
		if (map->map[mapy][mapx] == 1)
			return (free(cast), distance);
	}
	return (free(cast), FLT_MAX);
}

float	*init_distaces(t_map *map)
{
	float	playerangle;
	float	rayangle;
	float	*distances;
	int		i;

	i = 0;
	distances = ft_calloc(sizeof(float), NUM_RAYS); // ATTENTION IL EST PAS FREE !
	playerangle = M_PI / 2;
	while (i < NUM_RAYS)
	{
		rayangle = playerangle - (map->play->fov / 2)
			+ (map->play->fov / NUM_RAYS) * i;
		distances[i] = get_dist_from_player(map, rayangle);
		distances[i] *= cosf(rayangle - playerangle); //correctif de vision et eviter l'effet fish-eye
		i++;
	}
	return (distances);
}

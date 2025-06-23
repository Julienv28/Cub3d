/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:06:25 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/23 14:57:27 by juvitry          ###   ########.fr       */
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
	cast->distance = 0.0f;
	cast->rayy = map->play->y;
	cast->stepsize = 0.05f;
	return (cast);
}

float	get_dist_from_player(t_map *map, float rayAngle, t_rc *rc)
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
			rc->w_or = get_w_or(cast->dx, cast->dy);
			rc->impact_x = get_impact_x(cast->rayx, cast->rayy, rc->w_or);
			return (free(cast), distance);
		}
	}
	return (free(cast), FLT_MAX);
}

void	render_game(t_data *data)
{
	float	playerangle;
	float	rayangle;
	t_rc	*rc;
	int		ray;

	rc = malloc(sizeof(t_rc));
	if (!rc)
		return ;
	ray = 0;
	playerangle = data->map.play->angle;
	rc->constante = WIN_HEIGHT * TILE_SIZE;
	while (ray < NUM_RAYS)
	{
		rayangle = playerangle - (data->map.play->fov / 2)
			+ (data->map.play->fov / NUM_RAYS) * ray;
		rc->distance = get_dist_from_player(&data->map, rayangle, rc);
		rc->distance *= cosf(rayangle - playerangle);
		if (rc->distance == 0)
			rc->distance = 0.0001;
		rc->pr_hght = rc->constante / rc->distance;
		rc->top_pixel = (WIN_HEIGHT / 2) - (rc->pr_hght / 2);
		rc->bttm_pixel = (WIN_HEIGHT / 2) + (rc->pr_hght / 2);
		if (rc->top_pixel < 0)
			rc->top_pixel = 0;
		if (rc->bttm_pixel > WIN_HEIGHT)
			rc->bttm_pixel = WIN_HEIGHT;
		ray++;
	}
}

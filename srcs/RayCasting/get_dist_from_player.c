/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dist_from_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:58:36 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/01 17:42:11 by juvitry          ###   ########.fr       */
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
	if (side == -1)
		return (FLT_MAX);
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

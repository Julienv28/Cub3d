/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:26:24 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/01 15:34:49 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_ray_dir(t_cast *cast, float ray_angle)
{
	cast->dx = cosf(ray_angle);
	cast->dy = sinf(ray_angle);
}

static void	init_dda_base(t_map *map, t_cast *cast, t_dda *dda)
{
	dda->map_x = (int)map->play.x;
	dda->map_y = (int)map->play.y;
	if (cast->dx == 0 || cast->dy == 0)
		return ;
	dda->delta_d_x = fabsf(1.0f / cast->dx);
	dda->delta_d_y = fabsf(1.0f / cast->dy);
}

static void	init_dda_step_x(t_map *map, t_cast *cast, t_dda *dda)
{
	if (cast->dx < 0)
	{
		dda->step_x = -1;
		dda->side_d_x = (map->play.x - dda->map_x) * dda->delta_d_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_d_x = (dda->map_x + 1.0f - map->play.x) * dda->delta_d_x;
	}
}

static void	init_dda_step_y(t_map *map, t_cast *cast, t_dda *dda)
{
	if (cast->dy < 0)
	{
		dda->step_y = -1;
		dda->side_d_y = (map->play.y - dda->map_y) * dda->delta_d_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_d_y = (dda->map_y + 1.0f - map->play.y) * dda->delta_d_y;
	}
}

void	init_ray_data(t_map *map, float ray_angle, t_cast *cast, t_dda *dda)
{
	init_ray_dir(cast, ray_angle);
	init_dda_base(map, cast, dda);
	init_dda_step_x(map, cast, dda);
	init_dda_step_y(map, cast, dda);
}

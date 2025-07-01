/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:26:20 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/01 10:37:26 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_out_of_bounds(t_map *map, t_dda *dda)
{
	if (dda->map_x < 0)
		return (1);
	if (dda->map_x >= map->width)
		return (1);
	if (dda->map_y < 0)
		return (1);
	if (dda->map_y >= map->height)
		return (1);
	return (0);
}

static void	step_dda(t_dda *dda, int *side)
{
	if (dda->side_d_x < dda->side_d_y)
	{
		dda->side_d_x += dda->delta_d_x;
		dda->map_x += dda->step_x;
		*side = 0;
	}
	else
	{
		dda->side_d_y += dda->delta_d_y;
		dda->map_y += dda->step_y;
		*side = 1;
	}
}

void	run_dda(t_map *map, t_dda *dda, int *side)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		step_dda(dda, side);
		if (is_out_of_bounds(map, dda))
		{
			*side = -1;
			return ;
		}
		if (map->map[dda->map_y][dda->map_x] == '1')
			hit = 1;
	}
}

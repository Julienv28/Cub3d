/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:40 by opique            #+#    #+#             */
/*   Updated: 2025/06/18 16:33:27 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_map(t_map *map)
{
	int	total_positions;

	count_elements(map);
    total_positions = map->north + map->south + map->east + map->west;
	if (total_positions != 1)
	{
		ft_putstr_fd("Error: plus d'une position de joueur sur la carte\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

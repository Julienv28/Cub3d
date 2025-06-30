/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:00:11 by opique            #+#    #+#             */
/*   Updated: 2025/06/30 15:02:43 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_sides(t_map *map)
{
	int		y;
	char	*line;

	y = 1;
	while (y < map->height - 1)
	{
		line = map->map[y];
		if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
		{
			ft_putstr_fd("Error: map not closed (sides).\n", STDERR_FILENO);
			return (0);
		}
		y++;
	}
	return (1);
}

int	check_top_and_bottom(t_map *map)
{
	int		x;
	char	*line;

	line = map->map[0];
	x = 0;
	while (line[x])
	{
		if (line[x] != '1')
			return (ft_putstr_fd("Error: map not closed.\n", STDERR_FILENO), 0);
		x++;
	}
	line = map->map[map->height - 1];
	x = 0;
	while (line[x])
	{
		if (line[x] != '1')
		{
			ft_putstr_fd("Error: map not closed.\n", STDERR_FILENO);
			return (0);
		}
		x++;
	}
	return (1);
}

int	check_wall(t_map *map)
{
	if (!check_top_and_bottom(map))
		return (0);
	if (!check_sides(map))
		return (0);
	return (1);
}

int	check_map(t_map *map)
{
	int	total_positions;

	count_elements(map);
	total_positions = map->north + map->south + map->east + map->west;
	if (total_positions != 1)
	{
		ft_putstr_fd("Error: plus d'une position de joueur sur la carte\n", \
			STDERR_FILENO);
		return (0);
	}
	return (1);
}

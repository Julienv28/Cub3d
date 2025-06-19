/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:40 by opique            #+#    #+#             */
/*   Updated: 2025/06/19 13:03:49 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// La 1er et dernier ligne dovent etre 1 
// Sinon 1e et dernier caractere de la ligne doivent etre 1
int	check_wall(t_map *map)
{
	int		x;
	int		y;
	char	*line;

	line = map->map[0];
	x = 0;
	while (line[x])
	{
		if (line[x] != '1')
		{
			ft_putstr_fd("Error: map non fermer.\n", STDERR_FILENO);
			return (0);
		}
		x++;
	}
	line = map->map[map->height - 1];
	x = 0;
	while (line[x])
	{
		if (line[x] != '1')
		{
			ft_putstr_fd("Error: map non fermer.\n", STDERR_FILENO);
			return (0);
		}
		x++;
	}
	y = 1;
	while (y < map->height - 1)
	{
		line = map->map[y];
		if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
		{
			ft_putstr_fd("Error: map non fermer.\n", STDERR_FILENO);
			return (0);
		}
		y++;
	}
	return (1);
}

void	replace_spaces_by_walls(t_map *map)
{
	int	y;
	int	x;
	int line_len;

	y = 0;
	while (y < map->height)
	{
        line_len = ft_strlen(map->map[y]);
        x = 0;
		while (x < line_len)
		{
			if (map->map[y][x] == ' ' || map->map[y][x] == '\t')
				map->map[y][x] = '1';
            x++;
		}
        y++;
	}
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
	replace_spaces_by_walls(map);
	if (!check_wall(map))
		return (0);
	return (1);
}

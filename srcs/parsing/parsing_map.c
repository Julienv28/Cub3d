/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:36:07 by opique            #+#    #+#             */
/*   Updated: 2025/06/23 10:12:10 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_param_map(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

char	**add_line_to_map(t_map *map, char *line)
{
	char	**new_map;
	int		line_len;

    line_len = ft_strlen(line);
	if (map->width < line_len)
        map->width = line_len;
	new_map = realloc(map->map, sizeof(char *) * (map->height + 2));
	if (!new_map)
		return (free(map->map), NULL);
    map->map = new_map;
    map->map[map->height] = ft_strdup(line);
	if (!map->map[map->height])
		return (free(map->map), NULL);
    map->height++;
    map->map[map->height] = NULL;
	return (map->map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:37:49 by opique            #+#    #+#             */
/*   Updated: 2025/06/19 13:05:25 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->map.map = NULL;
}

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}

char	**init_map(int fd, t_data *data, t_map *map)
{
	char	*line;
	int		len;

	map->height = 0;
	map->width = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (is_param_line(line, data))
			printf("Paramètre line détecté : %s\n", line);
		else if (is_param_map(line))
		{
			if (!add_line_to_map(map, line))
				return (free(line), NULL);
		}
		else
		{
			ft_putstr_fd("Error: caractere non valide map\n", STDERR_FILENO);
			free(line);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (map->map);
}

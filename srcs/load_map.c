/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:27:08 by opique            #+#    #+#             */
/*   Updated: 2025/06/30 15:28:51 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

char	*load_param(int fd, t_data *data)
{
	char	*line;
	int		len;

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
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		return (line);
	}
	return (NULL);
}

char	**load_map(int fd, t_map *map, char *first_line)
{
	char	*line;
	int		len;

	map->height = 0;
	map->width = 0;
	line = first_line;
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
		if (!is_param_map(line))
		{
			if (is_param_prefix_only(line))
				ft_putstr_fd("Error: map mal placee\n", STDERR_FILENO);
			else
				ft_putstr_fd("Error: car non valid\n", STDERR_FILENO);
			return (free(line), NULL);
		}
		if (!add_line_to_map(map, line))
			return (free_map(map->map, map->height), free(line), NULL);
		free(line);
		line = get_next_line(fd);
	}
	return (map->map);
}

int	load_map_and_param(char **av, t_data *data, t_map *map)
{
	int		fd;
	char	*first_line;

	if (!cub_extansion(av[1]))
		return (ft_putstr_fd("Error: bad extansion\n", STDERR_FILENO), 0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error: ouverture map"), 0);
	first_line = load_param(fd, data);
	if (!first_line)
	{
		ft_putstr_fd("Error: missing map\n", STDERR_FILENO);
		on_destroy(data);
		return (close(fd), 0);
	}
	if (!load_map(fd, map, first_line))
		return (close(fd), on_destroy(data), 0);
	close(fd);
	if (!check_all(data, map))
		on_destroy(data);
	return (1);
}

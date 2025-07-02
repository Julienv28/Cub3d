/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:27:08 by opique            #+#    #+#             */
/*   Updated: 2025/07/02 12:08:48 by opique           ###   ########.fr       */
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

	line = get_next_line(fd, &data->buffer);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd, &data->buffer);
			continue ;
		}
		if (is_param_line(line, data))
		{
			free(line);
			line = get_next_line(fd, &data->buffer);
			continue ;
		}
		return (line);
	}
	return (NULL);
}

static int	process_map_line(t_map *map, char *line, t_data *data)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (is_empty_line(line))
		return (free(line), 1);
	if (!is_param_map(line))
	{
		if (is_param_prefix_only(line))
			ft_putstr_fd("Error\nmap mal placee.\n", STDERR_FILENO);
		else
			ft_putstr_fd("Error\ncaractere invalid.\n", STDERR_FILENO);
		free(line);
		free(data->buffer);
		ft_free_paths_textures(data);
		return (-1);
	}
	if (!add_line_to_map(map, line))
		return (free(line), free_map(map->map, map->height), -1);
	return (free(line), 0);
}

char	**load_map(int fd, t_map *map, char *first_line, t_data *data)
{
	char	*line;
	int		ret;

	map->height = 0;
	map->width = 0;
	line = first_line;
	while (line != NULL)
	{
		ret = process_map_line(map, line, data);
		if (ret == 1)
			line = get_next_line(fd, &data->buffer);
		else if (ret == -1)
			return (NULL);
		else
			line = get_next_line(fd, &data->buffer);
	}
	return (map->map);
}

int	load_map_and_param(char **av, t_data *data, t_map *map)
{
	int		fd;
	char	*first_line;

	data->buffer = NULL;
	if (!cub_extansion(av[1]))
		return (ft_putstr_fd("Error\nbad extansion\n", STDERR_FILENO), 0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\nouverture map."), 0);
	first_line = load_param(fd, data);
	if (!first_line)
	{
		ft_putstr_fd("Error\nmissing map\n", STDERR_FILENO);
		ft_free_paths_textures(data);
		on_destroy(data);
		return (free(data->buffer), close(fd), 0);
	}
	if (!load_map(fd, map, first_line, data))
		return (close(fd), on_destroy(data), 0);
	close(fd);
	free(data->buffer);
	if (!check_all(data, map))
		on_destroy(data);
	return (1);
}

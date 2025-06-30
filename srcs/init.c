/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:37:49 by opique            #+#    #+#             */
/*   Updated: 2025/06/30 16:44:18 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->map.map = NULL;
	data->textures.ea_check = 0;
	data->textures.no_check = 0;
	data->textures.so_check = 0;
	data->textures.we_check = 0;
	data->textures.no_xpm = NULL;
	data->textures.so_xpm = NULL;
	data->textures.we_xpm = NULL;
	data->textures.ea_xpm = NULL;
	data->textures.no.xpm_ptr = NULL;
	data->textures.so.xpm_ptr = NULL;
	data->textures.we.xpm_ptr = NULL;
	data->textures.ea.xpm_ptr = NULL;
	data->textures.no.data_addr = NULL;
	data->textures.so.data_addr = NULL;
	data->textures.we.data_addr = NULL;
	data->textures.ea.data_addr = NULL;
	data->check_c = 0;
	data->check_f = 0;
	data->mouse_locked = false;
	data->ignore_mouse_event = false;
	data->need_redraw = true;
	data->last_mouse_x = WIN_LEN / 2;
	data->map.play.x = 0;
	data->map.play.y = 0;
	data->map.play.angle = 0;
	data->map.play.fov = 0;
	data->map.play.orientation = 0;
	data->minimap.addr = NULL;
	data->minimap.bits_per_pixel = 0;
	data->minimap.endian = 0;
	data->minimap.img_ptr = NULL;
	data->minimap.line_length = 0;
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

char	**load_map(int fd, t_map *map, char *first_line,
		t_data *data)
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
			line = get_next_line(fd, &data->buffer);
			continue ;
		}
		if (!is_param_map(line))
		{
			if (is_param_prefix_only(line))
				ft_putstr_fd("Error: map mal placee\n", STDERR_FILENO);
			else
				ft_putstr_fd("Error: char non valid\n", STDERR_FILENO);
			ft_free_paths_textures(data);
			return (free(line), NULL);
		}
		if (!add_line_to_map(map, line))
		{
			free_map(map->map, map->height);
			return (free(line), NULL);
		}
		free(line);
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
		return (ft_putstr_fd("Error: bad extansion\n", STDERR_FILENO), 0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error: ouverture map"), 0);
	first_line = load_param(fd, data);
	if (!first_line)
	{
		ft_putstr_fd("Error: missing map\n", STDERR_FILENO);
		on_destroy(data);
		free(data->buffer);
		return (close(fd), 0);
	}
	if (!load_map(fd, map, first_line, data))
		return (close(fd), on_destroy(data), 0);
	close(fd);
	free(data->buffer);
	if (!check_all(data, map))
		on_destroy(data);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:52:27 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/01 09:54:08 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_and_check(char *line, char *id, char **texture, int *check)
{
	if (ft_strncmp(line, id, 2) == 0)
	{
		if (parse_texture(line, texture))
		{
			(*check)++;
			return (1);
		}
		return (0);
	}
	return (0);
}

int	is_param_prefix_only(char *line)
{
	if (!line)
		return (0);
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0)
		return (1);
	if (ft_strncmp(line, "SO", 2) == 0)
		return (1);
	if (ft_strncmp(line, "WE", 2) == 0)
		return (1);
	if (ft_strncmp(line, "EA", 2) == 0)
		return (1);
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\0'))
		return (1);
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\0'))
		return (1);
	return (0);
}

int	is_param_line(char *line, t_data *data)
{
	if (!line)
		return (0);
	while (*line == ' ')
		line++;
	if (is_texture_line(line, data))
		return (1);
	if (is_color_line(line, data))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd("Usage: ./cub3D map.cub\n", STDERR_FILENO), 1);
	init_data(&data);
	init_texture(&data);
	if (!load_map_and_param(av, &data, &data.map))
		return (1);
	parse_player(&data.map);
	ft_init_mlx(&data);
	init_hook_loop(&data);
	return (0);
}

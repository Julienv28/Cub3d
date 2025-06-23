/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:52:27 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/23 11:55:00 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_param_line(char *line, t_data *data)
{
	if (!line)
		return (0);
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		data->textures.no_check++;
		return (parse_texture(line, &data->textures.no_xpm));
	}
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		data->textures.so_check++;
		return (parse_texture(line, &data->textures.so_xpm));
	}
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		data->textures.we_check++;
		return (parse_texture(line, &data->textures.we_xpm));
	}
	if (ft_strncmp(line, "EA", 2) == 0)
	{
		data->textures.ea_check++;
		return (parse_texture(line, &data->textures.ea_xpm));
	}
	if (ft_strncmp(line, "F", 1) == 0)
	{
		data->check_f++;
		return (parse_color(line, &data->floor));
	}
	if (ft_strncmp(line, "C", 1) == 0)
	{
		data->check_c++;
		return (parse_color(line, &data->ceiling));
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_putstr_fd("Usage: ./cub3D map.cub\n", STDERR_FILENO), 1);
	init_data(&data);
	if (!load_map_and_param(av, &data, &data.map))
		return (1);
	print_map(data.map.map);
	return (0);
}

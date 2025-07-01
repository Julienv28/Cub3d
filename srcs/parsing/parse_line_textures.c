/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:44:42 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/01 10:54:24 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_texture_line(char *line, t_data *data)
{
	if (!data)
		return (0);
	if (parse_and_check(line, "NO", &data->textures.no_xpm,
			&data->textures.no_check))
		return (1);
	if (parse_and_check(line, "SO", &data->textures.so_xpm,
			&data->textures.so_check))
		return (1);
	if (parse_and_check(line, "WE", &data->textures.we_xpm,
			&data->textures.we_check))
		return (1);
	if (parse_and_check(line, "EA", &data->textures.ea_xpm,
			&data->textures.ea_check))
		return (1);
	return (0);
}

int	is_color_line(char *line, t_data *data)
{
	if (!data)
		return (0);
	if (ft_strncmp(line, "F", 1) == 0)
	{
		if (parse_color(line, &data->floor, data))
		{
			data->check_f++;
			return (1);
		}
		return (0);
	}
	if (ft_strncmp(line, "C", 1) == 0)
	{
		if (parse_color(line, &data->ceiling, data))
		{
			data->check_c++;
			return (1);
		}
		return (0);
	}
	return (0);
}

int	parse_number(char *line, int *i)
{
	int	num;

	num = 0;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (!ft_isdigit(line[*i]))
		return (-1);
	while (ft_isdigit(line[*i]))
	{
		num = num * 10 + (line[*i] - '0');
		(*i)++;
	}
	return (num);
}

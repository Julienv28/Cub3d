/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:52:27 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/19 13:18:02 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Check que la carte est entoure de mur
// Parsing joueur + position

#include "../includes/cub3d.h"

int	is_param_line(char *line, t_params *params)
{
	if (!line)
		return (0);
	while (*line == ' ')
        line++;
	if (ft_strncmp(line, "NO",2) == 0)
		return (parse_texture(line, &params->textures.no));
	if (ft_strncmp(line, "SO",2) == 0)
		return (parse_texture(line, &params->textures.so));
	if (ft_strncmp(line, "WE",2) == 0)
		return (parse_texture(line, &params->textures.we));
	if (ft_strncmp(line, "EA",2) == 0)
		return (parse_texture(line, &params->textures.ea));
	if (ft_strncmp(line, "F", 1) == 0)
		return (parse_color(line, &params->floor));
	if (ft_strncmp(line, "C", 1) == 0)
		return (parse_color(line, &params->ceiling));
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		fprintf(stderr, "Usage: %s map.cub\n", av[0]);
		return (1);
	}
	init_data(&data);
	if (!load_map(av, &data.params, &data.map))
		return (perror("Error chargement map\n"), 1);
	print_map(data.map.map);
	if (!check_map(&data.map))
		return (perror("false\n"), 1);
	return (0);
}

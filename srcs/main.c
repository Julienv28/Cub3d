/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:52:27 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/18 13:19:20 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_param_line(char *line, t_params *params)
{
    if (!line)
        return(0);
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

char    **load_map(char **av, t_params *params)
{
    int     fd;
    char    **map;

    fd = open(av[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error: ouverture map\n");
        return (NULL);
    }
    map = init_map(fd, params);
    close(fd);
    return (map);
}

// Check 
int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		fprintf(stderr, "Usage: %s map.cub\n", av[0]);
		return (1);
	}
	init_data(&data);
	data.map.map = load_map(av, &data.params);
	if (!data.map.map)
	{
		perror("Error chargement map\n");
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:52:27 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/18 12:55:55 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
int parse_texture(char *line, char **texture)
{
    int i;

    i = 0;
    while (line[i])
    {
        printf("line = %s\n", line);
        i++;
    }
    
}*/

int	parse_number(char *line, int *i)
{
	int	num = 0;

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

// Coueur au format RGB
int parse_color(char *line, t_color *color)
{
    int r = 0;
    int g = 0;
    int b = 0;
    int i = 1;

    while (line[i] == ' ')
		i++;
    r = parse_number(line, &i);
	if (line[i++] != ',' || r < 0 || r > 255)
		return (0);
	g = parse_number(line, &i);
	if (line[i++] != ',' || g < 0 || g > 255)
		return (0);
	b = parse_number(line, &i);
	if (line[i] != '\0' && line[i] != '\n')
		return (0);
	if (b < 0 || b > 255)
		return (0);
    color->r = r;
    color->g = g;
    color->b = b;
    return (1);
}

int is_param_line(char *line, t_params *params)
{
    if (!line)
        return(0);
    while (*line == ' ')
        line++;
    // if (ft_strncmp(line, "NO",2) == 0)
    //     return (parse_texture(line, &params->textures.no));
    // if (ft_strncmp(line, "SO",2) == 0)
    //     return (parse_texture(line, &params->textures.so));
    // if (ft_strncmp(line, "WE",2) == 0)
    //     return (parse_texture(line, &params->textures.we));
    // if (ft_strncmp(line, "EA",2) == 0)
    //     return (parse_texture(line, &params->textures.ea));
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
    t_data data;

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
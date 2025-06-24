/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_and_textures.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:16:09 by opique            #+#    #+#             */
/*   Updated: 2025/06/24 14:31:01 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	print_color_error(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(1);
}

int	parse_color(char *line, t_color *color)
{
	int	r;
	int	g;
	int	b;
	int	i;

	r = 0;
	g = 0;
	b = 0;
	i = 1;
	while (line[i] == ' ')
		i++;
	r = parse_number(line, &i);
	if (line[i++] != ',' || r < 0 || r > 255)
		return (print_color_error("Error: red color invalid\n"), 0);
	g = parse_number(line, &i);
	if (line[i++] != ',' || g < 0 || g > 255)
		return (print_color_error("Error: green color invalid\n"), 0);
	b = parse_number(line, &i);
	if (line[i] != '\0' && line[i] != '\n')
		return (print_color_error("Error: blue color invalid\n"), 0);
	if (b < 0 || b > 255)
		return (print_color_error("Error: RGB invalid format\n"), 0);
	color->r = r;
	color->g = g;
	color->b = b;
	return (1);
}

int	parse_texture(char *line, char **texture)
{
	int		i;
	char	*path;

	i = 2;
	path = NULL;
	while (line[i] && line[i] == ' ')
		i++;
	path = &line[i];
	*texture = malloc((sizeof(char) * ft_strlen(path) + 1));
	if (*texture == NULL)
		return (0);
	ft_strcpy(*texture, path);
	return (1);
}

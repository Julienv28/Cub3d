/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_and_textures.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:16:09 by opique            #+#    #+#             */
/*   Updated: 2025/07/01 11:02:49 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_comma(char *line, int *i)
{
	if (line[*i] != ',')
		return (0);
	(*i)++;
	return (1);
}

static int	check_range(int val)
{
	if (val < 0 || val > 255)
		return (0);
	return (1);
}

static int	check_line_end(char *line, int i)
{
	if (line[i] != '\0' && line[i] != '\n')
		return (0);
	return (1);
}

int	parse_color(char *line, t_color *color, t_data *data)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 1;
	while (line[i] == ' ')
		i++;
	r = parse_number(line, &i);
	if (!check_comma(line, &i) || !check_range(r))
		return (print_col_error("Error: red color invalid\n", data, line), 0);
	g = parse_number(line, &i);
	if (!check_comma(line, &i) || !check_range(g))
		return (print_col_error("Error: green color invalid\n", data, line), 0);
	b = parse_number(line, &i);
	if (!check_line_end(line, i) || !check_range(b))
		return (print_col_error("Error: blue color invalid\n", data, line), 0);
	if (b < 0 || b > 255)
		return (print_col_error("Error: RGB invalid format\n", data, line), 0);
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
	if (*texture)
		free(*texture);
	*texture = malloc((sizeof(char) * ft_strlen(path) + 1));
	if (*texture == NULL)
		return (0);
	ft_strcpy(*texture, path);
	return (1);
}

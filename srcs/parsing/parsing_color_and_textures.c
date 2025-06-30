/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_and_textures.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:16:09 by opique            #+#    #+#             */
/*   Updated: 2025/06/30 17:17:20 by opique           ###   ########.fr       */
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

int	parse_color(char *line, t_color *color, t_data *data)
{
	int	r;
	int	g;
	int	b;
	int	i;

	r = 0;
	g = 0;
	b = 0;
	i = 1;
	while (line[i] == ' ') i++;
	r = parse_number(line, &i);
	if (line[i++] != ',' || r < 0 || r > 255)
		return (print_color_error("Error: red color invalid\n", data, line),
			 0);
	g = parse_number(line, &i);
	if (line[i++] != ',' || g < 0 || g > 255)
		return (print_color_error("Error: green color invalid\n", data, line),
			 0);
	b = parse_number(line, &i);
	if (line[i] != '\0' && line[i] != '\n')
		return (print_color_error("Error: blue color invalid\n", data, line),
			 0);
	if (b < 0 || b > 255)
		return (print_color_error("Error: RGB invalid format\n", data, line),
			 0);
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
 
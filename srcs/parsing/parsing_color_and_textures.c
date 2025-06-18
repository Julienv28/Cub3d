# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    parsing_color_and_texttures                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opique <opique@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 13:06:36 by opique            #+#    #+#              #
#    Updated: 2025/06/18 13:07:47 by opique           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

int parse_texture(char *line, char **texture)
{
    int i;

    i = 0;
    while (line[i])
    {
        printf("line = %s\n", line);
        i++;
    }
    
}
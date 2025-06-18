/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:37:49 by opique            #+#    #+#             */
/*   Updated: 2025/06/18 12:23:17 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    init_data(t_data *data)
{
    data->mlx_ptr = NULL;
    data->win_ptr = NULL;
    data->map.map = NULL;
}

char    **init_map(int fd, t_params *params)
{
    char    *line;
    char    **map;

    map = NULL;
    line = get_next_line(fd);
    while (line != NULL)
    {
        if (is_param_line(line, params))
			printf("Paramètre détecté : %s", line);
		else
			printf("Autre ligne : %s", line);
		free(line);
        line = get_next_line(fd);
    }
    return (map);
}
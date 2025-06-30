/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:40 by opique            #+#    #+#             */
/*   Updated: 2025/06/30 15:00:44 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_param(t_data *data)
{
	if (data->textures.ea_check > 1)
		return (ft_putstr_fd("Error: doublon EA\n", STDERR_FILENO), 0);
	if (data->textures.no_check > 1)
		return (ft_putstr_fd("Error: doublon NO\n", STDERR_FILENO), 0);
	if (data->textures.so_check > 1)
		return (ft_putstr_fd("Error: doublon SO\n", STDERR_FILENO), 0);
	if (data->textures.we_check > 1)
		return (ft_putstr_fd("Error: doublon WE\n", STDERR_FILENO), 0);
	if (data->check_f > 1)
		return (ft_putstr_fd("Error: doublon F\n", STDERR_FILENO), 0);
	if (data->check_c > 1)
		return (ft_putstr_fd("Error: doublon C\n", STDERR_FILENO), 0);
	if (data->textures.ea_check == 0 || data->textures.no_check == 0
		|| data->textures.so_check == 0 || data->textures.we_check == 0
		|| data->check_c == 0 || data->check_f == 0)
		return (ft_putstr_fd("Missing param\n", STDERR_FILENO), 0);
	return (1);
}

int	check_all(t_data *data, t_map *map)
{
	if (!check_param(data))
		return (0);
	replace_spaces_by_walls(map);
	if (!check_wall(map))
		return (0);
	if (!check_map(map))
		return (0);
	return (1);
}

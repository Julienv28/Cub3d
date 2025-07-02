/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:40 by opique            #+#    #+#             */
/*   Updated: 2025/07/02 12:03:33 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_param(t_data *data)
{
	if (data->textures.ea_check > 1)
		return (ft_putstr_fd("Error\ndoublon EA.\n", STDERR_FILENO),
			ft_free_paths_textures(data), 0);
	if (data->textures.no_check > 1)
		return (ft_putstr_fd("Error\ndoublon NO.\n", STDERR_FILENO),
			ft_free_paths_textures(data), 0);
	if (data->textures.so_check > 1)
		return (ft_putstr_fd("Error\ndoublon SO.\n", STDERR_FILENO),
			ft_free_paths_textures(data), 0);
	if (data->textures.we_check > 1)
		return (ft_putstr_fd("Error\ndoublon WE.\n", STDERR_FILENO),
			ft_free_paths_textures(data), 0);
	if (data->check_f > 1)
		return (ft_putstr_fd("Error\ndoublon F.\n", STDERR_FILENO),
			ft_free_paths_textures(data), 0);
	if (data->check_c > 1)
		return (ft_putstr_fd("Error\ndoublon C.\n", STDERR_FILENO),
			ft_free_paths_textures(data), 0);
	if (data->textures.ea_check == 0 || data->textures.no_check == 0
		|| data->textures.so_check == 0 || data->textures.we_check == 0
		|| data->check_c == 0 || data->check_f == 0)
		return (ft_putstr_fd("Error\nMissing param.\n", STDERR_FILENO),
			ft_free_paths_textures(data), 0);
	return (1);
}

int	check_all(t_data *data, t_map *map)
{
	if (!check_param(data))
		return (0);
	replace_spaces_by_walls(map);
	if (!check_wall(map, data))
		return (0);
	if (!check_map(map, data))
		return (0);
	return (1);
}

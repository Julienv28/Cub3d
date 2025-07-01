/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:41:19 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/01 11:00:10 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map(char **map, int height)
{
	int	i;

	if (map == NULL || height <= 0)
		return ;
	i = 0;
	while (i < height)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

int	on_destroy(t_data *data)
{
	if (data->mlx_ptr)
	{
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		if (data->textures.no.xpm_ptr)
			mlx_destroy_image(data->mlx_ptr, data->textures.no.xpm_ptr);
		if (data->textures.so.xpm_ptr)
			mlx_destroy_image(data->mlx_ptr, data->textures.so.xpm_ptr);
		if (data->textures.we.xpm_ptr)
			mlx_destroy_image(data->mlx_ptr, data->textures.we.xpm_ptr);
		if (data->textures.ea.xpm_ptr)
			mlx_destroy_image(data->mlx_ptr, data->textures.ea.xpm_ptr);
		if (data->screen.xpm_ptr)
			mlx_destroy_image(data->mlx_ptr, data->screen.xpm_ptr);
		if (data->minimap.img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->minimap.img_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_map(data->map.map, data->map.height);
	exit(0);
}

int	print_col_error(char *msg, t_data *data, char *line)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	if (line)
		free(line);
	if (data->buffer)
		free(data->buffer);
	ft_free_paths_textures(data);
	exit(1);
}

int	ft_error_close(char *message, t_data *data)
{
	printf(ORANGE"ERROR\n"GREY"%s\n"RESET, message);
	if (data && data->mlx_ptr)
		on_destroy(data);
	return (0);
}

void	ft_free_paths_textures(t_data *data)
{
	free(data->textures.no_xpm);
	free(data->textures.so_xpm);
	free(data->textures.ea_xpm);
	free(data->textures.we_xpm);
}

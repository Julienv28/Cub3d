/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:26:28 by opique            #+#    #+#             */
/*   Updated: 2025/06/30 16:26:29 by opique           ###   ########.fr       */
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

int on_destroy(t_data *data)
{
    printf("Fenêtre fermée (event 17)\n");
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

int	print_color_error(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(1);
}

int	ft_error_close(char *message, t_data *data)
{
	printf(ORANGE"ERROR\n"GREY"%s\n"RESET, message);
	if (data && data->mlx_ptr)
		on_destroy(data);
	return (0);
}
 
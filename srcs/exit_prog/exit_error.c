/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:41:19 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/30 15:52:41 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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


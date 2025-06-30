/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:37:49 by opique            #+#    #+#             */
/*   Updated: 2025/06/30 15:27:21 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_texture(t_data *data)
{
	data->textures.ea_check = 0;
	data->textures.no_check = 0;
	data->textures.so_check = 0;
	data->textures.we_check = 0;
	data->textures.no_xpm = NULL;
	data->textures.so_xpm = NULL;
	data->textures.we_xpm = NULL;
	data->textures.ea_xpm = NULL;
	data->textures.no.xpm_ptr = NULL;
	data->textures.so.xpm_ptr = NULL;
	data->textures.we.xpm_ptr = NULL;
	data->textures.ea.xpm_ptr = NULL;
	data->textures.no.data_addr = NULL;
	data->textures.so.data_addr = NULL;
	data->textures.we.data_addr = NULL;
	data->textures.ea.data_addr = NULL;
}

void	init_data(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->map.map = NULL;
	data->check_c = 0;
	data->check_f = 0;
	data->mouse_locked = false;
	data->ignore_mouse_event = false;
	data->need_redraw = true;
	data->last_mouse_x = WIN_LEN / 2;
	data->map.play.x = 0;
	data->map.play.y = 0;
	data->map.play.angle = 0;
	data->map.play.fov = 0;
	data->map.play.orientation = 0;
	data->minimap.addr = NULL;
	data->minimap.bits_per_pixel = 0;
	data->minimap.endian = 0;
	data->minimap.img_ptr = NULL;
	data->minimap.line_length = 0;
}

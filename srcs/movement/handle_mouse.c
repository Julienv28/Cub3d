/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:10:20 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/30 11:36:05 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

	// if (delta_x > 0) // droite -> angle augmente
	// 	data->map.play.angle += delta_x * sensibility;
	// else if (delta_x < 0) // gauche -> angle diminue
	// 	data->map.play.angle -= delta_x * sensibility;
	// printf("Pos souris : x = %d\n", x);
int	handle_mouse(int x, int y, t_data *data)
{
	int		delta_x;
	float	sensibility;

	(void) y;
	sensibility = 0.003;
	if (!data->mouse_locked)
	{
		data->last_mouse_x = x;
		data->mouse_locked = true;
		return (0);
	}
	if (data->ignore_mouse_event)
	{
		data->ignore_mouse_event = false;
		return (0);
	}
	delta_x = x - data->last_mouse_x;
	data->map.play.angle += delta_x * sensibility;
	data->map.play.angle = normalize_angle(data->map.play.angle);
	data->ignore_mouse_event = true;
	mlx_mouse_move(data->mlx_ptr, data->win_ptr, WIN_LEN / 2, WIN_HEIGHT / 2);
	data->last_mouse_x = WIN_LEN / 2;
	data->need_redraw = true;
	return (0);
}

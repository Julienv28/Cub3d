/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oceanepique <oceanepique@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:06:25 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/27 15:14:11 by oceanepique      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	clear_screen(t_image *screen, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_LEN)
		{
			put_pixel_to_image(screen, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_game(t_data *data)
{
	float	playerangle;
	float	rayangle;
	t_rc	rc;
	int		ray;

	clear_screen(&data->screen, 0x000000);
	ray = 0;
	playerangle = data->map.play.angle;
	while (ray < NUM_RAYS)
	{
		rayangle = playerangle - (data->map.play.fov / 2)
			+ (data->map.play.fov / NUM_RAYS) * ray;
		rayangle = normalize_angle(rayangle);
		rc.distance = get_dist_from_player(&data->map, rayangle, &rc);
		if (rc.distance == FLT_MAX)
			rc.distance = 20.0f;
		rc.distance *= cosf(rayangle - playerangle);
		if (rc.distance < 0.0001f)
			rc.distance = 0.0001f;
		// printf("Ray %d -> distance = %f\n", ray, rc.distance);
		rc.dis_proj_plane = (WIN_LEN / 2) / tan(data->map.play.fov / 2);
		rc.pr_hght = (rc.dis_proj_plane * TILE_SIZE) / rc.distance;
		if (rc.pr_hght >= WIN_HEIGHT)
			rc.pr_hght = WIN_HEIGHT - 1;
		rc.top_pixel = (WIN_HEIGHT / 2) - (rc.pr_hght / 2);
		rc.bttm_pixel = (WIN_HEIGHT / 2) + (rc.pr_hght / 2);
		if (rc.top_pixel < 0)
			rc.top_pixel = 0;
		if (rc.bttm_pixel > WIN_HEIGHT)
			rc.bttm_pixel = WIN_HEIGHT;
		draw_column(data, &rc, ray);
		ray++;
	}
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->screen.xpm_ptr, 0, 0);
	draw_minimap(data);
}

// void	render_game(t_data *data)
// {
// 	for (int y = 0; y < WIN_HEIGHT; y++)
// 	{
// 		for (int x = 0; x < WIN_LEN; x++)
// 		{
// 			if (y < WIN_HEIGHT / 2)
// 				put_pixel_to_image(&data->screen, x, y, rgb_to_int(data->ceiling)); // bleu ciel
// 			else
// 				put_pixel_to_image(&data->screen, x, y, rgb_to_int(data->floor)); // marron
// 		}
// 	}
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->screen.xpm_ptr, 0, 0);
// }

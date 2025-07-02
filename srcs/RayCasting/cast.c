/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:06:25 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/02 11:01:37 by juvitry          ###   ########.fr       */
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

static void	count_ray(t_data *data, float playerangle, t_rc *rc, int ray)
{
	float	rayangle;
	float	camera_x;

	camera_x = ((float)ray / (float)NUM_RAYS) - 0.5f;
	rayangle = normalize_angle(playerangle + camera_x * data->map.play.fov);
	rc->distance = get_dist_from_player(&data->map, rayangle, rc);
	if (rc->distance == FLT_MAX)
		rc->distance = 20.0f;
	rc->correct = cosf(rayangle - playerangle);
	if (fabsf(rc->correct) < 0.0001f)
		rc->correct = 0.0001f;
	rc->corrected_distance = rc->distance * rc->correct;
	if (rc->corrected_distance < MIN_DISTANCE)
		rc->corrected_distance = MIN_DISTANCE;
	rc->dis_proj_plane = (float)(WIN_LEN / 2) / tanf(data->map.play.fov / 2.0f);
	rc->pr_hght = ((rc->dis_proj_plane * TILE_SIZE) / rc->corrected_distance);
	rc->top_pixel = (int)((WIN_HEIGHT / 2.0f) - (rc->pr_hght / 2.0f));
	rc->bttm_pixel = (int)((WIN_HEIGHT / 2.0f) + (rc->pr_hght / 2.0f));
}

static void	render_rays(t_data *data, float playerangle)
{
	t_rc	rc;
	int		ray;

	ray = 0;
	while (ray < NUM_RAYS)
	{
		count_ray(data, playerangle, &rc, ray);
		draw_column(data, &rc, ray);
		ray++;
	}
}

void	render_game(t_data *data)
{
	float	playerangle;

	clear_screen(&data->screen, 0x000000);
	playerangle = data->map.play.angle;
	render_rays(data, playerangle);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->screen.xpm_ptr, 0, 0);
	draw_minimap(data);
}

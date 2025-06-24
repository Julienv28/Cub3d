/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:06:25 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/24 14:34:12 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

float get_dist_from_player(t_map *map, float rayAngle, t_rc *rc)
{
	t_cast cast;
	int hit = 0;
	int mapX, mapY;
	int stepX, stepY;
	float deltaDistX, deltaDistY;
	float sideDistX, sideDistY;
	float posX = map->play->x;
	float posY = map->play->y;

	// Direction du rayon
	cast.dx = cosf(rayAngle);
	cast.dy = sinf(rayAngle);
	// Case actuelle
	mapX = (int)posX;
	mapY = (int)posY;
	// Delta distances
	deltaDistX = fabsf(1 / cast.dx);
	deltaDistY = fabsf(1 / cast.dy);
	// Init des pas & sideDist
	if (cast.dx < 0)
	{
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0f - posX) * deltaDistX;
	}
	if (cast.dy < 0)
	{
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0f - posY) * deltaDistY;
	}
	int side; // 0 = x, 1 = y
	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (mapX < 0 || mapX >= map->width || mapY < 0 || mapY >= map->height)
			return FLT_MAX;
		if (map->map[mapY][mapX] == '1')
			hit = 1;
	}
	// Distance exacte
	if (side == 0)
		cast.distance = (sideDistX - deltaDistX);
	else
		cast.distance = (sideDistY - deltaDistY);
	// Orientation (NORD, SUD, EST, OUEST)
	if (side == 0)
		rc->w_or = (stepX > 0) ? WEST : EAST;
	else
		rc->w_or = (stepY > 0) ? NORTH : SOUTH;
	// Impact X
	if (side == 0)
		rc->impact_x = posY + cast.distance * cast.dy;
	else
		rc->impact_x = posX + cast.distance * cast.dx;
	rc->impact_x -= floorf(rc->impact_x);
	return cast.distance;
}

void	render_game(t_data *data)
{
	float	playerangle;
	float	rayangle;
	t_rc	rc;
	int		ray;

	ray = 0;
	playerangle = data->map.play->angle;
	while (ray < NUM_RAYS)
	{
		rayangle = playerangle - (data->map.play->fov / 2)
			+ (data->map.play->fov / NUM_RAYS) * ray;
        rayangle = normalize_angle(rayangle);
		rc.distance = get_dist_from_player(&data->map, rayangle, &rc);
        if (rc.distance == FLT_MAX)
             rc.distance = 20.0f;
		rc.distance *= cosf(rayangle - playerangle);
		if (rc.distance < 0.0001f)
			rc.distance = 0.0001f;
        rc.dis_proj_plane = (WIN_LEN / 2) / tan(data->map.play->fov / 2);
		rc.pr_hght = (rc.dis_proj_plane * TILE_SIZE) / rc.distance;
        if (rc.pr_hght > WIN_HEIGHT)
            rc.pr_hght = WIN_HEIGHT;
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
}

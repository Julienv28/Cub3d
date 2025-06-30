/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:39:24 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/30 13:43:32 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_wall(float x, float y, char **map)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map[map_y] == NULL || map[map_y][map_x] == '\0')
		return (true);
	return (map[map_y][map_x] == '1');
}

static void	move_player(t_map *map, float dir)
{
	float	new_x;
	float	new_y;
	float	angle;

	angle = map->play.angle;
	new_x = map->play.x + cosf(angle) * SPEED * dir;
	new_y = map->play.y + sinf(angle) * SPEED * dir;
	if (!is_wall(new_x, map->play.y, map->map))
		map->play.x = new_x;
	if (!is_wall(map->play.x, new_y, map->map))
		map->play.y = new_y;
}

static void	strafe_player(t_map *map, float dir)
{
	float	new_x;
	float	new_y;
	float	angle;

	angle = map->play.angle + (M_PI_2 * dir);
	new_x = map->play.x + cosf(angle) * SPEED;
	new_y = map->play.y + sinf(angle) * SPEED;
	if (!is_wall(new_x, map->play.y, map->map))
		map->play.x = new_x;
	if (!is_wall(map->play.x, new_y, map->map))
		map->play.y = new_y;
}

static void	rotate_player(float direction, t_data *data)
{
	float	rotation_speed;

	rotation_speed = 0.05f;
	data->map.play.angle += direction * rotation_speed;
	data->map.play.angle = normalize_angle(data->map.play.angle);
}

int	handle_keypress(int keysum, t_data *data)
{
	if (keysum == KEY_ESC)
		on_destroy(data);
	else if (keysum == KEY_RIGHT)
		rotate_player(1.0f, data);
	else if (keysum == KEY_LEFT)
		rotate_player(-1.0f, data);
	else if (keysum == KEY_W)
		move_player(&data->map, 1.0f);
	else if (keysum == KEY_S)
		move_player(&data->map, -1.0f);
	else if (keysum == KEY_D)
		strafe_player(&data->map, 1.0f);
	else if (keysum == KEY_A)
		strafe_player(&data->map, -1.0f);
	else
		return (0);
	data->need_redraw = true;
	return (0);
}

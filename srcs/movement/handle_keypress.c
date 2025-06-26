/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:14:01 by opique            #+#    #+#             */
/*   Updated: 2025/06/26 13:25:06 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_mouse(int x, int y, t_data *data)
{
	int		delta_x;
	float	sensibility;

	(void) y;
	sensibility = 0.003;
	delta_x = x - data->last_mouse_x;
	if (delta_x > 0)
		data->map.play.angle += delta_x * sensibility;
	else if (delta_x < 0)
		data->map.play.angle -= delta_x * sensibility;
	data->last_mouse_x = x;
	// printf("Pos souris : x = %d\n", x);
	render_game(data);
	return (0);
}

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
	if (is_wall(map->play.x, new_y, map->map))
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

int	handle_keypress(int keysum, t_data *data)
{
	if (keysum == KEY_ESC || keysum == KEY_Q)
		on_destroy(data);
	else if (keysum == KEY_W || keysum == KEY_UP)
		move_player(&data->map, 1.0f);
	else if (keysum == KEY_S || keysum == KEY_DOWN)
		move_player(&data->map, -1.0f);
	else if (keysum == KEY_D || keysum == KEY_RIGHT)
		strafe_player(&data->map, 1.0f);
	else if (keysum == KEY_A || keysum == KEY_LEFT)
		strafe_player(&data->map, -1.0f);
	else
		return (0);
	render_game(data);
	// printf("Pos joueur : x = %.2f, y = %.2f\n", data->map.play.x, data->map.play.y);
	return (0);
}

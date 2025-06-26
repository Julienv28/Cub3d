/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:39:24 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/26 18:37:33 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static void	player_movement(int keysum, t_position *player, float *new_x, 
// 	float *new_y)
// {
//  	float	move_speed;

//  	*new_x = player->x;
//  	*new_y = player->y;
//  	move_speed = 0.1;
//  	if (keysum == 119) // W -> avancer
//  	{
//  		*new_x = player->x + cosf(player->angle) * move_speed;
//  		*new_y = player->y - sinf(player->angle) * move_speed;
//  		printf("touche W -> avancer\n");
//  	}
//  	else if (keysum == 115) // S -> reculer
//  	{
//  		*new_x = player->x - cosf(player->angle) * move_speed;
//  		*new_y = player->y + sinf(player->angle) * move_speed;
//  		printf("touche S -> reculer\n");
//  	}
//  	else if (keysum == 97) // A -> gauche
//  	{
//  		*new_x = player->x - sinf(player->angle) * move_speed;
//  		*new_y = player->y - cosf(player->angle) * move_speed;
//  		printf("touche A -> gauche\n");
//  	}
//  	else if (keysum == 100) // D -> droite
//  	{
//  		*new_x = player->x + sinf(player->angle) * move_speed;
//  		*new_y = player->y + cosf(player->angle) * move_speed;
//  		printf("touche D -> droite\n");
//  	}
// }

// static void	handle_player(int keysum, t_map *map)
// {
//  	t_position	*player;
//  	float		new_x;
//  	float		new_y;

//  	player = &map->play;
//  	player_movement(keysum, player, &new_x, &new_y);
//  	if (map->map[(int)new_y][(int)new_x] != '1')
//  	{
//  		player->x = new_x;
//  		player->y = new_y;
//  	}
// 	printf("Pos joueur : x = %.2f, y = %.2f\n", player->x, player->y);
// }

// int	handle_keypress(int keysum, t_data *data)
// {
// 	if (keysum == XK_Escape)
// 		on_destroy(data);
// 	if (keysum == KEY_W || keysum == KEY_S || keysum == KEY_A
// 		|| keysum == KEY_D)
// 	{
// 		handle_player(keysum, &data->map);
// 		render_game(data);
// 	}
// 	return (0);
// }

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

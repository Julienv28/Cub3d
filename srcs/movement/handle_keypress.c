/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:19:45 by opique            #+#    #+#             */
/*   Updated: 2025/06/24 14:29:35 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	player_movement(int keysum, t_position *player, float *new_x, float *new_y)
{
	float	move_speed;

	*new_x = player->x;
	*new_y = player->y;
	move_speed = 0.1;
	if (keysum == 119) // W -> avancer
	{
		*new_x = player->x + cosf(player->angle) * move_speed;
		*new_y = player->y - sinf(player->angle) * move_speed;
		printf("touche W -> avancer\n");
	}
	else if (keysum == 115) // S -> reculer
	{
		*new_x = player->x - cosf(player->angle) * move_speed;
		*new_y = player->y + sinf(player->angle) * move_speed;
		printf("touche S -> reculer\n");
	}
	else if (keysum == 97) // A -> gauche
	{
		*new_x = player->x - sinf(player->angle) * move_speed;
		*new_y = player->y - cosf(player->angle) * move_speed;
		printf("touche A -> gauche\n");
	}
	else if (keysum == 100) // D -> droite
	{
		*new_x = player->x + sinf(player->angle) * move_speed;
		*new_y = player->y + cosf(player->angle) * move_speed;
		printf("touche D -> droite\n");
	}
}

static void	handle_player(int keysum, t_map *map)
{
	t_position	*player;
	float		new_x;
	float		new_y;

	player = &map->play;
	player_movement(keysum, player, &new_x, &new_y);
	if (map->map[(int)new_y][(int)new_x] != '1')
	{
		player->x = new_x;
		player->y = new_y;
	}
	printf("Pos joueur : x = %.2f, y = %.2f\n", player->x, player->y);
}

int	handle_keypress(int keysum, t_data *data)
{
	if (keysum == XK_Escape)
		on_destroy(data);
	if (keysum == 119 || keysum == 115 || keysum == 97 || keysum == 100)
	{
		handle_player(keysum, &data->map);
		render_game(data);
	}
	return (0);
}

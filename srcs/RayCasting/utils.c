/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:14:17 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/02 11:29:00 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
Application rapide du DDA avec la lib mathematique.

- Si le rayon avance + en X (dx > dy), c’est sûrement un mur Est ou Ouest
- Si le rayon avance + en Y, c’est un mur Nord ou Sud
Selon la direction :
ray_dir_x > 0	Ouest (car mur est à gauche)
ray_dir_x < 0	Est (mur à droite)
ray_dir_y > 0	Nord (car mur est au-dessus)
ray_dir_y < 0	Sud (mur en dessous)
*/
int	get_w_or(float dx, float dy)
{
	if (fabsf(dx) > fabsf(dy))
	{
		if (dx < 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (dy < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
}

/*
Dans la meme logique dertermine l'impact avec la fonction floorf.

NB: floorf calcul l'arrondi entier inferieur de a valeur specifiee en param.
Ici elle retourne un float.accessL'objectif est d'exploiter cette coordoner 
pour savoir quel pixel exploiter.
- collision horizontale = on récupère la coordonnée X à l'intérieur de la case
- collision verticale = on récupère la coordonnée Y à l'intérieur de la case
*/

void	get_impacts(float rayx, float rayy, int w_or, t_vec2f *impact)
{
	float	local_x;
	float	local_y;

	local_x = rayx - floorf(rayx);
	local_y = rayy - floorf(rayy);
	if (w_or == NORTH || w_or == SOUTH)
	{
		impact->x = local_x;
		impact->y = local_y;
		if (w_or == NORTH)
			impact->x = 1.0f - impact->x;
	}
	else
	{
		impact->x = local_x;
		impact->y = local_y;
		if (w_or == EAST)
			impact->y = 1.0f - impact->y;
	}
	if (impact->x < 0.0f)
		impact->x += 1.0f;
	if (impact->y < 0.0f)
		impact->y += 1.0f;
}

int	rgb_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = color.r;
	g = color.g;
	b = color.b;
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

int	loop_handler(t_data *data)
{
	if (data->need_redraw)
	{
		render_game(data);
		data->need_redraw = false;
	}
	return (0);
}

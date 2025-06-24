/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:14:17 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/24 14:34:11 by juvitry          ###   ########.fr       */
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
			return (SOUTH);
		else
			return (NORTH);
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
float	get_impact_x(float rayx, float rayy, int w_or)
{
	float	impact;

	if (w_or == NORTH || w_or == SOUTH)
		impact = rayx - floorf(rayx);
	else
		impact = rayy - floorf(rayy);
	return (impact);
}

/*
Lorsque l'on exprime une couleur avec un code RGB, on renvoit en realite un
entier. Il est donc necessaire de convertir ces valeur rgb pour ensuite etre
en capacite d'afficher le bon set de couleurs.
*/
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

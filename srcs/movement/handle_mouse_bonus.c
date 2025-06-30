/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:10:20 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/30 16:08:27 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_mouse(int x, int y, t_data *data)
{
	int		delta_x;
	float	sensibility;

	if (!data->mouse_locked)
		return (0);
	(void) y;
	sensibility = 0.003;
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

/*
Fonction bonus necessitant l'utilisation de gettimeofday.
Cette fonction nous sert a observer si on opere un double
clic. En operant de cette facon, on peut unlock la souris
et fermer la fenetre et ne pas etre restreint tout en remplissant les
consignes de base.

Recall de l'encadre du Bonus : "Dans le cadre des bonus, vous êtes 
autorisé à utiliser d’autres fonctions ou à ajouter des symboles sur la 
carte pour compléter la partie bonus tant que leur utilisation est 
justifiée lors de votre évaluation."
*/

// Fonction pour traiter le premier clic
int	first_c(struct timeval *last, struct timeval current_click, int *first_c)
{
	if (*first_c == 0)
	{
		*last = current_click;
		*first_c = 1;
		return (0);
	}
	return (1);
}

// Fonction pour gérer le double clic
void	double_c(struct timeval cur_click, t_data *data, struct timeval *last)
{
	long	elapsed;

	elapsed = (cur_click.tv_sec - last->tv_sec) * 1000
		+ (cur_click.tv_usec - last->tv_usec) / 1000;
	if (elapsed < 300)
	{
		data->mouse_locked = !data->mouse_locked;
		if (data->mouse_locked)
		{
			mlx_mouse_move(data->mlx_ptr, data->win_ptr,
				WIN_LEN / 2, WIN_HEIGHT / 2);
			data->last_mouse_x = WIN_LEN / 2;
			data->ignore_mouse_event = true;
		}
	}
	*last = cur_click;
}

// Fonction principale qui gère le clic de la souris
int	handle_mouse_click(int but, int x, int y, t_data *data)
{
	static struct timeval	last_click;
	static int				first_click;
	struct timeval			current_click;

	(void)x;
	(void)y;
	if (but == 1)
	{
		gettimeofday(&current_click, NULL);
		if (!first_c(&last_click, current_click, &first_click))
			return (0);
		double_c(current_click, data, &last_click);
	}
	return (0);
}

/*
int	handle_mouse_click(int but, int x, int y, t_data *data)
{
	static struct timeval	last_click;
	static int				first_click;
	struct timeval			current_click;
	long					elapsed;

	(void)x;
	(void)y;
	if (but == 1)
	{
		gettimeofday(&current_click, NULL);
		if (first_click == 0)
		{
			last_click = current_click;
			first_click = 1;
			return (0);
		}
		elapsed = (current_click.tv_sec - last_click.tv_sec) * 1000
			+ (current_click.tv_usec - last_click.tv_usec) / 1000;
 		if (elapsed < 300)
		{
			data->mouse_locked = !data->mouse_locked;
			if (data->mouse_locked)
			{
				mlx_mouse_move(data->mlx_ptr, data->win_ptr, WIN_LEN / 2,
					WIN_HEIGHT / 2);
				data->last_mouse_x = WIN_LEN / 2;
				data->ignore_mouse_event = true;
			}
		}
		last_click = current_click;
	}
	return (0);
}*/

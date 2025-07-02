/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_columns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:04:04 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/02 10:56:22 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void draw_wall_strip(t_data *data, t_rc *rc, int ray, int text_x)
{
    t_image *texture = data->textures.all[rc->w_or];
    if (!texture)
        return;

    float wall_height = rc->pr_hght; // hauteur projetée (float)
    float step = (float)texture->y / wall_height; // ratio texture pixels / hauteur mur à l'écran

    int draw_start = rc->top_pixel;
    int draw_end = rc->bttm_pixel;

    // Calcul du décalage vertical dans la texture si mur dépasse en haut (draw_start < 0)
    float tex_pos = 0.0f;
    if (draw_start < 0)
        tex_pos = -draw_start * step;

    // Clamp draw_start et draw_end pour rester dans l'écran
    if (draw_start < 0)
        draw_start = 0;
    if (draw_end > WIN_HEIGHT)
        draw_end = WIN_HEIGHT;

    for (int y = draw_start; y < draw_end; y++)
    {
        int text_y = (int)tex_pos;
        if (text_y < 0)
            text_y = 0;
        if (text_y >= texture->y)
            text_y = texture->y - 1;

        unsigned int color = get_text_pixel_color(texture, text_x, text_y);
        put_pixel_to_image(&data->screen, ray, y, color);

        tex_pos += step;
    }
}


static void	draw_ceiling(t_data *data, t_rc *rc, int ray)
{
	int	y;
	int	color;

	y = 0;
	color = rgb_to_int(data->ceiling);
	while (y < rc->top_pixel)
	{
		put_pixel_to_image(&data->screen, ray, y, color);
		y++;
	}
}

static void	draw_floor(t_data *data, t_rc *rc, int ray)
{
	int	y;
	int	color;

	y = rc->bttm_pixel;
	color = rgb_to_int(data->floor);
	while (y < WIN_HEIGHT)
	{
		put_pixel_to_image(&data->screen, ray, y, color);
		y++;
	}
}

void	draw_column(t_data *data, t_rc *rc, int ray)
{
	t_image	*texture;
	int		text_x;

	if (rc->w_or < 0 || rc ->w_or > 3)
		return ;
	texture = data->textures.all[rc->w_or];
	if (texture == NULL)
		return ;
	text_x = init_text_x(rc, texture);
	draw_wall_strip(data, rc, ray, text_x);
	draw_ceiling(data, rc, ray);
	draw_floor(data, rc, ray);
}

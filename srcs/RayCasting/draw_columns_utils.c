/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_columns_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:22:28 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/01 10:05:03 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_text_x(t_rc *rc, t_image *texture)
{
	float	textures;

	textures = rc->impact_x - floorf(rc->impact_x);
	if (textures < 0.0f)
		textures = 0.0f;
	if (textures > 1.0f)
		textures = 1.0f;
	return ((int)(textures * texture->x));
}

int	set_text_y(t_rc *rc, int y, t_image *texture)
{
	int	textures;

	textures = (int)(((float)(y - rc->top_pixel) / rc->pr_hght) * texture->y);
	if (textures < 0)
		textures = 0;
	if (textures >= texture->y)
		textures = texture->y - 1;
	return (textures);
}

unsigned int	get_text_pixel_color(t_image *img, int x, int y)
{
	char			*pixel;
	unsigned int	color;

	if (x < 0 || x >= img->x || y < 0 || y >= img->y)
		return (0xFF00FF);
	pixel = img->data_addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	put_pixel_to_image(t_image *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= img->x || y < 0 || y >= img->y)
		return ;
	dst = img->data_addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

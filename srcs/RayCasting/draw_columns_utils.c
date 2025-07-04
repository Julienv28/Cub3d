/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_columns_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:22:28 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/02 11:02:03 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_text_x(t_rc *rc, t_image *texture)
{
	float	hit_coord;
	int		tex_x;

	if (rc->w_or == NORTH || rc->w_or == SOUTH)
		hit_coord = rc->impact_x;
	else
		hit_coord = rc->impact_y;
	hit_coord -= floor(hit_coord);
	tex_x = (int)(hit_coord * texture->x);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->x)
		tex_x = texture->x - 1;
	if (rc->w_or == SOUTH || rc->w_or == WEST)
		tex_x = texture->x - 1 - tex_x;
	return (tex_x);
}

int	set_text_y(t_rc *rc, int y, t_image *texture)
{
	int		textures_height;
	float	wall_height_on_screen;
	int		relative_y;
	float	ratio;
	int		text_y;

	textures_height = texture->y;
	wall_height_on_screen = rc->pr_hght;
	relative_y = y - rc->top_pixel;
	ratio = (float)relative_y / (float)wall_height_on_screen;
	text_y = (int)(ratio * textures_height);
	if (text_y < 0)
		text_y = 0;
	if (text_y >= textures_height)
		text_y = textures_height - 1;
	return (text_y);
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

void	clear_screen(t_image *screen, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_LEN)
		{
			put_pixel_to_image(screen, x, y, color);
			x++;
		}
		y++;
	}
}

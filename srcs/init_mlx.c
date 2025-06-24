/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:16:17 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/24 10:18:24 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		ft_error_close("Couldn't find mlx pointer. Try using a VNC.", data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_LEN, WIN_HEIGHT, "cub3D");
	if (data->win_ptr == NULL)
	{
		free(data->mlx_ptr);
		ft_error_close("Couldn't create the Window.", data);
	}
}

void	init_hook_loop(t_data *data)
{
	load_textures(data);
	draw_map(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, data); // pour le clavier
	mlx_hook(data->win_ptr, 17, 0, on_destroy, data);
	mlx_loop(data->mlx_ptr);
}

t_image	ft_new_img(void *mlx, char *path, t_data *data, int or)
{
	t_image	img;
	int		width;
	int		height;

	img.xpm_ptr = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (img.xpm_ptr == NULL)
		ft_error_close("Couldn't find the img file. Does it exist ?", data);
	img.or = or;
	return (img);
}

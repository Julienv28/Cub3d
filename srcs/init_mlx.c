/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:16:17 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/23 07:57:51 by opique           ###   ########.fr       */
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
/*
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

void	ft_init_textures(t_data *data)
{
	void	*mlx;

	mlx = data->mlx_ptr;
	data->textures.no = ft_new_img(mlx, data->textures.no_xpm, data, NORTH);
	data->textures.so = ft_new_img(mlx, data->textures.so_xpm, data, SOUTH);
	data->textures.ea = ft_new_img(mlx, data->textures.ea_xpm, data, EAST);
	data->textures.we = ft_new_img(mlx, data->textures.we_xpm, data, WEST);
}*/

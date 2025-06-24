/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:16:17 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/24 14:50:41 by opique           ###   ########.fr       */
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
		ft_error_close("Couldn't create the Window.", data);
	data->screen.xpm_ptr = mlx_new_image(data->mlx_ptr, WIN_LEN, WIN_HEIGHT);
	if (data->screen.xpm_ptr == NULL)
		ft_error_close("Couldn't create screen buffer image", data);
	data->screen.x = WIN_LEN;
	data->screen.y = WIN_HEIGHT;
	data->screen.data_addr = mlx_get_data_addr(data->screen.xpm_ptr,
			&data->screen.bpp, &data->screen.line_len, &data->screen.endian);
}

void	init_hook_loop(t_data *data)
{
	load_textures(data);
	draw_map(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, data); // pour le clavier
	mlx_hook(data->win_ptr, MotionNotify, PointerMotionMask, handle_mouse, data); // pour souris
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
	img.data_addr = mlx_get_data_addr(img.xpm_ptr, &img.bpp, &img.line_len,
			&img.endian);
	if (img.data_addr == NULL)
		ft_error_close("mlx_get_data_adr failed", data);
	img.or = or;
	return (img);
}

//2e partie d'initialisation = tableau pour le rendu avec RayCast
void	ft_init_textures(t_data *data)
{
	void	*mlx;

	mlx = data->mlx_ptr;
	data->textures.no = ft_new_img(mlx, data->textures.no_xpm, data, NORTH);
	data->textures.so = ft_new_img(mlx, data->textures.so_xpm, data, SOUTH);
	data->textures.ea = ft_new_img(mlx, data->textures.ea_xpm, data, EAST);
	data->textures.we = ft_new_img(mlx, data->textures.we_xpm, data, WEST);
	data->textures.all[NORTH] = &data->textures.no;
	data->textures.all[SOUTH] = &data->textures.so;
	data->textures.all[EAST] = &data->textures.ea;
	data->textures.all[WEST] = &data->textures.we;
}

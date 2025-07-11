/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:16:17 by juvitry           #+#    #+#             */
/*   Updated: 2025/07/02 12:06:15 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		ft_error_close("Error\nCouldn't find mlx pointer. Try using a VNC.\n", data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_LEN, WIN_HEIGHT, "cub3D");
	if (data->win_ptr == NULL)
		ft_error_close("Error\nCouldn't create the Window.\n", data);
	data->screen.xpm_ptr = mlx_new_image(data->mlx_ptr, WIN_LEN, WIN_HEIGHT);
	if (data->screen.xpm_ptr == NULL)
		ft_error_close("Error\nCouldn't create screen buffer image.\n", data);
	data->screen.x = WIN_LEN;
	data->screen.y = WIN_HEIGHT;
	data->screen.data_addr = mlx_get_data_addr(data->screen.xpm_ptr,
			&data->screen.bpp, &data->screen.line_len, &data->screen.endian);
	if (data->screen.data_addr == NULL)
		ft_error_close("Error\nBad creation of screen addr.\n", data);
}

void	init_minimap(t_data *data)
{
	data->minimap.img_ptr = mlx_new_image(data->mlx_ptr,
			data->map.width * MINMAP_BOX,
			data->map.height * MINMAP_BOX);
	if (!data->minimap.img_ptr)
		ft_error_close("Error\nminimap image alloc failed.\n", data);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img_ptr,
			&data->minimap.bits_per_pixel,
			&data->minimap.line_length,
			&data->minimap.endian);
	if (!data->minimap.addr)
		ft_error_close("Error\nminimap addr setup failed.\n", data);
}

void	init_hook_loop(t_data *data)
{
	ft_init_textures(data);
	init_minimap(data);
	render_game(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, handle_keypress, data);
	mlx_hook(data->win_ptr, MotionNotify, PointerMotionMask,
		handle_mouse, data);
	mlx_loop_hook(data->mlx_ptr, loop_handler, data);
	mlx_mouse_hook(data->win_ptr, handle_mouse_click, data);
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
	{
		ft_free_paths_textures(data);
		ft_error_close("Error\nCouldn't find the img file. Does it exist ?\n", data);
	}
	img.x = width;
	img.y = height;
	img.data_addr = mlx_get_data_addr(img.xpm_ptr, &img.bpp, &img.line_len,
			&img.endian);
	if (img.data_addr == NULL)
		ft_error_close("Error\nmlx_get_data_adr failed.\n", data);
	img.ori = or;
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
	data->textures.all[NORTH] = &data->textures.no;
	data->textures.all[SOUTH] = &data->textures.so;
	data->textures.all[EAST] = &data->textures.ea;
	data->textures.all[WEST] = &data->textures.we;
	ft_free_paths_textures(data);
}

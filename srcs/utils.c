/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oceanepique <oceanepique@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:33:44 by opique            #+#    #+#             */
/*   Updated: 2025/06/27 15:42:16 by oceanepique      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	count_elements(t_map *map)
{
	int		y;
	int		x;
	char	cell;
	int		len;

	map->east = 0;
	map->north = 0;
	map->south = 0;
	map->west = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		len = ft_strlen(map->map[y]);
		while (x < len)
		{
			cell = map->map[y][x];
			if (cell == 'N')
				map->north++;
			else if (cell == 'S')
				map->south++;
			else if (cell == 'E')
				map->east++;
			else if (cell == 'W')
				map->west++;
			x++;
		}
		y++;
	}
}

int	cub_extansion(char *filename)
{
	int		len;
	int		res;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	res = ft_strcmp(filename + len - 4, ".cub");
	if (res == 0)
		return (1);
	else
		return (0);
}	

void	free_map(char **map, int height)
{
	int	i;

	if (map == NULL || height <= 0)
		return ;
	i = 0;
	while (i < height)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

int	on_destroy(t_data *data)
{
	printf("Fenêtre fermée (event 17)\n"); 
    if (data->win_ptr != NULL)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    if (data->textures.ea.xpm_ptr)
        mlx_destroy_image(data->mlx_ptr, data->textures.ea.xpm_ptr);
    if (data->textures.no.xpm_ptr)
        mlx_destroy_image(data->mlx_ptr, data->textures.no.xpm_ptr);
    if (data->textures.so.xpm_ptr)
        mlx_destroy_image(data->mlx_ptr, data->textures.so.xpm_ptr);
    if (data->textures.we.xpm_ptr)
        mlx_destroy_image(data->mlx_ptr, data->textures.we.xpm_ptr);
    if (data->screen.xpm_ptr)
        mlx_destroy_image(data->mlx_ptr, data->screen.xpm_ptr);
    if (data->minimap.img_ptr)
        mlx_destroy_image(data->mlx_ptr, data->minimap.img_ptr);
	if (data->mlx_ptr != NULL)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
    free_map(data->map.map, data->map.height);
	exit(0);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i] != NULL)
	{
		printf("%s\n", map[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juvitry <juvitry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:41:19 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/30 13:50:49 by juvitry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_error_close(char *message, t_data *data)
{
	printf(ORANGE"ERROR\n"GREY"%s\n"RESET, message);
	if (data && data->mlx_ptr)
		on_destroy(data);
	return (0);
}

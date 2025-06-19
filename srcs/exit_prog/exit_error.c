/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opique <opique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:41:19 by juvitry           #+#    #+#             */
/*   Updated: 2025/06/19 13:55:38 by opique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_error_close(char *message, t_data *data)
{
	free(data);
	printf(ORANGE"ERROR\n"GREY"%s\n"RESET, message);
	exit (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycasting_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:33:22 by paugonca          #+#    #+#             */
/*   Updated: 2023/12/07 17:33:32 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rot_raycaster(t_cub3d *cub, double rot)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = cub->dir_x;
	old_planex = cub->plane_x;
	cub->dir_x = cub->dir_x * cosf(rot) - cub->dir_y * sinf(rot);
	cub->dir_y = old_dirx * sinf(rot) + cub->dir_y * cosf(rot);
	cub->plane_x = cub->plane_x * cosf(rot) - cub->plane_y * sinf(rot);
	cub->plane_y = old_planex * sinf(rot) + cub->plane_y * cosf(rot);
}

void	init_raycaster(t_cub3d *cub)
{
	if (cub->direction == NORTH)
	{
		cub->dir_y = -1;
		cub->plane_x = 0.6;
	}
	else if (cub->direction == EAST)
	{
		cub->dir_x = 1;
		cub->plane_y = 0.6;
	}
	else if (cub->direction == SOUTH)
	{
		cub->dir_y = 1;
		cub->plane_x = -0.6;
	}
	else
	{
		cub->dir_x = -1;
		cub->plane_y = -0.6;
	}
}

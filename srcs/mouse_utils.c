/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:44:50 by paugonca          #+#    #+#             */
/*   Updated: 2023/12/08 11:45:38 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	move_with_mouse(t_cub3d *cub)
{
	double	times;

	times = (double)WWID / 2 - cub->mouse_x;
	if (cub->mouse_x > 0 && cub->mouse_x < WWID)
	{
		if (cub->mouse_x != WWID / 2)
		{
			if (times < (double)WWID / 2)
				add_player_rot(cub, ARROW_LEFT);
			else
				add_player_rot(cub, ARROW_RIGHT);
			rot_raycaster(cub, times * cub->min_ray);
			if (times < (double)WWID / 2)
				remove_player_rot(cub, ARROW_LEFT);
			else
				remove_player_rot(cub, ARROW_RIGHT);
		}
		mlx_mouse_move(cub->mlx, cub->mlx_win, WWID / 2, WHEI / 2);
	}
	else
		return (0);
	return (1);
}

int	mouse_position(int x, int y, t_cub3d *cub)
{
	if (cub->mouse_x == x && cub->mouse_y == y)
		return (0);
	cub->mouse_x = x;
	cub->mouse_y = y;
	return (1);
}

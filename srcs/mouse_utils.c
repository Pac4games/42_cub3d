/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:44:50 by paugonca          #+#    #+#             */
/*   Updated: 2023/12/08 12:32:05 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	move_with_mouse(t_cub3d *cub)
{
	double	times;
	int		arrow;

	times = WWID / 2 - cub->mouse_x;
	if (cub->mouse_x > 0 && cub->mouse_x < WWID)
	{
		if (cub->mouse_x != WWID / 2)
		{
			if (times < WWID / 2)
				arrow = ARROW_LEFT;
			else
				arrow = ARROW_RIGHT;
			add_player_rot(cub, arrow);
			rot_raycaster(cub, times * cub->min_ray);
			remove_player_rot(cub, arrow);
			mlx_mouse_move(cub->mlx, cub->mlx_win, WWID / 2, WHEI / 2);
		}
		else
			return (0);
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

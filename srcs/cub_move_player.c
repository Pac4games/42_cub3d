/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_move_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/07 19:05:59 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	move_player_and_gaze(t_cub3d *cub, float distx, float disty)
{
	int	moved;

	moved = 0;
	if (!player_colision_x(cub, (cub->player_x - 0.25) * SQR_SIZE + distx, NWALL) \
	&& !player_colision_x(cub, (cub->player_x + 0.25) * SQR_SIZE + distx, NWALL))
	{
		cub->player_x += distx;
		moved = 1;
	}
	if (!player_colision_y(cub, (cub->player_y - 0.25) * SQR_SIZE + disty, NWALL) \
	&& !player_colision_y(cub, (cub->player_y + 0.25) * SQR_SIZE + disty, NWALL))
	{
		cub->player_y += disty;
		moved = 1;
	}
	return (moved);
}

static int	sum_movement_x(t_cub3d *cub, float distx)
{
	if (!player_colision_x(cub, (cub->player_x - 0.25) * SQR_SIZE + distx, NWALL) \
	&& !player_colision_x(cub, (cub->player_x + 0.25) * SQR_SIZE + distx, NWALL))
		return (distx);
	return (0);
}

static int	sum_movement_y(t_cub3d *cub, float disty)
{
	if (!player_colision_y(cub, (cub->player_y - 0.25) * SQR_SIZE + disty, NWALL) \
	&& !player_colision_y(cub, (cub->player_y + 0.25) * SQR_SIZE + disty, NWALL))
		return (disty);
	return (0);
}

static void	sum_movements(t_cub3d *cub, float *distx, float *disty)
{
	float	dist;

	dist = SQR_SIZE;
	if (cub->move >> MOV_UP & 1)
	{
		(*distx) += sum_movement_x(cub, dist * cub->dir_x);
		(*disty) += sum_movement_y(cub, dist * cub->dir_y);
	}
	if (cub->move >> MOV_DOWN & 1)
	{
		(*distx) += sum_movement_x(cub, -dist * cub->dir_x);
		(*disty) += sum_movement_y(cub, -dist * cub->dir_y);
	}
	if (cub->move >> MOV_LEFT & 1)
	{
		(*distx) += sum_movement_x(cub, dist * cub->dir_y);
		(*disty) += sum_movement_y(cub, -dist * cub->dir_x);
	}
	if (cub->move >> MOV_RIGHT & 1)
	{
		(*distx) += sum_movement_x(cub, -dist * cub->dir_y);
		(*disty) += sum_movement_y(cub, dist * cub->dir_x);
	}
}

int	move_with_gaze(t_cub3d *cub)
{
	int		ret;
	float	distx;
	float	disty;

	distx = 0;
	disty = 0;
	sum_movements(cub, &distx, &disty);
	ret = move_player_and_gaze(cub, distx, disty);
	ret += check_door_colision(cub, distx, disty);
	return (ret);
}

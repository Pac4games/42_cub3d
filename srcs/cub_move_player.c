/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_move_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/05 23:43:10 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	move_player_and_gaze(t_cub3d *cub, float distx, float disty)
{
	if (!player_colision_x(cub, cub->player->xi + distx, NWALL) \
	&& !player_colision_x(cub, cub->player->xf + distx, NWALL))
	{
		cub->player->xi += distx;
		cub->player->xf += distx;
		cub->gaze_x += distx;
	}
	if (!player_colision_y(cub, cub->player->yi + disty, NWALL) \
	&& !player_colision_y(cub, cub->player->yf + disty, NWALL))
	{
		cub->player->yi += disty;
		cub->player->yf += disty;
		cub->gaze_y += disty;
	}
}

static int	sum_movement_x(t_cub3d *cub, float distx)
{
	if (!player_colision_x(cub, cub->player->xi + distx, NWALL) \
	&& !player_colision_x(cub, cub->player->xf + distx, NWALL))
		return (distx);
	return (0);
}

static int	sum_movement_y(t_cub3d *cub, float disty)
{
	if (!player_colision_y(cub, cub->player->yi + disty, NWALL) \
	&& !player_colision_y(cub, cub->player->yf + disty, NWALL))
		return (disty);
	return (0);
}

static void	sum_movements(t_cub3d *cub, float *distx, \
float *disty, float radians)
{
	int		dist;

	dist = STEP;
	if (cub->move >> MOV_UP & 1)
	{
		(*distx) += sum_movement_x(cub, dist * cosf(radians));
		(*disty) += sum_movement_y(cub, dist * sinf(radians));
	}
	if (cub->move >> MOV_DOWN & 1)
	{
		(*distx) += sum_movement_x(cub, -dist * cosf(radians));
		(*disty) += sum_movement_y(cub, -dist * sinf(radians));
	}
	if (cub->move >> MOV_LEFT & 1)
	{
		(*distx) += sum_movement_x(cub, dist * sinf(radians));
		(*disty) += sum_movement_y(cub, -dist * cosf(radians));
	}
	if (cub->move >> MOV_RIGHT & 1)
	{
		(*distx) += sum_movement_x(cub, -dist * sinf(radians));
		(*disty) += sum_movement_y(cub, dist * cosf(radians));
	}
}

void	move_with_gaze(t_cub3d *cub)
{
	float	radians;
	int		dist;
	float	distx;
	float	disty;

	radians = (MY_PI / 180) * (cub->degrees);
	dist = STEP;
	distx = 0;
	disty = 0;
	sum_movements(cub, &distx, &disty, radians);
	move_player_and_gaze(cub, distx, disty);
	check_door_colision(cub, dist);
}

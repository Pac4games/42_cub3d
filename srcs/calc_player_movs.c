/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_player_movs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/26 15:47:58 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	move_player(t_cub3d *cub, double distx, double disty)
{
	int	moved;

	moved = 0;
	if (!player_colision_x(cub, cub->player_x - 0.25 + distx, WALL) \
	&& (!player_colision_x(cub, cub->player_x + 0.25 + distx, WALL)))
	{
		cub->player_x += distx;
		moved = 1;
	}
	if (!player_colision_y(cub, cub->player_y - 0.25 + disty, WALL) \
	&& (!player_colision_y(cub, cub->player_y + 0.25 + disty, WALL)))
	{
		cub->player_y += disty;
		moved = 1;
	}
	return (moved);
}

static double	sum_movement_x(t_cub3d *cub, double distx)
{
	if (!player_colision_x(cub, cub->player_x - 0.25 + distx, WALL) \
	&& (!player_colision_x(cub, cub->player_x + 0.25 + distx, WALL)))
		return (distx);
	return (0);
}

static double	sum_movement_y(t_cub3d *cub, double disty)
{
	if (!player_colision_y(cub, cub->player_y - 0.25 + disty, WALL) \
	&& (!player_colision_y(cub, cub->player_y + 0.25 + disty, WALL)))
		return (disty);
	return (0);
}

static void	sum_movements(t_cub3d *cub, double *distx, double *disty)
{
	double	dist;

	dist = STEP;
	(*distx) += (cub->move >> MOV_UP & 1) * \
	sum_movement_x(cub, dist * cub->dir_x);
	(*disty) += (cub->move >> MOV_UP & 1) * \
	sum_movement_y(cub, dist * cub->dir_y);
	(*distx) += (cub->move >> MOV_DOWN & 1) * \
	sum_movement_x(cub, -dist * cub->dir_x);
	(*disty) += (cub->move >> MOV_DOWN & 1) * \
	sum_movement_y(cub, -dist * cub->dir_y);
	(*distx) += (cub->move >> MOV_LEFT & 1) * \
	sum_movement_x(cub, dist * cub->dir_y);
	(*disty) += (cub->move >> MOV_LEFT & 1) * \
	sum_movement_y(cub, -dist * cub->dir_x);
	(*distx) += (cub->move >> MOV_RIGHT & 1) * \
	sum_movement_x(cub, -dist * cub->dir_y);
	(*disty) += (cub->move >> MOV_RIGHT & 1) * \
	sum_movement_y(cub, dist * cub->dir_x);
}

int	check_colisions_and_move(t_cub3d *cub)
{
	int		ret;
	double	distx;
	double	disty;

	distx = 0;
	disty = 0;
	sum_movements(cub, &distx, &disty);
	ret = move_player(cub, distx, disty);
	ret += check_door_colision(cub, distx, disty);
	return (ret);
}

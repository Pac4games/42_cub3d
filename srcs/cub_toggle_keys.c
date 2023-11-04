/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_toggle_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:15:01 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/04 20:00:22 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	add_player_mov(t_cub3d *cub, int key)
{
	int	to_move;

	to_move = cub->move;
	if (key == TORIGHT)
		to_move |= (1 << MOV_RIGHT);
	else if (key == TOLEFT)
		to_move |= (1 << MOV_LEFT);
	else if (key == FRONT)
		to_move |= (1 << MOV_UP);
	else if (key == BACK)
		to_move |= (1 << MOV_DOWN);
	cub->move = to_move;
}

void	remove_player_mov(t_cub3d *cub, int key)
{
	int	to_move;

	to_move = cub->move;
	if (key == TORIGHT)
		to_move &= ~(1 << MOV_RIGHT);
	else if (key == TOLEFT)
		to_move &= ~(1 << MOV_LEFT);
	else if (key == FRONT)
		to_move &= ~(1 << MOV_UP);
	else if (key == BACK)
		to_move &= ~(1 << MOV_DOWN);
	cub->move = to_move;
}

void	add_player_rot(t_cub3d *cub, int key)
{
	int	to_move;

	to_move = cub->move;
	if (key == ARROW_RIGHT)
		to_move |= (1 << ROT_RIGHT);
	else if (key == ARROW_LEFT)
		to_move |= (1 << ROT_LEFT);
	cub->move = to_move;
}

void	remove_player_rot(t_cub3d *cub, int key)
{
	int	to_move;

	to_move = cub->move;
	if (key == ARROW_RIGHT)
		to_move &= ~(1 << ROT_RIGHT);
	else if (key == ARROW_LEFT)
		to_move &= ~(1 << ROT_LEFT);
	cub->move = to_move;
}

void	rot_with_gaze(t_cub3d *cub)
{
	int		newdeg;
	int		mid;
	float	radians;

	mid = cub->sqr_size * 0.25;
	newdeg = cub->degrees;
	if ((cub->move >> ROT_LEFT & 1) && !(cub->move >> ROT_RIGHT & 1))
		newdeg -= 5;
	else if ((cub->move >> ROT_RIGHT & 1) && !(cub->move >> ROT_LEFT & 1))
		newdeg += 5;
	if (newdeg != cub->degrees)
	{
		cub->degrees = newdeg % 360;
		radians = (MY_PI / 180) * cub->degrees;
		cub->gaze_x = cub->player->xi + mid + cub->sqr_size * cosf(radians);
		cub->gaze_y = cub->player->yi + mid + cub->sqr_size * sinf(radians);
	}
}

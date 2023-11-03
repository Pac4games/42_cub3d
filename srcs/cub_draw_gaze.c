/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_gaze.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:15:01 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/03 15:41:17 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	add_mov_with_gaze(t_cub3d *cub, int key)
{
	int	mid;
	int	to_move;

	mid = cub->sqr_size * 0.25;
	to_move = cub->move;
	if (cub->player->xi + mid < cub->gaze_x \
	&& abs(cub->player->xi + mid - cub->gaze_x) > 1)
	{
		if (key == BACK)
			to_move |= (1 << MOV_LEFT);
		else if (key == FRONT)
			to_move |= (1 << MOV_RIGHT);
		else if (key == TORIGHT)
			to_move |= (1 << MOV_DOWN);
		else if (key == TOLEFT)
			to_move |= (1 << MOV_UP);
	}
	else if (cub->player->xi + mid > cub->gaze_x \
	&& abs(cub->player->xi + mid - cub->gaze_x) > 1)
	{
		if (key == BACK)
			to_move |= (1 << MOV_RIGHT);
		else if (key == FRONT)
			to_move |= (1 << MOV_LEFT);
		else if (key == TORIGHT)
			to_move |= (1 << MOV_UP);
		else if (key == TOLEFT)
			to_move |= (1 << MOV_DOWN);
	}
	if (cub->player->yi + mid < cub->gaze_y \
	&& abs(cub->player->yi + mid - cub->gaze_y) > 1)
	{
		if (key == FRONT)
			to_move |= (1 << MOV_DOWN);
		else if (key == BACK)
			to_move |= (1 << MOV_UP);
		else if (key == TOLEFT)
			to_move |= (1 << MOV_RIGHT);
		else if (key == TORIGHT)
			to_move |= (1 << MOV_LEFT);
	}
	else if (cub->player->yi + mid > cub->gaze_y \
	&& abs(cub->player->yi + mid - cub->gaze_y) > 1)
	{
		if (key == TORIGHT)
			to_move |= (1 << MOV_RIGHT);
		else if (key == TOLEFT)
			to_move |= (1 << MOV_LEFT);
		else if (key == FRONT)
			to_move |= (1 << MOV_UP);
		else if (key == BACK)
			to_move |= (1 << MOV_DOWN);
	}
	cub->move = to_move;
}

void	remove_mov_with_gaze(t_cub3d *cub, int key)
{
	int	mid;
	int	to_move;

	mid = cub->sqr_size * 0.25;
	to_move = cub->move;
	if (cub->player->xi + mid < cub->gaze_x \
	&& abs(cub->player->xi + mid - cub->gaze_x) > 1)
	{
		if (key == BACK)
			to_move &= ~(1 << MOV_LEFT);
		else if (key == FRONT)
			to_move &= ~(1 << MOV_RIGHT);
		else if (key == TORIGHT)
			to_move &= ~(1 << MOV_DOWN);
		else if (key == TOLEFT)
			to_move &= ~(1 << MOV_UP);
	}
	else if (cub->player->xi + mid > cub->gaze_x \
	&& abs(cub->player->xi + mid - cub->gaze_x) > 1)
	{
		if (key == BACK)
			to_move &= ~(1 << MOV_RIGHT);
		else if (key == FRONT)
			to_move &= ~(1 << MOV_LEFT);
		else if (key == TORIGHT)
			to_move &= ~(1 << MOV_UP);
		else if (key == TOLEFT)
			to_move &= ~(1 << MOV_DOWN);
	}
	if (cub->player->yi + mid < cub->gaze_y \
	&& abs(cub->player->yi + mid - cub->gaze_y) > 1)
	{
		if (key == FRONT)
			to_move &= ~(1 << MOV_DOWN);
		else if (key == BACK)
			to_move &= ~(1 << MOV_UP);
		else if (key == TOLEFT)
			to_move &= ~(1 << MOV_RIGHT);
		else if (key == TORIGHT)
			to_move &= ~(1 << MOV_LEFT);
	}
	else if (cub->player->yi + mid > cub->gaze_y \
	&& abs(cub->player->yi + mid - cub->gaze_y) > 1)
	{
		if (key == TORIGHT)
			to_move &= ~(1 << MOV_RIGHT);
		else if (key == TOLEFT)
			to_move &= ~(1 << MOV_LEFT);
		else if (key == FRONT)
			to_move &= ~(1 << MOV_UP);
		else if (key == BACK)
			to_move &= ~(1 << MOV_DOWN);
	}
	cub->move = to_move;
}

void	add_rot_with_gaze(t_cub3d *cub, int key)
{
	int	to_move;

	to_move = cub->move;
	if (key == ARROW_RIGHT)
		to_move |= (1 << ROT_RIGHT);
	else if (key == ARROW_LEFT)
		to_move |= (1 << ROT_LEFT);
	cub->move = to_move;
}

void	remove_rot_with_gaze(t_cub3d *cub, int key)
{
	int	to_move;

	to_move = cub->move;
	if (key == ARROW_RIGHT)
		to_move &= ~(1 << ROT_RIGHT);
	else if (key == ARROW_LEFT)
		to_move &= ~(1 << ROT_LEFT);
	cub->move = to_move;
}

void	get_initial_gaze(t_cub3d *cub, int dist)
{
	int		mid;
	float	deg;

	mid = cub->sqr_size * 0.25;
	cub->gaze_x = cub->player->xi + \
	(cub->player->xf - cub->player->xi) * 0.5;
	cub->gaze_y = cub->player->yi + \
	(cub->player->yf - cub->player->yi) * 0.5;
	deg = 180;
	if (cub->direction == NNORTH)
	{
		cub->gaze_y -= dist;
		deg = 270;
	}
	else if (cub->direction == NSOUTH)
	{
		cub->gaze_y += dist;
		deg = 90;
	}
	else if (cub->direction == NEAST)
	{
		cub->gaze_x += dist;
		deg = 0;
	}
	else if (cub->direction == NWEST)
		cub->gaze_x -= dist;
	cub->degrees = (MY_PI / 180) * deg;
}

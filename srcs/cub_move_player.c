/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_move_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/04 12:01:49 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	player_in_wall_x(t_cub3d *cub, int dist)
{
	int	x;
	int	x2;
	int	y;

	x = 0;
	y = 0;
	while (y < cub->map->tot_cols - 1 && dist > \
	cub->minimap->mapx[y] + cub->sqr_size)
		y++;
	while (x < cub->map->tot_rows - 1 && cub->sqr_size \
	+ cub->minimap->mapy[x] < cub->player->yi)
		x++;
	x2 = x;
	while (x2 < cub->map->tot_rows - 1 && cub->sqr_size \
	+ cub->minimap->mapy[x2] < cub->player->yf)
		x2++;
	if (x < cub->map->tot_rows && y < cub->map->tot_cols \
	&& cub->map->map[x][y] == NWALL)
		return (1);
	if (x2 != x && x2 < cub->map->tot_rows && y < \
	cub->map->tot_cols && cub->map->map[x2][y] == NWALL)
		return (1);
	return (0);
}

static int	player_in_wall_y(t_cub3d *cub, int dist)
{
	int	x;
	int	y;
	int	y2;

	x = 0;
	y = 0;
	while (x < cub->map->tot_rows - 1 && dist > \
	cub->minimap->mapy[x] + cub->sqr_size)
		x++;
	while (y < cub->map->tot_cols - 1 && cub->sqr_size \
	+ cub->minimap->mapx[y] < cub->player->xi)
		y++;
	y2 = y;
	while (y2 < cub->map->tot_cols - 1 && cub->sqr_size \
	+ cub->minimap->mapx[y2] < cub->player->xf)
		y2++;
	if (x < cub->map->tot_rows && y < cub->map->tot_cols \
	&& cub->map->map[x][y] == NWALL)
		return (1);
	if (y2 != y && x < cub->map->tot_rows && y2 < \
	cub->map->tot_cols && cub->map->map[x][y2] == NWALL)
		return (1);
	return (0);
}

static void	move_player_and_gaze(t_cub3d *cub, int distx, int disty)
{
	if (!player_in_wall_x(cub, cub->player->xi + distx) \
	&& !player_in_wall_x(cub, cub->player->xf + distx))
	{
		cub->player->xi += distx;
		cub->player->xf += distx;
		cub->gaze_x += distx;
	}
	if (!player_in_wall_y(cub, cub->player->yi + disty) \
	&& !player_in_wall_y(cub, cub->player->yf + disty))
	{
		cub->player->yi += disty;
		cub->player->yf += disty;
		cub->gaze_y += disty;
	}
}

void	move_with_gaze(t_cub3d *cub)
{
	float	radians;
	int		dist;

	radians = (MY_PI / 180) * (cub->degrees);
	dist = (cub->sqr_size / 9);
	if (cub->move >> MOV_UP & 1)
		move_player_and_gaze(cub, dist * cosf(radians), dist * sinf(radians));
	if (cub->move >> MOV_DOWN & 1)
		move_player_and_gaze(cub, -dist * cosf(radians), -dist * sinf(radians));
	if (cub->move >> MOV_LEFT & 1)
		move_player_and_gaze(cub, dist * sinf(radians), -dist * cosf(radians));
	if (cub->move >> MOV_RIGHT & 1)
		move_player_and_gaze(cub, -dist * sinf(radians), dist * cosf(radians));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_move_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/05 21:31:29 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	player_colision_x(t_cub3d *cub, int dist, int type)
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
	&& cub->map->map[x][y] == type)
		return (reload_player_pos(cub, x, y));
	if (x2 != x && x2 < cub->map->tot_rows && y < \
	cub->map->tot_cols && cub->map->map[x2][y] == type)
		return (reload_player_pos(cub, x2, y));
	return (0);
}

static int	player_colision_y(t_cub3d *cub, int dist, int type)
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
	&& cub->map->map[x][y] == type)
		return (reload_player_pos(cub, x, y));
	if (y2 != y && x < cub->map->tot_rows && y2 < \
	cub->map->tot_cols && cub->map->map[x][y2] == type)
		return (reload_player_pos(cub, x, y2));
	return (0);
}

static int	check_door_colision(t_cub3d *cub, int dist)
{
	int		door;

	door = NUP_DOOR_AT_UP;
	while (door <= NDOWN_DOOR_AT_RIGHT)
	{
		if (((door == NUP_DOOR_AT_RIGHT || door == NDOWN_DOOR_AT_RIGHT) \
		&& player_colision_x(cub, cub->player->xi - dist, door) == 2) || \
		((door == NUP_DOOR_AT_LEFT || door == NDOWN_DOOR_AT_LEFT) \
		&& player_colision_x(cub, cub->player->xf + dist, door) == 2) || \
		((door == NUP_DOOR_AT_DOWN || door == NDOWN_DOOR_AT_DOWN) \
		&& player_colision_y(cub, cub->player->yi - dist, door) == 2) || \
		((door == NUP_DOOR_AT_UP || door == NDOWN_DOOR_AT_UP) \
		&& player_colision_y(cub, cub->player->yf + dist, door) == 2))
		{
			set_gaze(cub, cub->sqr_size);
			return (1);
		}
		else
			door++;
	}
	return (0);
}

static void	move_player_and_gaze(t_cub3d *cub, int distx, int disty)
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

void	move_with_gaze(t_cub3d *cub)
{
	float	radians;
	int		dist;

	radians = (MY_PI / 180) * (cub->degrees);
	dist = STEP;
	if (cub->move >> MOV_UP & 1)
		move_player_and_gaze(cub, dist * cosf(radians), dist * sinf(radians));
	if (cub->move >> MOV_DOWN & 1)
		move_player_and_gaze(cub, -dist * cosf(radians), -dist * sinf(radians));
	if (cub->move >> MOV_LEFT & 1)
		move_player_and_gaze(cub, dist * sinf(radians), -dist * cosf(radians));
	if (cub->move >> MOV_RIGHT & 1)
		move_player_and_gaze(cub, -dist * sinf(radians), dist * cosf(radians));
	check_door_colision(cub, dist);
}

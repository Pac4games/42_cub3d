/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/03 15:41:39 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_player_lines(t_cub3d *cub, t_vector vec, int dist, int color)
{
	int	times;

	times = -1;
	vec.xf = vec.xi;
	while (++times <= dist)
	{
		if (times == 0 || times == dist)
		{
			vec.yi++;
			vec.yf--;
		}
		draw_line(cub, &vec, color);
		vec.xi++;
		vec.xf++;
		if (times == 0 || times == dist)
		{
			vec.yi--;
			vec.yf++;
		}
	}
}

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

int	move_with_gaze(t_cub3d *cub)
{
	int	distx;
	int	disty;

	distx = cub->sqr_size / 6;
	disty = distx;
	if ((cub->move >> MOV_UP & 1) && !(cub->move >> MOV_DOWN & 1) \
	&& !player_in_wall_y(cub, cub->player->yi - disty))
	{
		cub->player->yi -= disty;
		cub->player->yf -= disty;
		cub->gaze_y -= disty;
	}
	else if ((cub->move >> MOV_DOWN & 1) && !(cub->move >> MOV_UP & 1) \
	&& !player_in_wall_y(cub, cub->player->yf + disty))
	{
		cub->player->yi += disty;
		cub->player->yf += disty;
		cub->gaze_y += disty;
	}
	else
		disty = 0;
	if ((cub->move >> MOV_LEFT & 1) && !(cub->move >> MOV_RIGHT & 1) \
	&& !player_in_wall_x(cub, cub->player->xi - distx))
	{
		cub->player->xi -= distx;
		cub->player->xf -= distx;
		cub->gaze_x -= distx;
	}
	else if ((cub->move >> MOV_RIGHT & 1) && !(cub->move >> MOV_LEFT & 1) \
	&& !player_in_wall_x(cub, cub->player->xf + distx))
	{
		cub->player->xi += distx;
		cub->player->xf += distx;
		cub->gaze_x += distx;
	}
	else
		distx = 0;
	if (!distx && !disty)
		return (0);
	return (1);
}

int	rot_with_gaze(t_cub3d *cub)
{
	float	newdeg;
	int		mid;

	mid = cub->sqr_size * 0.25;
	newdeg = cub->degrees;
	if ((cub->move >> ROT_LEFT & 1) && !(cub->move >> ROT_RIGHT & 1))
		newdeg -= 0.05;
	else if ((cub->move >> ROT_RIGHT & 1) && !(cub->move >> ROT_LEFT & 1))
		newdeg += 0.05;
	if (newdeg != cub->degrees)
	{
		cub->degrees = newdeg;
		cub->gaze_x = cub->player->xi + mid + cub->sqr_size * cosf(newdeg);
		cub->gaze_y = cub->player->yi + mid + cub->sqr_size * sinf(newdeg);
		return (1);
	}
	return (0);
}

t_vector	*get_player_pos(t_cub3d *cub, int x, int y)
{
	t_vector	*vec;
	int			dist;

	vec = malloc(sizeof(*vec));
	if (!vec)
		return (NULL);
	dist = cub->sqr_size * 0.25;
	while (++x < cub->map->tot_rows)
	{
		y = 0;
		while (++y < cub->map->tot_cols)
		{
			if (cub->map->map[x - 1][y - 1] >= NNORTH \
			&& cub->map->map[x - 1][y - 1] <= NWEST)
			{
				cub->direction = cub->map->map[x - 1][y - 1];
				vec->xi = cub->minimap->mapx[y - 1] + dist;
				vec->yi = cub->minimap->mapy[x - 1] + dist;
				vec->xf = cub->minimap->mapx[y] - dist;
				vec->yf = cub->minimap->mapy[x] - dist;
				break ;
			}
		}
	}
	return (vec);
}

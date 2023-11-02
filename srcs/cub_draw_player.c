/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/02 12:46:30 by mnascime         ###   ########.fr       */
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
	cub->minimap->mapx[x][y] + get_sqr_size(cub))
		y++;
	while (x < cub->map->tot_rows - 1 && get_sqr_size(cub) \
	+ cub->minimap->mapy[x][y] < cub->player->yi)
		x++;
	x2 = x;
	while (x2 < cub->map->tot_rows - 1 && get_sqr_size(cub) \
	+ cub->minimap->mapy[x2][y] < cub->player->yf)
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
	cub->minimap->mapy[x][y] + get_sqr_size(cub))
		x++;
	while (y < cub->map->tot_cols - 1 && get_sqr_size(cub) \
	+ cub->minimap->mapx[x][y] < cub->player->xi)
		y++;
	y2 = y;
	while (y2 < cub->map->tot_cols - 1 && get_sqr_size(cub) \
	+ cub->minimap->mapx[x][y2] < cub->player->xf)
		y2++;
	if (x < cub->map->tot_rows && y < cub->map->tot_cols \
	&& cub->map->map[x][y] == NWALL)
		return (1);
	if (y2 != y && x < cub->map->tot_rows && y2 < \
	cub->map->tot_cols && cub->map->map[x][y2] == NWALL)
		return (1);
	return (0);
}

int	move_player(t_cub3d *cub, int key)
{
	int	dist;

	if (!key)
		return (0);
	dist = get_sqr_size(cub) / 6;
	if (key == FRONT && !player_in_wall_y(cub, cub->player->yi - dist))
	{
		cub->player->yi -= dist;
		cub->player->yf -= dist;
		cub->gaze_y -= dist;
		return (1);
	}
	if (key == BACK && !player_in_wall_y(cub, cub->player->yf + dist))
	{
		cub->player->yi += dist;
		cub->player->yf += dist;
		cub->gaze_y += dist;
		return (1);
	}
	if (key == TOLEFT && !player_in_wall_x(cub, cub->player->xi - dist))
	{
		cub->player->xi -= dist;
		cub->player->xf -= dist;
		cub->gaze_x -= dist;
		return (1);
	}
	if (key == TORIGHT && !player_in_wall_x(cub, cub->player->xf + dist))
	{
		cub->player->xi += dist;
		cub->player->xf += dist;
		cub->gaze_x += dist;
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
	dist = get_sqr_size(cub) * 0.25;
	while (++x < cub->map->tot_rows)
	{
		y = 0;
		while (++y < cub->map->tot_cols)
		{
			if (cub->map->map[x - 1][y - 1] >= NNORTH \
			&& cub->map->map[x - 1][y - 1] <= NWEST)
			{
				cub->direction = cub->map->map[x - 1][y - 1];
				vec->xi = cub->minimap->mapx[x - 1][y - 1] + dist;
				vec->yi = cub->minimap->mapy[x - 1][y - 1] + dist;
				vec->xf = cub->minimap->mapx[x][y] - dist;
				vec->yf = cub->minimap->mapy[x][y] - dist;
				break ;
			}
		}
	}
	return (vec);
}

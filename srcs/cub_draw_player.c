/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/07 18:55:21 by mnascime         ###   ########.fr       */
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
		minimap_draw_line(cub, &vec, color);
		vec.xi++;
		vec.xf++;
		if (times == 0 || times == dist)
		{
			vec.yi--;
			vec.yf++;
		}
	}
}

static void	new_player_dir(t_cub3d *cub, int type)
{
	cub->direction = type;
	if (cub->direction == NUP_DOOR_AT_UP \
	|| cub->direction == NDOWN_DOOR_AT_UP)
		cub->direction = NSOUTH;
	else if (cub->direction == NUP_DOOR_AT_LEFT \
	|| cub->direction == NDOWN_DOOR_AT_LEFT)
		cub->direction = NEAST;
	else if (cub->direction == NUP_DOOR_AT_RIGHT \
	|| cub->direction == NDOWN_DOOR_AT_RIGHT)
		cub->direction = NWEST;
	else if (cub->direction == NUP_DOOR_AT_DOWN \
	|| cub->direction == NDOWN_DOOR_AT_DOWN)
		cub->direction = NNORTH;
}

int	reload_player_pos(t_cub3d *cub, int x, int y)
{
	int			dist;

	if (cub->map->map[x][y] == NWALL)
		return (1);
	new_player_dir(cub, cub->map->map[x][y]);
	dist = SQR_SIZE * 0.25;
	cub->player->xi = cub->minimap->mapx[y] + dist + 1;
	cub->player->yi = cub->minimap->mapy[x] + dist + 1;
	cub->player->xf = cub->minimap->mapx[y] + SQR_SIZE - dist;
	cub->player->yf = cub->minimap->mapy[x] + SQR_SIZE - dist;
	if (cub->direction == NNORTH || cub->direction == NWEST)
		dist *= -1;
	if (cub->direction == NNORTH || cub->direction == NSOUTH)
	{
		cub->player->yi += dist;
		cub->player->yf += dist;
	}
	if (cub->direction == NEAST || cub->direction == NWEST)
	{
		cub->player->xi += dist;
		cub->player->xf += dist;
	}
	change_textures(cub, x, y);
	init_raycaster(cub);
	return (2);
}

void	get_player_pos(t_cub3d *cub, int x, int y)
{
	while (++x < cub->map->tot_rows)
	{
		y = -1;
		while (++y < cub->map->tot_cols)
		{
			if (cub->map->map[x][y] >= NNORTH \
			&& cub->map->map[x][y] <= NWEST)
			{
				cub->direction = cub->map->map[x][y];
				cub->player_x = y + 0.5;
				cub->player_y = x + 0.5;
				break ;
			}
		}
	}
}

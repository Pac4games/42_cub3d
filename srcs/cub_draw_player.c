/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/08 18:14:09 by mnascime         ###   ########.fr       */
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

int	reload_player_pos(t_cub3d *cub, int y, int x)
{
	float	dist;

	if (cub->map->map[y][x] == NWALL)
		return (1);
	new_player_dir(cub, cub->map->map[y][x]);
	dist = 0.5;
	cub->player_x = x + dist;
	cub->player_y = y + dist;
	if (cub->direction == NNORTH || cub->direction == NWEST)
		dist *= -1;
	if (cub->direction == NNORTH || cub->direction == NSOUTH)
		cub->player_x += dist;
	if (cub->direction == NEAST || cub->direction == NWEST)
		cub->player_y += dist;
	change_textures(cub, y, x);
	init_raycaster(cub);
	return (2);
}

void	get_player_pos(t_cub3d *cub, int y, int x)
{
	while (++y < cub->map->tot_rows)
	{
		x = -1;
		while (++x < cub->map->tot_cols)
		{
			if (cub->map->map[y][x] >= NNORTH \
			&& cub->map->map[y][x] <= NWEST)
			{
				cub->direction = cub->map->map[y][x];
				cub->player_y = y + 0.5;
				cub->player_x = x + 0.5;
				break ;
			}
		}
	}
}

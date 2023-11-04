/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/04 11:57:29 by mnascime         ###   ########.fr       */
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

void	get_initial_gaze(t_cub3d *cub, int dist)
{
	cub->gaze_x = cub->player->xi + \
	(cub->player->xf - cub->player->xi) * 0.5;
	cub->gaze_y = cub->player->yi + \
	(cub->player->yf - cub->player->yi) * 0.5;
	cub->degrees = 180;
	if (cub->direction == NNORTH)
		cub->gaze_y -= dist;
	else if (cub->direction == NSOUTH)
		cub->gaze_y += dist;
	else if (cub->direction == NEAST)
		cub->gaze_x += dist;
	else if (cub->direction == NWEST)
		cub->gaze_x -= dist;
	if (cub->direction == NNORTH)
		cub->degrees = 270;
	else if (cub->direction == NSOUTH)
		cub->degrees = 90;
	else if (cub->direction == NEAST)
		cub->degrees = 0;
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

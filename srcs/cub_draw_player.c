/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/30 13:56:35 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_player_lines(t_data *img, t_vector *vec, int dist, int color)
{
	int	times;

	times = -1;
	while (++times <= dist)
	{
		if (times == 0 || times == dist)
		{
			vec->yi++;
			vec->yf--;
		}
		draw_line(img, vec, color);
		vec->xi++;
		vec->xf++;
		if (times == 0 || times == dist)
		{
			vec->yi--;
			vec->yf++;
		}
	}
}

void	draw_player(t_data *img, t_map *map)
{
	int			x;
	int			y;
	t_vector	vec;
	int			dist;

	dist = get_sqr_size(img) * 0.25;
	x = 0;
	while (++x <= map->tot_rows)
	{
		y = 0;
		while (++y <= map->tot_cols)
		{
			if (map->map[x - 1][y - 1] >= NNORTH && map->map[x - 1][y - 1] <= NWEST)
			{
				begin_coord(&vec, img->cub->minimap->mapx[x - 1][y - 1] \
				+ dist, img->cub->minimap->mapy[x - 1][y - 1] + dist);
				end_coord(&vec, img->cub->minimap->mapx[x - 1][y - 1] + dist,\
				img->cub->minimap->mapy[x][y] - dist);
				draw_player_lines(img, &vec, dist * 2, 0x44FF24);
			}
		}
	}
}

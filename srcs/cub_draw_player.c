/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/09 14:13:10 by mnascime         ###   ########.fr       */
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

int	reload_player_pos(t_cub3d *cub, int y, int x)
{
	if (cub->map->map[y][x] == WALL)
		return (1);
	cub->dir_x *= -1;
	cub->dir_y *= -1;
	cub->plane_x *= -1;
	cub->plane_y *= -1;
	cub->inverted = -1;
	change_textures(cub, y, x);
	return (2);
}

void	get_player_pos(t_cub3d *cub, int y, int x)
{
	while (++y < cub->map->tot_rows)
	{
		x = -1;
		while (++x < cub->map->tot_cols)
		{
			if (cub->map->map[y][x] == NORTH \
			|| cub->map->map[y][x] == SOUTH \
			|| cub->map->map[y][x] == EAST \
			|| cub->map->map[y][x] == WEST)
			{
				cub->direction = cub->map->map[y][x];
				cub->player_y = y + 0.5;
				cub->player_x = x + 0.5;
				break ;
			}
		}
	}
}

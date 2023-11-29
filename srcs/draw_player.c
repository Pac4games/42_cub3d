/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/10 14:36:26 by mnascime         ###   ########.fr       */
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

void	draw_player(t_cub3d *cub, double ycorr, double xcorr)
{
	t_vector	vec;

	xcorr++;
	ycorr++;
	vec.xi = cub->sqr_size + (cub->player_x - 0.25) * cub->sqr_size;
	vec.yi = cub->sqr_size + (cub->player_y - 0.25) * cub->sqr_size;
	vec.xf = cub->sqr_size + (cub->player_x + 0.25) * cub->sqr_size;
	vec.yf = cub->sqr_size + (cub->player_y + 0.25) * cub->sqr_size;
	draw_player_lines(cub, vec, (double)(cub->sqr_size * 0.5), 0x44FF24);
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
	change_txtrs(cub, y, x);
	return (2);
}

int	get_player_sqr(t_cub3d *cub, int is_horiz)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < cub->map->tot_rows && y + 1 < cub->player_y)
		y++;
	while (x < cub->map->tot_cols && cub->player_x > x + 1)
		x++;
	if (is_horiz)
		return (x);
	return (y);
}

void	init_player_pos(t_cub3d *cub, int y, int x)
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

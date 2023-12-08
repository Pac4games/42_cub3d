/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:37:57 by mnascime          #+#    #+#             */
/*   Updated: 2023/12/07 16:30:12 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_paralell_hlines(t_cub3d *cub, t_vector *vec, int dist, int color)
{
	int	times;

	times = 0;
	vec->xf--;
	while (++times < dist)
	{
		minimap_draw_line(cub, vec, color);
		vec->yi++;
		vec->yf++;
	}
}

void	draw_doors(t_cub3d *cub, t_map *map, double ycorr, double xcorr)
{
	int			y;
	int			x;
	t_vector	vec;

	y = -1;
	while (++y < map->tot_rows)
	{
		x = -1;
		while (++x < map->tot_cols)
		{
			get_h_vector(cub, &vec, x, y);
			position_minimap(&vec, ycorr, xcorr);
			if (map->map[y][x] == DOOR)
				draw_paralell_hlines(cub, &vec, cub->sqr_size, 0x00FFFF);
		}
	}
}

void	draw_walls(t_cub3d *cub, t_map *map, double ycorr, double xcorr)
{
	int			y;
	int			x;
	t_vector	vec;

	y = -1;
	while (++y < map->tot_rows)
	{
		x = -1;
		while (++x < map->tot_cols)
		{
			get_h_vector(cub, &vec, x, y);
			position_minimap(&vec, ycorr, xcorr);
			if (map->map[y][x] == WALL)
				draw_paralell_hlines(cub, &vec, cub->sqr_size, 0xF2F2F2);
			else if (map->map[y][x] != SPACE)
				draw_paralell_hlines(cub, &vec, cub->sqr_size, 0x727272);
			else
				continue ;
			minimap_draw_line(cub, &vec, 0x000000);
			get_v_vector(cub, &vec, x, y);
			position_minimap(&vec, ycorr, xcorr);
			minimap_draw_line(cub, &vec, 0x000000);
		}
	}
}

void	position_minimap(t_vector *vec, double ycorr, double xcorr)
{
	vec->yi += (int)ycorr;
	vec->yf += (int)ycorr;
	vec->xi += (int)xcorr;
	vec->xf += (int)xcorr;
}

void	redraw_minimap(t_cub3d *cub)
{
	double		midx;
	double		midy;
	double		xcorr;
	double		ycorr;
	t_vector	vec;

	midx = WWID * 0.15;
	midy = WHEI * 0.15;
	ycorr = midy - (cub->sqr_size + cub->player_y * cub->sqr_size);
	xcorr = midx - (cub->sqr_size + cub->player_x * cub->sqr_size);
	draw_walls(cub, cub->map, ycorr, xcorr);
	draw_doors(cub, cub->map, ycorr, xcorr);
	draw_player(cub, ycorr, xcorr);
	ft_memset(&vec, 0, sizeof(vec));
	vec.xi = cub->sqr_size + cub->player_x * \
	(double)cub->sqr_size + (double)cub->sqr_size * cub->dir_x;
	vec.xf = cub->sqr_size + cub->player_x * \
	(double)cub->sqr_size + (double)cub->sqr_size * cub->dir_x * 1.25;
	vec.yi = cub->sqr_size + cub->player_y * \
	(double)cub->sqr_size + (double)cub->sqr_size * cub->dir_y;
	vec.yf = cub->sqr_size + cub->player_y * \
	(double)cub->sqr_size + (double)cub->sqr_size * cub->dir_y * 1.25;
	position_minimap(&vec, ycorr, xcorr);
	minimap_draw_line(cub, &vec, 0x44FF24);
}

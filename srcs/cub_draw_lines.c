/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:06:19 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/28 12:52:37 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_paralell_hlines(t_data *img, t_vector *vec, int beg, int color)
{
	int	times;

	times = 0;
	vec->yf--;
	while (++times < (abs(beg) * 2))
	{
		draw_line(img, vec, color);
		vec->xi++;
		vec->xf++;
	}
}

void	draw_paralell_vlines(t_data *img, t_vector *vec, int beg, int color)
{
	int	times;

	times = 0;
	vec->xf--;
	while (++times < (abs(beg) * 2))
	{
		draw_line(img, vec, color);
		vec->yi++;
		vec->yf++;
	}
}

void	draw_midlines(t_data *img, t_map *map)
{
	int			x;
	int			y;
	t_vector	vec;

	x = 0;
	while (++x < map->tot_rows)
	{
		y = 0;
		while (++y < map->tot_cols)
		{
			begin_coord(&vec, img->mapx[x - 1][y - 1], img->mapy[x - 1][y - 1]);
			end_coord(&vec, img->mapx[x][y - 1], img->mapy[x][y - 1]);
			if (map->map[x - 1][y - 1] == NWALL)
				draw_paralell_hlines(img, &vec, get_sqr_size(img), 0xFFFFFF);
			else if (map->map[x - 1][y - 1] != NSPACE)
				draw_paralell_hlines(img, &vec, get_sqr_size(img), 0x666666);
			begin_coord(&vec, img->mapx[x - 1][y - 1], img->mapy[x - 1][y - 1]);
			end_coord(&vec, img->mapx[x - 1][y], img->mapy[x - 1][y]);
			if (map->map[x - 1][y - 1] == NWALL)
				draw_paralell_vlines(img, &vec, get_sqr_size(img), 0xFFFFFF);
			else if (map->map[x - 1][y - 1] != NSPACE)
				draw_paralell_vlines(img, &vec, get_sqr_size(img), 0x666666);
		}
	}
}

void	draw_vedges(t_data *img, t_map *map)
{
	int			x;
	int			y;
	t_vector	vec;
	int			dist;

	x = map->tot_rows - 1;
	y = 1;
	dist = (img->mapx[1][2] - img->mapx[1][1]) * 0.5;
	while (y < map->tot_cols)
	{
		begin_coord(&vec, img->mapx[x][y - 1], img->mapy[x][y - 1]);
		end_coord(&vec, img->mapx[x][y], img->mapy[x][y]);
		if (map->map[x][y - 1] == NWALL)
			draw_paralell_vlines(img, &vec, dist, 0xFFFFFF);
		y++;
	}
}

void	draw_hedges(t_data *img, t_map *map)
{
	int			x;
	int			y;
	t_vector	vec;
	int			dist;

	x = 0;
	dist = (img->mapx[1][2] - img->mapx[1][1]) * 0.5;
	while (++x < map->tot_rows)
	{
		y = 1;
		while (y < map->tot_cols)
		{
			y++;
			if (y == map->tot_cols)
			{
				begin_coord(&vec, img->mapx[x - 1][y - 1], \
				img->mapy[x - 1][y - 1]);
				end_coord(&vec, img->mapx[x][y - 1], img->mapy[x][y - 1]);
				if (map->map[x - 1][y - 1] == NWALL)
					draw_paralell_hlines(img, &vec, dist, 0xFFFFFF);
				break ;
			}
		}
	}
}

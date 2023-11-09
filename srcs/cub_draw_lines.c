/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:06:19 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/09 12:31:32 by mnascime         ###   ########.fr       */
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

void	draw_paralell_vlines(t_cub3d *cub, t_vector *vec, int dist, int color)
{
	int	times;

	times = 0;
	vec->yf--;
	while (++times < dist)
	{
		minimap_draw_line(cub, vec, color);
		vec->xi++;
		vec->xf++;
	}
}

void	get_v_vector(t_cub3d *cub, t_vector *vec, int y, int x)
{
	vec->xi = x;
	vec->yi = y;
	vec->xf = x;
	vec->yf = y + cub->sqr_size;
}

void	get_h_vector(t_cub3d *cub, t_vector *vec, int y, int x)
{
	vec->xi = x;
	vec->yi = y;
	vec->xf = x + cub->sqr_size;
	vec->yf = y;
}

void	draw_minimap(t_cub3d *cub, t_map *map, double xcorr, double ycorr)
{
	int			y;
	int			x;
	t_vector	vec;

	xcorr++;
	ycorr++;
	y = -1;
	while (++y < map->tot_rows)
	{
		x = -1;
		while (++x < map->tot_cols)
		{
			get_h_vector(cub, &vec, cub->sqr_size + y * \
			cub->sqr_size, cub->sqr_size + x * cub->sqr_size);
			//minimap_scale_down(&vec, xcorr, ycorr);
			if (map->map[y][x] == WALL)
				draw_paralell_hlines(cub, &vec, cub->sqr_size, 0xF2F2F2);
			else if (map->map[y][x] != SPACE)
				draw_paralell_hlines(cub, &vec, cub->sqr_size, 0x727272);
			else
				continue ;
			minimap_draw_line(cub, &vec, 0x000000);
			get_v_vector(cub, &vec, cub->sqr_size + y * \
			cub->sqr_size, cub->sqr_size + x * cub->sqr_size);
			vec.xi += cub->sqr_size - 1;
			vec.xf += cub->sqr_size - 1;
			minimap_draw_line(cub, &vec, 0x000000);
		}
	}
}

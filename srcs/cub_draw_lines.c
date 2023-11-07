/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:06:19 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/07 19:16:33 by mnascime         ###   ########.fr       */
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

void	get_v_vector(t_vector *vec, int x, int y)
{
	x--;
	y--;
	vec->xi = SQR_SIZE + x * SQR_SIZE;
	vec->yi = SQR_SIZE + y * SQR_SIZE;
	vec->xf = SQR_SIZE + x * SQR_SIZE;
	y++;
	vec->yf = SQR_SIZE + y * SQR_SIZE;
}

void	get_h_vector(t_vector *vec, int x, int y)
{
	x--;
	y--;
	vec->xi = x;
	vec->yi = y;
	x++;
	vec->xf = x;
	vec->yf = y;
}

void	draw_minimap(t_cub3d *cub, t_map *map, int xcorr, int ycorr)
{
	int			x;
	int			y;
	t_vector	vec;

	x = -1;
	while (++x < map->tot_rows)
	{
		y = -1;
		while (++y < map->tot_cols)
		{
			get_h_vector(&vec, cub->minimap->mapy[x], cub->minimap->mapx[y]);
			printf("%d\n", cub->minimap->mapy[x] + xcorr);
			minimap_scale_down(&vec, xcorr, ycorr);
			if (map->map[x][y] == NWALL)
				draw_paralell_hlines(cub, &vec, SQR_SIZE, 0xF2F2F2);
			else if (map->map[x][y] != NSPACE)
				draw_paralell_hlines(cub, &vec, SQR_SIZE, 0x727272);
		}
	}
}

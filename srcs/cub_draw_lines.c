/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:06:19 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/29 16:16:37 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_paralell_hlines(t_data *img, t_vector *vec, int beg, int color)
{
	int	times;

	times = 0;
	vec->xf--;
	while (++times < beg)
	{
		draw_line(img, vec, color);
		vec->yi++;
		vec->yf++;
	}
}

void	draw_paralell_vlines(t_data *img, t_vector *vec, int beg, int color)
{
	int	times;

	times = 0;
	vec->yf--;
	while (++times < beg)
	{
		draw_line(img, vec, color);
		vec->xi++;
		vec->xf++;
	}
}

void	get_h_vector(t_data *img, t_vector *vec, int x, int y)
{
	begin_coord(vec, img->cub->minimap->mapxi[x][y], \
	img->cub->minimap->mapyi[x][y]);
	end_coord(vec, img->cub->minimap->mapxf[x][y], \
	img->cub->minimap->mapyi[x][y]);
}

void	get_v_vector(t_data *img, t_vector *vec, int x, int y)
{
	begin_coord(vec, img->cub->minimap->mapxi[x][y], \
	img->cub->minimap->mapyi[x][y]);
	end_coord(vec, img->cub->minimap->mapxi[x][y], \
	img->cub->minimap->mapyf[x][y]);
}

void	draw_minimap(t_data *img, t_map *map)
{
	int			x;
	int			y;
	t_vector	vec;
	int			dist;

	dist = img->cub->minimap->mapxf[0][0] \
	- img->cub->minimap->mapxi[0][0];
	x = -1;
	while (++x < map->tot_rows)
	{
		y = -1;
		while (++y < map->tot_cols)
		{
			get_h_vector(img, &vec, x, y);
			if (map->map[x][y] == NWALL)
				draw_paralell_hlines(img, &vec, dist, 0xFFFFFF);
			else if (map->map[x][y] != NSPACE)
				draw_paralell_hlines(img, &vec, dist, 0x666666);
			get_v_vector(img, &vec, x, y);
			if (map->map[x][y] == NWALL)
				draw_paralell_vlines(img, &vec, get_sqr_size(img), 0xFFFFFF);
			else if (map->map[x][y] != NSPACE)
				draw_paralell_vlines(img, &vec, get_sqr_size(img), 0x666666);
		}
	}
}

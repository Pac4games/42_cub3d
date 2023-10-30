/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:06:19 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/30 11:31:19 by mnascime         ###   ########.fr       */
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

void	get_v_vector(t_data *img, t_vector *vec, int x, int y)
{
	int	dist;

	dist = img->cub->minimap->mapx[1][1] \
	- img->cub->minimap->mapx[0][0];
	begin_coord(vec, img->cub->minimap->mapx[x - 1][y - 1], \
	img->cub->minimap->mapy[x - 1][y - 1]);
	if (x < img->cub->map->tot_rows)
		end_coord(vec, img->cub->minimap->mapx[x][y - 1], \
	img->cub->minimap->mapy[x][y - 1]);
	else
	{
		end_coord(vec, img->cub->minimap->mapx[x - 1][y - 1], \
	img->cub->minimap->mapy[x - 1][y - 1]);
		vec->yf += dist;
	}
}

void	get_h_vector(t_data *img, t_vector *vec, int x, int y)
{
	int	dist;

	dist = img->cub->minimap->mapx[1][1] \
	- img->cub->minimap->mapx[0][0];
	begin_coord(vec, img->cub->minimap->mapx[x - 1][y - 1], \
	img->cub->minimap->mapy[x - 1][y - 1]);
	if (y < img->cub->map->tot_cols)
		end_coord(vec, img->cub->minimap->mapx[x - 1][y], \
	img->cub->minimap->mapy[x - 1][y]);
	else
	{
		end_coord(vec, img->cub->minimap->mapx[x - 1][y - 1], \
	img->cub->minimap->mapy[x - 1][y - 1]);
		vec->xf += dist;
	}
}

void	draw_minimap(t_data *img, t_map *map)
{
	int			x;
	int			y;
	t_vector	vec;
	int			dist;

	dist = img->cub->minimap->mapx[1][1] \
	- img->cub->minimap->mapx[0][0];
	x = 0;
	while (++x <= map->tot_rows)
	{
		y = 0;
		while (++y <= map->tot_cols)
		{
			get_h_vector(img, &vec, x, y);
			if (map->map[x - 1][y - 1] == NWALL)
				draw_paralell_hlines(img, &vec, dist, 0xFFFFFF);
			else if (map->map[x - 1][y - 1] != NSPACE)
				draw_paralell_hlines(img, &vec, dist, 0x666666);
			get_v_vector(img, &vec, x, y);
			if (map->map[x - 1][y - 1] == NWALL)
				draw_paralell_vlines(img, &vec, dist, 0xFFFFFF);
			else if (map->map[x - 1][y - 1] != NSPACE)
				draw_paralell_vlines(img, &vec, dist, 0x666666);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/31 19:36:20 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_player_lines(t_data *img, t_vector vec, int dist, int color)
{
	int	times;

	times = -1;
	while (++times <= dist)
	{
		if (times == 0 || times == dist)
		{
			vec.yi++;
			vec.yf--;
		}
		draw_line(img, &vec, color);
		vec.xi++;
		vec.xf++;
		if (times == 0 || times == dist)
		{
			vec.yi--;
			vec.yf++;
		}
	}
}

static int	player_in_wall_x(t_data *img, int key, int dist)
{
	int	x;
	int	y;
	int	distx;

	distx = img->cub->player->xf - \
	(img->cub->player->xf - img->cub->player->xi) * 0.5;
	if (key == TOLEFT)
		distx -= dist;
	if (key == TORIGHT)
		distx += dist;
	x = 0;
	y = 0;
	while (x < img->cub->map->tot_rows && \
	img->cub->minimap->mapy[x][y] < img->cub->player->yi)
		x++;
	while (y < img->cub->map->tot_cols && \
	img->cub->minimap->mapx[x][y] < img->cub->player->xi)
		y++;
	if (img->cub->map->map[x][y] == NWALL && \
	abs(distx - img->cub->minimap->mapx[x][y]) < get_sqr_size(img->cub) * 0.5)
		return (1);
	if (y > 0 && img->cub->map->map[x][y - 1] == NWALL && \
	abs(distx - img->cub->minimap->mapx[x][y - 1]) < get_sqr_size(img->cub))
		return (2);
	return (0);
}

static int	player_in_wall_y(t_data *img, int key, int dist)
{
	int	x;
	int	y;
	int	disty;

	disty = img->cub->player->yf - \
	(img->cub->player->yf - img->cub->player->yi) * 0.5;
	if (key == FRONT)
		disty -= dist;
	if (key == BACK)
		disty += dist;
	x = 0;
	y = 0;
	while (x < img->cub->map->tot_rows && \
	img->cub->minimap->mapy[x][y] < disty)
		x++;
	while (y < img->cub->map->tot_cols && \
	img->cub->minimap->mapx[x][y] < img->cub->player->xi)
		y++;
	if (img->cub->map->map[x][y] == NWALL && \
	abs(disty - img->cub->minimap->mapy[x][y]) < get_sqr_size(img->cub) * 0.25)
		return (1);
	if (img->cub->map->map[x - 1][y] == NWALL && \
	abs(disty - img->cub->minimap->mapy[x - 1][y]) < get_sqr_size(img->cub))
		return (2);
	return (0);
}

void	move_player(t_data *img, int key)
{
	int	dist;

	dist = get_sqr_size(img->cub) * 0.1;
	if (key == FRONT && !player_in_wall_y(img, key, dist))
	{
		img->cub->player->yi -= dist;
		img->cub->player->yf -= dist;
	}
	if (key == BACK && !player_in_wall_y(img, key, dist))
	{
		img->cub->player->yi += dist;
		img->cub->player->yf += dist;
	}
	if (key == TOLEFT && !player_in_wall_x(img, key, dist))
	{
		img->cub->player->xi -= dist;
		img->cub->player->xf -= dist;
	}
	if (key == TORIGHT && !player_in_wall_x(img, key, dist))
	{
		img->cub->player->xi += dist;
		img->cub->player->xf += dist;
	}
}

t_vector	*get_player_pos(t_cub3d *cub)
{
	int			x;
	int			y;
	t_vector	*vec;
	int			dist;

	vec = malloc(sizeof(*vec));
	if (!vec)
		return (NULL);
	dist = get_sqr_size(cub) * 0.25;
	x = 0;
	while (++x < cub->map->tot_rows)
	{
		y = 0;
		while (++y < cub->map->tot_cols)
		{
			if (cub->map->map[x - 1][y - 1] >= NNORTH && cub->map->map[x - 1][y - 1] <= NWEST)
			{
				vec->xi = cub->minimap->mapx[x - 1][y - 1] + dist;
				vec->yi = cub->minimap->mapy[x - 1][y - 1] + dist;
				vec->xf = cub->minimap->mapx[x - 1][y - 1] + dist;
				vec->yf = cub->minimap->mapy[x][y] - dist;
				break ;
			}
		}
	}
	return (vec);
}

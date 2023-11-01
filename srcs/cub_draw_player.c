/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:38:02 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/01 16:20:53 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_player_lines(t_data *img, t_vector vec, int dist, int color)
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

static int	player_in_wall_x(t_data *img, int dist)
{
	int	x;
	int	x2;
	int	y;

	x = 0;
	y = 0;
	while (y < img->cub->map->tot_cols - 1 && dist > \
	img->cub->minimap->mapx[x][y] + get_sqr_size(img->cub))
		y++;
	while (x < img->cub->map->tot_rows - 1 && get_sqr_size(img->cub) \
	+ img->cub->minimap->mapy[x][y] < img->cub->player->yi)
		x++;
	x2 = x;
	while (x2 < img->cub->map->tot_rows - 1 && get_sqr_size(img->cub) \
	+ img->cub->minimap->mapy[x2][y] < img->cub->player->yf)
		x2++;
	if (x < img->cub->map->tot_rows && y < img->cub->map->tot_cols \
	&& img->cub->map->map[x][y] == NWALL)
		return (1);
	if (x2 != x && x2 < img->cub->map->tot_rows && y < \
	img->cub->map->tot_cols && img->cub->map->map[x2][y] == NWALL)
		return (1);
	return (0);
}

static int	player_in_wall_y(t_data *img, int dist)
{
	int	x;
	int	y;
	int	y2;

	x = 0;
	y = 0;
	while (x < img->cub->map->tot_rows - 1 && dist > \
	img->cub->minimap->mapy[x][y] + get_sqr_size(img->cub))
		x++;
	while (y < img->cub->map->tot_cols - 1 && get_sqr_size(img->cub) \
	+ img->cub->minimap->mapx[x][y] < img->cub->player->xi)
		y++;
	y2 = y;
	while (y2 < img->cub->map->tot_cols - 1 && get_sqr_size(img->cub) \
	+ img->cub->minimap->mapx[x][y2] < img->cub->player->xf)
		y2++;
	if (x < img->cub->map->tot_rows && y < img->cub->map->tot_cols \
	&& img->cub->map->map[x][y] == NWALL)
		return (1);
	if (y2 != y && x < img->cub->map->tot_rows && y2 < \
	img->cub->map->tot_cols && img->cub->map->map[x][y2] == NWALL)
		return (1);
	return (0);
}

void	move_player(t_data *img, int key)
{
	int	dist;

	dist = get_sqr_size(img->cub) * 0.2;
	if (key == FRONT && !player_in_wall_y(img, img->cub->player->yi - dist))
	{
		img->cub->player->yi -= dist;
		img->cub->player->yf -= dist;
	}
	if (key == BACK && !player_in_wall_y(img, img->cub->player->yf + dist))
	{
		img->cub->player->yi += dist;
		img->cub->player->yf += dist;
	}
	if (key == TOLEFT && !player_in_wall_x(img, img->cub->player->xi - dist))
	{
		img->cub->player->xi -= dist;
		img->cub->player->xf -= dist;
	}
	if (key == TORIGHT && !player_in_wall_x(img, img->cub->player->xf + dist))
	{
		img->cub->player->xi += dist;
		img->cub->player->xf += dist;
	}
}

t_vector	*get_player_pos(t_cub3d *cub, int x, int y)
{
	t_vector	*vec;
	int			dist;

	vec = malloc(sizeof(*vec));
	if (!vec)
		return (NULL);
	dist = get_sqr_size(cub) * 0.25;
	while (++x < cub->map->tot_rows)
	{
		y = 0;
		while (++y < cub->map->tot_cols)
		{
			if (cub->map->map[x - 1][y - 1] >= NNORTH \
			&& cub->map->map[x - 1][y - 1] <= NWEST)
			{
				vec->xi = cub->minimap->mapx[x - 1][y - 1] + dist;
				vec->yi = cub->minimap->mapy[x - 1][y - 1] + dist;
				vec->xf = cub->minimap->mapx[x][y] - dist;
				vec->yf = cub->minimap->mapy[x][y] - dist;
				break ;
			}
		}
	}
	return (vec);
}

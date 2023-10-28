/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_doors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:39:59 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/28 13:15:50 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_up_doors(t_data *img, t_vector *vec, int map_point)
{
	int	color;

	if (map_point == NUP_DOOR_AT_UP || map_point == NDOWN_DOOR_AT_UP)
	{
		if (map_point == NUP_DOOR_AT_UP)
			color = 0x00FFFF;
		else
			color = 0xFF00FF;
		vec->xf--;
		draw_line(img, vec, color);
		vec->yi++;
		vec->yf++;
		draw_line(img, vec, color);
		vec->yi++;
		vec->yf++;
		draw_line(img, vec, color);
	}
}

static void	check_down_doors(t_data *img, \
t_vector *vec, int map_point, int dist)
{
	int	color;

	if (map_point == NUP_DOOR_AT_DOWN || map_point == NDOWN_DOOR_AT_DOWN)
	{
		vec->xf--;
		vec->yi += (dist * 2) - 4;
		vec->yf += (dist * 2) - 4;
		if (map_point == NUP_DOOR_AT_DOWN)
			color = 0x00FFFF;
		else
			color = 0xFF00FF;
		draw_line(img, vec, color);
		vec->yi++;
		vec->yf++;
		draw_line(img, vec, color);
		vec->yi++;
		vec->yf++;
		draw_line(img, vec, color);
	}
}

static void	check_left_doors(t_data *img, t_vector *vec, int map_point)
{
	int	color;

	if (map_point == NUP_DOOR_AT_LEFT || map_point == NDOWN_DOOR_AT_LEFT)
	{
		if (map_point == NUP_DOOR_AT_LEFT)
			color = 0x00FFFF;
		else
			color = 0xFF00FF;
		vec->yf--;
		draw_line(img, vec, color);
		vec->xi++;
		vec->xf++;
		draw_line(img, vec, color);
		vec->xi++;
		vec->xf++;
		draw_line(img, vec, color);
	}
}

static void	check_right_doors(t_data *img, \
t_vector *vec, int map_point, int dist)
{
	int	color;

	if (map_point == NUP_DOOR_AT_RIGHT || map_point == NDOWN_DOOR_AT_RIGHT)
	{
		if (map_point == NUP_DOOR_AT_RIGHT)
			color = 0x00FFFF;
		else
			color = 0xFF00FF;
		vec->yf--;
		vec->xi += (dist * 2) - 4;
		vec->xf += (dist * 2) - 4;
		draw_line(img, vec, color);
		vec->xi++;
		vec->xf++;
		draw_line(img, vec, color);
		vec->xi++;
		vec->xf++;
		draw_line(img, vec, color);
	}
}

void	draw_doors(t_data *img, t_map *map)
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
			begin_coord(&vec, img->mapx[x - 1][y - 1], img->mapy[x - 1][y - 1]);
			end_coord(&vec, img->mapx[x][y - 1], img->mapy[x][y - 1]);
			check_left_doors(img, &vec, map->map[x - 1][y - 1]);
			check_right_doors(img, &vec, map->map[x - 1][y - 1], dist);
			begin_coord(&vec, img->mapx[x - 1][y - 1], img->mapy[x - 1][y - 1]);
			end_coord(&vec, img->mapx[x - 1][y], img->mapy[x - 1][y]);
			check_up_doors(img, &vec, map->map[x - 1][y - 1]);
			check_down_doors(img, &vec, map->map[x - 1][y - 1], dist);
			y++;
		}
	}
}

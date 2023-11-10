/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:39:59 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/09 16:40:34 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_up_doors(t_cub3d *cub, t_vector *vec, char map_point, int max)
{
	int	color;

	if (map_point == UP_DOOR_AT_UP || map_point == DOWN_DOOR_AT_UP)
	{
		if (map_point == UP_DOOR_AT_UP)
			color = 0x00FFFF;
		else
			color = 0xFF00FF;
		vec->xf--;
		while (--max)
		{
			minimap_draw_line(cub, vec, color);
			vec->yi++;
			vec->yf++;
		}
	}
}

static void	check_down_doors(t_cub3d *cub, \
t_vector *vec, char map_point, int dist)
{
	int	color;
	int	max;

	if (map_point == UP_DOOR_AT_DOWN || map_point == DOWN_DOOR_AT_DOWN)
	{
		vec->xf--;
		max = (int)(dist * DOOR_MULTIP);
		vec->yi += dist - max;
		vec->yf += dist - max;
		if (map_point == UP_DOOR_AT_DOWN)
			color = 0x00FFFF;
		else
			color = 0xFF00FF;
		while (--max)
		{
			minimap_draw_line(cub, vec, color);
			vec->yi++;
			vec->yf++;
		}
	}
}

static void	check_left_doors(t_cub3d *cub, t_vector *vec, \
int map_point, char max)
{
	int	color;

	if (map_point == UP_DOOR_AT_LEFT || map_point == DOWN_DOOR_AT_LEFT)
	{
		if (map_point == UP_DOOR_AT_LEFT)
			color = 0x00FFFF;
		else
			color = 0xFF00FF;
		vec->yf--;
		while (--max)
		{
			minimap_draw_line(cub, vec, color);
			vec->xi++;
			vec->xf++;
		}
	}
}

static void	check_right_doors(t_cub3d *cub, \
t_vector *vec, char map_point, int dist)
{
	int	color;
	int	max;

	if (map_point == UP_DOOR_AT_RIGHT || map_point == DOWN_DOOR_AT_RIGHT)
	{
		vec->yf--;
		max = (int)(dist * DOOR_MULTIP);
		vec->xi += dist - max;
		vec->xf += dist - max;
		if (map_point == UP_DOOR_AT_RIGHT)
			color = 0x00FFFF;
		else
			color = 0xFF00FF;
		while (--max)
		{
			minimap_draw_line(cub, vec, color);
			vec->xi++;
			vec->xf++;
		}
	}
}

void	draw_doors(t_cub3d *cub, t_map *map, double xcorr, double ycorr)
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
			//position_minimap(&vec, xcorr, ycorr);
			check_up_doors(cub, &vec, map->map[y][x], \
			(int)(cub->sqr_size * DOOR_MULTIP));
			check_down_doors(cub, &vec, map->map[y][x], cub->sqr_size);
			get_v_vector(cub, &vec, cub->sqr_size + y * \
			cub->sqr_size, cub->sqr_size + x * cub->sqr_size);
			//position_minimap(&vec, xcorr, ycorr);
			check_left_doors(cub, &vec, map->map[y][x], \
			(int)(cub->sqr_size * DOOR_MULTIP));
			check_right_doors(cub, &vec, map->map[y][x], cub->sqr_size);
		}
	}
}

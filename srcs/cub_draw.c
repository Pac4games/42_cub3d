/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:06:19 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/26 22:12:35 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	begin_coord(t_vector *vector, int x, int y)
{
	vector->xi = x;
	vector->yi = y;
}

static void	end_coord(t_vector *vector, int x, int y)
{
	vector->xf = x;
	vector->yf = y;
}

void draw_paralell_hlines(t_data *img, t_vector *vec, int beg, int color)
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

void draw_paralell_vlines(t_data *img, t_vector *vec, int beg, int color)
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

static void	check_up_doors(t_data *img, t_vector *vec, int map_point)
{
	if (map_point == NUP_DOOR_AT_UP)
	{
		vec->xf--;
		draw_line(img, vec, 0x00FFFF);
		vec->yi++;
		vec->yf++;
		draw_line(img, vec, 0x00FFFF);
		vec->yi++;
		vec->yf++;
		draw_line(img, vec, 0x00FFFF);
	}
	if (map_point == NDOWN_DOOR_AT_UP)
	{
		vec->xf--;
		draw_line(img, vec, 0xFF00FF);
		vec->yi++;
		vec->yf++;
		draw_line(img, vec, 0xFF00FF);
		vec->yi++;
		vec->yf++;
		draw_line(img, vec, 0xFF00FF);
	}
}
static void	check_down_doors(t_data *img, t_vector *vec, int map_point, int dist)
{
	if (map_point == NUP_DOOR_AT_DOWN || map_point == NDOWN_DOOR_AT_DOWN)
	{
		vec->xf--;
		vec->yi += dist - 4;
		vec->yf += dist - 4;
	}
	if (map_point == NUP_DOOR_AT_DOWN)
	{
		draw_line(img, vec, 0x00FFFF);
		vec->yi++;
		vec->yf++;
		draw_line(img, vec, 0x00FFFF);
		vec->yi++;
		vec->yf++;
		draw_line(img, vec, 0x00FFFF);
	}
	if (map_point == NDOWN_DOOR_AT_DOWN)
	{
		draw_line(img, vec, 0xFF00FF);
		vec->yi++;
		vec->yf++;
		draw_line(img, vec, 0xFF00FF);
		vec->yi++;
		vec->yf++;
		draw_line(img, vec, 0xFF00FF);
	}
}

static void	check_left_doors(t_data *img, t_vector *vec, int map_point)
{
	if (map_point == NUP_DOOR_AT_LEFT)
	{
		vec->yf--;
		draw_line(img, vec, 0x00FFFF);
		vec->xi++;
		vec->xf++;
		draw_line(img, vec, 0x00FFFF);
		vec->xi++;
		vec->xf++;
		draw_line(img, vec, 0x00FFFF);
	}
	if (map_point == NDOWN_DOOR_AT_LEFT)
	{
		vec->yf--;
		draw_line(img, vec, 0xFF00FF);
		vec->xi++;
		vec->xf++;
		draw_line(img, vec, 0xFF00FF);
		vec->xi++;
		vec->xf++;
		draw_line(img, vec, 0xFF00FF);
	}
}

static void	check_right_doors(t_data *img, t_vector *vec, int map_point, int dist)
{
	if (map_point == NUP_DOOR_AT_RIGHT)
	{
		vec->yf--;
		vec->xi += dist - 4;
		vec->xf += dist - 4;
		draw_line(img, vec, 0x00FFFF);
		vec->xi++;
		vec->xf++;
		draw_line(img, vec, 0x00FFFF);
		vec->xi++;
		vec->xf++;
		draw_line(img, vec, 0x00FFFF);
	}
	if (map_point == NDOWN_DOOR_AT_RIGHT)
	{
		vec->yf--;
		vec->xi += dist - 3;
		vec->xf += dist - 3;
		draw_line(img, vec, 0xFF00FF);
		vec->xi++;
		vec->xf++;
		draw_line(img, vec, 0xFF00FF);
		vec->xi++;
		vec->xf++;
		draw_line(img, vec, 0xFF00FF);
	}
}

void	draw_midlines(t_data *img, t_map *map, int **mapx, int **mapy)
{
	int			x;
	int			y;
	t_vector	vec;
	int			dist;

	x = 0;
	dist = (mapx[1][2] - mapx[1][1]) * 0.5;
	while (++x < map->tot_rows)
	{
		y = 1;
		while (y < map->tot_cols)
		{
			begin_coord(&vec, mapx[x - 1][y - 1], mapy[x - 1][y - 1]);
			end_coord(&vec, mapx[x][y - 1], mapy[x][y - 1]);
			if (map->map[x - 1][y - 1] == NWALL)
				draw_paralell_hlines(img, &vec, dist, 0xFFFFFF);
			else if (map->map[x - 1][y - 1] != NSPACE)
				draw_paralell_hlines(img, &vec, dist, 0x666666);
			begin_coord(&vec, mapx[x - 1][y - 1], mapy[x - 1][y - 1]);
			end_coord(&vec, mapx[x - 1][y], mapy[x - 1][y]);
			if (map->map[x - 1][y - 1] == NWALL)
				draw_paralell_vlines(img, &vec, dist, 0xFFFFFF);
			else if (map->map[x - 1][y - 1] != NSPACE)
				draw_paralell_vlines(img, &vec, dist, 0x666666);
			y++;
		}
	}
}

void	draw_vedges(t_data *img, t_map *map, int **mapx, int **mapy)
{
	int			x;
	int			y;
	t_vector	vec;
	int			dist;

	x = map->tot_rows - 1;
	y = 1;
	dist = (mapx[1][2] - mapx[1][1]) * 0.5;
	while (y < map->tot_cols)
	{
		begin_coord(&vec, mapx[x][y - 1], mapy[x][y - 1]);
		end_coord(&vec, mapx[x][y], mapy[x][y]);
		if (map->map[x][y - 1] == NWALL)
			draw_paralell_vlines(img, &vec, dist, 0xFFFFFF);
		y++;
	}
}

void	draw_hedges(t_data *img, t_map *map, int **mapx, int **mapy)
{
	int			x;
	int			y;
	t_vector	vec;
	int			dist;

	x = 0;
	dist = (mapx[1][2] - mapx[1][1]) * 0.5;
	while (++x < map->tot_rows)
	{
		y = 1;
		while (y < map->tot_cols)
		{
			y++;
			if (y == map->tot_cols)
			{
				begin_coord(&vec, mapx[x - 1][y - 1], mapy[x - 1][y - 1]);
				end_coord(&vec, mapx[x][y - 1], mapy[x][y - 1]);
				if (map->map[x - 1][y - 1] == NWALL)
					draw_paralell_hlines(img, &vec, dist, 0xFFFFFF);
				break ;
			}
		}
	}
}

void	draw_doors(t_data *img, t_map *map, int **mapx, int **mapy)
{
	int			x;
	int			y;
	t_vector	vec;
	int			dist;

	x = 0;
	dist = (mapx[1][2] - mapx[1][1]);
	while (++x < map->tot_rows)
	{
		y = 1;
		while (y < map->tot_cols)
		{
			begin_coord(&vec, mapx[x - 1][y - 1], mapy[x - 1][y - 1]);
			end_coord(&vec, mapx[x][y - 1], mapy[x][y - 1]);
			check_left_doors(img, &vec, map->map[x - 1][y - 1]);
			check_right_doors(img, &vec, map->map[x - 1][y - 1], dist);
			begin_coord(&vec, mapx[x - 1][y - 1], mapy[x - 1][y - 1]);
			end_coord(&vec, mapx[x - 1][y], mapy[x - 1][y]);
			check_up_doors(img, &vec, map->map[x - 1][y - 1]);
			check_down_doors(img, &vec, map->map[x - 1][y - 1], dist);
			y++;
		}
	}
}

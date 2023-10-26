/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:15:22 by margarida         #+#    #+#             */
/*   Updated: 2023/10/26 22:00:00 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	quits(t_data *img)
{
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window (img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	destroy_matrix(&img->map);
	exit(EXIT_SUCCESS);
}

static int	read_keys(int key_pressed, void *param)
{
	t_data	*img;

	img = (t_data *) param;
	if (key_pressed == ESC)
		quits(img);
	return (0);
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && x < WWID && y < WHEI)
	{
		dst = data->addr + (y * data->line_length + \
		x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	smlnum(int rows, int cols)
{
	if (rows < cols)
		return (cols);
	return (rows);
}

void	draw_line(t_data *data, t_vector *vector, int color)
{
	double	dx;
	double	dy;
	double	pxx;
	double	pxy;
	int		pxs;

	pxx = vector->xi;
	pxy = vector->yi;
	dx = vector->xf - vector->xi;
	dy = vector->yf - vector->yi;
	pxs = sqrt((dx * dx) + (dy * dy));
	dx /= pxs;
	dy /= pxs;
	pxx = vector->xi;
	pxy = vector->yi;
	while (pxs)
	{
		my_mlx_pixel_put(data, pxx, pxy, color);
		pxx += dx;
		pxy += dy;
		--pxs;
	}
}

static int	**update_display_x(t_map *map, int y, int x)
{
	int		**newmap;
	int		sml;
	int		smltab;
	int		tempx;

	newmap = solo_matrix(map->tot_rows, map->tot_cols);
	sml = (WHEI * 0.55) / smlnum(map->tot_rows, map->tot_cols);
	smltab = smlnum(map->tot_rows, map->tot_cols) - 1;
	while (++y < map->tot_rows)
	{
		x = -1;
		while (++x < map->tot_cols)
		{
			tempx = (WWID - sml * smltab) * 0.05 + x * sml;
			newmap[y][x] = tempx;
		}
	}
	return (newmap);
}

static int	**update_display_y(t_map *map, int y, int x)
{
	int		**newmap;
	int		sml;
	int		smltab;
	int		tempy;

	newmap = solo_matrix(map->tot_rows, map->tot_cols);
	sml = (WHEI * 0.55) / smlnum(map->tot_rows, map->tot_cols);
	smltab = smlnum(map->tot_rows, map->tot_cols) - 1;
	while (++y < map->tot_rows)
	{
		x = -1;
		tempy = (WHEI - sml * smltab) * 0.1 + y * sml;
		while (++x < map->tot_cols)
			newmap[y][x] = tempy;
	}
	return (newmap);
}

void	display_in_canvas(t_cub3d *cub3d)
{
	t_data	img;
	int		**mapx;
	int		**mapy;

	cub3d->display = &img;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, WWID, WHEI, "cub3D");
	img.img = mlx_new_image(img.mlx, WWID, WHEI);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
	&img.line_length, &img.endian);
	img.map = cub3d->map;
	mapx = update_display_x(cub3d->map, -1, -1);
	mapy = update_display_y(cub3d->map, -1, -1);
	draw_midlines(&img, cub3d->map, mapx, mapy);
	draw_hedges(&img, cub3d->map, mapx, mapy);
	draw_vedges(&img, cub3d->map, mapx, mapy);
	draw_doors(&img, cub3d->map, mapx, mapy);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_key_hook (img.mlx_win, read_keys, &img);
	mlx_hook(img.mlx_win, 17, (1L << 0), quits, &img);
	mlx_loop(img.mlx);
}

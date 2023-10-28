/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:15:22 by margarida         #+#    #+#             */
/*   Updated: 2023/10/28 12:38:37 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	quits(t_data *img)
{
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window (img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	destroy_matrix(img->mapx, img->cub->map->tot_rows);
	destroy_matrix(img->mapy, img->cub->map->tot_rows);
	destroy_cub(img->cub);
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

void	display_in_canvas(t_cub3d *cub3d)
{
	t_data	img;

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, WWID, WHEI, "cub3D");
	img.img = mlx_new_image(img.mlx, WWID, WHEI);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
	&img.line_length, &img.endian);
	img.cub = cub3d;
	img.map = cub3d->map;
	img.mapx = update_display_x(cub3d->map->tot_rows, cub3d->map_cols, -1, -1);
	img.mapy = update_display_y(cub3d->map->tot_rows, cub3d->map_cols, -1, -1);
	draw_midlines(&img, cub3d->map);
	draw_hedges(&img, cub3d->map);
	draw_vedges(&img, cub3d->map);
	draw_doors(&img, cub3d->map);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_key_hook (img.mlx_win, read_keys, &img);
	mlx_hook(img.mlx_win, 17, (1L << 0), quits, &img);
	mlx_loop(img.mlx);
}

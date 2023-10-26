/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:15:22 by margarida         #+#    #+#             */
/*   Updated: 2023/10/25 22:09:45 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	quits(t_cub3d *img)
{
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window (img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	destroy_matrix(&img->map);
	exit(EXIT_SUCCESS);
}

int	read_keys(int key_pressed, void *param)
{
	t_cub3d	*img;

	img = (t_cub3d *) param;
	if (key_pressed == ESC)
		quits(img);
	return (0);
}

void	my_mlx_pixel_put(t_cub3d *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && x < WWID && y < WHEI)
	{
		dst = data->addr + (y * data->line_length + \
		x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_cub3d *data, t_vector *vector, int zi, int zf)
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
		my_mlx_pixel_put(data, pxx, pxy, zi);
		zi = recolor(zi, ((zf >> 16) & 0xFF), \
		((zf >> 8) & 0xFF), ((zf) & 0xFF));
		pxx += dx;
		pxy += dy;
		--pxs;
	}
}

void	display_in_canvas(t_map *map)
{
	t_cub3d	img;
	double	**blockx;
	double	**blocky;

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, WWID, WHEI, "cub3D");
	img.img = mlx_new_image(img.mlx, WWID, WHEI);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
	&img.line_length, &img.endian);
	img.map = map;
	blockx = creat_blockx(map, -1, -1);
	blocky = creat_blocky(map, -1, -1);
	rescale(map, blockx, blocky);
	colorize(map);
	draw_midlines(&img, map, blockx, blocky);
	draw_hedges(&img, map, blockx, blocky);
	draw_vedges(&img, map, blockx, blocky);
	free_blocks(map->tot_rows, blockx, blocky);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_key_hook (img.mlx_win, read_keys, &img);
	mlx_hook(img.mlx_win, 17, (1L << 0), quits, &img);
	mlx_loop(img.mlx);
}

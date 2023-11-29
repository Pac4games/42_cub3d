/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_drawing_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:06:56 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/10 13:23:09 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	minimap_pixel_put(t_cub3d *cub, int x, int y, int color)
{
	char	*dst;

	if (x > cub->sqr_size && y > cub->sqr_size \
	&& x < WWID * 0.4 && y < WHEI * 0.4)
	{
		dst = cub->addr + (y * cub->line_length + \
		x * (cub->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	minimap_draw_line(t_cub3d *cub, t_vector *vector, int color)
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
		minimap_pixel_put(cub, pxx, pxy, color);
		pxx += dx;
		pxy += dy;
		--pxs;
	}
}

void	my_mlx_pixel_put(t_cub3d *cub, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && x < WWID && y < WHEI)
	{
		dst = cub->addr + (y * cub->line_length + \
		x * (cub->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_cub3d *cub, t_vector *vector, int color)
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
		my_mlx_pixel_put(cub, pxx, pxy, color);
		pxx += dx;
		pxy += dy;
		--pxs;
	}
}

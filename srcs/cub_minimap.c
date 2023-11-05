/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:37:52 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/05 17:38:43 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	*update_display_x(int size, int cols, int x)
{
	int		*newmap;
	int		sml;
	int		tempx;

	newmap = malloc(sizeof(newmap) * cols);
	if (!newmap)
		return (0);
	sml = size;
	while (++x < cols)
	{
		tempx = sml + x * sml;
		newmap[x] = tempx;
	}
	return (newmap);
}

int	*update_display_y(int size, int rows, int y)
{
	int		*newmap;
	int		sml;
	int		tempy;

	newmap = malloc(sizeof(newmap) * rows);
	if (!newmap)
		return (0);
	sml = size;
	while (++y < rows)
	{
		tempy = sml + y * sml;
		newmap[y] = tempy;
	}
	return (newmap);
}

int	get_sqr_size(void)
{
	int	dist;

	dist = SQR_SIZE;
	if (dist < 18)
		dist = 18;
	return (dist);
}

void	redraw_minimap(t_cub3d *cub)
{
	int	midx;
	int	midy;
	int	xcorr;
	int	ycorr;

	midx = WWID * 0.2;
	midy = WHEI * 0.2;
	xcorr = midx - WWID * 0.05 - (cub->player->xi \
	+ (cub->player->xf - cub->player->xi) * 0.5);
	ycorr = midy - WHEI * 0.05 - (cub->player->yi \
	+ (cub->player->yf - cub->player->yi) * 0.5);
	draw_minimap(cub, cub->map, xcorr, ycorr);
	draw_doors(cub, cub->map, xcorr, ycorr);
	player_scaled_down(cub, xcorr, ycorr);
	my_mlx_pixel_put(cub, cub->gaze_x + xcorr, \
	cub->gaze_y + ycorr, 0x44FF24, 0);
}

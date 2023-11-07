/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:37:52 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/07 19:01:43 by mnascime         ###   ########.fr       */
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
	t_vector vec;

	midx = WWID * 0.15;
	midy = WHEI * 0.15;
	xcorr = midx - cub->player_x * SQR_SIZE;
	ycorr = midy - cub->player_y * SQR_SIZE;
	draw_minimap(cub, cub->map, xcorr, ycorr);
	draw_doors(cub, cub->map, xcorr, ycorr);
	player_scaled_down(cub, xcorr, ycorr);
	vec.xi = cub->player_x * SQR_SIZE + SQR_SIZE * cub->dir_x + xcorr;
	vec.xf = cub->player_x * SQR_SIZE + SQR_SIZE * cub->dir_x * 1.5 + xcorr;
	vec.yi = cub->player_y * SQR_SIZE + SQR_SIZE * cub->dir_y + ycorr;
	vec.yf = cub->player_y * SQR_SIZE + SQR_SIZE * cub->dir_y * 1.5 + ycorr;
	minimap_draw_line(cub, &vec, 0x44FF24);
}

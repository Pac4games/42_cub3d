/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:37:52 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/09 12:30:54 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	double		midx;
	double		midy;
	double		xcorr;
	double		ycorr;
	t_vector	vec;

	midx = WWID * 0.15;
	midy = WHEI * 0.15;
	xcorr = midx - cub->sqr_size + cub->player_x * cub->sqr_size;
	ycorr = midy - cub->sqr_size + cub->player_y * cub->sqr_size;
	draw_minimap(cub, cub->map, ycorr, xcorr);
	draw_doors(cub, cub->map, ycorr, xcorr);
	player_scaled_down(cub, ycorr, xcorr);
	vec.xi = cub->sqr_size + cub->player_x * \
	cub->sqr_size + cub->sqr_size * cub->dir_x;
	vec.xf = cub->sqr_size + cub->player_x * \
	cub->sqr_size + cub->sqr_size * cub->dir_x * 1.25;
	vec.yi = cub->sqr_size + cub->player_y * \
	cub->sqr_size + cub->sqr_size * cub->dir_y;
	vec.yf = cub->sqr_size + cub->player_y * \
	cub->sqr_size + cub->sqr_size * cub->dir_y * 1.25;
	minimap_draw_line(cub, &vec, 0x44FF24);
}

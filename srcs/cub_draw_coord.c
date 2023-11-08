/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_coord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:41:33 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/08 17:50:57 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	minimap_scale_down(t_vector *vec, int xcorr, int ycorr)
{
	vec->xi += xcorr;
	vec->xf += xcorr;
	vec->yi += ycorr;
	vec->yf += ycorr;
}

void	player_scaled_down(t_cub3d *cub, int xcorr, int ycorr)
{
	t_vector	vec;

	xcorr++;
	ycorr++;
	vec.xi = cub->sqr_size + (cub->player_x - 0.25) * cub->sqr_size;
	vec.yi = cub->sqr_size + (cub->player_y - 0.25) * cub->sqr_size;
	vec.xf = cub->sqr_size + (cub->player_x + 0.25) * cub->sqr_size;
	vec.yf = cub->sqr_size + (cub->player_y + 0.25) * cub->sqr_size;
	draw_player_lines(cub, vec, (float)(cub->sqr_size * 0.5), 0x44FF24);
}

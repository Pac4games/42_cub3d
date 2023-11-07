/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_coord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:41:33 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/07 19:00:44 by mnascime         ###   ########.fr       */
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

	vec.xi = (cub->player_x - 0.25) * SQR_SIZE + xcorr;
	vec.yi = (cub->player_y - 0.25) * SQR_SIZE + ycorr;
	vec.xf = (cub->player_x + 0.25) * SQR_SIZE + xcorr;
	vec.yf = (cub->player_y + 0.25) * SQR_SIZE + ycorr;
	draw_player_lines(cub, vec, (float)(SQR_SIZE * 0.5), 0x44FF24);
}

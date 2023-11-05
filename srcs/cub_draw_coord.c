/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_coord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:41:33 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/05 17:36:50 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	begin_coord(t_vector *vector, int x, int y)
{
	vector->xi = x;
	vector->yi = y;
}

void	end_coord(t_vector *vector, int x, int y)
{
	vector->xf = x;
	vector->yf = y;
}

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

	vec.xi = cub->player->xi + xcorr;
	vec.xf = cub->player->xf + xcorr;
	vec.yi = cub->player->yi + ycorr;
	vec.yf = cub->player->yf + ycorr;
	draw_player_lines(cub, vec, cub->sqr_size * 0.5, 0x44FF24);
}

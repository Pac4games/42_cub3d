/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:37:52 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/08 17:51:11 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	*get_minimap_coord(int size, int max)
{
	int		*newmap;
	int		sml;
	int		i;

	i = -1;
	newmap = malloc(sizeof(newmap) * max);
	if (!newmap)
		return (0);
	sml = size;
	while (++i < max)
		newmap[i] = sml + i * sml;
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
	int	mid_w;
	int	mid_h;
	int	wid_corr;
	int	hei_corr;
	t_vector vec;

	mid_w = WWID * 0.15;
	mid_h = WHEI * 0.15;
	wid_corr = mid_w - cub->sqr_size + cub->player_x * cub->sqr_size;
	hei_corr = mid_h - cub->sqr_size + cub->player_y * cub->sqr_size;
	draw_minimap(cub, cub->map, wid_corr, hei_corr);
	draw_doors(cub, cub->map, wid_corr, hei_corr);
	player_scaled_down(cub, wid_corr, hei_corr);
	vec.xi = cub->sqr_size + cub->player_x * cub->sqr_size + cub->sqr_size * cub->dir_x;
	vec.xf = cub->sqr_size + cub->player_x * cub->sqr_size + cub->sqr_size * cub->dir_x * 1.25;
	vec.yi = cub->sqr_size + cub->player_y * cub->sqr_size + cub->sqr_size * cub->dir_y;
	vec.yf = cub->sqr_size + cub->player_y * cub->sqr_size + cub->sqr_size * cub->dir_y * 1.25;
	minimap_draw_line(cub, &vec, 0x44FF24);
}

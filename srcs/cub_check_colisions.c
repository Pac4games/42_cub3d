/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check_colisions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:22:31 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/05 23:25:03 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	player_colision_x(t_cub3d *cub, float dist, int type)
{
	int	x;
	int	x2;
	int	y;

	x = 0;
	y = 0;
	while (y < cub->map->tot_cols - 1 && dist > \
	cub->minimap->mapx[y] + cub->sqr_size)
		y++;
	while (x < cub->map->tot_rows - 1 && cub->sqr_size \
	+ cub->minimap->mapy[x] < cub->player->yi)
		x++;
	x2 = x;
	while (x2 < cub->map->tot_rows - 1 && cub->sqr_size \
	+ cub->minimap->mapy[x2] < cub->player->yf)
		x2++;
	if (x < cub->map->tot_rows && y < cub->map->tot_cols \
	&& cub->map->map[x][y] == type)
		return (reload_player_pos(cub, x, y));
	if (x2 != x && x2 < cub->map->tot_rows && y < \
	cub->map->tot_cols && cub->map->map[x2][y] == type)
		return (reload_player_pos(cub, x2, y));
	return (0);
}

int	player_colision_y(t_cub3d *cub, float dist, int type)
{
	int	x;
	int	y;
	int	y2;

	x = 0;
	y = 0;
	while (x < cub->map->tot_rows - 1 && dist > \
	cub->minimap->mapy[x] + cub->sqr_size)
		x++;
	while (y < cub->map->tot_cols - 1 && cub->sqr_size \
	+ cub->minimap->mapx[y] < cub->player->xi)
		y++;
	y2 = y;
	while (y2 < cub->map->tot_cols - 1 && cub->sqr_size \
	+ cub->minimap->mapx[y2] < cub->player->xf)
		y2++;
	if (x < cub->map->tot_rows && y < cub->map->tot_cols \
	&& cub->map->map[x][y] == type)
		return (reload_player_pos(cub, x, y));
	if (y2 != y && x < cub->map->tot_rows && y2 < \
	cub->map->tot_cols && cub->map->map[x][y2] == type)
		return (reload_player_pos(cub, x, y2));
	return (0);
}

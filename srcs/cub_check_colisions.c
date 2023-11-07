/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check_colisions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:22:31 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/07 18:39:34 by mnascime         ###   ########.fr       */
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
	cub->minimap->mapx[y] + SQR_SIZE)
		y++;
	while (x < cub->map->tot_rows - 1 && SQR_SIZE \
	+ cub->minimap->mapy[x] < (cub->player_y - 0.25) * SQR_SIZE)
		x++;
	x2 = x;
	while (x2 < cub->map->tot_rows - 1 && SQR_SIZE \
	+ cub->minimap->mapy[x2] < (cub->player_y - 0.25) * SQR_SIZE)
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
	cub->minimap->mapy[x] + SQR_SIZE)
		x++;
	while (y < cub->map->tot_cols - 1 && SQR_SIZE \
	+ cub->minimap->mapx[y] < (cub->player_x - 0.25) * SQR_SIZE)
		y++;
	y2 = y;
	while (y2 < cub->map->tot_cols - 1 && SQR_SIZE \
	+ cub->minimap->mapx[y2] < (cub->player_x - 0.25) * SQR_SIZE)
		y2++;
	if (x < cub->map->tot_rows && y < cub->map->tot_cols \
	&& cub->map->map[x][y] == type)
		return (reload_player_pos(cub, x, y));
	if (y2 != y && x < cub->map->tot_rows && y2 < \
	cub->map->tot_cols && cub->map->map[x][y2] == type)
		return (reload_player_pos(cub, x, y2));
	return (0);
}

int	get_player_sqr(t_cub3d *cub, char is_horiz)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < cub->map->tot_cols - 1 && (cub->player_y) \
	* SQR_SIZE > cub->minimap->mapx[y] + SQR_SIZE)
		y++;
	while (x < cub->map->tot_rows - 1 && SQR_SIZE \
	+ cub->minimap->mapy[x] < (cub->player_x) * SQR_SIZE)
		x++;
	if (is_horiz)
		return (x);
	return (y);
}

int	get_sqr(t_cub3d *cub, int xval, int yval, char is_horiz)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < cub->map->tot_cols - 1 && \
	xval > cub->minimap->mapx[y] + SQR_SIZE)
		y++;
	while (x < cub->map->tot_rows - 1 && SQR_SIZE \
	+ cub->minimap->mapy[x] < yval)
		x++;
	if (is_horiz)
		return (x);
	return (y);
}

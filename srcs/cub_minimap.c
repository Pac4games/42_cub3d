/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:37:52 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/05 11:29:15 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	*update_display_x(int cols, int x)
{
	int		*newmap;
	int		sml;
	int		tempx;

	newmap = malloc(sizeof(newmap) * cols);
	if (!newmap)
		return (0);
	sml = SQR_SIZE;
	while (++x < cols)
	{
		tempx = sml + x * sml;
		newmap[x] = tempx;
	}
	return (newmap);
}

int	*update_display_y(int rows, int y)
{
	int		*newmap;
	int		sml;
	int		tempy;

	newmap = malloc(sizeof(newmap) * rows);
	if (!newmap)
		return (0);
	sml = SQR_SIZE;
	while (++y < rows)
	{
		tempy = sml + y * sml;
		newmap[y] = tempy;
	}
	return (newmap);
}

int	get_sqr_size(t_cub3d *cub)
{
	int	dist;

	dist = (cub->minimap->mapx[1] \
	- cub->minimap->mapx[0]);
	if (dist <= 9)
		dist = 36;
	return (dist);
}

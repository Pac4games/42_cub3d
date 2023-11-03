/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:37:52 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/03 12:37:52 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	smlnum(int rows, int cols)
{
	if (rows < cols)
		return (cols);
	return (rows);
}

int	*update_display_x(int rows, int cols, int x)
{
	int		*newmap;
	int		sml;
	int		smltab;
	int		tempx;

	newmap = malloc(sizeof(newmap) * cols);
	if (!newmap)
		return (0);
	sml = (WHEI * MAP_MULTIP) / smlnum(rows, cols);
	smltab = smlnum(rows, cols) - 1;
	while (++x < cols)
	{
		tempx = (WWID - sml * smltab) * X_MULTIP + x * sml;
		newmap[x] = tempx;
	}
	return (newmap);
}

int	*update_display_y(int rows, int cols, int y)
{
	int		*newmap;
	int		sml;
	int		smltab;
	int		tempy;

	newmap = malloc(sizeof(newmap) * rows);
	if (!newmap)
		return (0);
	sml = (WHEI * MAP_MULTIP) / smlnum(rows, cols);
	smltab = smlnum(rows, cols) - 1;
	while (++y < rows)
	{
		tempy = (WHEI - sml * smltab) * Y_MULTIP + y * sml;
		newmap[y] = tempy;
	}
	return (newmap);
}

int	get_sqr_size(t_cub3d *cub)
{
	int	dist;

	dist = (cub->minimap->mapx[1] \
	- cub->minimap->mapx[0]);
	return (dist);
}

void	sqr_adjustments(int *map, int rows, int cols, int size)
{
	int	times;
	int	dist;
	int	corr;

	corr = -1;
	dist = ((WHEI * MAP_MULTIP) / smlnum(rows, cols));
	if (corr == -1)
		return ;
	times = -1;
	while (++times < size)
	{
		map[times] += corr;
		times++;
		corr++;
	}
}

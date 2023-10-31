/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:37:52 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/31 13:56:57 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	smlnum(int rows, int cols)
{
	if (rows < cols)
		return (cols);
	return (rows);
}

int	**update_display_x(int rows, int cols, int y, int x)
{
	int		**newmap;
	int		sml;
	int		smltab;
	int		tempx;

	newmap = solo_matrix(rows, cols);
	sml = (WHEI * 0.55) / smlnum(rows, cols);
	smltab = smlnum(rows, cols) - 1;
	while (++y < rows)
	{
		x = -1;
		while (++x < cols)
		{
			tempx = (WWID - sml * smltab) * 0.05 + x * sml;
			newmap[y][x] = tempx;
		}
	}
	return (newmap);
}

int	**update_display_y(int rows, int cols, int y, int x)
{
	int		**newmap;
	int		sml;
	int		smltab;
	int		tempy;

	newmap = solo_matrix(rows, cols);
	if (!newmap)
		return (NULL);
	sml = (WHEI * 0.55) / smlnum(rows, cols);
	smltab = smlnum(rows, cols) - 1;
	while (++y < rows)
	{
		x = -1;
		tempy = (WHEI - sml * smltab) * 0.1 + y * sml;
		while (++x < cols)
			newmap[y][x] = tempy;
	}
	return (newmap);
}

int	get_sqr_size(t_cub3d *cub)
{
	int	dist;

	dist = (cub->minimap->mapx[1][1] \
	- cub->minimap->mapx[0][0]);
	if (dist % 2 != 0)
		dist++;
	return (dist);
}

void	sqr_adjustments(int **map, int rows, int cols)
{
	int	x;
	int	y;
	int	dist;
	int	corr;

	corr = -1;
	dist = ((WHEI * 0.55) / smlnum(rows, cols));
	if (dist % 2 != 0)
		corr++;
	if (corr == -1)
		return ;
	y = -1;
	while (++y < rows)
	{
		x = 0;
		corr = 0;
		while (x < cols)
		{
			map[y][x] += corr;
			x++;
			corr++;
		}
	}
}

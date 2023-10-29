/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:37:52 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/29 15:22:11 by mnascime         ###   ########.fr       */
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

int	get_sqr_size(t_data *img)
{
	return (((WHEI * 0.55) / smlnum(img->cub->map->tot_rows, \
	img->cub->map->tot_cols)));
}

void	calc_sqr_end(int **map, int rows, int cols)
{
	int	x;
	int	y;
	int	dist;

	dist = ((WHEI * 0.55) / smlnum(rows, cols));
	y = -1;
	while (++y < rows)
	{
		x = 0;
		while (x < cols)
		{
			map[y][x] += dist;
			x++;
		}
	}
}

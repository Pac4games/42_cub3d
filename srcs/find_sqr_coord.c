/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sqr_coord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:37:29 by paugonca          #+#    #+#             */
/*   Updated: 2023/12/08 11:37:38 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	rotate_view(t_cub3d *cub)
{
	int		dif;

	dif = 0;
	if ((cub->move >> ROT_LEFT & 1) && !(cub->move >> ROT_RIGHT & 1))
		dif = -1;
	else if ((cub->move >> ROT_RIGHT & 1) && !(cub->move >> ROT_LEFT & 1))
		dif = 1;
	if (dif != 0)
	{
		rot_raycaster(cub, dif * 0.1);
		return (1);
	}
	return (0);
}

int	get_sqr_coord(t_cub3d *cub, int yval, int xval, char is_horiz)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < cub->map->tot_rows - 1 && y < yval)
		y++;
	while (x < cub->map->tot_cols - 1 && xval > x)
		x++;
	if (is_horiz)
		return (x);
	return (y);
}

void	get_v_vector(t_cub3d *cub, t_vector *vec, int x, int y)
{
	int	new_x;
	int	new_y;

	new_x = cub->sqr_size + x * cub->sqr_size;
	new_y = cub->sqr_size + y * cub->sqr_size;
	vec->xi = new_x;
	vec->yi = new_y;
	vec->xf = new_x;
	vec->yf = new_y + cub->sqr_size;
	vec->xi += cub->sqr_size - 1;
	vec->xf += cub->sqr_size - 1;
}

void	get_h_vector(t_cub3d *cub, t_vector *vec, int x, int y)
{
	int	new_x;
	int	new_y;

	new_x = cub->sqr_size + x * cub->sqr_size;
	new_y = cub->sqr_size + y * cub->sqr_size;
	vec->xi = new_x;
	vec->yi = new_y;
	vec->xf = new_x + cub->sqr_size;
	vec->yf = new_y;
}

int	get_sqr_size(void)
{
	int	dist;
	int	base;

	if (WHEI < WWID)
		base = WHEI;
	else
		base = WWID;
	dist = (double)(base) *STEP * 0.1;
	return (dist);
}

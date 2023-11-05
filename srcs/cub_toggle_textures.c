/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_toggle_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:33:17 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/05 21:55:25 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	change_textures(t_cub3d *cub, int x, int y)
{
	static int	lastx = 0;
	static int	lasty = 0;

	if (cub->map->map[x][y] != cub->map->map[lastx][lasty])
	{
		if (cub->map->map[x][y] >= NUP_DOOR_AT_UP && cub->map->map[x][y] <= NUP_DOOR_AT_RIGHT)
			cub->level++;
		else if (cub->level > 0)
			cub->level--;
		else
			return ;
		if (cub->level < 0)
			cub->level = cub->all_txtrs->tot_txtrs;
		printf("%s\n", cub->all_txtrs->textures[SO].path[cub->level \
		% (cub->all_txtrs->textures[SO].levels)]);
		lastx = x;
		lasty = y;
	}
}

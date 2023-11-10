/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:33:17 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/10 10:06:05 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	change_textures(t_cub3d *cub, int y, int x)
{
	static int	lastx = 0;
	static int	lasty = 0;

	if (cub->map->map[y][x] != cub->map->map[lasty][lastx])
	{
		if (cub->map->map[y][x] == UP_DOOR_AT_UP \
		|| cub->map->map[y][x] == UP_DOOR_AT_DOWN \
		|| cub->map->map[y][x] == UP_DOOR_AT_LEFT \
		|| cub->map->map[y][x] == UP_DOOR_AT_RIGHT)
			cub->level++;
		else if (cub->level > 0)
			cub->level--;
		else
			return ;
		if (cub->level < 0)
			cub->level = cub->all_txtrs->tot_txtrs;
		printf("%s\n", cub->all_txtrs->textures[SO].path[cub->level \
		% (cub->all_txtrs->textures[SO].levels)]);
		lasty = y;
		lastx = x;
	}
}

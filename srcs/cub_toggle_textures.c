/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_toggle_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:33:17 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/09 12:27:27 by mnascime         ###   ########.fr       */
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

int	check_door_colision(t_cub3d *cub, double distx, double disty)
{
	char	door;

	distx++;
	disty++;
	door = cub->map->map[get_player_sqr(cub, 0)][get_player_sqr(cub, 1)];
	if (((door == UP_DOOR_AT_RIGHT || door == DOWN_DOOR_AT_RIGHT) \
	&& player_colision_x(cub, cub->player_x - 0.25, door) == 2) || \
	((door == UP_DOOR_AT_LEFT || door == DOWN_DOOR_AT_LEFT) \
	&& player_colision_x(cub, cub->player_x + 0.25, door) == 2) || \
	((door == UP_DOOR_AT_DOWN || door == DOWN_DOOR_AT_DOWN) \
	&& player_colision_y(cub, cub->player_y - 0.25, door) == 2) || \
	((door == UP_DOOR_AT_UP || door == DOWN_DOOR_AT_UP) \
	&& player_colision_y(cub, cub->player_y + 0.25, door) == 2))
		return (1);
	return (0);
}

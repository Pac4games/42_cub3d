/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_toggle_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:33:17 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/07 15:32:23 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	change_textures(t_cub3d *cub, int x, int y)
{
	static int	lastx = 0;
	static int	lasty = 0;

	if (cub->map->map[x][y] != cub->map->map[lastx][lasty])
	{
		if (cub->map->map[x][y] >= NUP_DOOR_AT_UP \
		&& cub->map->map[x][y] <= NUP_DOOR_AT_RIGHT)
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

int	check_door_colision(t_cub3d *cub, float distx, float disty)
{
	int		door;

	distx++;
	disty++;
	door = NUP_DOOR_AT_UP;
	while (door <= NDOWN_DOOR_AT_RIGHT)
	{
		if (((door == NUP_DOOR_AT_RIGHT || door == NDOWN_DOOR_AT_RIGHT) \
		&& player_colision_x(cub, cub->player_x - 0.25, door) == 2) || \
		((door == NUP_DOOR_AT_LEFT || door == NDOWN_DOOR_AT_LEFT) \
		&& player_colision_x(cub, cub->player_x + 0.25, door) == 2) || \
		((door == NUP_DOOR_AT_DOWN || door == NDOWN_DOOR_AT_DOWN) \
		&& player_colision_y(cub, cub->player_y - 0.25, door) == 2) || \
		((door == NUP_DOOR_AT_UP || door == NDOWN_DOOR_AT_UP) \
		&& player_colision_y(cub, cub->player_y + 0.25, door) == 2))
			return (1);
		else
			door++;
	}
	return (0);
}

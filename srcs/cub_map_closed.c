/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_closed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:35:23 by paugonca          #+#    #+#             */
/*   Updated: 2023/11/10 17:39:50 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_border(char **map, int i)
{
	int	j;

	j = -1;
	while (map[i][++j])
		if (map[i][j] == ZERO || map[i][j] == NORTH ||
			map[i][j] == SOUTH || map[i][j] == EAST ||
			map[i][j] == WEST || map[i][j] == DOOR1_UP ||
			map[i][j] == DOOR1_DOWN || map[i][j] == DOOR1_LEFT ||
			map[i][j] == DOOR1_RIGHT || map[i][j] == DOOR2_UP ||
			map[i][j] == DOOR2_DOWN || map[i][j] == DOOR2_LEFT ||
			map[i][j] == DOOR2_RIGHT)
				return (0);
	return (1);
}

int	check_line(char **map, int i)
{
	int	j;

	j = -1;
	while (map[i][++j])
	{
		if (map[i][j] == ZERO || map[i][j] == NORTH || map[i][j] == SOUTH ||
			map[i][j] == EAST || map[i][j] == WEST)
		{
			
		}
	}
}

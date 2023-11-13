/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_closed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:35:23 by paugonca          #+#    #+#             */
/*   Updated: 2023/11/13 14:59:28 by paugonca         ###   ########.fr       */
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
			map[i][j] == WEST || map[i][j] == DOOR_UP ||
			map[i][j] == DOOR_DOWN)
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

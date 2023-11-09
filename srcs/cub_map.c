/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:08:12 by paugonca          #+#    #+#             */
/*   Updated: 2023/11/09 11:24:16 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_map_obj(char **map)
{
	int	i;
	int	j;

	printf("map:\n");
	for (int k = 0; map[k]; k++)
		printf("%s\n", map[k]);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while(map[i][++j])
		{
			printf("char: %c\n", map[i][j]);
			if (map[i][j] != ZERO && map[i][j] != WALL && \
				map[i][j] != SPACE && map[i][j] != NORTH &&\
				map[i][j] != SOUTH && map[i][j] != EAST &&\
				map[i][j] != WEST)
					return (0);
		}
	}
	return (1);
}

int	is_valid_map(char **map)
{
	if (!check_map_obj(map))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_util_prints.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:12:28 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/28 20:09:54 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_map(t_map *map, int cols)
{
	int	i;
	int	f;

	i = -1;
	if (!map || !map->map)
		return ;
	while (++i < map->tot_rows)
	{
		f = -1;
		while (++f < cols)
		{
			printf("%d", map->map[i][f]);
			printf(" ");
		}
		printf("\n");
	}
}

void	print_txtrs(t_all_txtrs *txtrs)
{
	int	i;
	int	f;

	i = -1;
	while (++i < txtrs->tot_txtrs)
	{
		printf("%s\n", conv_to_txtr_text(txtrs->textures[i].type));
		f = -1;
		while (txtrs->textures[i].path[++f])
			printf("%s\n", txtrs->textures[i].path[f]);
	}
}

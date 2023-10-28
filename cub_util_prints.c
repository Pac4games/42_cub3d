/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_util_prints.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:12:28 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/27 20:41:12 by mnascime         ###   ########.fr       */
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
	t_txtr	*stxtr;

	stxtr = txtrs->head;
	while (stxtr)
	{
		printf("%s %s\n", conv_to_txtr_text(stxtr->type), stxtr->path);
		stxtr = stxtr->next;
	}
}

void	print_cur_txtrs(t_txtr **txtrs)
{
	int	i;

	i = 0;
	while (txtrs[i])
	{
		printf("%s %s\n", conv_to_txtr_text(txtrs[i]->type), txtrs[i]->path);
		i++;
	}
}

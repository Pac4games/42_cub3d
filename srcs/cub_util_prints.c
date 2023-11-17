/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_util_prints.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:12:28 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/17 14:34:11 by paugonca         ###   ########.fr       */
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
			printf("%c", map->map[i][f]);
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

void	print_matrix(int **mat, int rows, int cols)
{
	int	i;
	int	f;

	i = -1;
	if (!mat)
		return ;
	while (++i < rows)
	{
		f = -1;
		while (++f < cols)
		{
			printf("%c", mat[i][f]);
			printf(" ");
		}
		printf("\n");
	}
}

int	print_err_ret(char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:47:26 by paugonca          #+#    #+#             */
/*   Updated: 2023/11/23 16:41:00 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		free(mtx[i++]);
	free(mtx);
}

void	print_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		ft_putendl_fd(mtx[i++], STDOUT_FILENO);
}

int	mtx_len(char **mtx)
{
	int	res;

	res = 0;
	while (mtx[res])
		res++;
	return (res);
}

int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

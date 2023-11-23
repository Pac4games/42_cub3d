/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txtr_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:44:35 by paugonca          #+#    #+#             */
/*   Updated: 2023/11/23 17:26:48 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	insert_colors(t_cub3d *cub, int type, char **split)
{
	if (type == F)
	{
		cub->all_txtrs->textures->floor->r = ft_atoi(split[0]);
		cub->all_txtrs->textures->floor->g = ft_atoi(split[1]);
		cub->all_txtrs->textures->floor->b = ft_atoi(split[2]);
	}
	else if (type == C)
	{
		cub->all_txtrs->textures->ceiling->r = ft_atoi(split[0]);
		cub->all_txtrs->textures->ceiling->g = ft_atoi(split[1]);
		cub->all_txtrs->textures->ceiling->b = ft_atoi(split[2]);
	}
}

int	parse_colors(t_cub3d *cub, char *line, int type)
{
	int		i;
	char	**split;

	if (ft_strlen(&line[2]) < 5 || ft_strlen(&line[2]) > 11 + 1)
		return (print_err_ret("incorrect color formatting"));
	split = ft_split(&line[2], ',');
	if (!split)
		print_err_cub("failed to allocate memory", cub);
	i = -1;
	while (++i <= 2)
		if (ft_atoi(split[i]) < 0 || ft_atoi(split[i]) > 255 ||
		!str_isdigit(split[i]))
		{
			free_mtx(split);
			return (print_err_ret("incorrect color formatting"));
		}
	insert_colors(cub, type, split);
	free_mtx(split);
	return (1);
}
/*
int	parse_textures(t_cub3d *cub, char *line, int type)
{
	int		i;
	int		*fds;
	void	**tmp;
	char	**split;

	split = ft_split(&line[3], ' ');
	if (!split)
		print_err_cub("failed to allocate memory", cub);
	fds = malloc(mtx_len(split) * sizeof(int));
	i = -1;
	while (split[++i])
	{
		fds[i] = open(split[i], O_RDONLY);
		if (fds[i] == -1)
			print_err_cub("error opening file", cub);
	}
}
*/

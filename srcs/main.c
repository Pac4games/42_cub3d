/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:59:52 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/26 17:06:25 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	*fill_line_of_list(char *line)
{
	int	*map_line;
	int	len;
	int	i;

	len = ft_str_end_trim(line);
	map_line = malloc(sizeof(*map_line) * len);
	if (!map_line)
		return (0);
	i = 0;
	while (i < len)
	{
		map_line[i] = conv_to_map_num(line[i]);
		i++;
	}
	return (map_line);
}

t_cub3d	*fill_in_cub(int fd)
{
	t_cub3d	*cub3d;
	t_list	*list;
	char	*line;
	int		i;

	cub3d = init_cub();
	list = init_list();
	if (!list)
	{
		free(cub3d);
		return (NULL);
	}
	line = (char *)1;
	while (line)
	{
		line = get_next_line(fd);
		if (line && !is_only_spaces(line) && ft_strlen(line) > 0)
		{
			i = 0;
			while (ft_isspace(line[i]))
				i++;
			if (line[i] && is_valid_elem(&line[i]) > 0 && is_valid_elem(&line[i]) != TOT)
				insert_txtrs(&cub3d, &line[i], is_valid_elem(&line[i]));
			else if (line[i] && is_valid_elem(&line[i]) == TOT && map_line_is_valid(line))
			{
				insert_map_tail(list, fill_line_of_list(line), ft_str_end_trim(line));
				if (ft_str_end_trim(line) > cub3d->map_cols)
					cub3d->map_cols = ft_str_end_trim(line);
			}
			else
			{
				free(line);
				destroy_list(&list);
				if (cub3d)
					destroy_cub(&cub3d);
				return (NULL);
			}
		}
		free(line);
	}
	if (list && cub3d)
	{
		cub3d->map = list_to_map(&list, cub3d->map_cols);
		destroy_list(&list);
	}
	return (cub3d);
}

int	main(int ac, char *av[])
{
	t_cub3d	*cub3d;
	int		fd;

	if (ac == 2 && ft_strnstr(&av[1][ft_strlen(av[1]) \
	- 4], ".cub", ft_strlen(av[1])))
	{
		fd = open(av[1], O_RDONLY, 0777);
		if (fd <= 0)
			return (0);
		cub3d = fill_in_cub(fd);
		close(fd);
		//print_map(cub3d->map);
		//display_in_canvas(cub3d);
		if (cub3d)
		{
			//if (cub3d->textures)
			//	print_txtrs(cub3d->textures);
			if (cub3d->cur_txtrs)
				print_txtrs(cub3d->cur_txtrs);
			if (cub3d->map)
				print_map(cub3d->map, cub3d->map_cols);
			display_in_canvas(cub3d);
			destroy_cub(&cub3d);
		}
	}
	return (0);
}

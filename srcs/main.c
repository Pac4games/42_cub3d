/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:59:52 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/15 12:05:09 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	*fill_line_of_list(char *line)
{
	int	*map_line;
	int	len;
	int	i;

	len = ft_str_end_trim(line);
	map_line = malloc(sizeof(map_line) * len);
	if (!map_line)
		return (0);
	i = 0;
	while (i < len)
	{
		map_line[i] = line[i];
		i++;
	}
	map_line[i] = '\0';
	return (map_line);
}

static int	insert_line(t_cub3d *cub, t_list *list, char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] && is_valid_elem(&line[i]) != TOT)
		insert_txtrs(&cub, &line[i], is_valid_elem(&line[i]));
	else if (line[i] && is_valid_elem(&line[i]) == TOT)
	{
		insert_map_tail(list, fill_line_of_list(line), ft_str_end_trim(line));
		if (ft_str_end_trim(line) > cub->map_cols)
			cub->map_cols = ft_str_end_trim(line);
	}
	else
		return (0);
	return (1);
}

int	fill_in_cub(t_cub3d *cub, int fd)
{
	t_list	list;
	char	*line;

	init_list(&list);
	line = (char *)1;
	while (line)
	{
		line = get_next_line(fd);
		if (line && !is_only_spaces(line) && ft_strlen(line) > 0 \
		&& line[0] != '\n')
		{
			if (!insert_line(cub, &list, line))
			{
				free(line);
				destroy_list(&list);
//				if (cub)
//					destroy_cub(cub);
				return (0);
			}
		}
		free(line);
	}
	if (list.head && cub)
		list_to_map(&list, cub);
	return (1);
}

int	main(int ac, char *av[])
{
	t_cub3d	cub;
	int		fd;

	if (ac == 2 && ft_strnstr(&av[1][ft_strlen(av[1]) \
	- 4], ".cub", ft_strlen(av[1])))
	{
		fd = open(av[1], O_RDONLY);
		if (fd <= 0 || !init_cub(&cub) \
		|| !fill_in_cub(&cub, fd) || close(fd) == -1)
			return (0);
		close(fd);
		check_map(&cub);
		(&cub)->sqr_size = get_sqr_size();
		init_player_pos(&cub, -1, -1);
		init_raycaster(&cub);
		display_in_canvas(&cub);
		destroy_cub(&cub);
	}
	return (0);
}

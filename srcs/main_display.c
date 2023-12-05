/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:15:22 by margarida         #+#    #+#             */
/*   Updated: 2023/12/05 15:44:05 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	display_in_canvas(t_cub3d *cub)
{
	int	type;

	type = 0;
	cub->mlx = mlx_init();
	cub->img = mlx_new_image(cub->mlx, WWID, WHEI);
	while (++type <= cub->tot_txtrs)
	{
		if ((cub->elems >> type & 1))
			if (!fill_txtrs(cub, type - 1, cub->txtrs[type - 1]->levels))
				quits(cub);
	}
	cub->mlx_win = mlx_new_window(cub->mlx, WWID, WHEI, "cub3D");
	cub->addr = mlx_get_data_addr(cub->img, &cub->bpp, \
	&cub->line_length, &cub->endian);
	raycasting(cub);
	redraw_minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img, 0, 0);
	mlx_hook(cub->mlx_win, 2, (1L << 0), read_keys, cub);
	mlx_hook(cub->mlx_win, 3, (1L << 1), key_release, cub);
	mlx_hook(cub->mlx_win, 17, (1L << 1), quits, cub);
	mlx_do_key_autorepeatoff(cub->mlx);
	mlx_loop_hook(cub->mlx, in_key, cub);
	mlx_loop(cub->mlx);
}

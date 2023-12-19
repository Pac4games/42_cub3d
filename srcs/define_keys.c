/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:57:34 by mnascime          #+#    #+#             */
/*   Updated: 2023/12/19 22:19:38 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	quits(t_cub3d *cub, int exit_stts)
{
	destroy_cub(cub);
	if (cub->mlx_win)
	{
		mlx_do_key_autorepeaton(cub->mlx);
		mlx_mouse_show(cub->mlx, cub->mlx_win);
		mlx_destroy_window (cub->mlx, cub->mlx_win);
	}
	mlx_destroy_image(cub->mlx, cub->img);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(exit_stts);
}

int	in_key(t_cub3d *cub)
{
	int		ret;

	ret = 0;
	if (move_with_mouse(cub) || cub->move != 0)
	{
		ret = check_colisions_and_move(cub);
		ret += rotate_view(cub);
		if (ret == 0)
			return (1);
		ft_memset(cub->addr, 0, WHEI * WWID \
		* sizeof(cub->bpp));
		raycasting(cub);
		redraw_minimap(cub);
		if ((cub->elems >> (SP + 1) & 1))
			draw_sprite(cub);
		mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img, 0, 0);
	}
	return (1);
}

int	key_press(int key_pressed, t_cub3d *cub)
{
	if (key_pressed == FRONT || key_pressed == BACK \
	|| key_pressed == TOLEFT || key_pressed == TORIGHT)
		add_player_mov(cub, key_pressed);
	if (key_pressed == ARROW_LEFT || key_pressed == ARROW_RIGHT)
		add_player_rot(cub, key_pressed);
	return (0);
}

int	key_release(int key_pressed, t_cub3d *cub)
{
	if (key_pressed == FRONT || key_pressed == BACK \
	|| key_pressed == TOLEFT || key_pressed == TORIGHT)
		remove_player_mov(cub, key_pressed);
	if (key_pressed == ARROW_LEFT || key_pressed == ARROW_RIGHT)
		remove_player_rot(cub, key_pressed);
	return (0);
}

int	read_keys(int key_pressed, t_cub3d *cub)
{
	if (key_pressed == ESC)
		quits(cub, EXIT_SUCCESS);
	else if (key_pressed == FRONT || key_pressed == BACK \
	|| key_pressed == TOLEFT || key_pressed == TORIGHT \
	|| key_pressed == ARROW_LEFT || key_pressed == ARROW_RIGHT)
		key_press(key_pressed, cub);
	return (0);
}

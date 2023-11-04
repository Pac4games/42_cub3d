/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_handle_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:57:34 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/04 10:54:48 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	in_key(t_cub3d *cub)
{
	if (cub->move != 0)
	{
		ft_memset(cub->addr, 0, WHEI * WWID \
		* sizeof(cub->bits_per_pixel));
		rot_with_gaze(cub);
		move_with_gaze(cub);
		draw_minimap(cub, cub->map);
		draw_doors(cub, cub->map);
		draw_player_lines(cub, *cub->player, \
		cub->sqr_size * 0.5, 0x44FF24);
		my_mlx_pixel_put(cub, cub->gaze_x, cub->gaze_y, 0x44FF24);
		mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img, 0, 0);
	}
	return (1);
}

int	key_press(int key_pressed, t_cub3d *cub)
{
	if (key_pressed == FRONT || key_pressed == BACK \
	|| key_pressed == TOLEFT || key_pressed == TORIGHT)
		add_mov_with_gaze(cub, key_pressed);
	if (key_pressed == ARROW_LEFT || key_pressed == ARROW_RIGHT)
		add_rot_with_gaze(cub, key_pressed);
	return (0);
}

int	key_release(int key_pressed, t_cub3d *cub)
{
	if (key_pressed == FRONT || key_pressed == BACK \
	|| key_pressed == TOLEFT || key_pressed == TORIGHT)
		remove_mov_with_gaze(cub, key_pressed);
	if (key_pressed == ARROW_LEFT || key_pressed == ARROW_RIGHT)
		remove_rot_with_gaze(cub, key_pressed);
	return (0);
}

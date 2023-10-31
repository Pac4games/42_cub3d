/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_handle_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:57:34 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/31 16:12:22 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	in_key(t_data *img)
{
	if (img->go == FRONT || img->go == BACK || img->go == TOLEFT || img->go == TORIGHT)
	{
		mlx_destroy_image(img->mlx, img->img);
		img->img = mlx_new_image(img->mlx, WWID, WHEI);
		draw_minimap(img, img->cub->map);
		draw_doors(img, img->cub->map);
		move_player(img, img->go);
		draw_player_lines(img, *img->cub->player,  get_sqr_size(img->cub) * 0.5, 0x44FF24);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	}
	return (0);
}

int	key_press(int key_pressed, void *param)
{
	t_data	*img;

	img = (t_data *) param;
	if (key_pressed == FRONT || key_pressed == BACK \
	|| key_pressed == TOLEFT || key_pressed == TORIGHT)
		img->go = key_pressed;
	return (0);
}

int	key_release(int key_pressed, void *param)
{
	t_data	*img;

	img = (t_data *) param;
	if (key_pressed == FRONT || key_pressed == BACK \
	|| key_pressed == TOLEFT || key_pressed == TORIGHT)
	{
		if (img->go == key_pressed)
			img->go = 0;
	}
	return (0);
}

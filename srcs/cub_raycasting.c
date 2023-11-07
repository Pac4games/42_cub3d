/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:07:44 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/07 19:02:25 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rot_raycaster(t_cub3d *cub, float rot)
{
	float oldDirX = cub->dir_x;
	float oldPlaneX = cub->plane_x;

	cub->dir_x = cub->dir_x * cosf(rot) - cub->dir_y * sinf(rot);
	cub->dir_y = oldDirX * sinf(rot) + cub->dir_y * cosf(rot);
	cub->plane_x = cub->plane_x * cosf(rot) - cub->plane_y * sinf(rot);
	cub->plane_y = oldPlaneX * sinf(rot) + cub->plane_y * cosf(rot);
}

void	init_raycaster(t_cub3d *cub)
{
	if (cub->direction == NNORTH)
	{
		cub->dir_y = -1;
		cub->plane_x = -0.6;
	}
	else if (cub->direction == NEAST)
	{
		cub->dir_x = 1;
		cub->plane_y = -0.6;
	}
	else if (cub->direction == NSOUTH)
	{
		cub->dir_y = 1;
		cub->plane_x = 0.6;
	}
	else
	{
		cub->dir_x = -1;
		cub->plane_y = 0.6;
	}
}

void	raycasting(t_cub3d *cub)
{
	double posX = cub->player_x;
	double posY = cub->player_y;
	int lineHeight;
	int i = 0;
	int color;
	t_vector vec;

	while(i < WWID)
	{
		color = 0X00ff00 / 2;
		for(int x = 0; x < WWID; x++)
		{
			double cameraX = 2 * (WWID - x) / (double)WWID - 1;
			double rayDirX = cub->dir_x + cub->plane_x * cameraX;
			double rayDirY = cub->dir_y + cub->plane_y * cameraX;
			double mapX = posX;
			double mapY = posY;
			double sideDistX;
			double sideDistY;
			double deltaDistX = fabs(1 / rayDirX);
			double deltaDistY = fabs(1 / rayDirY);
			double perpWallDist;
			double stepX;
			double stepY;
			int hit = 0;
			int side;
			if(rayDirX < 0)
			{
			stepX = -STEP;
			sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
			stepX = STEP;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if(rayDirY < 0)
			{
			stepY = -STEP;
			sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
			stepY = STEP;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			while(hit == 0)
			{
				if(sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				if (cub->map->map[get_sqr(cub, mapX, mapY, 1)][get_sqr(cub, mapX, \
				mapY, 0)] == NWALL || cub->map->map[get_sqr(cub, mapX, mapY, \
				1)][get_sqr(cub, mapX, mapY, 0)] >= NUP_DOOR_AT_UP)
					hit = 1;
			}
			if(side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);
			lineHeight = (int)(WHEI / perpWallDist);

			vec.xi = x;
			vec.xf = x;
			vec.yi = -lineHeight / 2 + WHEI / 2;
			vec.yf = lineHeight / 2 + WHEI / 2;

			draw_line(cub, &vec, color);
			i++;
		}
	}
}
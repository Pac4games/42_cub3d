/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:07:44 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/09 15:33:52 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rot_raycaster(t_cub3d *cub, double rot)
{
	double oldDirX = cub->dir_x;
	double oldPlaneX = cub->plane_x;

	cub->dir_x = cub->dir_x * cosf(rot) - cub->dir_y * sinf(rot);
	cub->dir_y = oldDirX * sinf(rot) + cub->dir_y * cosf(rot);
	cub->plane_x = cub->plane_x * cosf(rot) - cub->plane_y * sinf(rot);
	cub->plane_y = oldPlaneX * sinf(rot) + cub->plane_y * cosf(rot);
}

void	init_raycaster(t_cub3d *cub)
{
	if (cub->direction == NORTH)
	{
		cub->dir_y = -1;
		cub->plane_x = 0.6;
	}
	else if (cub->direction == EAST)
	{
		cub->dir_x = 1;
		cub->plane_y = 0.6;
	}
	else if (cub->direction == SOUTH)
	{
		cub->dir_y = 1;
		cub->plane_x = -0.6;
	}
	else
	{
		cub->dir_x = -1;
		cub->plane_y = -0.6;
	}
}
/*
static void	real_distance_calc(t_cub3d *cub, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->dist_x < ray->dist_y)
		{
			ray->dist_x += ray->delt_dist_x;
			ray->x += ray->xstep;
			ray->side = 0;
		}
		else
		{
			ray->dist_y += ray->delt_dist_y;
			ray->y += ray->ystep;
			ray->side = 1;
		}
		if (cub->map->map[ray->y][ray->x] == NWALL \
		|| cub->map->map[ray->y][ray->x] >= NUP_DOOR_AT_UP)
			hit = 1;
	}
	if (ray->side == 0)
		ray->real_dist = (ray->dist_x - ray->delt_dist_x);
	else
		ray->real_dist = (ray->dist_y - ray->delt_dist_y);
}

static void	raycast_step_calc(t_cub3d *cub, t_ray *ray)
{
	if ((int)ray->dir_x < 0)
	{
		ray->xstep = -1;
		ray->dist_x = (cub->player_x - ray->x)
			* ray->delt_dist_x;
	}
	else
	{
		ray->xstep = 1;
		ray->dist_x = (ray->x + 1.0 - cub->player_x)
			* ray->delt_dist_x;
	}
	if ((int)ray->dir_y < 0)
	{
		ray->ystep = -1;
		ray->dist_y = (cub->player_y - ray->y) * ray->delt_dist_y;
	}
	else
	{
		ray->ystep = 1;
		ray->dist_y = (ray->y + 1.0 - cub->player_y)
			* ray->delt_dist_y;
	}
}

static void	raycast_draw_walls(t_cub3d *cub, t_ray *ray, int i)
{
	int			line_height;
	int			color;
	t_vector	vec;

	color = 0X00ff00 / 2;
	line_height = (int)(WHEI / ray->real_dist);
	vec.xi = i;
	vec.xf = i;
	vec.yi = -line_height / 2 + WHEI / 2;
	if (vec.yi < 0 || line_height < 0)
		vec.yi = 0;
	vec.yf = line_height / 2 + WHEI / 2;
	if (vec.yf >= WHEI || line_height < 0)
		vec.yf = WHEI - 1;
	if (cub->map->map[ray->y][ray->x] \
	>= NUP_DOOR_AT_UP && cub->map->map[ray->y][ray->x] <= NUP_DOOR_AT_RIGHT)
		color = 0x00FFFF;
	if (cub->map->map[ray->y][ray->x] \
	>= NDOWN_DOOR_AT_UP && cub->map->map[ray->y][ray->x] <= NDOWN_DOOR_AT_RIGHT)
		color = 0xFF00FF;
	draw_line(cub, &vec, color);
}

void	raycasting(t_cub3d *cub)
{
	int		i;
	double	camera_ray;
	t_ray	ray;

	i = 0;
	while (i < WWID)
	{
		ray.x = get_player_sqr(cub, 1);
		ray.y = get_player_sqr(cub, 0);
		camera_ray = 2 * i / (double) WWID - 1;
		ray.dir_x = cub->dir_x + cub->plane_x * camera_ray;
		ray.dir_y = cub->dir_y + cub->plane_y * camera_ray;
		ray.delt_dist_x = fabs(1 / ray.dir_x);
		ray.delt_dist_y = fabs(1 / ray.dir_y);
		raycast_step_calc(cub, &ray);
		real_distance_calc(cub, &ray);
		raycast_draw_walls(cub, &ray, i);
		//dda_side_selector(mlx, &ray, player, info);
		i++;
	}
}
*/

void	raycasting(t_cub3d *cub)
{
	double posX = cub->player_x;
	double posY = cub->player_y;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	int lineHeight;
	int mapX;
	int mapY;
	int i = 0;
	int color;
	t_vector vec;

	while(i < WWID)
	{
		for(int x = 0; x < WWID; x++)
		{
			color = 0X00ff00 / 2;
			double cameraX = 2 * x / (double)WWID - 1;
			double rayDirX = cub->dir_x + cub->plane_x * cameraX;
			double rayDirY = cub->dir_y + cub->plane_y * cameraX;
			mapX = get_player_sqr(cub, 1);
			mapY = get_player_sqr(cub, 0);
			deltaDistX = fabs(1 / rayDirX);
			deltaDistY = fabs(1 / rayDirY);
			double perpWallDist;
			double stepX;
			double stepY;
			int hit = 0;
			int side;
			if(rayDirX < 0)
			{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if(rayDirY < 0)
			{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
			stepY = 1;
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
				mapY = get_sqr_coord(cub, mapY, mapX, 0);
				mapX = get_sqr_coord(cub, mapY, mapX, 1);
				if (cub->map->map[mapY][mapX] == WALL || cub->map->map[mapY][mapX] >= UP_DOOR_AT_UP)
					hit = 1;
				if (cub->map->map[mapY][mapX] == UP_DOOR_AT_UP \
				|| cub->map->map[mapY][mapX] == UP_DOOR_AT_DOWN \
				|| cub->map->map[mapY][mapX] == UP_DOOR_AT_LEFT \
				|| cub->map->map[mapY][mapX] == UP_DOOR_AT_RIGHT)
						color = 0x00FFFF;
				if (cub->map->map[mapY][mapX] == DOWN_DOOR_AT_UP \
				|| cub->map->map[mapY][mapX] == DOWN_DOOR_AT_DOWN \
				|| cub->map->map[mapY][mapX] == DOWN_DOOR_AT_LEFT \
				|| cub->map->map[mapY][mapX] == DOWN_DOOR_AT_RIGHT)
						color = 0xFF00FF;
			}
			if(side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);
			lineHeight = (int)(WHEI / perpWallDist);

			vec.xi = x;
			vec.xf = x;
			vec.yi = -lineHeight / 2 + WHEI / 2;
			if (vec.yi < 0)
				vec.yi = 0;
			vec.yf = lineHeight / 2 + WHEI / 2;

			draw_line(cub, &vec, color);
			i++;
		}
	}
}

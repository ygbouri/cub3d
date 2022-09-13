/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:02:01 by ygbouri           #+#    #+#             */
/*   Updated: 2022/09/13 19:22:04 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	ft_display(t_cub *all)
{
	t_data	img;

	all->mlx = mlx_init();
	all->mlx_win = mlx_new_window(all->mlx, W, H, "CUB3D");
	img.img = mlx_new_image(all->mlx, 512, 256);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
									&img.line_length, &img.endian);
	affichminimap(all, &img);
}

void	pixelcarre(t_cub *all, t_data *img, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 12 && all->h < 256)
	{
		j = 0;
		while (j < 12 && all->w < 512)
		{
			my_mlx_pixel_put(img, j + all->w, i + all->h, color);
			j++;
		}
		i++;
	}
}

int	checkplayer(t_cub *all)
{
	all->xp = 0;
	all->yp = 0;
	while (all->map[all->yp])
	{
		all->xp = 0;
		while (all->map[all->yp][all->xp])
		{
			if (all->map[all->yp][all->xp] == 'N'
				|| all->map[all->yp][all->xp] == 'S'
				|| all->map[all->yp][all->xp] == 'W'
				|| all->map[all->yp][all->xp] == 'E')
			{
				all->P = all->map[all->yp][all->xp];
				return (1);
			}
			all->xp++;
		}
		all->yp++;
	}
	return (0);
}

// void	keyw(t_cub *all)
// {
// 	checkplayer(all);
// 	if (all->map[--all->yp][all->xp] == '0')
// 	{
// 		all->map[++all->yp][all->xp] = '0';
// 		all->map[--all->yp][all->xp] = all->P;
// 	}
// }

// void	keys(t_cub *all)
// {
// 	checkplayer(all);
// 	if (all->map[++all->yp][all->xp] == '0')
// 	{
// 		all->map[--all->yp][all->xp] = '0';
// 		all->map[++all->yp][all->xp] = all->P;
// 	}
// }

// void	keya(t_cub *all)
// {
// 	checkplayer(all);
// 	if (all->map[all->yp][--all->xp] == '0')
// 	{
// 		all->map[all->yp][++all->xp] = '0';
// 		all->map[all->yp][--all->xp] = all->P;
// 	}
// }

// void	keyd(t_cub *all)
// {
// 	checkplayer(all);
// 	if (all->map[all->yp][++all->xp] == '0')
// 	{
// 		all->map[all->yp][--all->xp] = '0';
// 		all->map[all->yp][++all->xp] = all->P;
// 	}
// }

int	keyhook(t_cub *all, int key)
{
	if (key == 13)
		keyw(all);
	else if (key == 0)
		keya(all);
	else if (key == 1)
		keys(all);
	else if (key == 2)
		keyd(all);
	mlx_clear_window(all->mlx, all->mlx_win);
	affichminimap(all, all->img);
	return(0);
}

void	affichminimap(t_cub *all, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	all->h = 0;
	all->w = 0;
	all->img = img;
	while (all->map[i])
	{
		j = 0;
		all->w = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '1')
				pixelcarre(all, img, 0x00117864);
			else if (all->map[i][j] == ' ' || all->map[i][j] == '0')
				pixelcarre(all, img, 0x0f39c12);
			else if (all->map[i][j] != ' ' && all->map[i][j] != '0')
				pixelcarre(all, img, 0x00ecf0f1);
			j++;
			all->w += 16;
		}
		i++;
		all->h += 16;
	}
	mlx_put_image_to_window(all->mlx, all->mlx_win, img->img, 0, 0);
	mlx_hook(all->mlx_win, 2, 0, keyhook, all);
	mlx_loop(all->mlx);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:02:01 by ygbouri           #+#    #+#             */
/*   Updated: 2022/09/18 16:10:30 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_strleny(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return(i);
}

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

void	keyw(t_cub *all)
{
	checkplayer(all);
	if (all->map[--all->yp][all->xp] == '0')
	{
		all->map[++all->yp][all->xp] = '0';
		all->map[--all->yp][all->xp] = all->P;
	}
	// if ((all->yp - 10) <= 0)
	// 	all->yp = 0;
	// else
	// 	all->yp -= 10; 
}

void	keys(t_cub *all)
{
	checkplayer(all);
	if (all->map[++all->yp][all->xp] == '0')
	{
		all->map[--all->yp][all->xp] = '0';
		all->map[++all->yp][all->xp] = all->P;
	}
	// if ((all->yp + 10) <= ft_strleny(all->map))
	// 	all->yp += 10;
	// else
	// 	all->yp -= 10; 
}

void	keya(t_cub *all)
{
	checkplayer(all);
	if (all->map[all->yp][--all->xp] == '0')
	{
		all->map[all->yp][++all->xp] = '0';
		all->map[all->yp][--all->xp] = all->P;
	}
}

void	keyd(t_cub *all)
{
	checkplayer(all);
	if (all->map[all->yp][++all->xp] == '0')
	{
		all->map[all->yp][--all->xp] = '0';
		all->map[all->yp][++all->xp] = all->P;
	}
}

int	keyhook(int key, t_cub *all)
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
	all->img->img = mlx_new_image(all->mlx, 512, 256);
	all->img->addr = mlx_get_data_addr(all->img->img, &(all->img->bits_per_pixel),
									&(all->img->line_length), &(all->img->endian));
	affichminimap(all, all->img);
	return(0);
}

void	checksizexy(t_cub *all, t_data *img)
{
	all->h = 0;
	all->w = 0;
	all->img = img;
	all->topy = all->yp + 10;
	all->topx = all->xp + 10;
	if (all->topy >= ft_strleny(all->map))
		all->topy = ft_strleny(all->map) - 1;
	if (all->i < 0)
		all->i = 0;
	if (all->j < 0)
		all->j = 0;
	if (all->topx >= (int)ft_strlen(all->map[all->i]))
		all->topx = ft_strlen(all->map[all->j]);
}
void	drawingline(t_cub *all, t_data *img)
{
	int		dx;
	int		dy;
	int		i;
	int		x;
	int		y;
	double	incx;
	double	incy;
	double	step;

	i = 0;
	checkplayer(all);
	x = all->xp;
	y = all->yp;
	printf("x ===>%d y====>%d\n", x, y);
	dx = all->xp;
	dy = (all->yp - 2) + all->yp;
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	incx = dx / step;
	incy = dy / step;
	while (i < step)
	{
		printf("dy ====> %d\n", i);
		my_mlx_pixel_put(img, x, y, 0x00ecf0f1);
		x += incx;
		y += incy;
		i++;
	}
}
void	affichminimap(t_cub *all, t_data *img)
{
	checkplayer(all);
	all->i = all->yp - 10;
	all->j = all->xp - 10;
	checksizexy(all, img);
	while (all->i <= all->topy)
	{
		all->j = all->xp - 10;
		all->w = 0;
		if (all->j < 0)
			all->j = 0;
		all->topx = all->xp + 10;
		if (all->topx >= (int)ft_strlen(all->map[all->i]))
			all->topx = ft_strlen(all->map[all->i]);
		while (all->j <= all->topx)
		{
			if (all->map[all->i][all->j] == '1')
				pixelcarre(all, img, 0x00117864);
			else if (all->map[all->i][all->j] == ' ' || all->map[all->i][all->j] == '0')
				pixelcarre(all, img, 0x0f39c12);
			else if (all->map[all->i][all->j] != ' ' && all->map[all->i][all->j] != '0')
			{
				pixelcarre(all, img, 0x00ecf0f1);
			}
			all->j++;
			all->w += 16;
		}
		all->i++;
		all->h += 16;
	}
	drawingline(all, img);
	mlx_put_image_to_window(all->mlx, all->mlx_win, img->img, 0, 0);
	mlx_hook(all->mlx_win, 2, 1L<<0, keyhook, all);
	mlx_loop(all->mlx);
}
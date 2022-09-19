/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:02:01 by ygbouri           #+#    #+#             */
/*   Updated: 2022/09/19 21:16:05 by ygbouri          ###   ########.fr       */
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
	while (i < 15 && all->h < 256) 
	{
		j = 0;
		while (j < 15 && all->w < 512)
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

t_player	*iniatialiserp(t_cub *all)
{
	t_player	*p;

	p = (t_player *) malloc(sizeof(t_player));
	p->walkDirection = 0;
	p->turnDirection = 0;
	p->movespeed = 2.0;
	p->radius = 0;
	p->rotationangl =0.0;
	p->rotationspeed = 2 * (M_PI / 180);
	checkplayer(all);
	p->xp = all->xp;
	p->yp = all->yp;
	return (p);
}

void	detectang(t_cub *all)
{
	checkplayer(all);
	if (all->P == 'N')
		all->p->rotationangl = M_PI_2;
	else if (all->P == 'S')
		all->p->rotationangl = M_PI * 3/2;
	else if (all->P == 'W')
		all->p->rotationangl = M_PI;
	else
		all->p->rotationangl = 0;
}

void	drawingline(t_cub *all)
{
	int	dx;
	int	dy;
	int	i;
	int	x;
	int	y;
	float incx;
	float incy;
	int step;

	i = 0;
	checkplayer(all);
	if (all->checker == 0)
		detectang(all);
	all->p->rotationangl += all->p->turnDirection * all->p->rotationspeed;
	all->dirx = all->xp + (cos(all->p->rotationangl) * 30);
	all->diry = all->yp + (sin(all->p->rotationangl) * 30);
	x = all->pscreenx + 6;
	y = all->pscreeny + 6;
	dx = all->dirx - all->xp;
	dy = all->diry - all->yp;
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	incx = dx / (float)step;
	incy = dy / (float)step;
	while (i < step)
	{
		my_mlx_pixel_put(all->img, x, y, 0xFD1700);
		x += incx;
		y += incy;
		i++;
	}
}
void	paintplayer(t_cub *all)
{
	t_player	*p;

	p = NULL;
	if(all->checker == 0)
	{
		p = iniatialiserp(all);
		all->checker = 1;
	}
	if (all->map[all->yp][all->xp] == all->P)
		my_mlx_pixel_put(all->img, all->pscreenx + 6, all->pscreeny + 6, 0xFD1700);
	all->p = p;
	//detectang(all);
	drawingline(all);
}

int	keypressed(int key, t_cub *all)
{
	if (key == 124) // right
	{
		all->p->turnDirection += 1;
		//printf("%f\n", all->p->walkDirection);
	}
	else if (key == 123)
	{
		all->p->turnDirection -= 1;
		//printf("%f\n", all->p->turnDirection);
	} // left
	if (key == 124 || key == 123)
	{
		//mlx_clear_window(all->mlx, all->mlx_win);
		all->img->img = mlx_new_image(all->mlx, 512, 256);
		all->img->addr = mlx_get_data_addr(all->img->img, &(all->img->bits_per_pixel),
										&(all->img->line_length), &(all->img->endian));
		affichminimap(all, all->img);
	}
	return (0);
}
void	affichminimap(t_cub *all, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	all->w = 0;
	all->h = 0;
	checkplayer(all);
	while (all->map[i])
	{
		j = 0;
		all->w = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '1')
				pixelcarre(all, img, 0xC3E8F5);
			else if (all->map[i][j] != '1')
			{
				pixelcarre(all, img, 0xffffff);
			}
			if (all->map[i][j] == all->P)
			{
				all->pscreenx = all->w;
				all->pscreeny = all->h;
			}
			j++;
			all->w += 16;
		}
		i++;
		all->h += 16;
	}
	all->img = img;
	paintplayer(all);
	mlx_put_image_to_window(all->mlx, all->mlx_win, img->img, 0, 0);
	mlx_hook(all->mlx_win, 2, 1L<<0, keypressed, all);
	mlx_loop(all->mlx);
}
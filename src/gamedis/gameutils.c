/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:02:01 by ygbouri           #+#    #+#             */
/*   Updated: 2022/09/21 21:26:33 by ygbouri          ###   ########.fr       */
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
	affichminimap(all, &img, 0);
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
	p->walkDirectionx = 0;
	p->walkDirectiony = 0;
	p->turnDirection = 0;
	p->movespeed = 2.0;
	p->movestep = 0.0;
	p->radius = 0;
	p->rotationangl = 0.0;
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
		all->p->rotationangl = 0;
	else
		all->p->rotationangl = M_PI;
}

void	drawingline(t_cub *all, int ch)
{
	int	dx;
	int	dy;
	int	i;
	float	x;
	float	y;
	float incx;
	float incy;
	int step;

	i = 0;
	checkplayer(all);
	if (ch == 0)
		detectang(all);
	dx = all->dirx - all->xp;
	dy = all->diry - all->yp;
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	incx = dx / (float)step;
	incy = dy / (float)step;
	x = (float)all->pscreenx + 6;
	y = (float)all->pscreeny + 6;
	while (i < step)
	{
		my_mlx_pixel_put(all->img, round(x), round(y), 0x0D1700);
		x += incx;
		y += incy;
		i++;
	}
}
void	paintplayer(t_cub *all, int ch)
{
	t_player	*p;

	p = NULL;
	if(ch == 0)
	{
		p = iniatialiserp(all);
		all->p = p;
	}
	//if (all->map[all->yp][all->xp] == all->P)
	my_mlx_pixel_put(all->img, round(all->pscreenx + 6), round(all->pscreeny + 6), 0xFD1700);
	//detectang(all);
	free(p);
	all->dirx = all->xp + (cos(all->p->rotationangl) * 30);
	all->diry = all->yp + (sin(all->p->rotationangl) * 30);
	drawingline(all, ch);
}

void	moveleft(t_cub *all)
{
	//int movestep = all->p->walkDirection * all->p->movespeed;
	all->posx += sin(all->p->rotationangl) * 10;
	all->posy -= cos(all->p->rotationangl) * 10;
	all->pscreenx = all->posx;
	all->pscreeny = all->posy;
}

void	moveright(t_cub *all)
{
	all->posx -= sin(all->p->rotationangl) * 10;
	all->posy += cos(all->p->rotationangl) * 10;
	all->pscreenx = all->posx;
	all->pscreeny = all->posy;
}

void	moveup(t_cub *all)
{
	//int movestep = all->p->walkDirection * all->p->movespeed;
	all->posx += cos(all->p->rotationangl) * 10;
	all->posy += sin(all->p->rotationangl) * 10;
	all->pscreenx = all->posx;
	all->pscreeny = all->posy;
}

void	movedown(t_cub *all)
{
	//int movestep = all->p->walkDirection * all->p->movespeed;
	all->posx -= cos(all->p->rotationangl) * 10;
	all->posy -= sin(all->p->rotationangl) * 10;
	all->pscreenx = all->posx;
	all->pscreeny = all->posy; 
}

void	moveraytleft(t_cub *all)
{
	all->p->rotationangl += 0.2;// * (M_PI / 180);
	if (all->p->rotationangl >= (M_PI * 2))
		all->p->rotationangl -= 2 * M_PI;
}

void	moveraytright(t_cub *all)
{
	all->p->rotationangl -= 0.2;// * (M_PI / 180);
	if (all->p->rotationangl <= 0)
		all->p->rotationangl += 2 * M_PI;
}

int keyrelease(int key, t_cub *all)
{
	if (key >= 0 && all->i == 1)
	{
		if (all->p->walkDirectionx == 1)
			moveleft(all);
		else if (all->p->walkDirectionx == -1)
			moveright(all);
		if (all->p->walkDirectiony == 1)
			movedown(all);
		else if (all->p->walkDirectiony == -1)
			moveup(all);
		if (all->p->turnDirection == 1)
			moveraytleft(all);
		else if (all->p->turnDirection == -1)
			moveraytright(all);
		mlx_clear_window(all->mlx, all->mlx_win);
		affichminimap(all, all->img, 1);
	}
	all->p->walkDirectionx = 0;
	all->p->walkDirectiony = 0;
	all->p->turnDirection = 0;
	return (0);
}

int	keypressed(int key, t_cub *all)
{
	if (key == 124)
		all->p->turnDirection = 1;
	else if (key == 123)
		all->p->turnDirection = -1;
	if (key == 0)
		all->p->walkDirectionx = 1;
	else if (key == 2)
		all->p->walkDirectionx = -1;
	else if (key == 1)
		all->p->walkDirectiony = 1;
	else if (key == 13)
		all->p->walkDirectiony = -1;
	if (key == 124 || key == 123 || key == 0
		|| key == 1 || key == 2 || key == 13)
	{
		all->i = 1;
		keyrelease(key, all);
	}
	return (0);
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
	if (all->k < 0)
		all->k = 0;
	if (all->j < 0)
		all->j = 0;
	if (all->topx >= (int)ft_strlen(all->map[all->k]))
		all->topx = ft_strlen(all->map[all->j]);
}

void	checklineofmap(t_cub *all)
{
	all->topx = all->xp + 10;
	all->j = all->xp - 10;
	all->w = 0;
	if (all->j < 0)
		all->j = 0;
	if (all->topx > (int)ft_strlen(all->map[all->j]))
		all->topx = ft_strlen(all->map[all->j]);
}

void	affichminimap(t_cub *all, t_data *img, int ch)
{
	all->w = 0;
	all->h = 0;
	all->i = 0;
	checkplayer(all);
	all->k = all->yp - 10;
	all->j = all->xp - 10;
	checksizexy(all, img);
	while (all->k < all->topy)
	{
		checklineofmap(all);
		while (all->j < all->topx)
		{
			if (all->map[all->k][all->j] == '1')
				pixelcarre(all, img, 0xC3E8F5);
			else if (all->map[all->k][all->j] != '1')
				pixelcarre(all, img, 0xffffff);
			if (ch == 0)
			{
				if (all->map[all->k][all->j] == all->P)
				{
					all->pscreenx = (double)all->w;
					all->pscreeny = (double)all->h;
				}
			}
			all->j++;
			all->w += 16;
		}
		all->k++;
		all->h += 16;
	}
	printf("%.2lf\n", all->pscreeny);
	all->posx = all->pscreenx;
	all->posy = all->pscreeny;
	all->img = img;
	paintplayer(all, ch);
	mlx_put_image_to_window(all->mlx, all->mlx_win, img->img, 0, 0);
	mlx_hook(all->mlx_win, 2, 1L<<0, keypressed, all);
	mlx_hook(all->mlx_win, 3, 1L<<1, keyrelease, all);
	mlx_loop(all->mlx);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:02:01 by ygbouri           #+#    #+#             */
/*   Updated: 2022/09/25 22:07:00 by ygbouri          ###   ########.fr       */
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

	if (x >= 0  && x < W && y >= 0 && y < H)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	drawimg(t_cub *all, int ch)
{
	all->img->img = mlx_new_image(all->mlx, W, H);
	all->img->addr = mlx_get_data_addr(all->img->img, &all->img->bits_per_pixel, &all->img->line_length, &all->img->endian);		
	if (ch == 0)
	{
			affichminimap(all, 0);
			
	}

}
void	ft_display(t_cub *all)
{
	// t_data	img;
	all->img = (t_data *)malloc(sizeof(t_data));
	all->mlx = mlx_init();
	all->mlx_win = mlx_new_window(all->mlx, W, H, "CUB3D");
	// all->img->img = mlx_new_image(all->mlx, 128, 128);
	// all->img->addr = mlx_get_data_addr(all->img->img, &all->img->bits_per_pixel, &all->img->line_length, &all->img->endian);
	// all->img = &img;
	
	drawimg(all, 0);
	// draw_cieling()
	mlx_hook(all->mlx_win, 3, 1L<<1, keyrelease, all);
	mlx_hook(all->mlx_win, 2, 1L<<0, keypressed, all);
	mlx_loop_hook(all->mlx, moveplayer, all);
	mlx_loop(all->mlx);					
	//affichminimap(all, &img, 0);
}

// void	pixemap(t_cub *all, t_data *img, int color)

void	pixelcarre(t_cub *all, int pi, t_data *img, int color)
{
	int	i;
	int	j;

	i = all->miniy;
	j = all->minix;
	while (i < all->miniy + pi) 
	{
		j = all->minix;
		while (j < all->minix + pi)
		{
			if ((i >= 0 && i < 128) && (j >= 0 && j < 128))
				my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
}


void	pixelmap(t_data *img, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 128)
	{
		j = 0;
		while (j < 128)
		{
				my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

int	checkplayer(t_cub *all, int ch)
{
	if (ch == 0)
	{
		all->w = 0;
		all->h = 0;
		all->xp = 0;
		all->yp = 0;
		while (all->map[all->yp])
		{
			all->xp = 0;
			all->w = 0;
			while (all->map[all->yp][all->xp])
			{
				if (all->map[all->yp][all->xp] == 'N'
					|| all->map[all->yp][all->xp] == 'S'
					|| all->map[all->yp][all->xp] == 'W'
					|| all->map[all->yp][all->xp] == 'E')
				{
					all->P = all->map[all->yp][all->xp];
					all->pscreenx = all->w;
					all->pscreeny = all->h;
					return (1);
				}
				all->w += 16;
				all->xp++;
			}
			all->yp++;
			all->h += 16;
		}
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
	p->rotationangl = -1;
	p->rotationspeed = 2 * (M_PI / 180);
	checkplayer(all, 0);
	p->xp = all->xp;
	p->yp = all->yp;
	return (p);
}

void	detectang(t_cub *all)
{
	if (all->P == 'N')
		all->p->rotationangl = M_PI_2;
	else if (all->P == 'S')
		all->p->rotationangl = M_PI * 3/2;
	else if (all->P == 'W')
		all->p->rotationangl = 0;
	else
		all->p->rotationangl = M_PI;
}

void	drawingline(t_cub *all)
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
	dx = all->dirx - all->xp;
	dy = all->diry - all->yp;
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	incx = dx / (float)step;
	incy = dy / (float)step;
	x = (float)64;
	y = (float)64;
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
	if(ch == 0)
	{
		all->p = iniatialiserp(all);
		detectang(all);
	}
	my_mlx_pixel_put(all->img, 64, 64, 0xFD1700);
	all->dirx = all->xp + (cos(all->p->rotationangl) * 30);
	all->diry = all->yp + (sin(all->p->rotationangl) * 30);
	drawingline(all);
}

int	checkwall(t_cub *all)
{
	int	x;
	int	y;
	int	x_line;


	x = floor(all->posx / 16);
	y = floor(all->posy / 16);
	
	if (y < 0 && y > ft_strleny(all->map))
		return (0);
	if (all->map[y] != NULL)
		x_line = ft_strlen(all->map[y]);
	else
		return (0);
	if (x < 0 && x > x_line)
		return (0); 
	// printf("x===>%d y===>%d\n", x, y);
	if (all->map[y][x] == '1')
		return (0);
	return (1);
}

void	moveleft(t_cub *all)
{
	all->posx += sin(all->p->rotationangl) * 1;
	all->posy -= cos(all->p->rotationangl) * 1;
	if (checkwall(all) == 1)
	{
		all->pscreenx = all->posx;
		all->pscreeny = all->posy;
	}
}

void	moveright(t_cub *all)
{
	all->posx -= sin(all->p->rotationangl) * 1;
	all->posy += cos(all->p->rotationangl) * 1;
	if (checkwall(all) == 1)
	{
		all->pscreenx = all->posx;
		all->pscreeny = all->posy;
	}
}

void	moveup(t_cub *all)
{
	all->posx += cos(all->p->rotationangl) * 1;
	all->posy += sin(all->p->rotationangl) * 1;
	if (checkwall(all) == 1)
	{
		all->pscreenx = all->posx;
		all->pscreeny = all->posy;
	}
}

void	movedown(t_cub *all)
{
	all->posx -= cos(all->p->rotationangl) * 1;
	all->posy -= sin(all->p->rotationangl) * 1;
	if (checkwall(all) == 1)	
	{
		all->pscreenx = all->posx;
		all->pscreeny = all->posy;
	}
}

void	moveraytleft(t_cub *all)
{
	all->p->rotationangl += 0.05;
	if (all->p->rotationangl >= (M_PI * 2))
		all->p->rotationangl -= 2 * M_PI;
}

void	moveraytright(t_cub *all)
{
	all->p->rotationangl -= 0.05;
	if (all->p->rotationangl <= 0)
		all->p->rotationangl += 2 * M_PI;
}

void	updat_data(t_cub **all)
{
	double step;

	step = (*all)->p->walkDirectiony * 2;
	(*all)->p->rotationangl += (*all)->p->turnDirection * (4 * M_PI / 180);
	(*all)->posx += cos((*all)->p->rotationangl) * step;
	(*all)->posy += sin((*all)->p->rotationangl) * step;
	if (checkwall(*all) == 1)
	{
		(*all)->pscreenx = (*all)->posx;
		(*all)->pscreeny = (*all)->posy;
	}
	step = (*all)->p->walkDirectionx * 2;
	(*all)->posx -= sin((*all)->p->rotationangl) * step;
	(*all)->posy += cos((*all)->p->rotationangl) * step;
	if (checkwall(*all) == 1)
	{
		(*all)->pscreenx = (*all)->posx;
		(*all)->pscreeny = (*all)->posy;
	}
}
int keyrelease(int key, t_cub *all)
{
	if (key == 124)
		all->p->turnDirection = 0;
	else if (key == 123)
		all->p->turnDirection = 0;
	if (key == 0)
		all->p->walkDirectionx = 0;
	else if (key == 2)
		all->p->walkDirectionx = 0;
	else if (key == 1)
		all->p->walkDirectiony = 0;
	else if (key == 13)
		all->p->walkDirectiony = 0;
	// updat_data(all);
	// mlx_clear_window(all->mlx, all->mlx_win);
	// mlx_destroy_image(all->mlx, all->img->img);
	// drawimg(all, 1);
	// affichminimap(all, 1);
	return (0);
}


int	keypressed(int key, t_cub *all)
{
	if (key == 124)
		all->p->turnDirection = 1;
	else if (key == 123)
		all->p->turnDirection = -1;
	if (key == 0)
		all->p->walkDirectionx = -1;
	else if (key == 2)
	 	all->p->walkDirectionx = 1;
	else if (key == 1)
		all->p->walkDirectiony = -1;
	else if (key == 13)
		all->p->walkDirectiony = 1;
	// updat_data(all);
	// mlx_clear_window(all->mlx, all->mlx_win);
	// mlx_destroy_image(all->mlx, all->img->img);
	// drawimg(all, 1);
	// affichminimap(all, 1);
	return (0);
}
int	moveplayer(t_cub *all)
{
	// if (all->p->turnDirection == 1)
	// 	moveraytleft(all);
	// if (all->p->turnDirection == -1)
	// 	moveraytright(all);
	// if (all->p->walkDirectionx == -1)
	// 	moveright(all);
	// if (all->p->walkDirectionx == 1)
	// 	moveleft(all);
	// if (all->p->walkDirectiony == 1)
	// 	moveup(all);
	// if (all->p->walkDirectiony == -1)
	// 	movedown(all);
	updat_data(&all);
	// if (all->p->turnDirection != 0 || all->p->walkDirectionx != 0 || all->p->walkDirectiony != 0)
	// {
	mlx_clear_window(all->mlx, all->mlx_win);
	mlx_destroy_image(all->mlx, all->img->img);
	drawimg(all, 1);
	affichminimap(all, 1);
	
	return (0);
}

void	paintmap(t_cub *all, t_data *img, int ch)
{
	int		x;
	int		y;

	int i = 0;
	int j = 0;
	checkplayer(all, ch);
	x = all->pscreenx - 64;
	y = all->pscreeny - 64;
	pixelmap(img, 0xff000);
	while (all->map[i])
	{
		j = 0;
		all->miniy = 16 * i - y;
		while(all->map[i][j] && all->map[i][j] != '\n')
		{
			all->minix = 16 * j - x;
			if (all->map[i][j] == '1')
				pixelcarre(all, 15, img, 0xfffff);
			j++;
		}
		i++;
	}
	//all->img = img;
}

void	affichminimap(t_cub *all, int ch)
{
	//if (ch == 0)
		//all->p->turnDirection = 0; all->p->walkDirectionx = 0; all->p->walkDirectiony = 0;
	// 	all->img = img;
	paintmap(all, all->img, ch);
	all->posx = all->pscreenx;
	all->posy = all->pscreeny;
	paintplayer(all, ch);
	
	mlx_put_image_to_window(all->mlx, all->mlx_win, all->img->img, 0, 0);
	// raycasting(all);
}

void	raycasting(t_cub *all)
{
	mlx_hook(all->mlx_win, 3, 1L<<1, keyrelease, all);
	mlx_hook(all->mlx_win, 2, 1L<<0, keypressed, all);
	mlx_loop_hook(all->mlx, moveplayer, all);
	mlx_loop(all->mlx);
}
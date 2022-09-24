/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:02:01 by ygbouri           #+#    #+#             */
/*   Updated: 2022/09/24 22:54:52 by ygbouri          ###   ########.fr       */
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
	img.img = mlx_new_image(all->mlx, 128, 128);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
									&img.line_length, &img.endian);
	affichminimap(all, &img, 0);
}

// void	pixemap(t_cub *all, t_data *img, int color)

void	pixelcarre(t_cub *all, int pi, t_data *img, int color)
{
	int	i;
	int	j;

	i = all->miniy;
	j = all->minix;
	while (i < all->miniy + pi)// && all->h < 128) 
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
	while (i < 128)// && all->h < 128) 
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
void	calculedistance(t_cub *all)
{
	// if ((all->pscreenx > all->centerx) && (all->pscreeny > all->centery))
	// {
		all->centerx = 128 / 2;
		all->centery = 128 / 2;
		all->disx = all->pscreenx - all->centerx;
		all->disy = all->pscreeny - all->centery;
		// x cases 
	// 	if(all->disx == 0)
	// 		all->translation_x = all->pscreenx;
	// 	else if(all->disx < 0)
	// 		all->translation_x = all->pscreenx + fabs(all->disx);
	// 	else if(all->disx > 0)
	// 		all->translation_x = all->pscreenx - fabs(all->disx);
	// 	// y cases 
	// 	if(all->disy == 0)
	// 		all->translation_y = all->pscreeny;
	// 	else if(all->disy < 0)
	// 		all->translation_y = all->pscreeny + fabs(all->disy);
	// 	else if(all->disy > 0)
	// 		all->translation_y = all->pscreeny - fabs(all->disy);
	// // }
	// else if ((all->pscreenx < all->centerx) && (all->pscreeny < all->centery))
	// {
		// all->disx = all->pscreenx + all->centerx;
		// all->disy = all->pscreeny + all->centery;
	// }
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
					all->pscreenx = all->w + 6;
					all->pscreeny = all->h + 6;
					printf("checplayerx%f checplayery %f\n", all->pscreenx, all->pscreeny);
					calculedistance(all);
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
	p->rotationangl = 0.0;
	p->rotationspeed = 2 * (M_PI / 180);
	checkplayer(all, 0);
	p->xp = all->xp;
	p->yp = all->yp;
	return (p);
}

void	detectang(t_cub *all)
{
	//checkplayer(all, 0);
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
	checkplayer(all, ch);
	if (ch == 0)
		detectang(all);
	all->dirx = all->xp + (cos(all->p->rotationangl) * 30);
	all->diry = all->yp + (sin(all->p->rotationangl) * 30);
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
	t_player	*p;

	p = NULL;
	if(ch == 0)
	{
		p = iniatialiserp(all);
		all->p = p;
	}
	my_mlx_pixel_put(all->img, 64, 64, 0xFD1700);
	free(p);
	drawingline(all, ch);
}

void	moveleft(t_cub *all)
{
	all->posx += sin(all->p->rotationangl) * 4;
	all->posy -= cos(all->p->rotationangl) * 4;
	all->pscreenx = all->posx;
	all->pscreeny = all->posy;
}

void	moveright(t_cub *all)
{
	all->posx -= sin(all->p->rotationangl) * 4;
	all->posy += cos(all->p->rotationangl) * 4;
	all->pscreenx = all->posx;
	all->pscreeny = all->posy;
}

void	moveup(t_cub *all)
{
	all->posx += cos(all->p->rotationangl) * 4;
	all->posy += sin(all->p->rotationangl) * 4;
	all->pscreenx = all->posx;
	all->pscreeny = all->posy;
}

void	movedown(t_cub *all)
{
	all->posx -= cos(all->p->rotationangl) * 4;
	all->posy -= sin(all->p->rotationangl) * 4;
	all->pscreenx = all->posx;
	all->pscreeny = all->posy; 
}

void	moveraytleft(t_cub *all)
{
	all->p->rotationangl += 0.2;
	if (all->p->rotationangl >= (M_PI * 2))
		all->p->rotationangl -= 2 * M_PI;
}

void	moveraytright(t_cub *all)
{
	all->p->rotationangl -= 0.2;
	if (all->p->rotationangl <= 0)
		all->p->rotationangl += 2 * M_PI;
}

int keyrelease(int key, t_cub *all)
{
	if (key == 124)
		all->p->turnDirection = 0;
	else if (key == 123)
		all->p->turnDirection = 0;
	else if (key == 0)
		all->p->walkDirectionx = 0;
	else if (key == 2)
		all->p->walkDirectionx = 0;
	else if (key == 1)
		all->p->walkDirectiony = 0;
	else if (key == 13)
		all->p->walkDirectiony = 0;
	return (0);
}


int	moveplayer(t_cub *all)
{
	if (all->p->turnDirection == 1)
		moveraytleft(all);
	if (all->p->turnDirection == -1)
		moveraytright(all);
	if (all->p->walkDirectionx == -1)
		moveright(all);
	if (all->p->walkDirectionx == 1)
		moveleft(all);
	if (all->p->walkDirectiony == 1)
		moveup(all);
	if (all->p->walkDirectiony == -1)
		movedown(all);
	// if (all->p->turnDirection != 0 || all->p->walkDirectionx != 0 || all->p->walkDirectiony == 0)
	// {
	// 	mlx_clear_window(all->mlx, all->mlx_win);
	// 	affichminimap(all, all->img, 1);
	// }
	return (1);
}
int	keypressed(int key, t_cub *all)
{
	if (key == 124)
		all->p->turnDirection = 1;
	if (key == 123)
		all->p->turnDirection = -1;
	if (key == 0)
		all->p->walkDirectionx = 1;
	if (key == 2)
		all->p->walkDirectionx = -1;
	if (key == 1)
		all->p->walkDirectiony = -1;
	if (key == 13)
		all->p->walkDirectiony = 1;
	moveplayer(all);
	mlx_clear_window(all->mlx, all->mlx_win);
	affichminimap(all, all->img, 1);
	return (0);
}
void	checksizexy(t_cub *all, t_data *img)
{
	all->h = 0;
	all->w = 0;
	all->img = img;
	all->topy = all->yp + (all->translation_y / 15) + (all->translation_y / 15);
	printf("jfdksklj%dkkkkkkkk%d\n", all->topy, all->k);
	if (all->topy >= ft_strleny(all->map))
		all->topy = ft_strleny(all->map) - 1;
	if (all->k < 0)
		all->k = 0;
	
	// if (all->topy < 0)
	// 	all->topy = abs(all->topy);
}

void	checklineofmap(t_cub *all)
{
	all->topx = all->xp + (all->translation_x / 15) + 4;
	printf("topx=======>%d\n", all->topx);
	all->w = 0;
	// if (all->j < 0)
	// 	all->j = 0;
	// if (all->topx > (int)ft_strlen(all->map[all->k]))
	// 	all->topx = ft_strlen(all->map[all->k]);
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
	printf("x%d y%d\n", x, y);
	pixelmap(img, 0xff000);
	while (all->map[i])
	{
		j = 0;
		all->miniy = 16 * i - y;
		while(all->map[i][j])
		{
			all->minix = 16 * j - x;
			if (all->map[i][j] == '1')
				pixelcarre(all,14, img, 0xfffff);
			j++;
		}
		i++;
	}
	all->img = img;
}

// void	paintmap2(t_cub *all)
// {
// 	all->k = all->diry - 10;
// 	all->topy = all->diry + 10;
// 	ch
// }
// void	moveplayer(t_cub *all, t_data *img)
// {
// 	checksizexy(all, img);
// 	checklineofmap(all);
// 	all->w = 0;
// 	all->h = 0;
// 	all->k = round(all->pscreeny) - 50;
// 	all->j = round(all->pscreenx) - 50;
// 	while(all->k <= all->topy)
// 	{
// 		all->j = round(all->pscreenx) - 50;
// 		while (all->j <= all->topx)
// 		{
// 			if (all->map[all->k / 15][all->j / 15] == '1')
// 				pixelcarre(all, img, 0xC3E8F5);
// 			else if (all->map[all->k / 15][all->j / 15] != '0')
// 				pixelcarre(all, img, 0xffffff);
// 			all->j += 15;
// 			all->w += 16;
// 		}
// 		all->k += 15;
// 		all->h += 16; 
// 	}

// }
void	affichminimap(t_cub *all, t_data *img, int ch)
{
	all->img = img;
	paintmap(all, all->img, ch);
	all->posx = all->pscreenx;
	all->posy = all->pscreeny;
	paintplayer(all, ch);
	mlx_put_image_to_window(all->mlx, all->mlx_win, all->img->img, 0, 0);
	mlx_hook(all->mlx_win, 2, 1L<<0, keypressed, all);
	mlx_hook(all->mlx_win, 3, 0, keyrelease, all);
	//mlx_loop_hook(all->mlx, moveplayer, all);
	mlx_loop(all->mlx);
}
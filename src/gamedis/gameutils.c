/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:02:01 by ygbouri           #+#    #+#             */
/*   Updated: 2022/10/01 23:59:54 by ygbouri          ###   ########.fr       */
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
		affichminimap(all, 0);
}

void	ft_display(t_cub *all)
{
	all->img = (t_data *)malloc(sizeof(t_data));
	all->mlx = mlx_init();
	all->mlx_win = mlx_new_window(all->mlx, W, H, "CUB3D");
	drawimg(all, 0);
	mlx_hook(all->mlx_win, 3, 1L<<1, keyrelease, all);
	mlx_hook(all->mlx_win, 2, 1L<<0, keypressed, all);
	mlx_hook(all->mlx_win, 17, 0, closewin, all);
	mlx_loop_hook(all->mlx, moveplayer, all);
	mlx_loop(all->mlx);		
}

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
					all->pscreenx = all->w + 8;
					all->pscreeny = all->h + 8;
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
	int	i;
	t_drawrays *tmp;

	i = 0;
	tmp = all->node;
	(void)ch;
	my_mlx_pixel_put(all->img, 64, 64, 0xFD1700);
	while (tmp->next)
	{
		
		drawingray(all, tmp->x0, tmp->y0, tmp->x1, tmp->y1);
		tmp = tmp->next;
	}
	drawingray(all, tmp->x0, tmp->y0, tmp->x1, tmp->y1);
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
	if (all->map[y][x] == '1' || all->map[y][x] == ' ' || all->map[y][x] == 0)
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
	(*all)->p->rotationangl = fmod((*all)->p->rotationangl, 2 * M_PI);
	if ((*all)->p->rotationangl < 0)
		(*all)->p->rotationangl +=  2 * M_PI;
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
	// while (all->node->next)
	// 	free(all->node);
	// free(all->node);
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
	else if (key == 53)
	{
		printf("Game is finish\n");
		exit(1);
	}
	return (0);
}

void	freenode(t_cub *all)
{
	while ((all->node)->next != NULL)
	{
		free(all->node);
		all->node = (all->node)->next;
	}
	free(all->node);
}
int	moveplayer(t_cub *all)
{
	updat_data(&all);
	mlx_clear_window(all->mlx, all->mlx_win);
	mlx_destroy_image(all->mlx, all->img->img);
	freenode(all);
	drawimg(all, 1);
	affichminimap(all, 1);
	
	return (0);
}

int	closewin(int key, t_cub *all)
{
	(void)key;
	(void)all;
	printf("game closed!!!!");
	exit(0);
}

void	paintmap(t_cub *all, t_data *img, int ch)
{
	int		x;
	int		y;
	int		i;
	int		j;

	i = 0;
	j = 0;
	checkplayer(all, ch);
	x = all->pscreenx - 64;
	y = all->pscreeny - 64;
	// // all->distancexx = x;
	// // all->distanceyy = y;
	(void)ch;
	pixelmap(img, 0xff000);
	while (all->map[i])
	{
		j = 0;
		all->miniy = 16 * i - y;
		while(all->map[i][j] && all->map[i][j] != '\n')
		{
			all->minix = 16 * j - x;
			if (all->map[i][j] == '1')
				pixelcarre(all, 16, img, (int)all->info.cc);
			j++;
		}
		i++;
	}
}

void	conserveangle(t_cub *all)
{
	all->ray->rayangle /= (2 * M_PI);
	if (all->ray->rayangle < 0)
		all->ray->rayangle += (2 * M_PI);
}

double	calculdistance(double x, double y, double a, double b)
{
	return (sqrt(pow((a - x), 2) + pow((b - y), 2)));
}

void	raydirection(t_cub *all)
{
	if (all->ray->rayangle >= 0 && all->ray->rayangle <= M_PI)
		all->ray->downdirect = 1;
	else
		all->ray->updirect = 1;
	if ((all->ray->rayangle < (0.5 * M_PI)) || (all->ray->rayangle > (1.5 * M_PI)))
		all->ray->rightdirect = 1;
	else 
		all->ray->leftdirect = 1;
}

void	drawingray(t_cub *all, double x0, double y0, double x1, double y1)
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
	dx = x1 - x0 ;
	dy = y1 - y0;
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	incx = dx / (float)step;
	incy = dy / (float)step;
	x = x0;
	y = y0;
	while (i < step && x < 128 && y < 128)
	{
		my_mlx_pixel_put(all->img, round(x), round(y),0xeb4034);
		x += incx;
		y += incy;
		i++;
	}
}

int	checkwall_ray(t_cub *all, double xr, double yr)
{
	int	x;
	int	y;
	int	x_line;


	x = floor(xr / 16);
	y = floor(yr / 16);
	
	if (y < 0 && y > ft_strleny(all->map))
		return (0);
	if (all->map[y] != NULL)
		x_line = ft_strlen(all->map[y]);
	else
		return (0);
	if (x < 0 && x > x_line)
		return (0); 
	if (all->map[y][x] == '1' || all->map[y][x] == ' ' || all->map[y][x] == 0)
		return (0);
	return (1);
}

void	hintercept(t_cub *all, double angle)
{
	t_pos	intercept;
	t_pos	player;
	t_pos	step;
	t_pos	po;
	t_pos  hori;
	t_pos  verti;
	double hori_d;
	double verti_d;
	double nbr;
	bool hori_f; 
	bool verti_f;

	hori_f = false;
 	verti_f = false;
	int	len = ft_strleny(all->map) - 2;
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	
	all->ray->downdirect = (angle >= 0 && angle <= M_PI);
	all->ray->updirect = !all->ray->downdirect;
	
	all->ray->rightdirect = ((angle < (0.5 * M_PI)) || (angle > (1.5 * M_PI)));
	all->ray->leftdirect = !all->ray->rightdirect;
	
	// horizontal
	player.x = all->pscreenx;
	player.y = all->pscreeny;
	intercept.y = floor(player.y / 16) * 16;
	if (all->ray->downdirect)
		intercept.y += 16;
	intercept.x = player.x + (intercept.y - player.y) / tan(angle);
	step.y = 16;
	if (all->ray->updirect)
		step.y *= -1;
	step.x = step.y / tan(angle);
	if (all->ray->leftdirect && step.x > 0)
		step.x *= -1;
	if (all->ray->rightdirect && step.x < 0)
		step.x *= -1;
	while ((((int)(intercept.y / 16) >= 0) 
			&& (int)(intercept.y / 16) < len) 
			&& (int)(intercept.x / 16)>= 0 
			&& (int)(intercept.x / 16)< (int)ft_strlen(all->map[(int)intercept.y / 16]) * 16)
	{
		nbr = intercept.y;
		if (all->ray->updirect)
			nbr --;
		if (checkwall_ray(all, intercept.x, nbr))
		{
			intercept.x += step.x;
			intercept.y += step.y;
		}
		else
		{
			hori_f = true;
			hori.x = intercept.x;
			hori.y = intercept.y;
			break;
		}
	}
	// vertical

	intercept.x = floor(player.x / 16) * 16;
	if (all->ray->rightdirect)
		intercept.x += 16;
	intercept.y = player.y + (intercept.x - player.x) * tan(angle);

	step.x = 16;
	if (all->ray->leftdirect)
		step.x *= -1;
	step.y = step.x * tan(angle);
	if (all->ray->updirect && step.y > 0)
		step.y *= -1;
	if (all->ray->downdirect && step.y < 0)
		step.y *= -1;

	while ((((int)(intercept.y / 16) >= 0) 
			&& (int)(intercept.y / 16) < len) 
			&& (int)(intercept.x / 16)>= 0 
			&& (int)(intercept.x / 16) < (int)ft_strlen(all->map[(int)intercept.y / 16]) * 16)
	{
		nbr = intercept.x;
		if (all->ray->leftdirect)
			nbr--;
		if (checkwall_ray(all, nbr, intercept.y))
		{
			intercept.x += step.x;
			intercept.y += step.y;
		}
		else
		{
			verti_f = true;
			verti.x = intercept.x;
			verti.y = intercept.y;
			break;
		}
	}
	
	if (verti_f)
		verti_d = calculdistance(player.x, player.y, verti.x, verti.y);
	else 
		verti_d = 1e30;
	if (hori_f)
		hori_d = calculdistance(player.x, player.y, hori.x, hori.y);
	else 
		hori_d = 1e30;
	
	if (hori_d < verti_d)
	{
		po.x = hori.x ;
		po.y = hori.y;
		all->ray->distance = hori_d;
	}
	else
	{
		po.x = verti.x;
		po.y = verti.y;
		all->ray->distance = verti_d;
	}
	double departx = player.x - all->distancexx;
	double departy = player.y - all->distanceyy;
	double    finx 	= po.x - all->distancexx;
	double    finy 	= po.y - all->distanceyy;
	lstaddback(&(all->node), lstnew(departx, departy, finx, finy));
}

t_drawrays *lstnew(double x, double y, double a, double b)
{
	t_drawrays	*element;

	element = (t_drawrays *)malloc(sizeof(t_drawrays));
	if (!element)
		return (NULL);
	element->x0 = x;
	element->y0 = y;
	element->x1 = a;
	element->y1 = b;
	element->next = NULL;
	return (element);
}

void	lstaddback(t_drawrays **header, t_drawrays *new)
{
	t_drawrays	*p;

	p = NULL;
	if (header)
	{
		if ((*header) == NULL)
			(*header) = new;
		else
		{
			p = *header;
			while (p->next != NULL)
				p = p->next;
			p->next = new;
		}
	}
}

void	initialrayvar(t_cub *all)
{
	all->ray->colid = 0;
	all->ray->fovangle = 60 * (M_PI / 180);
	all->ray->wallstrip = 1;
	all->ray->numrays = W / all->ray->wallstrip;
	all->ray->rayangle = all->p->rotationangl - (all->ray->fovangle / 2);
	all->ray->distance = 0;
	all->ray->wallhitx = 0;
	all->ray->wallhity = 0;
	all->ray->downdirect = false;
	all->ray->updirect = false;
	all->ray->leftdirect = false;
	all->ray->rightdirect = false;
}

void	paintceiling(t_cub *all, int top)
{
	int	i;

	i = 0;
	while (i < top)
	{
		my_mlx_pixel_put(all->img, all->ray->colid, i, all->info.cc);
		i++;
	}
}

void	paintfloor(t_cub *all, int bottom)
{
	int	i;

	i = bottom;
	while (i < H)
	{
		my_mlx_pixel_put(all->img, all->ray->colid, i, all->info.fc);
		i++;
	}
}

void	renderthreeD(t_cub *all)
{
	int		i;
	double	correctdistance;
	double	distoprojectionplane;
	double	wallheight;
	int		wallstripheight;
	int		topofwall;
	int		bottomofwall;

	i = 0;
	correctdistance = 0;
	correctdistance = all->ray->distance * cos(all->ray->rayangle - all->p->rotationangl);
	distoprojectionplane = (W / 2.0) / tan(all->ray->fovangle / 2.0);
	wallheight = (16 / correctdistance) * distoprojectionplane;
	wallstripheight = (int)wallheight;
	topofwall = (H / 2.0) - (wallstripheight / 2.0);
	bottomofwall = (H / 2.0) + (wallstripheight / 2.0);
	if (topofwall < 0 || topofwall > H)
		topofwall = 0;
	if (bottomofwall > H || bottomofwall < 0)
		bottomofwall = H;
	i = topofwall;
	paintceiling(all, topofwall);
	paintfloor(all, bottomofwall);
	while (i < bottomofwall)
	{
		my_mlx_pixel_put(all->img, all->ray->colid, i, 0x3A3845);
		i++;
	}
}

void	fovminimap(t_cub *all)
{
	double 		inc_angle;

	inc_angle = all->ray->fovangle / W;
	initialrayvar(all);
	while (all->ray->colid < all->ray->numrays)
	{
		hintercept(all, all->ray->rayangle);
		renderthreeD(all);
		all->ray->rayangle += inc_angle;
		all->ray->colid++;
	}
}


void	affichminimap(t_cub *all, int ch)
{
	int x,y;
	all->node = NULL;
	checkplayer(all, ch);
	x = all->pscreenx - 64;
	y = all->pscreeny - 64;
	all->distancexx = x;
	all->distanceyy = y;
	all->posx = all->pscreenx;
	all->posy = all->pscreeny;
	if(ch == 0)
	{
		all->p = iniatialiserp(all);
		detectang(all);
	}
	fovminimap(all);
	paintmap(all, all->img, ch);
	paintplayer(all, ch);
	mlx_put_image_to_window(all->mlx, all->mlx_win, all->img->img, 0, 0);
}

void	raycasting(t_cub *all)
{
	mlx_hook(all->mlx_win, 3, 1L<<1, keyrelease, all);
	mlx_hook(all->mlx_win, 2, 1L<<0, keypressed, all);
	mlx_loop_hook(all->mlx, moveplayer, all);
	mlx_loop(all->mlx);
}
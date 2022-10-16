/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momayaz <momayaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:45:44 by ygbouri           #+#    #+#             */
/*   Updated: 2022/10/09 17:37:24 by momayaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


static void	ft_left(t_cub *all, int x, int pos)
{
	if (x > pos)
	{
		(all)->p->rotationangl +=  (2 * M_PI / 180);
        (all)->p->rotationangl = fmod((all)->p->rotationangl, 2 * M_PI);
        if ((all)->p->rotationangl < 0)
            (all)->p->rotationangl +=  2 * M_PI;
	}
}

static void	ft_right(t_cub *all, int x, int pos)
{
	if (x < pos)
	{
		(all)->p->rotationangl +=  -1 * (2 * M_PI / 180);
        (all)->p->rotationangl = fmod((all)->p->rotationangl, 2 * M_PI);
        if ((all)->p->rotationangl < 0)
            (all)->p->rotationangl +=  2 * M_PI;
	}
}

int	ft_mouse(int x, int y, t_cub *game)
{
	static int	pos;

	mlx_clear_window(game->mlx, game->mlx_win);
	ft_left(game, x, pos);
	ft_right(game, x, pos);
	pos = x;
    moveplayer(game);
	return (y);
}


void   sorting_sprites(t_cub *all)
{
	int i;
	int j;
	int tmp;

	i = 0;
	while (i < all->spritecount)
	{
		j = i + 1;
		while (j < all->spritecount)
		{
			if (all->sprite[i].dist < all->sprite[j].dist && all->sprite[i].visible == 1 && all->sprite[j].visible == 1)
			{
				tmp = all->sprite[i].dist;
				all->sprite[i].dist = all->sprite[j].dist;
				all->sprite[j].dist = tmp;
			}
			j++;
		}
		i++;
	}
}

int calculspritenumber(t_cub *all)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == 'F')
				k++;
			j++;
		}
		i++;
	}
	return (k);
}

void locateSprite(t_cub *all)
{
	int i;
	int j;
	int k;
	int l;
	int m;

	i = 0;
	k = 0;
	l = 0;
	while (all->map[i])
	{
		j = 0;
		m = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == 'F')
			{
				all->sprite[k].x = i + 0.5;
				all->sprite[k].screenx = m;
				all->sprite[k].y = j + 0.5;
				all->sprite[k].screeny = l;
				k++;
			}
			j++;
			m += 16;
		}
		i++;
		l += 16;
	}
}

void calculspritedistance(t_cub *all)
{
	int i;

	i = 0;
	while (i < all->spritecount)
	{
		all->sprite[i].dist = calculdistance(all->pscreenx, all->pscreeny, all->sprite[i].screenx, all->sprite[i].screeny);
		i++;
	}
}

void randringsprite(t_cub *all)
{
	int i;
	int x = 0;
	int y = 0;
	t_data info;
	void *img;
	unsigned int *addr;
	int w;
	int h;

	i = 0;
	img = mlx_xpm_file_to_image(all->mlx, "./pics/1.xpm", &w, &h);
	if (!img)
	{
		printf("error");
		exit(0);
	}
	addr = (unsigned int*) mlx_get_data_addr(img, &info.bits_per_pixel, &info.line_length, &info.endian);
	while (i < all->spritecount)
	{
		if (all->sprite[i].visible)
		{
			//sprite height and width
			all->sprite[i].spritrheight = (16 / all->sprite[i].dist) * all->distoprojectionplane;
			all->sprite[i].spritewidth = all->sprite[i].spritrheight;
			// sprit top y and bottom y
			all->sprite[i].spritetopy = (H / 2) - (all->sprite[i].spritrheight / 2);
			if (all->sprite[i].spritetopy < 0)
				all->sprite[i].spritetopy = 0;
			all->sprite[i].spriteboty = (H / 2) + (all->sprite[i].spritrheight / 2);
			if (all->sprite[i].spriteboty > H)
				all->sprite[i].spriteboty = H;
			// sprite position on pscreen
			all->sprite[i].spritangle = atan2(all->sprite[i].x - all->pscreeny / 16, all->sprite[i].y - all->pscreenx / 16) - all->p->rotationangl;
			all->sprite[i].spritxpos = tan(all->sprite[i].spritangle) * all->distoprojectionplane;
			//sprite x left and right
			all->sprite[i].spriteleftx = (W / 2)  + all->sprite[i].spritxpos;
			all->sprite[i].spriterightx = all->sprite[i].spriteleftx + all->sprite[i].spritewidth;
			all->sprite[i].texturewidth = w;
			all->sprite[i].textureheight = h;
			x = all->sprite[i].spriteleftx;
			while (x < all->sprite[i].spriterightx)
			{
				int spriteoffsetx = (x - all->sprite[i].spriteleftx) * all->sprite[i].texturewidth / all->sprite[i].spritewidth;
				y = all->sprite[i].spritetopy;
				while (y < all->sprite[i].spriteboty)
				{
					int spriteoffsety = (y - all->sprite[i].spritetopy) * all->sprite[i].textureheight / all->sprite[i].spritrheight;
					if (x > 0 && x < W && y > 0 && y < H)
					{
						int color = addr[spriteoffsety * all->sprite[i].texturewidth + spriteoffsetx];
						if (color > 0 && all->sprite[i].dist < all->ray->distance && all->ray->distance)
							my_mlx_pixel_put(all->img, x , y, color);
					}
					y++;
				}
				x++;
			}
		}
		i++;
	}
}

void ifspritevisible(t_cub *all, int k){
	int i;

	i = 0;
	while(i < k)
	{
		all->sprite[i].spritangle = all->p->rotationangl - atan2(all->sprite[i].x - all->pscreeny / 16, all->sprite[i].y - all->pscreenx / 16);
		if (all->sprite[i].spritangle < - M_PI)
			all->sprite[i].spritangle += 2 * M_PI;
		if (all->sprite[i].spritangle > M_PI)
			all->sprite[i].spritangle -= 2 * M_PI;//dop
		all->sprite[i].spritangle = ft_abs(all->sprite[i].spritangle);
		if (all->sprite[i].spritangle < all->ray->fovangle / 2 )
		{
			all->sprite[i].visible = 1;
		}
		else
		{
			all->sprite[i].visible = 0;
		}
		i++;
	}
			calculspritedistance(all);
			locateSprite(all);
			randringsprite(all);
}


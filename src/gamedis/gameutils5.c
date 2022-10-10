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

void initSprite(t_cub *all)
{
	all->sprit[0].x = 640;
	all->sprit[0].y = 630;
	all->sprit[0].tex_x = 9;
	all->sprit[1].x = 2;
	all->sprit[1].y = 8;
	all->sprit[1].tex_x = 9;
	all->sprit[2].x = 8;
	all->sprit[2].y = 8;
	all->sprit[2].tex_x = 10;
	all->sprit[3].x = 8;
	all->sprit[3].y = 2;
	all->sprit[3].tex_x = 11;
}

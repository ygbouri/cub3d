/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameutils11.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momayaz <momayaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:12:03 by momayaz           #+#    #+#             */
/*   Updated: 2022/10/17 18:24:36 by momayaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void spriteimginit(t_cub *all)
{
	t_data info;

	all->spriteimg[0].img = mlx_xpm_file_to_image(all->mlx, "./pics/1.xpm", &all->spriteimg[0].w, &all->spriteimg[0].h);
	if (!all->spriteimg[0].img)
		exit(1);
	all->spriteimg[0].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[0].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->spriteimg[1].img = mlx_xpm_file_to_image(all->mlx, "./pics/2.xpm", &all->spriteimg[1].w, &all->spriteimg[1].h);
	if (!all->spriteimg[1].img)
		exit(1);
	all->spriteimg[1].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[1].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->spriteimg[2].img = mlx_xpm_file_to_image(all->mlx, "./pics/3.xpm", &all->spriteimg[2].w, &all->spriteimg[2].h);
	if (!all->spriteimg[2].img)
		exit(1);
	all->spriteimg[2].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[2].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->spriteimg[3].img = mlx_xpm_file_to_image(all->mlx, "./pics/4.xpm", &all->spriteimg[3].w, &all->spriteimg[3].h);
	if (!all->spriteimg[3].img)
		exit(1);
	all->spriteimg[3].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[3].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->spriteimg[4].img = mlx_xpm_file_to_image(all->mlx, "./pics/5.xpm", &all->spriteimg[4].w, &all->spriteimg[4].h);
	if (!all->spriteimg[4].img)
		exit(1);
	all->spriteimg[4].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[4].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	spriteimginit1(all);
	spriteimginit2(all);
}

void spriteimginit1(t_cub *all)
{
	t_data info;

	all->spriteimg[5].img = mlx_xpm_file_to_image(all->mlx, "./pics/6.xpm", &all->spriteimg[5].w, &all->spriteimg[5].h);
	if (!all->spriteimg[5].img)
		exit(1);
	all->spriteimg[5].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[5].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->spriteimg[6].img = mlx_xpm_file_to_image(all->mlx, "./pics/7.xpm", &all->spriteimg[6].w, &all->spriteimg[6].h);
	if (!all->spriteimg[6].img)
		exit(1);
	all->spriteimg[6].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[6].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->spriteimg[7].img = mlx_xpm_file_to_image(all->mlx, "./pics/8.xpm", &all->spriteimg[7].w, &all->spriteimg[7].h);
	if (!all->spriteimg[7].img)
		exit(1);
	all->spriteimg[7].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[7].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->spriteimg[8].img = mlx_xpm_file_to_image(all->mlx, "./pics/9.xpm", &all->spriteimg[8].w, &all->spriteimg[8].h);
	if (!all->spriteimg[8].img)
		exit(1);
	all->spriteimg[8].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[8].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->spriteimg[9].img = mlx_xpm_file_to_image(all->mlx, "./pics/10.xpm", &all->spriteimg[9].w, &all->spriteimg[9].h);
	if (!all->spriteimg[9].img)
		exit(1);
	all->spriteimg[9].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[9].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
}

void spriteimginit2(t_cub *all)
{
	t_data info;

	all->spriteimg[10].img = mlx_xpm_file_to_image(all->mlx, "./pics/11.xpm", &all->spriteimg[10].w, &all->spriteimg[10].h);
	if (!all->spriteimg[10].img)
		exit(1);
	all->spriteimg[10].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[10].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->spriteimg[11].img = mlx_xpm_file_to_image(all->mlx, "./pics/12.xpm", &all->spriteimg[11].w, &all->spriteimg[11].h);
	if (!all->spriteimg[11].img)
		exit(1);
	all->spriteimg[11].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[11].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->spriteimg[12].img = mlx_xpm_file_to_image(all->mlx, "./pics/13.xpm", &all->spriteimg[12].w, &all->spriteimg[12].h);
	if (!all->spriteimg[12].img)
		exit(1);
	all->spriteimg[12].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[12].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->spriteimg[13].img = mlx_xpm_file_to_image(all->mlx, "./pics/14.xpm", &all->spriteimg[13].w, &all->spriteimg[13].h);
	if (!all->spriteimg[13].img)
		exit(1);
	all->spriteimg[13].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[13].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
	all->spriteimg[14].img = mlx_xpm_file_to_image(all->mlx, "./pics/15.xpm", &all->spriteimg[14].w, &all->spriteimg[14].h);
	if (!all->spriteimg[14].img)
		exit(1);
	all->spriteimg[14].data = (unsigned int*) mlx_get_data_addr(all->spriteimg[14].img, &all->img->bits_per_pixel, &info.line_length, &info.endian);
}

void paintmap1(t_cub *all, int i, int j, t_data *img)
{
	int s;

	s = 0;
	if (all->map[i][j] == '1')
		pixelcarre(all, 16, img, (int)all->info.cc);
	if (all->map[i][j] == 'D')
		pixelcarre(all, 16, img, 0x125AFF);
	if (all->map[i][j] == 'F')
	{
		while (s < all->spritecount)
		{
			if ((int)floor(all->sprite[s].x)  == i && (int)floor(all->sprite[s].y) == j)
			{
				if (all->sprite[s].visible)
					pixelcarre(all, 16, img, 0x00ffff);
				else
					pixelcarre(all, 16, img, 0x0000FF);
			}
			s++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:39:24 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/11 18:03:38 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

t_mlx	*create_mlx(t_coor *map)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, 1200, 1200, "FdF");
	mlx->map = map;
	mlx->scale = 25;
	mlx->w = 0;
	mlx->mode = 0;
	mlx->mode_c = 0;
	mlx->theta = PI / 6;
	return (mlx);
}

int		get_w(char *map)
{
	int w;

	w = 0;
	while (*map && *map != '\n')
	{
		if (*map == ' ')
		{
			while (*(map + 1) == ' ')
				map++;
			w++;
		}
		map++;
	}
	return (w + 1);
}

int		get_h(char *map)
{
	int h;

	h = 1;
	while (*map)
	{
		if (*map == '\n')
			h++;
		map++;
	}
	return (h);
}

int		get_c(int color)
{
	if (color == 0)
		return (0xFFFFFF);
	color = color * 10 + color * 20 * 256 + color * 20 * 256 * 256;
	color = 0xFFFFFF - color;
	while (color <= 0)
		color += 0xFFFFFF;
	return (color);
}

t_coor	*find_below(t_coor *map, int w)
{
	int i;

	i = 0;
	while (i < w)
	{
		if (!map)
			return (NULL);
		map = map->next;
		i++;
	}
	return (map);
}

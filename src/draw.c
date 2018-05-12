/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:38:42 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/11 18:04:56 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

static void		draw_angle(t_mlx *mlx)
{
	char	*s;
	int		i;

	i = (int)round(mlx->theta * 180 / PI);
	s = ft_itoa(i);
	mlx_string_put(mlx->mlx, mlx->win, 32, 145, 0x1FA277, "Angle: ");
	mlx_string_put(mlx->mlx, mlx->win, 132, 145, 0x1FA277, s);
	free(s);
}

static void		draw_inst(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < 190)
	{
		if (i < 145)
			mlx_pixel_put(mlx->mlx, mlx->win, 25, 25 + i, 0x666633);
		mlx_pixel_put(mlx->mlx, mlx->win, 25 + i, 25, 0x666633);
		if (i < 145)
			mlx_pixel_put(mlx->mlx, mlx->win, 215, 25 + i, 0x666633);
		mlx_pixel_put(mlx->mlx, mlx->win, 25 + i, 170, 0x666633);
		i++;
	}
	mlx_string_put(mlx->mlx, mlx->win, 32, 25, 0x215277, "Arrows: move");
	mlx_string_put(mlx->mlx, mlx->win, 32, 40, 0x215277, "Q,E: rotate Z");
	mlx_string_put(mlx->mlx, mlx->win, 32, 55, 0x215277, "A,D: rotate Y");
	mlx_string_put(mlx->mlx, mlx->win, 32, 70, 0x215277, "W,S: rotate X");
	mlx_string_put(mlx->mlx, mlx->win, 32, 85, 0x215277, "-,+ to zoom");
	mlx_string_put(mlx->mlx, mlx->win, 32, 100, 0x215277, "Space: toggle dots");
	mlx_string_put(mlx->mlx, mlx->win, 32, 115, 0x215277, "C: toggle color");
	mlx_string_put(mlx->mlx, mlx->win, 32, 130, 0x215277, "1, 2: change angle");
	draw_angle(mlx);
}

static void		draw_line(t_mlx *mlx, t_coor *c1, t_coor *c2)
{
	float	*x;
	int		dis;

	if (!c1 || !c2)
		return ;
	dis = d(mlx, c1, c2);
	x = (float *)malloc(6 * sizeof(float));
	x[0] = round(c1->matrix[0] * mlx->scale + 200);
	x[1] = round(c1->matrix[1] * mlx->scale + 200);
	x[2] = (round(c2->matrix[0] * mlx->scale + 200) - x[0]) / dis;
	x[3] = (round(c2->matrix[1] * mlx->scale + 200) - x[1]) / dis;
	x[4] = c1->h - c1->h * (mlx->mode_c % 2);
	x[5] = (c2->h - x[4]) / dis;
	while (round(x[0]) != round(c2->matrix[0] * mlx->scale + 200)
	|| round(x[1]) != round(c2->matrix[1] * mlx->scale + 200))
	{
		if (x[0] <= 1200 && x[1] <= 1200 && x[0] >= 0 && x[1] >= 0)
			mlx_pixel_put(mlx->mlx, mlx->win, x[0], x[1], get_c(round(x[4])));
		round(x[0]) != c2->matrix[0] * mlx->scale + 200 ? x[0] += x[2] : 1;
		round(x[1]) != c2->matrix[1] * mlx->scale + 200 ? x[1] += x[3] : 1;
		if (get_c(x[4]) != get_c(c2->h) && mlx->mode_c % 2 == 0)
			x[4] += x[5];
	}
	free(x);
}

void			draw_map(t_mlx *mlx)
{
	t_coor	*map;
	int		i;

	i = 0;
	map = mlx->map;
	while (map)
	{
		if (mlx->mode % 2 == 1)
		{
			mlx_pixel_put(mlx->mlx, mlx->win,
			round(map->matrix[0] * mlx->scale + 200),
			round(map->matrix[1] * mlx->scale + 200), map->color);
		}
		else
		{
			if (i != mlx->w - 1)
				draw_line(mlx, map, map->next);
			draw_line(mlx, map, find_below(map, mlx->w));
			if (i == mlx->w)
				i = 0;
		}
		i++;
		map = map->next;
	}
	draw_inst(mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:38:42 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/05 21:03:15 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

static float	color_s(int color, float *colors)
{
	float r;
	float g;
	float b;

	r = color / (256 * 256);
	g = (color % (256 * 256)) / 256;
	b = (color % (256 * 256)) % 256;
	r = r - colors[0];
	g = g - colors[1];
	b = b - colors[2];
	r = r * 256 * 256;
	g = g * 256;
	return (r + g + b);
}

static float	*color_c(t_mlx *mlx, t_coor *p1, t_coor *p2)
{
	float	*c;

	c = (float *)malloc(3 * sizeof(float));
	c[0] = p1->color / (256 * 256) - p2->color / (256 * 256);
	c[1] = (p1->color % (256 * 256)) / 256 - (p2->color % (256 * 256)) / 256;
	c[2] = (p1->color % (256 * 256)) % 256 - (p2->color % (256 * 256)) % 256;
	c[0] = c[0] / (10 * mlx->scale);
	c[1] = c[1] / (10 * mlx->scale);
	c[2] = c[2] / (10 * mlx->scale);
	if (c[0] < 0)
		c[0] = -c[0];
	if (c[1] < 0)
		c[1] = -c[1];
	if (c[2] < 0)
		c[2] = -c[2];
	if (mlx->mode_c % 2 == 1)
	{
		c[0] = 0;
		c[1] = 0;
		c[2] = 0;
	}
	return (c);
}

static void		draw_inst(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < 190)
	{
		if (i < 115)
			mlx_pixel_put(mlx->mlx, mlx->win, 25, 25 + i, 0x666633);
		mlx_pixel_put(mlx->mlx, mlx->win, 25 + i, 25, 0x666633);
		if (i < 115)
			mlx_pixel_put(mlx->mlx, mlx->win, 215, 25 + i, 0x666633);
		mlx_pixel_put(mlx->mlx, mlx->win, 25 + i, 140, 0x666633);
		i++;
	}
	mlx_string_put(mlx->mlx, mlx->win, 32, 25, 0x215277, "Arrows: move");
	mlx_string_put(mlx->mlx, mlx->win, 32, 40, 0x215277, "Q,E: rotate Z");
	mlx_string_put(mlx->mlx, mlx->win, 32, 55, 0x215277, "A,D: rotate Y");
	mlx_string_put(mlx->mlx, mlx->win, 32, 70, 0x215277, "W,S: rotate X");
	mlx_string_put(mlx->mlx, mlx->win, 32, 85, 0x215277, "-,+ to zoom");
	mlx_string_put(mlx->mlx, mlx->win, 32, 100, 0x215277, "Space: toggle dots");
	mlx_string_put(mlx->mlx, mlx->win, 32, 115, 0x215277, "C: toggle color");
}

static void		draw_line(t_mlx *mlx, t_coor *c1, t_coor *c2)
{
	float	*x;
	float	color;
	float	*c_d;

	if (!c1 || !c2)
		return ;
	x = (float *)malloc(4 * sizeof(float));
	x[0] = round(c1->matrix[0] * mlx->scale + 200);
	x[1] = round(c1->matrix[1] * mlx->scale + 200);
	x[2] = (round(c2->matrix[0] * mlx->scale + 200) - x[0]) / d(mlx, c1, c2);
	x[3] = (round(c2->matrix[1] * mlx->scale + 200) - x[1]) / d(mlx, c1, c2);
	color = c1->color + (0xFFFFFF - c1->color) * (mlx->mode_c % 2);
	c_d = color_c(mlx, c1, c2);
	while (round(x[0]) != round(c2->matrix[0] * mlx->scale + 200)
	|| round(x[1]) != round(c2->matrix[1] * mlx->scale + 200))
	{
		if (x[0] < 1200 && x[1] < 1200)
			mlx_pixel_put(mlx->mlx, mlx->win, x[0], x[1], round(color));
		round(x[0]) != c2->matrix[0] * mlx->scale + 200 ? x[0] += x[2] : 1;
		round(x[1]) != c2->matrix[1] * mlx->scale + 200 ? x[1] += x[3] : 1;
		if (color > c2->color)
			color = color_s(color, c_d);
	}
	free(c_d);
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

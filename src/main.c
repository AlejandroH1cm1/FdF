/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:43:20 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/28 01:57:31 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

static void		move(t_coor *map, int dir, int scale)
{
	while (map)
	{
		if (dir == 1)
			map->matrix[0] -= scale;
		if (dir == 2)
			map->matrix[0] += scale;
		if (dir == 3)
			map->matrix[1] += scale;
		if (dir == 4)
			map->matrix[1] -= scale;
		map = map->next;
	}
}

static void		mult_m(t_coor *map, float **mx)
{
	float	x;
	float	y;
	float	z;

	while (map)
	{
		x = map->matrix[0];
		y = map->matrix[1];
		z = map->matrix[2];
		map->matrix[0] = x * mx[0][0] + y * mx[1][0] + z * mx[2][0];
		map->matrix[1] = x * mx[0][1] + y * mx[1][1] + z * mx[2][1];
		map->matrix[2] = x * mx[0][2] + y * mx[1][2] + z * mx[2][2];
		map = map->next;
	}
}

static void		rotate(t_mlx *mlx, t_coor *map, int d)
{
	float	**matrix;

	matrix = NULL;
	if (d == 5)
		matrix = rot_mx_x(-mlx->theta);
	else if (d == 2)
		matrix = rot_mx_x(mlx->theta);
	else if (d == 1)
		matrix = rot_mx_y(mlx->theta);
	else if (d == 3)
		matrix = rot_mx_y(-mlx->theta);
	else if (d == 6)
		matrix = rot_mx_z(mlx->theta);
	else if (d == 4)
		matrix = rot_mx_z(-mlx->theta);
	mult_m(map, matrix);
	free(matrix[0]);
	free(matrix[1]);
	free(matrix[2]);
	free(matrix);
}

static int		deal_key(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	ft_putnbr(key);
	if (key == 49)
		mlx->mode++;
	if (key >= 123 && key <= 126)
		move(mlx->map, key - 122, 1);
	if (key >= 0 && key <= 2)
		rotate(mlx, mlx->map, key + 1);
	if (key >= 12 && key <= 14)
		rotate(mlx, mlx->map, key - 8);
	if (key == 53)
		dst_mlx(mlx);
	if (key == 69)
		mlx->scale += 1;
	if (key == 78)
		mlx->scale -= 1;
	if (key == 8)
		mlx->mode_c += 1;
	if (key == 18 || key == 19)
		extra_key(key, mlx);
	mlx_clear_window(mlx->mlx, mlx->win);
	draw_map(mlx);
	return (0);
}

int				main(int ac, char **av)
{
	t_coor	*map;
	t_mlx	*mlx;
	int		w;

	w = 0;
	if (ac != 2)
	{
		ft_putendl("usage: fdf file_to_read");
		return (-1);
	}
	if (!(map = get_map(av[1], &w)))
	{
		ft_putendl("Could not read from file");
		return (-1);
	}
	mlx = create_mlx(map);
	mlx->w = w;
	draw_map(mlx);
	mlx_key_hook(mlx->win, deal_key, (void *)mlx);
	mlx_loop(mlx->mlx);
	free(mlx);
	return (0);
}

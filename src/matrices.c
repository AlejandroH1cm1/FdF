/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:38:57 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/05 21:03:17 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

float	**rot_mx_x(double theta)
{
	float	**matrix;
	int		i;

	matrix = (float **)malloc(3 * sizeof(float *));
	i = 0;
	while (i < 4)
	{
		matrix[i] = (float *)malloc(3 * sizeof(float *));
		matrix[i][0] = 0;
		matrix[i][1] = 0;
		matrix[i][2] = 0;
		i++;
	}
	matrix[0][0] = 1;
	matrix[1][1] = (float)(cos(theta));
	matrix[1][2] = (float)(-sin(theta));
	matrix[2][1] = (float)(sin(theta));
	matrix[2][2] = (float)(cos(theta));
	return (matrix);
}

float	**rot_mx_y(double theta)
{
	float	**matrix;
	int		i;

	matrix = (float **)malloc(3 * sizeof(float *));
	i = 0;
	while (i < 3)
	{
		matrix[i] = (float *)malloc(3 * sizeof(float *));
		matrix[i][0] = 0;
		matrix[i][1] = 0;
		matrix[i][2] = 0;
		i++;
	}
	matrix[1][1] = 1;
	matrix[0][0] = (float)(cos(theta));
	matrix[0][2] = (float)(sin(theta));
	matrix[2][0] = (float)(-sin(theta));
	matrix[2][2] = (float)(cos(theta));
	return (matrix);
}

float	**rot_mx_z(double theta)
{
	float	**matrix;
	int		i;

	matrix = (float **)malloc(3 * sizeof(float *));
	i = 0;
	while (i < 3)
	{
		matrix[i] = (float *)malloc(3 * sizeof(float *));
		matrix[i][0] = 0;
		matrix[i][1] = 0;
		matrix[i][2] = 0;
		i++;
	}
	matrix[2][2] = 1;
	matrix[0][0] = (float)(cos(theta));
	matrix[0][1] = (float)(-sin(theta));
	matrix[1][0] = (float)(sin(theta));
	matrix[1][1] = (float)(cos(theta));
	return (matrix);
}

float	d(t_mlx *mlx, t_coor *p1, t_coor *p2)
{
	float	x;
	float	y;
	float	d;

	x = p1->matrix[0] * mlx->scale - p2->matrix[0] * mlx->scale;
	y = p1->matrix[1] * mlx->scale - p2->matrix[1] * mlx->scale;
	d = hypot(x, y);
	return (d * 2);
}

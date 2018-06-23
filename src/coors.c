/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:38:32 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/19 17:13:41 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

static t_coor	*new_coor(float x, float y, float z, int color)
{
	t_coor	*new;

	new = (t_coor *)malloc(sizeof(t_coor));
	new->color = color;
	new->matrix = (float *)malloc(4 * sizeof(float));
	new->matrix[0] = x;
	new->matrix[1] = y;
	new->matrix[2] = z;
	new->matrix[3] = 1;
	new->h = z;
	new->next = NULL;
	return (new);
}

void			add_coor(t_coor **map, float *matrix, int color)
{
	t_coor	*tmp;

	if (!*map)
	{
		*map = new_coor(matrix[0], matrix[1], matrix[2], color);
		return ;
	}
	tmp = *map;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_coor(matrix[0], matrix[1], matrix[2], color);
}

void			dst_map(t_coor **map)
{
	if ((*map)->next)
		dst_map(&((*map)->next));
	free((*map)->matrix);
	free(*map);
	map = NULL;
}

void			dst_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	dst_map(&(mlx->map));
	exit(0);
}

void			extra_key(int key, t_mlx *mlx)
{
	if (key == 18)
		mlx->theta += PI / 18;
	if (key == 19)
		mlx->theta -= PI / 18;
}

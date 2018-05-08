/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:41:50 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/07 20:08:41 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFDF_H
# define LIBFDF_H
# include "mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# define BUFF_SIZE 2048
# define PI 3.14159265359

typedef struct		s_coor
{
	float			*matrix;
	int				h;
	int				color;
	struct s_coor	*next;
}					t_coor;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	int				scale;
	int				w;
	int				mode;
	int				mode_c;
	float			theta;
	struct s_coor	*map;
}					t_mlx;

t_mlx				*create_mlx(t_coor *map);
t_coor				*get_map(char *file, int *w);
void				add_coor(t_coor **map, float *matrix, int color);
void				dst_map(t_coor **map);
void				dst_mlx(t_mlx *mlx);
void				extra_key(int key, t_mlx *mlx);
int					get_w(char *map);
int					get_h(char *map);
int					get_c(int color);
void				draw_map(t_mlx *mlx);
float				**rot_mx_x(double theta);
float				**rot_mx_y(double theta);
float				**rot_mx_z(double theta);
float				d(t_mlx *mlx, t_coor *p1, t_coor *p2);
t_coor				*find_below(t_coor *map, int w);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherrera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:38:24 by aherrera          #+#    #+#             */
/*   Updated: 2018/05/05 19:04:54 by aherrera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfdf.h"

static t_coor	*map_to_coors(char *map, int w, float *co)
{
	int		i;
	char	**words;
	t_coor	*coors;

	words = ft_strsplit(map, ' ');
	i = 0;
	coors = NULL;
	while (words[i + 1])
	{
		co[2] = (float)ft_atoi(words[i]);
		co[3] = get_c(words[i]);
		add_coor(&coors, co, co[3]);
		co[0]++;
		if (co[0] == w)
		{
			co[1]++;
			co[0] = 0;
		}
		i++;
	}
	return (coors);
}

static char		*r_fi(int fd, char **s)
{
	int		ret;
	char	*tmp;
	char	*r;

	tmp = ft_strnew(BUFF_SIZE + 1);
	ret = read(fd, tmp, BUFF_SIZE);
	if (ret < 0)
	{
		free(tmp);
		return (NULL);
	}
	tmp[ret] = '\0';
	if (ret != 0)
		tmp = r_fi(fd, &tmp);
	if (!s)
		r = ft_strdup(tmp);
	else
		r = ft_strjoin(*s, tmp);
	if (s)
		free(*s);
	free(tmp);
	return (r);
}

static char		*read_f(char *file)
{
	int		fd;
	char	*map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = r_fi(fd, NULL);
	return (map);
}

t_coor			*get_map(char *file, int *w)
{
	char	*map;
	float	*m;
	t_coor	*coors;

	map = read_f(file);
	if (!map)
		return (NULL);
	m = (float *)malloc(4 * sizeof(int));
	m[0] = 0;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0xFFFFFF;
	*w = get_w(map);
	coors = map_to_coors(map, *w, m);
	return (coors);
}

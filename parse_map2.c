/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvial <marvin@42quebec.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:35:04 by gvial             #+#    #+#             */
/*   Updated: 2023/02/06 16:35:05 by gvial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_to_map(t_cub3d *cub3d)
{
	int		count;
	int		map_fd;
	char	*line;

	map_fd = open(cub3d->map_path, O_RDONLY);
	count = 0;
	while (count != 6)
	{
		line = get_next_line(map_fd);
		if (!line)
			break ;
		if (line[0] == 'N' || line[0] == 'E' || line[0] == 'S'
			|| line[0] == 'W' || line[0] == 'C' || line[0] == 'F')
			count++;
		free(line);
	}
	return (map_fd);
}

char	*fill_map(t_cub3d *cub3d)
{
	char	*map;
	char	*line;
	int		map_fd;

	map = NULL;
	map_fd = skip_to_map(cub3d);
	line = get_next_line(map_fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(map_fd);
	}
	while (line && line[0] != '\n')
	{
		map = ft_strjoin_gnl(map, line);
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (map);
}

void	alloc_map(t_cub3d *cub3d)
{
	int		i;
	int		x;
	int		y;

	y = split_len(cub3d->map.map_d);
	x = 0;
	i = -1;
	while (cub3d->map.map_d[++i])
		if (ft_strlen(cub3d->map.map_d[i]) > x)
			x = ft_strlen(cub3d->map.map_d[i]);
	cub3d->map.map = malloc(sizeof(int *) * y);
	i = y;
	while (--i >= 0)
		cub3d->map.map[i] = ft_calloc(x, sizeof(int));
	cub3d->map.height = y;
	cub3d->map.width = x;
}

static void	log_map_norm(t_cub3d *cub3d, int i, int x, int z)
{
	if (z < ft_strlen(cub3d->map.map_d[i]) && cub3d->map.map_d[i][z] == ' ')
		cub3d->map.map[i][x] = -1;
	else if (cub3d->map.map_d[i][z] == 'E')
		cub3d->map.map[i][x] = 2;
	else if (cub3d->map.map_d[i][z] == 'N')
		cub3d->map.map[i][x] = 3;
	else if (cub3d->map.map_d[i][z] == 'W')
		cub3d->map.map[i][x] = 4;
	else if (cub3d->map.map_d[i][z] == 'S')
		cub3d->map.map[i][x] = 5;
	else if (z < ft_strlen(cub3d->map.map_d[i]))
		cub3d->map.map[i][x] = cub3d->map.map_d[i][z] - 48;
	else
		cub3d->map.map[i][x] = -1;
}

void	log_map(t_cub3d *cub3d)
{
	int		i;
	int		x;
	int		z;

	i = -1;
	z = 0;
	x = -1;
	while (cub3d->map.map_d[++i])
	{
		while (++x < cub3d->map.width)
		{
			log_map_norm(cub3d, i, x, z);
			z++;
		}
		x = -1;
		z = 0;
	}
}

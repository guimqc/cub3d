#include "cub3d.h"
#include "lib/libft/get_next_line/get_next_line.h"

static int	skip_to_map(t_cub3d *cub3d)
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
			break;
		if (line[0] == 'N' || line[0] == 'E' || line[0] == 'S'
			|| line[0] == 'W' || line[0] == 'C' || line[0] == 'F')
			count++;
		free(line);
	}
	return (map_fd);
}

static char	*fill_map(t_cub3d *cub3d)
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

// parse the map into cub3d->map.map and player x/y and orientation
void	parse_map(t_cub3d *cub3d)
{
	char	*map;

	map = fill_map(cub3d);
	// log map into a int**
	// verify map has walls all around it
	// get player's x and y position and orientation

	free(map);
}
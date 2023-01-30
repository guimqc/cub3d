#include "cub3d.h"

// function that display all the data from all the structs for debugging
static void	display_data(t_cub3d *cub3d)
{
	printf("map_path: %s\n", cub3d->map_path);
	printf("map_width: %i\n", cub3d->map.width);
	printf("map_height: %i\n", cub3d->map.height);
	printf("c_color: %i,%i,%i\n", cub3d->map.c_color[0], cub3d->map.c_color[1], cub3d->map.c_color[2]);
	printf("f_color: %i,%i,%i\n", cub3d->map.f_color[0], cub3d->map.f_color[1], cub3d->map.f_color[2]);
}

static void	init(t_cub3d *cub3d, char *map_path)
{
	cub3d->map_path = map_path;
	cub3d->map.c_color[0] = 0;
	cub3d->map.c_color[1] = 0;
	cub3d->map.c_color[2] = 0;
	cub3d->map.f_color[0] = 0;
	cub3d->map.f_color[1] = 0;
	cub3d->map.f_color[2] = 0;
	cub3d->map.map = NULL;
	cub3d->map.height = 0;
	cub3d->map.width = 0;
	cub3d->display.mlx = mlx_init();
	cub3d->display.mlx_win = NULL;
	cub3d->display.img_width = 0;
	cub3d->display.img_height = 0;
	cub3d->display.e_texture = NULL;
	cub3d->display.w_texture = NULL;
	cub3d->display.s_texture = NULL;
	cub3d->display.n_texture = NULL;
	cub3d->player.x = 0;
	cub3d->player.y = 0;
	cub3d->player.orientation = 0;
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (!argv[1])
		arg_error(&cub3d);
	init(&cub3d, argv[1]);
	parse(&cub3d);

	display_data(&cub3d);

	// mlx hook and displaying window
	display_window(&cub3d);
	mlx_key_hook(cub3d.display.mlx_win, key_hook, &cub3d);
	mlx_hook(cub3d.display.mlx_win, 17, 0, close_x, &cub3d);
	mlx_loop(cub3d.display.mlx);

	// free cub3d->map.worldMap and close all the fds in cub3d and cub3d->map and exit()

}

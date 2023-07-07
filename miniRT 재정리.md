```c
int	main(int ac, char **av)
{
	t_vars	vars;
	int		fd;

	fd = file_check(ac, av);
	vars.scene = scene_init(); // initing mlx canvas values
	check_len(av[1]);
	readmap(&vars.scene, fd);
	ft_init_mlx(&vars, &vars.scene, &vars.image);
	ft_draw(&vars.scene, &vars.image);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_key_hook(vars.win, key_press, &vars);
	mlx_hook(vars.win, X_EVENT_KEY_EXIT, 0, &key_destroy, &vars);
	mlx_loop(vars.mlx);
	return (0);
}```
```c
int	main(int ac, char **av)
{
	t_vars	vars;
	int		fd;

	fd = file_check(ac, av);
	vars.scene = scene_init(); // initing mlx canvas values
	check_rt(av[1]); //check rt file
	readmap(&vars.scene, fd); 
	// read map from the rt.file and parse into map info
	ft_init_mlx(&vars, &vars.scene, &vars.image);
	// init mlx
	ft_draw(&vars.scene, &vars.image);
	// circling the canvas pixels 
	// check if that pixel is pointing object
	// -- if false : background color is rendered by position
	// -- if true : check distance to the object, get the closest one
	//.-- render color by light, ambient, color of the object
	// -- after color is rendered, render phong lighting
	// 
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_key_hook(vars.win, key_press, &vars);
	mlx_hook(vars.win, X_EVENT_KEY_EXIT, 0, &key_destroy, &vars);
	mlx_loop(vars.mlx);
	return (0);
}```


# Questions - ongoing
### hit_### 여기서 판별식이 어떻게 나오는가?
### hit_cylinder 에서 왜 세 개의 값이 들어가는가?
```c
t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	int			result;

	cy = (t_cylinder *)cy_obj->element;
	result = 0;
	result += hit_cylinder_cap(cy_obj, ray, rec, cy->height / 2);
	result += hit_cylinder_cap(cy_obj, ray, rec, -(cy->height / 2));
	result += hit_cylinder_side(cy_obj, ray, rec);
	if (result > 0)
		return (TRUE);
	else
		return (FALSE);
}```
### Ray Traicing이란 무엇인가
### 색은 어떻게 결정되는가
### [[Phong lighting Model]]
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
	// -- after color is rendered, render phong lighting and shadow
	// color the pixel by result and save
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	// put saved image into mlx canvas
	mlx_key_hook(vars.win, key_press, &vars);
	// keyboard input setting for camera 
	mlx_hook(vars.win, X_EVENT_KEY_EXIT, 0, &key_destroy, &vars);
	// keyboard input setting for exit
	mlx_loop(vars.mlx);
	// run
	return (0);
}```

픽셀에서 색을 결정하는 로직
```c
t_color	ray_color(t_scene *scene)
{
	double	t;

	scene->rec = record_init();
	if (hit(scene->world, &scene->ray, &scene->rec) == TRUE)
		return (phong_lighting(scene));
	t = 0.5 * (scene->ray.dir.y + 1.0); //why ray direction?
	// t = 1;
	// return (vadd(vmuln(vec(1, 1, 1), 1.0 - t), vmuln(vec(0.5, 0.7, 1.0), t)));
	return (vadd(vmuln(vec(1, 1, 1), 1.0 - t), vmuln(vec(0, 0, 0), t)));
}
```

```c
t_bool	hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_anything;
	t_hit_record	temp_rec;

	temp_rec = *rec;
	hit_anything = FALSE;
	while (world)
	{
		if (hit_obj(world, ray, &temp_rec) == TRUE)
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		world = world->next;
	}
	return (hit_anything);
}```



# Questions - ongoing
[[hit_### 여기서 판별식이 어떻게 나오는가?]]
![[Screenshot 2023-07-10 at 1.02.56 PM.png]]
![[Screenshot 2023-07-10 at 1.02.46 PM.png]]
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
### 색은 어떻게 결정되는가 - 값을 더해가면서

### [[Phong lighting Model]]

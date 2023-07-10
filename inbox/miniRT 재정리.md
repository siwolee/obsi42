# 레이 트레이싱이란?
>카메라에 빛이 맺히기까지의 경로를 추적하는 것. 
>Ray 빛 + Tracing 추적
>다만 모든 빛을 다 추적할 수는 없으므로, 카메라에 들어오는 광선을 기준으로 빛의 반사와 굴절, 물체 색을 계산
![[Screenshot 2023-07-10 at 3.40.54 PM.png]]

![[Screenshot 2023-07-10 at 3.34.55 PM.png]]
1. 픽셀마다 이미지 상 광원을 향하고 있는 광선이 있으리라 가정한다.
	따라서 가로 x 세로 크기의 픽셀들을 돌면서 광선을 정의한다.
2. 광선을 추적하여 물체에 부딪히는지를 판별한다. (판별식 사용)
	부딪히지 않았을 경우 다음 과정을 생략하고, 배경색을 불러온다.
3. 부딪힌 지점에 대한 물체의 색을 계산 (원래 컬러, 매핑)
4. 부딪힌 지점에 대한 빛의 반사를 추적해 색을 계산 (light)
5. 부딪힌 지점에 대한 물체의 색을 계산 (shade)

3, 4, 5 과정을 합쳐서 계산한 색을 기반으로 퐁 라이팅을 진행한다, 


따라서 레이트레이싱을 직접적으로 수행하는 과정은 아래
ft_draw 함수에 전부 포함되어 있다.
- 물체와 광선의 부딪힘 판단, 
- phong reflection 쉐이딩, 
- 그림자, 
- 반사와 굴절, 
- 텍스쳐 매핑

### 메인 함수
```c
int	main(int ac, char **)
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
### [[hit_### 여기서 판별식이 어떻게 나오는가?]]
### [[hit_cylinder 에서 왜 세 개의 값이 들어가는가?]]
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
### SET_FACE_NORMAL

### [[Phong lighting Model]]


# 기본 용어
**법선**
곡선에서 교차점이 하나만 생기면서, 해당 교차점에 수직하는 선
![[Screenshot 2023-07-10 at 3.25.37 PM.png]]
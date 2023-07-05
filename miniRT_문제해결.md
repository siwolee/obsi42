
# 라이브러리 image not found
```sh
dyld: Library not loaded: libmlx.dylib
  Referenced from: /Users/siwolee/minirt/./a.out
  Reason: image not found
```

![[Screen Shot 2023-04-08 at 4.01.03 PM.png]]
참고한 페이짚 :
https://stackoverflow.com/questions/17703510/dyld-library-not-loaded-reason-image-not-found


### 해결방법 1 : otool을 통해 라이브러리 경로 확인 후 수동으로 경로를 바꿔주기
http://rette.iruis.net/2019/11/%EB%A7%A5%EC%97%90%EC%84%9C-%EB%8F%99%EC%A0%81-%EB%9D%BC%EC%9D%B4%EB%B8%8C%EB%9F%AC%EB%A6%AC-%EC%B0%B8%EC%A1%B0%EB%AC%B8%EC%A0%9C-reason-image-not-found/


실패

### 해결방법 2 : brew install node 
클러맥에서 안됨
실패

### 해결방법 3 : 베타 버전을 사용하고, 실행 루트에 라이브러리 파일 복사해두기
성공i



# LEAKS
```c
t_color	point_light_get(t_scene *scene, t_light *light)
{
	t_light_temp	*temp;
	t_color			color;

	temp = malloc(sizeof(t_light_temp));
	light_sub(temp, light, scene);
	if (in_shadow(scene->world, temp->light_ray, temp->light_len))
	{
		free(temp);
		return (vec(0, 0, 0));
	}
	color = vmuln(vadd(vadd(scene->ambient, temp->diffuse), \
	temp->specular), temp->brightness);
	free(temp);
	return (color);
}


double	ft_atod(const char *str)
{
	int		i;
	double	pos;
	double	neg;
	char	*temp;

	i = 0;
	neg = 0;
	while (str[i] != '.' && str[i])
		i++;
	temp = ft_strndup(str, i);
	pos = db_atoi(temp);
	free(temp);
	if (str[i] == '.')
	{
		temp = ft_strndup(&str[i + 1], ft_strlen(str));
		neg = db_under_atoi(temp);
		free(temp);
	}
	if (pos < 0)
		return ((pos + (neg * -1)));
	return (pos + neg);

int	hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	static t_cylinder	*cy;
	static t_cy_temp	temp;
	double				hit_height;

	cy = cy_obj->element;
	cy_temp_struct(&temp, cy, ray);
	if (temp.discriminant < 0)
		return (0);
	if (temp.root < rec->tmin || rec->tmax < temp.root)
	{
	temp.root = (-temp.half_b + temp.sqrtd) / temp.a;
		if (temp.root < rec->tmin || rec->tmax < temp.root)
			return (0);
	}
	hit_height = cy_boundary(cy, ray_at(ray, temp.root));
	if (!hit_height)
		return (0);
	rec->t = temp.root;
	rec->p = ray_at(ray, temp.root);
	rec->normal = get_cylinder_normal(cy, rec->p, hit_height);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (1);
}}```
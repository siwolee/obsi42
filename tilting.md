```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_tilt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:09:50 by siwolee           #+#    #+#             */
/*   Updated: 2023/07/10 21:51:34 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/miniRT.h"

// https://m.blog.naver.com/kimjw1218/70178629876
// tilt_cam functions 

//roll_rotate
// t_vec xaxis_rotate(t_vec point)

//pitch_rotate
// tilt updown
// [	1			0			0			0	]
// [	0		cos pitch	-sin pitch		0	]
// [	0		sin pitch	cos pitch		0	]
// [	0			0			0			1	]
//assume point is [x, y, z, 1]
t_vec	_xaxis_rotate(t_vec point, double sin, double cos)
{
	t_vec	temp;

	temp.x = point.x;
	temp.y = point.y * cos - point.y * sin;
	temp.z = point.z * sin + point.z * cos;
	return (temp);
}

void	xaxis_rotate(t_camera *cam, double sin, double cos)
{
	t_vec	temp;
	t_vec	point;

	point = vsub(cam->orig, cam->dir);
	temp.x = point.x;
	temp.y = point.y * cos - point.y * sin;
	temp.z = point
	  

// void* __debug_tmp__;.z * sin + point.z * cos;
	cam->dir = vadd(cam->orig, temp);
}

//yaw_rotate
// [	cos yaw		0		sin yaw			0	]
// [	0			1			0			0	]
// [	-sin yaw	0		cos yaw			0	]
// [	0			0			0			1	]
//tilt right/left
t_vec _yaxis_rotate(t_vec point, double sin, double cos)
{
	t_vec	temp;

	temp.x = point.x * cos + point.x * sin;
	temp.y = point.y;
	temp.z = - point.z * sin + point.x * cos;
	return (temp);
}

void	yaxis_rotate(t_camera *cam, int angle)
{
	t_vec new_dir;
	double cos_;
	double sin_;
	t_vec	temp;

	cos_ = cos(angle);
	sin_ = sin(angle);
	temp.x = 1 * cos_ + 1 * sin_;
	temp.y = 0;
	temp.z = -1 * sin_ + 1 * cos_;
}
```

  

// void* __debug_tmp__;
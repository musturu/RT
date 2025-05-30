/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:42:06 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/23 18:43:19 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec	calculate_axis(t_data *data, int x, int y);

t_vec	rotate(t_vec v, t_vec axis, float angle)
{
	float	cos_angle;
	float	sin_angle;
	t_vec	result;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	result = vecsum(scalar(v, cos_angle), scalar(cross(axis, v), sin_angle));
	result = vecsum(result, scalar(axis, dot(axis, v) * (1.0f - cos_angle)));
	return (normalize(result));
}

void	rotate_obj(t_data *data, int x, int y)
{
	t_vec		axis;
	float		angle;
	t_obj		*obj;
	t_cylinder	*to_rotate;

	obj = &data->scene.objs[data->obj_onhand];
	if (obj->type == SPHERE)
		return ;
	to_rotate = obj->self;
	angle = sqrt(x * x + y * y) * data->scene.cam.half_height * (SCALE * 0.1f);
	axis = calculate_axis(data, x, y);
	to_rotate->axis = rotate(to_rotate->axis, axis, angle);
}

void	rotate_camera(t_data *data, int x, int y)
{
	float	dx;
	float	dy;
	t_cam	*camera;

	dx = x * 0.001f;
	dy = y * 0.001f;
	camera = &data->scene.cam;
	camera->forward = rotate(camera->forward, camera->right, -dy);
	camera->up = rotate(camera->up, camera->right, -dy);
	camera->forward = rotate(camera->forward, camera->up, -dx);
	set_camera_axis(&data->scene);
}

static t_vec	calculate_axis(t_data *data, int x, int y)
{
	t_vec	rotation_vec;
	t_cam	*camera;
	t_vec	axis;

	camera = &data->scene.cam;
	rotation_vec = vecsum(scalar(camera->right, -x), scalar(camera->up, y));
	axis = cross(camera->forward, rotation_vec);
	axis = normalize(axis);
	return (axis);
}

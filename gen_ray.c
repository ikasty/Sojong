﻿#include <stdio.h>
#include <string.h>
#include "gen_ray.h"

#include "settings.h"
#include "include/type.h"

Ray gen_ray(float current_x, float current_y)
{
	Ray make_ray;
	int dir;
	float index[3];

	USE_CAMERA(cam);

	index[0] = current_x + cam->orig[0] - X_SCREEN_SIZE / 2;
	index[1] = current_y + cam->orig[1] - Y_SCREEN_SIZE / 2;
	index[2] = cam->distance;

	for(dir = 0; dir < 3; dir++)
	{
		make_ray.orig[dir] = cam->orig[dir];
		make_ray.dir[dir] = index[dir] - make_ray.orig[dir];
	}

	make_ray.max_t = MAX_RENDER_DISTANCE;

	return make_ray;
}

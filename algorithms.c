﻿
/*
Copyright (c) 2015, Minwoo Lee(hellomw@msl.yonsei.ac.kr)
					Daeyoun Kang(mail.ikasty@gmail.com),
                    HyungKwan Park(rpdladps@gmail.com),
                    Ingyu Kim(goracom0@gmail.com),
                    Jungmin Kim(kukakhan@gmail.com)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
*/

#include <stdio.h>
#include <string.h>
#include "algorithms.h"

////////////////////////////////////////
// search algorithms
// 1. NAIVE
// * naive algorithm
#  include "naive/naive_intersection.h"

// 2. KDTREE
// * kdtree_clear_accel, kdtree_intersect_search
#  include "kdtree/kdtree_intersect_clear.h"
// * nlog^2n algorithm
#  include "kdtree/nlog2n_build.h"
// * nlogn algorithm
#  include "kdtree/nlogn_build.h"
// * binning algorithm
#  include "kdtree/binning_build.h"
// * nlogn exclusion algorithm
#  include "kdtree/exclusion_build.h"

/////////////////////////////////////
// shading algorithms
// 1. naive
#  include "shading/naive_shading.h"
// 2. phong shading
#  include "shading/phong_shading.h"

// default values
void (*clear_accel)(Data *data) = NULL;
void (*accel_build)(Data *data) = NULL;
Hit (*intersect_search)(Data *data, Ray *ray) = NULL;

void init_search_algo(char *algo_name)
{
	// 이미 알고리즘이 선택된 경우 무시
	if (intersect_search) return ;

	if (strncmp(algo_name, "naive", 5) == 0)
	{
		printf("use naive algorithm\n");
		clear_accel = NULL;
		accel_build = NULL;
		intersect_search = &naive_intersect_search;
	}
	else if (strncmp(algo_name, "nlog2n", 6) == 0)
	{
		printf("use kdtree nlog^2n algorithm\n");
		clear_accel = &kdtree_clear_accel;
		accel_build = &nlog2n_accel_build;
		intersect_search = &kdtree_intersect_search;
	}
	else if (strncmp(algo_name, "nlogn", 5) == 0)
	{
		printf("use kdtree nlogn algorithm\n");
		clear_accel = &kdtree_clear_accel;
		accel_build = &nlogn_accel_build;
		intersect_search = &kdtree_intersect_search;
	}
	else if (strncmp(algo_name, "binning", 7) == 0)
	{
		printf("use kdtree binning algorighm\n");
		clear_accel = &kdtree_clear_accel;
		accel_build = &binning_accel_build;
		intersect_search = &kdtree_intersect_search;
	}
	else if (strncmp(algo_name, "exclusion", 9) == 0)
	{
		printf("use kdtree nlogn exclusion algorithm\n");
		clear_accel = &kdtree_clear_accel;
		accel_build = &exclusion_accel_build;
		intersect_search = &kdtree_intersect_search;
	}
	else
	{
		printf("use default(kdtree nlogn) algorithm\n");
		clear_accel = &kdtree_clear_accel;
		accel_build = &nlogn_accel_build;
		intersect_search = &kdtree_intersect_search;
	}

	return ;
}

void (*normal_shade)(float normal_vector[3], float hit_point[3], Primitive s_tri) = NULL;

void init_shading_algo(char *shading_name)
{
	if (strncmp(shading_name, "naive", 5) == 0)
	{
		printf("use naive shading\n");
		normal_shade = &naive_shading;
	}
	else if (strncmp(shading_name, "phong", 5) == 0)
	{
		printf("use phong shading\n");
		normal_shade = &phong_shading;
	}
	else
	{
		printf("use default(phong) shading\n");
		normal_shade = &phong_shading;
	}	
	return ;
}
/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.

working devel version
*/
#include "framework/ga_camera.h"
#include "framework/ga_compiler_defines.h"
#include "framework/ga_input.h"
#include "framework/ga_sim.h"
#include "framework/ga_output.h"
#include "jobs/ga_job.h"
#include "entity/ga_entity.h"
#include "graphics/ga_cube_component.h"
#include "graphics/ga_model_component.h"
#include "graphics/ga_program.h"

#include "gui/ga_font.h"
#include "gui/ga_button.h"
#include "gui/ga_checkbox.h"
#include "gui/ga_label.h"

/* assimp include files. These three are usually needed. */

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#include <iostream>

#if defined(GA_MINGW)
#include <unistd.h>
#endif

ga_font* g_font = nullptr;

static void gui_test(ga_frame_params* params);

char g_root_path[256];
static void set_root_path(const char* exepath);

ga_entity cube;
ga_entity model;
ga_entity model2;

int main(int argc, const char** argv)
{
	set_root_path(argv[0]);

	ga_job::startup(0xffff, 256, 256);

	// Create objects for three phases of the frame: input, sim and output.
	ga_input* input = new ga_input();
	ga_sim* sim = new ga_sim();
	ga_output* output = new ga_output(input->get_window());

	// Create camera.
	ga_entity camera_ent;
	ga_camera* camera = new ga_camera(&camera_ent);

	camera_ent.translate({ 0.0f, 3.0f, 10.0f });
	camera_ent.rotate({ -15.0f, 180.0f, 0 });
	sim->add_entity(&camera_ent);

	// create a spinning cube
	ga_cube_component cube_mesh(&cube, "data/textures/magic.png");
	sim->add_entity(&cube);

	// load a model from an OBJ  file
	ga_model_component model_mesh(&model, "data/models/sphere.obj");
	model.set_active(true);
	sim->add_entity(&model);

	// load a model from a COLLADA file 
	ga_model_component model_mesh2(&model2, "data/models/fox.dae");
	model2.set_active(false);
	sim->add_entity(&model2);

	// Create the default font:
	g_font = new ga_font("VeraMono.ttf", 24.0f, 512, 512);

	// Main loop:
	while (true)
	{
		ga_frame_params params;

		params._render_settings = &output->_render_settings;

		if (!input->update(&params))
		{
			break;
		}

		// Run gameplay.
		sim->update(&params);

		// Perform the late update.
		sim->late_update(&params);

		// Run gui test.
		gui_test(&params);

		// Draw to screen.
		output->update(&params);
	}

	delete output;
	delete sim;
	delete input;
	delete camera;

	ga_job::shutdown();
	return 0;
}


static void gui_test(ga_frame_params* params)
{
	ga_label("Model Viewer", 20, 100, params);

	if (ga_checkbox(params->_render_settings->_lighting_enabled, "Enable Lighting", 20.0f, 150.0f, params).get_clicked(params))
	{
		// TODO: Homework 4
		// toggle lighting 
	}
	
	if (ga_button("Show Cube", 20.0f, 200.0f, params).get_clicked(params))
	{
		// TODO: Homework 4
		// show the cube 
	}
	if (ga_button("Show Model 1", 20.0f, 250.0f, params).get_clicked(params))
	{
		// TODO: Homework 4
		// show the first model
	}
	if (ga_button("Show Model 2", 20.0f, 300.0f, params).get_clicked(params))
	{
		// TODO: Homework 4
		// show the second model
	}
	
}


static void set_root_path(const char* exepath)
{
#if defined(GA_MSVC)
	strcpy_s(g_root_path, sizeof(g_root_path), exepath);

	// Strip the executable file name off the end of the path:
	char* slash = strrchr(g_root_path, '\\');
	if (!slash)
	{
		slash = strrchr(g_root_path, '/');
	}
	if (slash)
	{
		slash[1] = '\0';
	}
#elif defined(GA_MINGW)
	char* cwd;
	char buf[PATH_MAX + 1];
	cwd = getcwd(buf, PATH_MAX + 1);
	strcpy_s(g_root_path, sizeof(g_root_path), cwd);

	g_root_path[strlen(cwd)] = '/';
	g_root_path[strlen(cwd) + 1] = '\0';
#endif
}

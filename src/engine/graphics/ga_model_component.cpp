/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_model_component.h"
#include "ga_material.h"

#include "entity/ga_entity.h"

/* assimp include files. These three are usually needed. */

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/postprocess.h>     // Post processing flags

#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <cassert>

ga_model_component::ga_model_component(ga_entity* ent, const char* model_file) : ga_component(ent)
{
	extern char g_root_path[256];
	Assimp::Importer importer;
	std::string model_path = g_root_path;
	model_path += model_file;

	_scene = importer.ReadFile(model_path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!_scene)
	{
		std::cout << "error: couldn't load obj\n";
	}
	else
	{
		// process the scene
		process_node_recursive(_scene->mRootNode, _scene);
	}
}

ga_model_component::~ga_model_component()
{
	
}

void ga_model_component::process_node_recursive(aiNode* node, const aiScene* scene)
{
	// process my meshes
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		ga_mesh* mesh = new ga_mesh();
		mesh->create_from_aiMesh(_scene->mMeshes[node->mMeshes[i]], _scene);
		_meshes.push_back(mesh);
	}
	// process my children
	for (int i = 0; i < node->mNumChildren; i++)
	{
		process_node_recursive(node->mChildren[i], scene);
	}
}

void ga_model_component::update(ga_frame_params* params)
{
	const float dt = std::chrono::duration_cast<std::chrono::duration<float>>(params->_delta_time).count();
	get_entity()->rotate({ 0,60.0f*dt,0 });

	for (ga_mesh* m : _meshes)
	{
		ga_static_drawcall draw;
		draw._name = "model";
		m->assemble_drawcall(draw);
		draw._transform = get_entity()->get_transform();

		while (params->_static_drawcall_lock.test_and_set(std::memory_order_acquire)) {}
		params->_static_drawcalls.push_back(draw);
		params->_static_drawcall_lock.clear(std::memory_order_release);
	}
}

ga_mesh::ga_mesh()
{
	_index_count = 0;
	_material = nullptr;
	_vao = 0;
}
ga_mesh::~ga_mesh()
{
	glDeleteBuffers(4, _vbo);
	glDeleteVertexArrays(1, &_vao);

}

void ga_mesh::create_from_aiMesh(aiMesh* mesh, const aiScene* scene)
{
	GLenum err;
	
	// request vertex array object and vertex buffer objects
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glGenBuffers(4, _vbo);

	// TODO: Homework 4
	// load vertex positions, indices, uv's and normals from importer mesh into our data structure

	ga_lit_material* mat = new ga_lit_material();
	mat->init();

	// TODO: Homework 4
	// set the diffuse color for the material 

	_material = mat;

	// TODO: Homework 4 
	// set up vertex and element array buffers for positions, indices, uv's and normals

	// unbind vertex array
	glBindVertexArray(0);

	err = glGetError();
	assert(err == GL_NO_ERROR);
	
}

void ga_mesh::assemble_drawcall(ga_static_drawcall& draw)
{
	draw._vao = _vao;
	draw._index_count = _index_count;
	draw._draw_mode = GL_TRIANGLES;
	draw._material = _material;
}




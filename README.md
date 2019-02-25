# ga2018-homework3
Third homework for RPI Game Architecture.

In this assignment you will draw a simple textured cube. The raw data
for the vertex positions in model space, the texture coordinates, and 
the indices are provided. You must implement all the steps required 
to get that raw data from your program through the graphics pipeline 
and on to the screen. This will involve:

	1. Create the vertex data and its specification for use by shader 
	programs (See: ga_cube_component::create_vertex_array and ga_cube_component::destroy_vertex_array)
	2. Write the vertex and fragment shaders (See: data\shaders\ga_unlit_texture_frag.glsl 
	and data\shaders\ga_unlit_texture_vert.glsl)
	3. Set any uniform variables needed by your shaders (See: the two 
	overloads for ga_uniform::set in src\engine\graphics\ga_program.cpp)
	4. Submit the vertex data for rendering (See: ga_output::draw in
	src\engine\framework\ga_output.cpp).

You can also search for "// TODO: Homework 3" to find locations that
are expected to be modified.

When you're done you should have something that looks like the image
in golden.png located in the root directory of the repository.

Note: By default ga_unlit_texture_material attempts to set the 
model-view-projection matrix to a uniform variable called u_mvp and 
the texture to another uniform called u_texture (See: ga_unlit_texture_material::bind 
in src\engine\graphics\ga_material.cpp). You're free to change this,
though it shouldn't be necessary.

For an extra 10-20% extra credit you can do something "interesting" in
your shaders. A very simple example worth 10% would be to animate the
color or texture coordinates using trig functions. You may also need
to add some other uniforms to help drive that animation. Your idea must 
be  well documented in comments to receive credit.
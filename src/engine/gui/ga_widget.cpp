/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
*/

#include "ga_widget.h"

#include "framework/ga_drawcall.h"
#include "framework/ga_frame_params.h"

const ga_vec3f ga_widget::k_button_color = { 0.5f, 0.5f, 1.0f };
const ga_vec3f ga_widget::k_button_hover_color = { 0.75f, 0.75f, 1.0f };
const ga_vec3f ga_widget::k_button_press_color = { 0.25f, 0.25f, 1.0f };
const ga_vec3f ga_widget::k_text_color = { 1.0f, 1.0f, 1.0f };
const float ga_widget::k_button_offset = 4.0f;
const float ga_widget::k_checkbox_offset = 30.0f;

void ga_widget::draw_outline(ga_frame_params* params, const ga_vec2f& min, const ga_vec2f& max, const ga_vec3f& color, float offset)
{
	// TODO: Homework 4
	// Check the README
}

void ga_widget::draw_check(ga_frame_params* params, const ga_vec2f& min, const ga_vec2f& max, const ga_vec3f& color)
{
	// TODO: Homework 4
	// It's like a box, with a smaller number of indices in a different order
}

void ga_widget::draw_fill(ga_frame_params* params, const ga_vec2f& min, const ga_vec2f& max, const ga_vec3f& color)
{
	// TODO: Homework 4
	// Draw with triangles instead of lines
}

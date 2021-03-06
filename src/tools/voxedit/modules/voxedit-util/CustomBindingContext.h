/**
 * @file
 */

#pragma once

#include "core/BindingContext.h"

namespace voxedit {

enum BindingContext {
	UI = core::BindingContext::UserInterface,
	Model = core::BindingContext::World,
	Scene = core::BindingContext::FirstCustom + 0,
	Editing = Model | Scene
};

}

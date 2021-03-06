/**
 * @file
 */

#include "LUAFilter.h"
#include "backend/entity/ai/LUAFunctions.h"

namespace backend {

void LUAFilter::filterLUA(const AIPtr& entity) {
	// get userdata of the filter
	const core::String name = "__meta_filter_" + _name;
	lua_getfield(_s, LUA_REGISTRYINDEX, name.c_str());
#if AI_LUA_SANTITY > 0
	if (lua_isnil(_s, -1)) {
		Log::error("LUA filter: could not find lua userdata for %s", _name.c_str());
		return;
	}
#endif
	// get metatable
	lua_getmetatable(_s, -1);
#if AI_LUA_SANTITY > 0
	if (!lua_istable(_s, -1)) {
		Log::error("LUA filter: userdata for %s doesn't have a metatable assigned", _name.c_str());
		return;
	}
#endif
	// get filter() method
	lua_getfield(_s, -1, "filter");
	if (!lua_isfunction(_s, -1)) {
		Log::error("LUA filter: metatable for %s doesn't have the filter() function assigned", _name.c_str());
		return;
	}

	// push self onto the stack
	lua_getfield(_s, LUA_REGISTRYINDEX, name.c_str());

	// first parameter is ai
	if (luaAI_pushai(_s, entity) == 0) {
		return;
	}
#if AI_LUA_SANTITY > 0
	if (!lua_isfunction(_s, -3)) {
		Log::error("LUA filter: expected to find a function on stack -3");
		return;
	}
	if (!lua_isuserdata(_s, -2)) {
		Log::error("LUA filter: expected to find the userdata on -2");
		return;
	}
	if (!lua_isuserdata(_s, -1)) {
		Log::error("LUA filter: second parameter should be the ai");
		return;
	}
#endif
	const int error = lua_pcall(_s, 2, 0, 0);
	if (error) {
		Log::error("LUA filter script: %s", lua_isstring(_s, -1) ? lua_tostring(_s, -1) : "Unknown Error");
	}

	// reset stack
	lua_pop(_s, lua_gettop(_s));
}

}

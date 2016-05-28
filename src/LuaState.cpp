#include "LuaState.h"
#include <assert.h>
#include <stdio.h>

#include "DinodeckLua.h"
#include "DDFile.h"


LuaState* LuaState::GetWrapper(lua_State* luaState)
{
	// Needs sanity checks.
	lua_pushliteral(luaState, "this");  /* push address */
    lua_gettable(luaState, LUA_REGISTRYINDEX);  /* retrieve value */
    LuaState* wrapper = static_cast<LuaState*>(lua_touserdata(luaState, -1));
    lua_pop(luaState, 1); // pop the user data off the top of the stack
    return wrapper;
}

int LuaState::LuaError(lua_State* luaState)
{
	LuaState* wrapper = LuaState::GetWrapper(luaState);
	assert(wrapper);
	wrapper->OnError();
	return 0;
}

LuaState::LuaState(const char* name)
    : mLuaState(NULL)
{
	mName = name;
	// lua_newstate( MemHandler, NULL ); <- can use this to get some mem stats
    mLuaState = lua_open();
    assert(mLuaState);
	luaL_openlibs(mLuaState);
	// Push game instance pointer in the lua state
	// So for static functions (used by Lua) we can find out the game associated with a lua state
	lua_pushliteral(mLuaState, "this");  /* push value */
    lua_pushlightuserdata(mLuaState, (void *)this);  /* push address */

    /* registry["this"] = this */
    lua_settable(mLuaState, LUA_REGISTRYINDEX);
}

LuaState::~LuaState()
{
    if(mLuaState)
    {
	   lua_close(mLuaState);
    }
}

void LuaState::OnError()
{
 	// Prints out the error and a stack trace
    printf("\n[LUASTATE|%s] Error: %s\n", mName, lua_tostring(mLuaState, -1));

    // Push the debug library on the stack
    lua_getfield(mLuaState, LUA_GLOBALSINDEX, "debug");
    if(!lua_istable(mLuaState, -1))
    {
        printf("[LUASTATE|%s] Debug library not loaded. Couldn't get stack trace\n", mName);
        lua_pop(mLuaState, 1); // pop the non-table
        return;
    }

    // Debug library is on the stack

    // A traceback is the most basic thing we can do but we can also
    // Get variable information and all that good stuff - it's just
    // a question of how to present it.

    // Push the traceback on to the stack as a field
    lua_getfield(mLuaState, -1, "traceback");

    if(!lua_isfunction(mLuaState, -1))
    {
        // If the traceback field doesn't exist
        printf("[LUASTATE|%s] Tried to get trackback but function doesnt exist.\n", mName);
        printf("[LUASTATE|%s] Have you overidden the default debug table?\n", mName);
        lua_pop(mLuaState, 2); // pop table and field
        return;
    }

    // Call function on the top of the stack, with no arguements, expecting one return.
    lua_call(mLuaState, 0, 1);
    printf("[LUASTATE|%s] %s\n", mName, lua_tostring(mLuaState, -1));

    return;
}

lua_State* LuaState::State() const
{
	return mLuaState;
}

unsigned int LuaState::ItemsInStack()
{
	return lua_gettop(mLuaState);
}

bool LuaState::DoString(const char* str)
{
	// Does this leave the stack messy in case or error (probaby doesn't matter!)
	lua_pushcfunction(mLuaState, LuaState::LuaError);
	int fail = luaL_loadstring(mLuaState, str);

	if(fail)
	{
		printf("\n[LUASTATE|%s] Error: %s\n", mName, lua_tostring(mLuaState, -1));
		return false;
	}
	else
	{
		// Execute the string on the stack
		// If anything goes wrong call the function under that
		bool result = lua_pcall(mLuaState, 0, LUA_MULTRET, -2) == 0;
		lua_pop(mLuaState, 1); // remove error function
		return result;
	}
}

bool LuaState::DoBuffer(const char* name, const char* buffer, unsigned int size)
{
    assert(buffer);
    lua_pushcfunction(mLuaState, LuaState::LuaError);
    int fail = luaL_loadbuffer
    (
        mLuaState,
        buffer,
        size,
        name
    );

    if(fail)
    {
        printf("\n[LUASTATE|%s] Error: %s\n", mName, lua_tostring(mLuaState, -1));
        return false;
    }
    else
    {
        // Execute the string on the stack
        // If anything goes wrong call the function under that
        bool result = lua_pcall(mLuaState, 0, LUA_MULTRET, -2) == 0;
        lua_pop(mLuaState, 1); // remove error function
        return result;
    }
}

bool LuaState::DoFile(const char* path)
{
    DDFile file(path);
    file.LoadFileIntoBuffer();
    return DoBuffer(path, file.Buffer(), file.Size());
}

std::string LuaState::GetString(const char* key, const char* defaultStr)
{
	lua_getfield(mLuaState, LUA_GLOBALSINDEX, key);
	const char* out = luaL_optlstring(mLuaState, -1, defaultStr, NULL);
	lua_pop(mLuaState, 1); // Remove key,
	return out;
}

int LuaState::GetInt(const char* key, int defaultInt)
{
	lua_getfield(mLuaState, LUA_GLOBALSINDEX, key);
	int out = luaL_optint (mLuaState, -1, defaultInt);
	lua_pop(mLuaState, 1); // Remove key,
	return out;
}

float LuaState::GetFloat(const char* key, float defaultFloat)
{
    lua_getfield(mLuaState, LUA_GLOBALSINDEX, key);
    int out = luaL_optnumber(mLuaState, -1, defaultFloat);
    lua_pop(mLuaState, 1); // Remove key,
    return out;
}
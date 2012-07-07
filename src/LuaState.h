#ifndef LUASTATE_H
#define LUASTATE_H
#include <string>

struct lua_State;

class LuaState
{
private:
	const char* mName;
	lua_State* mLuaState;
	// Get lua_State's wrapper instance of class LuaState
	static LuaState* GetWrapper(lua_State* luaState);
	// Lua static C style callback to be routed to LuaState's instance OnError function
	static int LuaError(lua_State* luaState);

	void OnError();
public:
	LuaState(const char* name);
	~LuaState();
	lua_State* State() const;
	unsigned int ItemsInStack();

	// Execute lua string, on error will print error and stacktrace if possible.
	bool DoString(const char* str);
	bool DoFile(const char* filepath);

	// Not sure about this approach.
	std::string GetString(const char* key, const char* defaultStr);
	int GetInt(const char* key, int defaultInt);
};

#endif

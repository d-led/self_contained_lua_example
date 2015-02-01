include 'premake'

lua = assert(dofile 'premake/recipes/lua.lua')

make_solution 'self_contained_lua_example'

lua:set_includedirs()
lua:set_libdirs()

includedirs { 
    './deps/LuaBridge-1.0.2',
    './deps/LuaState/include',
    './deps/bundle'
}

make_static_lib('bundle',{
    './deps/bundle/bundle.cpp',
    './deps/bundle/bundle.hpp'
})

make_cpp11()

make_console_app('self_contained_lua_example', { '*.h', '*.cpp', '*.lua', '*.json' })

run_target_after_build()

links { 'bundle' }

lua:set_links()

make_cpp11()

function exec(command)
    local handle = io.popen(command)
    local result = handle:read("*a")
    handle:close()
    print(result)
    return result
end

function get_uname()
    local uname = exec 'uname'
    uname = uname or 'windows'
    uname = uname:lower():gsub("^%s*(.-)%s*$", "%1") --trimmed--
    return uname
end

newaction {
   trigger     = "res",
   description = "compile the resources",
   execute     = function ()
        local ok = false
        local uname = get_uname()
        if uname == 'windows' or uname:find'mingw' then
            exec[[ris\ris resources.json]]
        elseif uname == 'macosx' or uname == 'darwin' then
            exec[[ris/ris.osx resources.json]]
        elseif uname == 'linux' then
            exec[[ris/ris resources.json]]
        end
   end
}

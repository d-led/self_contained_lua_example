_G.package.path=_G.package.path..[[;./?.lua;./?/?.lua]]

assert( require 'premake.quickstart' )

make_solution 'self_contained_lua_example'

includedirs { 
    './LuaBridge-1.0.2',
    './LuaState/include',
    './bundle'
}

local OS = os.get()
local settings = {
    includedirs = {
        linux = {'/usr/include/lua5.1'},
        windows = { [[C:\\luarocks\\2.1\\include]] },
        macosx = { '/usr/local/include'}
    },
    libdirs = {
        linux = {},
        windows = { [[C:\\luarocks\\2.1]] },
        macosx = { '/usr/local/lib'}	
    },
    links = {
        linux = { 'lua5.1' },
        windows = { 'lua5.1' },
        macosx = { 'lua' }
    }
}

includedirs { settings.includedirs[OS] }
libdirs { settings.libdirs[OS] }

make_static_lib('bundle',{
    './bundle/bundle.cpp',
    './bundle/bundle.hpp'
})
make_cpp11()

make_console_app('self_contained_lua_example', { '*.h', '*.cpp', '*.lua', '*.json' })

run_target_after_build()

links{settings.links[OS],'bundle'}

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

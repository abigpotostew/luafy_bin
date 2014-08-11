luafy_bin
=========

openFrameworks + lua app. This is like a Processing clone using Lua and Openframeworks.

* Install my branch of ofxLua: https://github.com/abigpotostew/ofxLua
* Run this app from the command line on mac:
* Usage: "path/to/luafy_bin.app/Contents/MacOS/luafy_bin" [-fw:h:pr:s] lua_script_path
 * -f: Supply this option to enable fullscreen.
 * -w width: Set GL context width. Default 1024.
 * -h height:  Set GL context height. Default 768.
 * -p: Use OpenGL programmable renderer.
 * -r data_path: Set the working directory root to another path. Default is this executable's path.
 * -s "Lua String": Double quoted lua string to prerun before executing the main script.
 * lua_script_path: Path to an ofxLua script for execution.


Use ZeroBrane Studio to write your lua scripts as well as debug and step through the code. Place ./luafy.lua into ~/.zbstudio/packages. Edit the file and set the path to your luafy_bin app. Happy coding!

-- luafy_bin interpreter for ZeroBrane Studio, allowing debugging in zbstudio.

-- Mac installation: 
--  - place this file in ~/.zbstudio/packages

-- Tested only on a mac.

-------------------------------------------------------------------------------
local interpreter_name = "Luafy"
local version = 0.1
local luafy_path = '"/Applications/of_v0.8.0_osx_release/apps/myApps/luafy_bin/bin/luafy_binDebug.app/Contents/MacOS/luafy_binDebug"'
local exe

local interpreter = {
  name = interpreter_name,
  description = "Luafy interpreter by Stewart Bracken.",
  api = {"baselib"},
  frun = function(self,wfilename,rundebug)

    exe = ide.config.path.luafy or luafy_path

    if rundebug then
      DebuggerAttachDefault({
          runstart = ide.config.debugger.runonstart == true
      })

      -- update arg to point to the proper file
      rundebug = ('if arg then arg[0] = [[%s]] end '):format(filepath)..rundebug

      local tmpfile = wx.wxFileName()
      tmpfile:AssignTempFileName(".")
      filepath = tmpfile:GetFullPath()
      local f = io.open(filepath, "w")
      if not f then
        DisplayOutput("Can't open temporary file '"..filepath.."' for writing\n")
        return
      end
      f:write(rundebug)
      f:close()
    end

    -- luafy_bin Usage: luafy_bin [-fw:h:pr:s] lua_script_path
    -- pass in
    local filepath = wfilename:GetFullPath()
    local params = ide.config.arg.any or ide.config.arg.lua
    local code = ([["%s"]]):format(filepath)
    local cmd = exe..' '.. (params and (params.." ") or "") .. code

    -- CommandLineRun(cmd,wdir,tooutput,nohide,stringcallback,uid,endcallback)
    CommandLineRun(cmd, self:fworkdir(wfilename), true, false)
  end,
  fprojdir = function(self,wfilename)
    return wfilename:GetPath(wx.wxPATH_GET_VOLUME)
  end,
  fworkdir = function (self,wfilename)
    return ide.config.path.projectdir or wfilename:GetPath(wx.wxPATH_GET_VOLUME)
  end,
  hasdebugger = true,
  fattachdebug = function(self) DebuggerAttachDefault() end,
}

return {
  name = interpreter_name,
  description =interpreter_name.." "..version,
  author = "Stewart Bracken",
  version = version,

  onRegister = function(self)
    ide:AddInterpreter(interpreter_name, interpreter)
  end,

  onUnRegister = function(self)
    ide:RemoveInterpreter(interpreter_name)
  end,

  hasdebugger = interpreter.hasdebugger,
  fattachdebug = function(self) DebuggerAttachDefault() end,
  scratchextloop = false,
  unhideanywindow = true,
  takeparameters = true,
}

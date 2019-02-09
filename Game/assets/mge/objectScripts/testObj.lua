local scripts = {"mge/gamescripts/testscript.lua"}
local meta = {["name"] = "ObjectName", ["objPath"] = "mge/models/sphere2.obj", ["materialKey"] = "Test Material", ["posX"] = 0, ["posY"] = 1, ["posZ"] = 0 }

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


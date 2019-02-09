local scripts = {"mge/gamescripts/enemy.lua"}
local meta = {["name"] = "Enemy", ["objPath"] = "mge/models/cone_smooth.obj", ["materialKey"] = "Enemy Material", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


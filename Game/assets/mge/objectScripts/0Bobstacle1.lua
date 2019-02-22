local scripts = {}
local meta = {["name"] = "0Bobstacle1", ["objPath"] = "mge/models/FarmForestBiome/chickenhouse.obj", ["texture"] = "red.png", ["posX"] = 0.5, ["posY"] = 1, ["posZ"] = 0 }
collider = { ["width"] = 2.5, ["height"] = 3, ["depth"] = 3}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


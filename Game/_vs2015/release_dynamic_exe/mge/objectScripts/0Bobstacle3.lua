local scripts = {}
local meta = {["name"] = "0Bobstacle3", ["objPath"] = "mge/models/FarmForestBiome/soil.obj", ["texture"] = "red.png", ["posX"] = -1, ["posY"] = 2, ["posZ"] = 0 }
collider = { ["width"] = 3, ["height"] = 1, ["depth"] = 6}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


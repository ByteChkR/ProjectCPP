local scripts = {}
local meta = {["name"] = "0Bobstacle2", ["objPath"] = "mge/models/FarmForestBiome/scarecrow.obj", ["texture"] = "red.png", ["posX"] = 2, ["posY"] = 1, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


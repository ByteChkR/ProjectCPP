local scripts = {}
local meta = {["name"] = "0Bobstacle4", ["objPath"] = "mge/models/FarmForestBiome/toilet.obj", ["texture"] = "red.png", ["posX"] = -2, ["posY"] = 0, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 3, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


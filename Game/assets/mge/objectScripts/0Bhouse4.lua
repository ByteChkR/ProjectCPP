local scripts = {}
local meta = {["name"] = "0Bhouse4", ["objPath"] = "mge/models/FarmForestBiome/Farm.obj", ["specular"]  = "black.png", ["texture"] = "red.png", ["emissive"] = "black.png", ["posX"] = -5.5, ["posY"] = 0, ["posZ"] = 0 }
collider = { ["width"] = 13, ["height"] = 15, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


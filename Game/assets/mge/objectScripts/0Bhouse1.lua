local scripts = {}
local meta = {["name"] = "0Bhouse1", ["objPath"] = "mge/models/FarmForestBiome/house1.obj", ["specular"]  = "black.png", ["texture"] = "red.png", ["emissive"] = "black.png", ["posX"] = -5.5, ["posY"] = 3, ["posZ"] = 0}
collider = { ["width"] = 14, ["height"] = 5, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


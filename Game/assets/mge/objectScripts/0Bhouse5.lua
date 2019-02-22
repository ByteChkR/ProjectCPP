local scripts = {}
local meta = {["name"] = "0Bhouse5", ["objPath"] = "mge/models/FarmForestBiome/toilet2.obj", ["specular"]  = "black.png", ["texture"] = "red.png", ["emissive"] = "black.png", ["posX"] = -1, ["posY"] = -0.5, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 5, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


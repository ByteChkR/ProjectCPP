local scripts = {}
local meta = {["name"] = "0Bhouse3", ["objPath"] = "mge/models/FarmForestBiome/windmill.obj", ["specular"]  = "black.png", ["texture"] = "red.png", ["emissive"] = "black.png", ["posX"] = -2, ["posY"] = 0, ["posZ"] = 0 }
collider = { ["width"] = 5, ["height"] = 15, ["depth"] = 2}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


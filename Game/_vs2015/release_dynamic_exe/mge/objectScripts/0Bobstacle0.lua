local scripts = {}
local meta = {["name"] = "0Bobstacle0", ["objPath"] = "mge/models/FarmForestBiome/hay.obj" , ["specular"]  = "black.png", ["emissive"] = "black.png", ["texture"] = "red.png", ["posX"] = -0.5, ["posY"] = 1, ["posZ"] = 0 }
collider = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


local scripts = {}
local meta = {["name"] = "2BLowObstacle5", ["objPath"] = "mge/models/CityBiome/railbarrierleft.obj" , 
["texture"] = "red.png", ["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, ["posY"] = -1, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


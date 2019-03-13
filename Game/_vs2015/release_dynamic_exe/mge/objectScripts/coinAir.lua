local scripts = {}
local meta = {["name"] = "coinAir", 
["objPath"] = "mge/models/Corn_pickup_baloon.obj", 
["texture"] = "Game/Shared/Corn/Baloon/Corn_pickup_baloon_Baloon_Corn_BaseColor.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, 
["posY"] = 5, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
colliderMode = "auto"
Shininess = 500
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


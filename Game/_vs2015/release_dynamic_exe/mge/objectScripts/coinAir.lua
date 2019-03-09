local scripts = {}
local meta = {["name"] = "coinAir", 
["objPath"] = "mge/models/Corn_pickup_baloon.obj", 
["specular"] = "Game/Shared/Corn/Baloon/Corn_pickup_baloon_Baloon_Corn_Roughness.png", 
["texture"] = "Game/Shared/Corn/Baloon/Corn_pickup_baloon_Baloon_Corn_BaseColor.png", 
["emissive"] = "Game/Shared/Corn/Baloon/Corn_pickup_baloon_Baloon_Corn_Emissive.png",
["posX"] = 0, 
["posY"] = 5, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


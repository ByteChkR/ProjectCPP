local scripts = {}
local meta = {["name"] = "coin", 
["objPath"] = "mge/models/Corn_pickup.obj", 
["specular"] = "Game/Shared/Corn/Basic/Corn_pickup_CornPickup_Roughness.png", 
["texture"] = "Game/Shared/Corn/Basic/Corn_pickup_CornPickup_BaseColor.png", 
["emissive"] = "Game/Shared/Corn/Basic/Corn_pickup_CornPickup_Emissive.png",
["posX"] = 0, 
["posY"] = 0, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
Shininess = 1024
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


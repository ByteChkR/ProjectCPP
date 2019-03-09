local scripts = {}
local meta = {["name"] = "coinAir", 
["objPath"] = "mge/models/CornPickup.obj", 
["specular"] = "black.png", 
["texture"] = "Game/Shared/Corn/Corn_pickup_CornPickup_BaseColor_retarded.png", 
["posX"] = 0, 
["posY"] = 5, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


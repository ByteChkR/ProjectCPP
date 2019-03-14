local scripts = {}
local meta = {["name"] = "turkeycage", 
["objPath"] = "mge/models/cage.obj", 
["texture"] = "Game/Shared/TurkeyCage/cage_cage_initialShadingGroup_AlbedoTransparency.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, 
["posY"] = -0.8, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


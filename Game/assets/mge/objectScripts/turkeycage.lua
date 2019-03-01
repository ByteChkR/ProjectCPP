local scripts = {}
local meta = {["name"] = "turkeycage", 
["objPath"] = "mge/models/CornPickup.obj", 
["specular"] = "Game/Shared/Corn/CornPickup_initialShadingGroup_MetallicSmoothness.png", 
["texture"] = "Game/Shared/Corn/CornPickup_initialShadingGroup_AlbedoTransparency.png", 
["normal"] = "Game/Shared/Corn/CornPickup_initialShadingGroup_Normal.png",
["posX"] = 0, 
["posY"] = 0, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


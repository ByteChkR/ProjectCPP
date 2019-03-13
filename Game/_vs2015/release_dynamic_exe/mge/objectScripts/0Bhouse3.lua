local scripts = {}
local meta = {["name"] = "0BHouse3", 
["objPath"] = "mge/models/FarmForestBiome/house1.obj", 
["texture"] = "Game/Maps/FarmForestBiome/house1_initialShadingGroup_Diffuse.png", 
["normal"] = "Game/Maps/FarmForestBiome/house1_initialShadingGroup_Normal.png",
["posX"] = 0, 
["posY"] = 3, 
["posZ"] = 0  }
colliderMin = { ["width"] = -8.5, ["height"] = -3, ["depth"] = -2}
colliderMax = { ["width"] = 8.5, ["height"] = 4, ["depth"] = 2}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


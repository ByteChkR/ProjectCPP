local scripts = {}
local meta = {["name"] = "0BLowObstacle1", 
["objPath"] = "mge/models/FarmForestBiome/hay.obj", 
["specular"] = "Game/Maps/FarmForestBiome/hay_initialShadingGroup_Specular.png", 
["texture"] = "Game/Maps/FarmForestBiome/hay_initialShadingGroup_Diffuse.png", 
["emissive"] = "Game/Maps/FarmForestBiome/hay_initialShadingGroup_Emissive.png", 
["normal"] = "Game/Maps/FarmForestBiome/hay_initialShadingGroup_Normal.png",
["posX"] = 0, 
["posY"] = -0.5, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1.5, ["height"] = -0.5, ["depth"] = -1}
colliderMax = { ["width"] = 1.5, ["height"] = 0.5, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


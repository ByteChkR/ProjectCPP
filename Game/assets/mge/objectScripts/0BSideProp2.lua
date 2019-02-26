local scripts = {}
local meta = {["name"] = "0BSideProp2", 
["objPath"] = "mge/models/FarmForestBiome/balloon.obj", 
["specular"] = "Game/Maps/FarmForestBiome/ballon_lambert4SG_Specular.png", 
["texture"] = "Game/Maps/FarmForestBiome/ballon_lambert4SG_Diffuse.png", 
["emissive"] = "Game/Maps/FarmForestBiome/ballon_lambert4SG_Emissive.png", 
["normal"] = "Game/Maps/FarmForestBiome/ballon_lambert4SG_Normal.png",
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


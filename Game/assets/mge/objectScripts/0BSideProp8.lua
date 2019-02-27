local scripts = {}
--local scripts = {"mge/gamescripts/exampleScript.lua"}
local meta = {["name"] = "0BSideProp8", 
["objPath"] = "mge/models/FarmForestBiome/fence2.obj", 
["specular"] = "Game/Maps/FarmForestBiome/fence2_lambert12SG_Specular.png", 
["texture"] = "Game/Maps/FarmForestBiome/fence2_lambert12SG_Diffuse.png", 
["emissive"] = "Game/Maps/FarmForestBiome/fence2_lambert12SG_Emissive.png", 
["normal"] = "Game/Maps/FarmForestBiome/fence2_lambert12SG_Normal.png",
["posX"] = 0, 
["posY"] = -0.6, 
["posZ"] = 0}
colliderMin = { ["width"] = -1, ["height"] = 0, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 2, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


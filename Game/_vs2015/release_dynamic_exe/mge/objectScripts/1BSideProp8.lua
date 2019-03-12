local scripts = {}
--local scripts = {"mge/gamescripts/exampleScript.lua"}
local meta = {["name"] = "1BSideProp8", 
["objPath"] = "mge/models/VillageForestBiome/16_VillageB_PineTree2_V1.obj",
["specular"] = "black.png",
["texture"] = "Game/Maps/VillageForestBiome/randombonsai/tex.jpg",
--["emissive"] = "Game/Maps/VillageForestBiome/pinetree/3/14_VillageB_PineTree3_V3_Geom_AlbedoTransparency.png",
["posX"] = 0, ["posY"] = -1, ["posZ"] = 0}
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


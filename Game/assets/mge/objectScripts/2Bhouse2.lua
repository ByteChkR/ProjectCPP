local scripts = {}
local meta = {["name"] = "2BHouse2", 
["objPath"] = "mge/models/CityBiome/2_CityB_OldHouse_v1.obj", 
["specular"] = "Game/Maps/CityBiome/OldHouse/OldHouse_Metallic.png", 
["texture"] = "Game/Maps/CityBiome/OldHouse/OldHouse_Base_Color.png", 
["emissive"] = "black.png",
["normal"] = "Game/Maps/CityBiome/OldHouse/OldHouse_Normal_OpenGL.png",
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


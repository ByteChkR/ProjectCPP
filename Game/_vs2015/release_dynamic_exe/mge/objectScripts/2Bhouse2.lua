local scripts = {}
local meta = {["name"] = "2BHouse2", 
["objPath"] = "mge/models/CityBiome/2_CityB_OldHouse_v1.obj", 
["specular"] = "Game/Maps/CityBiome/OldHouse/OldHouse_Metallic.png", 
["texture"] = "Game/Maps/CityBiome/OldHouse/OldHouse_Base_Color.png", 
["emissive"] = "black.png",
["normal"] = "Game/Maps/CityBiome/OldHouse/OldHouse_Normal_OpenGL.png",
["posX"] = 0, 
["posY"] = -1, 
["posZ"] = 0 }
colliderMin = { ["width"] = -2, ["height"] = -1, ["depth"] = -2}
colliderMax = { ["width"] = 2, ["height"] = 6, ["depth"] = 2}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


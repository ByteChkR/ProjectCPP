local scripts = {}
local meta = {["name"] = "2BSideProp1", 
["objPath"] = "mge/models/CityBiome/9_CityB_Restaurant_Umbrella_v1.obj", 
["specular"] = "Game/Maps/CityBiome/Restaurant_Umbrella/Restaurant_Umbrella_Metallic.png", 
["texture"] = "Game/Maps/CityBiome/Restaurant_Umbrella/Restaurant_Umbrella_Base_Color.png", 
["emissive"] = "black.png",
["normal"] = "Game/Maps/CityBiome/Restaurant_Umbrella/Restaurant_Umbrella_Normal_OpenGL.png",
["posX"] = 0, 
["posY"] = -1, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


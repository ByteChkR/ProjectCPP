local scripts = {}
local meta = {["name"] = "2BHouse1", 
["objPath"] = "mge/models/CityBiome/1_CityB_NewHouse_v1.obj", 
["specular"] = "Game/Maps/CityBiome/NewHouse/NewHouse_Metallic.png", 
["texture"] = "Game/Maps/CityBiome/NewHouse/NewHouse_Base_Color.png", 
["emissive"] = "black.png",
["normal"] = "Game/Maps/CityBiome/NewHouse/NewHouse_Normal_OpenGL.png",
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


local scripts = {}
local meta = {["name"] = "2BHouse9", 
["objPath"] = "mge/models/CityBiome/1_CityB_NewHouse_v1_right.obj", 
["specular"] = "Game/Maps/CityBiome/NewHouse/NewHouse_Metallic.png", 
["texture"] = "Game/Maps/CityBiome/NewHouse/NewHouse_Base_Color.png", 
["emissive"] = "black.png",
["normal"] = "Game/Maps/CityBiome/NewHouse/NewHouse_Normal_OpenGL.png",
["posX"] = 0, 
["posY"] = -1.5, 
["posZ"] = 0 }
colliderMin = { ["width"] = -2, ["height"] = 0, ["depth"] = -2}
colliderMax = { ["width"] = 2, ["height"] = 6, ["depth"] = 2}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


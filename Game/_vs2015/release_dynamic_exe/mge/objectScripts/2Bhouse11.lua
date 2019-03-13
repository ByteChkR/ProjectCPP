local scripts = {}
local meta = {["name"] = "2BHouse11", 
["objPath"] = "mge/models/CityBiome/1_CityB_NewHouse_v1_right.obj", 
["texture"] = "Game/Maps/CityBiome/NewHouse/NewHouse_Base_Color.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
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


local scripts = {}
local meta = {["name"] = "2BSideProp4", ["objPath"] = "mge/models/CityBiome/12_CityB_Add_Board_v1.obj", 
["texture"] = "Game/Maps/CityBiome/Add_Board/12_Add_Board_v1_Add_Board_BaseColor.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, ["posY"] = -0.50, ["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
colliderMode = "auto"

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


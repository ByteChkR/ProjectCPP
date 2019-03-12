local scripts = {}
local meta = {["name"] = "2BSideProp4", ["objPath"] = "mge/models/CityBiome/12_CityB_Add_Board_v1.obj", ["specular"] = "black.png", ["texture"] = "Game/Maps/CityBiome/Fire_Hydrant/13_CityB_FIre_Hydrant_v1_Fire_Hydrant_BaseColor.png", ["emissive"] = "black.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


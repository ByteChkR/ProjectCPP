local scripts = {}
local meta = {["name"] = "2BSideProp5", ["objPath"] = "mge/models/CityBiome/13_CityB_FIre_Hydrant_v1.obj", ["specular"] = "black.png", ["texture"] = "Game/Maps/CityBiome/Add_Board/12_Add_Board_v1_Add_Board_BaseColor.png", ["emissive"] = "black.png", ["posX"] = 0, ["posY"] = -1, ["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


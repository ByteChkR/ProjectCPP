local scripts = {}
local meta = {["name"] = "1BHouse2", ["objPath"] = "mge/models/VillageForestBiome/2_Village_B_HouseSquare_V1.obj", ["specular"] = "black.png", ["texture"] = "red.png", ["emissive"] = "black.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
colliderMin = { ["width"] = -3, ["height"] = 0, ["depth"] = -3}
colliderMax = { ["width"] = 1.5, ["height"] = 4, ["depth"] = 3}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


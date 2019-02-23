local scripts = {}
local meta = {["name"] = "1BSideProp4", ["objPath"] = "mge/models/VillageForestBiome/11_Village_B_Barrel_V1.obj", ["specular"] = "black.png", ["texture"] = "red.png", ["emissive"] = "black.png", ["posX"] = 0, ["posY"] = -0.5, ["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


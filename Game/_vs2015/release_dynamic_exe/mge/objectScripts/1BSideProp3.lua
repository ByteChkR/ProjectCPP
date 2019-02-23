local scripts = {}
local meta = {["name"] = "1BSideProp3", ["objPath"] = "mge/models/VillageForestBiome/10_Village_B_Fance2_V1.obj", ["specular"] = "black.png", ["texture"] = "red.png", ["emissive"] = "black.png", ["posX"] = 0, ["posY"] = -0.5, ["posZ"] = 0  }
colliderMin = { ["width"] = -0.1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 0.1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


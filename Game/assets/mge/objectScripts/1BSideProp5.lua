local scripts = {}
local meta = {["name"] = "1BSideProp5", ["objPath"] = "mge/models/VillageForestBiome/12_Village_B_Tree1_V1.obj", ["specular"] = "black.png", ["texture"] = "red.png", ["emissive"] = "black.png",["posX"] = 0, ["posY"] = 0, ["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = 0, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 2, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


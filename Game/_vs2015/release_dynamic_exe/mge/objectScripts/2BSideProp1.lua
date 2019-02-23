local scripts = {}
local meta = {["name"] = "2BSideProp1", ["objPath"] = "mge/models/CityBiome/9_CityB_Umbrella_v1.obj", ["specular"] = "black.png", ["texture"] = "red.png", ["emissive"] = "black.png",["posX"] = 0, ["posY"] = -0.5, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = 0, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 2, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


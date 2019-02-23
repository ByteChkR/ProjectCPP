local scripts = {}
local meta = {["name"] = "2Bobstacle0", ["objPath"] = "mge/models/CityBiome/9_CityB_Umbrella_v1.obj" , ["specular"]  = "green.png", ["emissive"] = "black.png", ["texture"] = "red.png", ["posX"] = 0, ["posY"] = 0, ["posZ"] = 0 }
colliderMin = { ["width"] = -0.5, ["height"] = -0.5, ["depth"] = -0.5}
colliderMax = { ["width"] = 0.5, ["height"] = 0.5, ["depth"] = 0.5}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


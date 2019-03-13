local scripts = {}
local meta = {["name"] = "2BSideProp3", ["objPath"] = "mge/models/CityBiome/11_CityB_Bench_v1.obj", 
["texture"] = "Game/Maps/CityBiome/Bench/11_CityB_Bench_v1_Bench_BaseColor.png", 
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, ["posY"] = -0.9, ["posZ"] = 0  }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
colliderMode = "auto"
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


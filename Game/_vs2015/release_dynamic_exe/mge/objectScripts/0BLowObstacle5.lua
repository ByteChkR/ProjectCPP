local scripts = {}
local meta = {["name"] = "0BLowObstacle5",["objPath"] = "mge/models/CityBiome/Roadwork3.obj", 
["texture"] = "Game/Maps/CityBiome/Roadwork3/Roadwork3_1001_AlbedoTransparency.png",["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0, ["posY"] = -1, ["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


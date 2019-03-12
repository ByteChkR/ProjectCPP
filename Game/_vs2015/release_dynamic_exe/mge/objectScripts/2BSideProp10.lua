local scripts = {}
--local scripts = {"mge/gamescripts/exampleScript.lua"}
local meta = {["name"] = "2BSideProp10", ["objPath"] = "mge/models/CityBiome/streetintersection.obj", ["specular"] = "black.png",  ["texture"] = "Game/Maps/CityBiome/street.png", ["emissive"] = "black.png", ["posX"] = 0, ["posY"] = -0.80, ["posZ"] = 0}
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


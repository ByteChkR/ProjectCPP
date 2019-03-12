local scripts = {}
--local scripts = {"mge/gamescripts/exampleScript.lua"}
local meta = {["name"] = "2BSideProp9", ["objPath"] = "mge/models/CityBiome/Railway.obj", ["specular"] = "black.png",  ["texture"] = "Game/Maps/CityBiome/railway_diffuse.png",  ["emissive"] = "black.png", ["posX"] = 0, ["posY"] = -0.7, ["posZ"] = 0}
colliderMin = { ["width"] = -1, ["height"] = -0.50, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


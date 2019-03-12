local scripts = {}
--local scripts = {"mge/gamescripts/exampleScript.lua"}
local meta = {["name"] = "2BSideProp8", ["objPath"] = "mge/models/CityBiome/fence.obj",
 ["specular"] = "black.png",
 ["texture"] = "Game/Maps/CityBiome/fence/fence_Diffuse.png",
 ["posX"] = 0, ["posY"] = -0.90, ["posZ"] = 0}
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


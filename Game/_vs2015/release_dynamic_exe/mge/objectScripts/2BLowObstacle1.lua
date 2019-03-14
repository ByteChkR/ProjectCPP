local scripts = {}
local meta = {["name"] = "2BLowObstacle1",
["objPath"] = "mge/models/CityBiome/17_CityB_Menu_Sign_v1.obj",
["texture"] = "Game/Maps/CityBiome/Menu_Sign/17_CityB_Menusign_v1_Menu_Sign_BaseColor.png",
["specular"] = "black.png",
["emissive"] = "black.png",
["posX"] = 0,
["posY"] = -1,
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = 0, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 0.5, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


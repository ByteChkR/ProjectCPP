local scripts = {}
local meta = {["name"] = "2BLowObstacle1", 
["objPath"] = "mge/models/CityBiome/17_CityB_Menu_Sign_v1.obj", 
["specular"] = "Game/Maps/CityBiome/Menu_Sign/Menu_Sign_Metallic.png", 
["texture"] = "Game/Maps/CityBiome/Menu_Sign/Menu_Sign_Base_Color.png", 
["emissive"] = "black.png",
["normal"] = "Game/Maps/CityBiome/Menu_Sign/Menu_Sign_Normal_OpenGL.png",
["posX"] = 0,
["posY"] = 0, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}
function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


local scripts = {}
local meta = {["name"] = "2BHighObstacle2", 
["objPath"] = "mge/models/CityBiome/23_CityB_Traffic_Light_v1.obj", 
["specular"] = "Game/Maps/CityBiome/Traffic_Light/Traffic_Light_Metallic.png", 
["texture"] = "Game/Maps/CityBiome/Traffic_Light/Traffic_Light_Base_Color.png", 
["normal"] = "Game/Maps/CityBiome/Traffic_Light/Traffic_Light_Normal_OpenGL.png",
["posX"] = 0, 
["posY"] = -0.80, 
["posZ"] = 0 }
colliderMin = { ["width"] = -1, ["height"] = -1, ["depth"] = -1}
colliderMax = { ["width"] = 1, ["height"] = 1, ["depth"] = 1}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


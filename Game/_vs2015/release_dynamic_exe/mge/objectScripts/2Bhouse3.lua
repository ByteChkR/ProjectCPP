local scripts = {}
local meta = {["name"] = "2BHouse3", 
["objPath"] = "mge/models/CityBiome/3_CityB_Hotel_v1.obj", 
["specular"] = "Game/Maps/CityBiome/hotel/hotel_Metallic.png", 
["texture"] = "Game/Maps/CityBiome/hotel/hotel_Base_Color.png", 
["emissive"] = "black.png",
["normal"] = "Game/Maps/CityBiome/hotel/hotel_Normal_OpenGL.png",
["posX"] = -10, 
["posY"] = -1,
["posZ"] = 0  }
colliderMin = { ["width"] = -4, ["height"] = 0, ["depth"] = -2.5}
colliderMax = { ["width"] = 2.5, ["height"] = 12, ["depth"] = 2.5}

function AttachedScripts()
	return scripts
end

function GetMeta()
	return meta
end


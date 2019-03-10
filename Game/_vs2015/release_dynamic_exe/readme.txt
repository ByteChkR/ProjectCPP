Cheats:
	godmode on = NUMPAD0
	godmode off = NUMPAD1
	ReloadPlayerSettings = NUMPAD2
	ReloadLightParams = NUMPAD3
	ReloadMapFile = NUMPAD4
	ReloadMap = HOME/POS1
	IncreaseSpeed = PageUp
	DecreaseSpeed = PageDown
	ResetSpeed = END
	Pause = PauseKey

Startup Parameters:
	Map Parameters:
		mge.exe -s : Story Mode(default when no valid -l or -p)
		mge.exe -l <mapfile.lua|txt> (no story panels, single map. nexstage and backto menu are crashing the game)
		mge.exe -p <maplist.lua> (no story panels)

	Gameplay Parameters:
		mge.exe -editor : Move forward and backwards with Q/E. Instant GOD Mode and Cheats enabled
		mge.exe -enableCheats : enables cheats
		mge.exe -noTutorial : No Tutorials throughout the game
		mge.exe -noStory : No Story throughout the game.
	
	EngineSettings Override Parameters
	mge.exe -e <pathtosettings> : Uses specified settings file
	mge.exe -res <width> <height> : Overrides engine settings resolution
	mge.exe -vsync <0|1> : Overrides engine settings vsync
	mge.exe -fpsTarget <fps> : Overrides engine settings fpstarget
	mge.exe -windowMode <0|1> : Overrides engine settings windowMode
	mge.exe -msaa <0|2|4|8> : Overrides engine settings msaaSamples
	mge.exe -name <WindowName> : Overrides engine settings WindowName

Shortcut:
	mge.exe -forceWindow : Shortcut to -windowMode 1
	
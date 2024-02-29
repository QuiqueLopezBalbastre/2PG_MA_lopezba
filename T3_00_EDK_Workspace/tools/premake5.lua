--
-- premake5.lua
--
-- GENIe solution to build the EDK project.
-- Ivan Sancho, Escuela Superior de Arte y Tecnologia (ESAT) Valencia, 2023/24
-- Graphic Programming
--
-- All rights are reserved.
--
--

PROJ_DIR = path.getabsolute("./../")

project_names = {
  "PR03_00_Template",
  "PR03_01_Demo",
  "PR03_02_FirstScene",
  "PR03_03_SolarSystem",

  --"PR03_04_DotProduct",
  "PR03_05_BasicMaterial",
  "PR03_06_CustomMaterial",
  "PR03_07_Quad",
  --"PR03_08_Cube",
  --"PR03_09_Sphere",
  --"PR03_10_Surface",
  --"PR03_11_Camera",
  --"PR03_12_Terrain",
  --"PR03_13_Transparencies",
  --"PR03_14_DemoRenderTarget",
  --"PR03_15_BasicPostprocess",
}

-- Solution workspace declaration:
solution("EDK_Workspace_" .. _ACTION)
  location(PROJ_DIR .. "/build/")
  language "C++"
  kind "ConsoleApp"
  startproject "PR03_07_Quad"
  platforms {
    "x32",
    "Native",
  }
  defines {
    "_CRT_SECURE_NO_WARNINGS",
  }
  configurations {
    "Debug",
    "Release",
  }

-- Workspace "Debug" configuration:
filter { "configurations:Debug" }
  defines {
    "DEBUG",
  }
  symbols "On"
  warnings "Extra"
  targetsuffix "_d"

-- Workspace "Release" configuration:
filter { "configurations:Release" }
  defines {
    "NDEBUG",
  }
  symbols "Off"
  warnings "Extra"
  optimize "On"
  optimize "Size"
  flags {
    "No64BitChecks",
    "NoPCH",
  }

--[[********************** PROJECT GENERATOR FUNCTION **********************]]--
function GenerateProject(project_name, project_group)
  project(project_name)
    location (PROJ_DIR .. "/build/" .. project_name .. "/" .. _ACTION)
    includedirs {
      path.join(PROJ_DIR, "./include/"),
      path.join(PROJ_DIR, "./include/dev"),
      path.join(PROJ_DIR, "./deps/EDK/include/"),
      path.join(PROJ_DIR, "./deps/Perlin/include/"),
      path.join(PROJ_DIR, "./deps/Perlin/src/"),
      path.join(PROJ_DIR, "./deps/STB/include/"),
    }
    files {
      path.join(PROJ_DIR, "./include/*.h"),
      path.join(PROJ_DIR, "./include/dev/*.h"),
      path.join(PROJ_DIR, "./src/*.cc"),
      path.join(PROJ_DIR, "./src/dev/*.cc"),
      path.join(PROJ_DIR, "./deps/EDK/include/EDK3/*.h"),
      path.join(PROJ_DIR, "./deps/EDK/include/EDK3/dev/*.h"),
      path.join(PROJ_DIR, "./deps/EDK/include/ESAT/*.h"),
      path.join(PROJ_DIR, "./deps/EDK/include/ESAT_extra/*.h"),
      path.join(PROJ_DIR, "./deps/Perlin/include/Perlin/*.h"),
      path.join(PROJ_DIR, "./deps/Perlin/src/*.cpp"),
      path.join(PROJ_DIR, "./deps/STB/include/*.h"),
    }

    libdirs { path.join(PROJ_DIR, "./deps/EDK/lib/EDK/x32"), }

    --Debug filters:
    filter { "configurations:Debug", "platforms:x32" }
      architecture "x86"
      targetdir (path.join(PROJ_DIR, "bin/Debug/x32"))
      objdir(path.join(PROJ_DIR, "./build/" .. project_name .. "/Debug"))
      links { path.join(PROJ_DIR, "deps/EDK/lib/EDK/x32/ESAT_d"),
              path.join(PROJ_DIR, "deps/EDK/lib/EDK/x32/ESAT_extra_d"),
              "OpenGL32",
              "winmm" }
    filter { "configurations:Release", "platforms:x32" }
      architecture "x86"
      targetdir (path.join(PROJ_DIR, "bin/Release/x32/"))
      objdir(path.join(PROJ_DIR, "./build/" .. project_name .. "/Release"))
      links { path.join(PROJ_DIR, "deps/EDK/lib/EDK/x32/ESAT"),
              path.join(PROJ_DIR, "deps/EDK/lib/EDK/x32/ESAT_extra"),
              "OpenGL32",
              "winmm" }
end --Function "GenerateProject" ends here.

--Calling the Lua function:
for i, prj in ipairs(project_names) do
  GenerateProject(prj)
end


project "PR03_00_Template"
	files {
	  path.join(PROJ_DIR, "./tests/PR03_00_Template.cc"),
  }

project "PR03_01_Demo"
	files {
	  path.join(PROJ_DIR, "./tests/PR03_01_Demo.cc"),
  }

  project "PR03_02_FirstScene"
	files {
    path.join(PROJ_DIR, "./tests/PR03_02_FirstScene.cc"),
  }
  
  project "PR03_03_SolarSystem"
	files {
    path.join(PROJ_DIR, "./tests/PR03_03_SolarSystem.cc"),
  }
  
  
  
  project "PR03_05_BasicMaterial"
	files {
    path.join(PROJ_DIR, "./tests/PR03_05_BasicMaterial.cc"),
  }
  
  project "PR03_06_CustomMaterial"
	files {
    path.join(PROJ_DIR, "./tests/PR03_06_CustomMaterial.cc"),
  }

project "PR03_07_Quad"
	files {
	  path.join(PROJ_DIR, "./tests/PR03_07_Quad.cc"),
  }
  --[[
project "PR03_04_DotProduct"
	files {
    path.join(PROJ_DIR, "./tests/PR03_04_DotProduct.cc"),
  }
  
project "PR03_08_Cube"
	files {
	  path.join(PROJ_DIR, "./tests/PR03_08_Cube.cc"),
  }

project "PR03_09_Sphere"
	files {
	  path.join(PROJ_DIR, "./tests/PR03_09_Sphere.cc"),
  }

project "PR03_10_Surface"
  files {
    path.join(PROJ_DIR, "./tests/PR03_10_Surface.cc"),
  }

project "PR03_11_Camera"
	files {
	  path.join(PROJ_DIR, "./tests/PR03_11_Camera.cc"),
  }

project "PR03_12_Terrain"
	files {
	  path.join(PROJ_DIR, "./tests/PR03_12_Terrain.cc"),
  }

project "PR03_13_Transparencies"
	files {
	  path.join(PROJ_DIR, "./tests/PR03_13_Transparencies.cc"),
  }

project "PR03_14_DemoRenderTarget"
	files {
	  path.join(PROJ_DIR, "./tests/PR03_14_DemoRenderTarget.cc"),
  }

project "PR03_15_BasicPostprocess"
	files {
	  path.join(PROJ_DIR, "./tests/PR03_15_BasicPostprocess.cc"),
  }
]]--

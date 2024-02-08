--
-- genie.lua
--
-- GENIe solution to build the EDK project.
-- Ivan Sancho, Escuela Superior de Arte y Tecnologia (ESAT) Valencia, 2022/23
-- Graphic Programming
--
-- All rights are reserved.
--
--

PROJ_DIR = path.getabsolute("./../")

solution("EDK_Workspace_" .. _ACTION)
  location(PROJ_DIR .. "/build/")
  language "C++"
  kind "ConsoleApp"
  startproject "PR03_01_Demo"

  defines {
    "_CRT_SECURE_NO_WARNINGS",
  }

  configurations {
    "Debug",
    "Release"
  }

  configuration { "Debug" }
    defines {
      "DEBUG",
    }
    flags {
      "Symbols",
      "ExtraWarnings",
    }
    targetsuffix "_d"

  configuration { "Release" }
    defines {
      "NDEBUG",
    }
    flags {
      "Optimize",
      "OptimizeSize",
      "No64BitChecks",
      "NoPCH",
    }

  projects_names = {
    "PR03_00_Template",
    "PR03_01_Demo",

    --"PR03_02_FirstScene",
    --"PR03_03_SolarSystem",
    --"PR03_04_DotProduct",
    --"PR03_05_BasicMaterial",
    --"PR03_06_CustomMaterial",
    --"PR03_07_Quad",
    --"PR03_08_Cube",
    --"PR03_09_Sphere",
    --"PR03_10_Surface",
    --"PR03_11_Camera",
    --"PR03_12_Terrain",
    --"PR03_13_Transparencies",
    --"PR03_14_DemoRenderTarget",
    --"PR03_15_BasicPostprocess",
  }

--[[************************* PROJECT GENERATOR FUNCTION *************************]]--
  for i, prj in ipairs(projects_names) do
    project(prj)
      location (PROJ_DIR .. "/build/" .. prj .. "/" .. _ACTION)
      platforms {
        "x32",
        "Native",
      }
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

      configuration { "Debug", "x32" }
        targetdir (path.join(PROJ_DIR, "bin/Debug/x32"))
        objdir(path.join(PROJ_DIR, "./build/" .. prj .. "/Debug"))
        targetsuffix "_d"
        links { path.join(PROJ_DIR, "deps/EDK/lib/EDK/x32/ESAT_d"),
                path.join(PROJ_DIR, "deps/EDK/lib/EDK/x32/ESAT_extra_d"),
                "OpenGL32",
                "winmm" }
      configuration { "Release", "x32" }
        targetdir (path.join(PROJ_DIR, "bin/Release/x32/"))
        objdir(path.join(PROJ_DIR, "./build/" .. prj .. "/Release"))
        links { path.join(PROJ_DIR, "deps/EDK/lib/EDK/x32/ESAT"),
                path.join(PROJ_DIR, "deps/EDK/lib/EDK/x32/ESAT_extra"),
                "OpenGL32",
                "winmm" }
	end

  project "PR03_00_Template"
  	files {
  	  path.join(PROJ_DIR, "./tests/PR03_00_Template.cc"),
    }

  project "PR03_01_Demo"
  	files {
  	  path.join(PROJ_DIR, "./tests/PR03_01_Demo.cc"),
    }

--[[
  project "PR03_02_FirstScene"
  	files {
  	  path.join(PROJ_DIR, "./tests/PR03_02_FirstScene.cc"),
    }

  project "PR03_03_SolarSystem"
  	files {
  	  path.join(PROJ_DIR, "./tests/PR03_03_SolarSystem.cc"),
    }

  project "PR03_04_DotProduct"
  	files {
  	  path.join(PROJ_DIR, "./tests/PR03_04_DotProduct.cc"),
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

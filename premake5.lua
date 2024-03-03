workspace "Istd"
    configurations {"Debug", "Release"}
    architecture "x86_64"

    warnings "Everything"

    function defaultBuildCfg()
        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
            runtime "Debug"
            optimize "Debug"

        filter "configurations:Release"
            defines { "NDEBUG" }
            symbols "Off"
            runtime "Release"
            optimize "Speed"
    end

    function defaultBuildLocation()
        targetdir ("bin/%{prj.name}/%{cfg.buildcfg}")
        objdir ("bin-int/%{prj.name}/%{cfg.buildcfg}")
    end

    project "Test"
        location "test"
        kind "ConsoleApp"
        language "C"
        cdialect "C17"

        files {
            "%{prj.location}/**.c",
            "%{prj.location}/**.h",
        }

        includedirs { "src" }

        links { "Istd" }

        defaultBuildLocation()
        defaultBuildCfg()

    project "Istd"
        location "src"
        kind "StaticLib"
        language "C"
        cdialect "C17"

        files {
            "%{prj.location}/**.c",
            "%{prj.location}/**.h",
        }

        includedirs {
            "%{prj.location}/",
        }

        defaultBuildLocation()
        defaultBuildCfg()
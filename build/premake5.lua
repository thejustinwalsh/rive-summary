include "../lib/rive-cpp/build"

workspace "main"
    configurations { "debug", "release" }

project "main"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"
    includedirs {"../lib/rive-cpp/include", "../lib/rive-cpp/test"}

    files {"../src/**.cpp"}

    buildoptions {"-Wall", "-fno-exceptions", "-fno-rtti"}

    libdirs { "../lib/rive-cpp/build/bin/%{cfg.buildcfg}" }
    links { "rive" }

    filter "configurations:debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:release"
        defines {"RELEASE"}
        defines { "NDEBUG" }
        optimize "On"

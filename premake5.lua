workspace "easy_time"
location("./Build")
architecture("x86_64")
configurations { "Debug", "Release" }

flags {"MultiProcessorCompile"}

filter "configurations:Release"
    defines {"NDEBUG"}
filter {}

    project("et")
        kind("StaticLib")
        language("C++")
        architecture("x86_64")
        staticruntime("on")
        
        files
        {
            "./**.h",
            "./**.hpp"
        }
        
        targetdir("./Build/%{prj.name}")
        objdir("./Build/Imde/%{prj.name}")
        filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
    
        filter "configurations:Release"
        runtime  "Release"
        optimize "On"
    
        filter ""
    

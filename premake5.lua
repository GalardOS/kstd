workspace "kstd"
    architecture "x86_64"
    configurations {"Debug", "Release"}
    flags {"MultiProcessorCompile"}

project "kstd"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("build/")
    objdir("build/obj/")

    files {"src/**.cc", "src/**.hh"}
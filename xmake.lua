add_requires("glfw >=3.4", "glew")

set_project("GraphicalTest")
set_languages("c++20")

add_rules("mode.debug", "mode.release")

target("Window")
    set_kind("static")
    set_default(false)
    add_files("src/window.cpp")
    add_includedirs("src")

    add_packages("glfw", "glew")

-- Main projet
target("app")
    set_kind("binary")
    set_default(true)

    add_files("src/main.cpp")
    add_includedirs("src")

    add_deps("Window")
    add_packages("glfw", "glew")

    set_rundir("$(projectdir)")

target("mock")
    set_kind("static")
    set_default(false)
    add_files("tests/mock_*.cpp")

-- Test with mocking
target("test")
    set_kind("binary")
    set_default(true)

    add_files("tests/test.cpp")
    add_deps("mock", "Window")
    add_includedirs("src")

    set_rundir("$(projectdir)")

if is_mode("debug") then
    add_defines("ES_DEBUG")
    set_symbols("debug")
    set_optimize("none")
end

if is_mode("release") then
    set_optimize("fastest")
end

if is_plat("windows") then
    add_cxflags("/W4")
end

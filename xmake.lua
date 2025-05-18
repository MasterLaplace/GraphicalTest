add_requires("glfw >=3.4")

set_project("GraphicalTest")
set_languages("c++20")

add_rules("mode.debug", "mode.release")

if is_plat("windows") then
    add_cxflags("/W4")
end

-- Main projet
target("app")
    set_kind("binary")
    set_default(true)

    add_files("src/main.cpp", "src/window.cpp")
    add_includedirs("src")

    add_packages("glfw")

    set_rundir("$(projectdir)")

-- Test with mocking
target("test")
    set_kind("binary")
    set_default(true)

    add_files("tests/test.cpp", "tests/mock_glfw.cpp", "src/window.cpp")
    add_includedirs("src")

    add_packages("glfw")

    set_rundir("$(projectdir)")

if is_mode("debug") then
    add_defines("ES_DEBUG")
    set_symbols("debug")
    set_optimize("none")
end

if is_mode("release") then
    set_optimize("fastest")
end

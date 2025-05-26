add_requires("glfw", "glew")

-- Static library: window wrappers
target("window")
    set_kind("static")
    add_files("window.c")
    add_headerfiles("window.h")
    add_includedirs(".")
    add_packages("glfw", "glew")

-- Static library: mocks for test (wrapping via --wrap or MSVC alternate-naming)
target("mock")
    set_kind("static")
    add_files("mock_wrap.c")
    add_packages("glfw", "glew")

-- Application executable
target("app")
    set_kind("binary")
    add_files("app.c")
    add_deps("window")
    add_packages("glfw", "glew")

-- Unit test executable
target("test")
    set_kind("binary")
    add_files("test.c")
    add_deps("window", "mock")
    add_packages("glfw", "glew")
    -- On GCC/Clang: use --wrap to override glfwInit / glfwCreateWindow
    if is_plat("windows") then
    else
        add_ldflags("-Wl,--wrap=glfwInit", "-Wl,--wrap=glfwCreateWindow", {force = true})
    end

after_build(function (target)
    if target:is_default() then
        print("Built target: " .. target:name())
    end
end)

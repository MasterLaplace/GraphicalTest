add_rules("mode.debug", "mode.release")

-- Dépendance GLFW
add_requires("glfw")

-- Target 1: Librairie window (abstraction GLFW)
target("window")
    set_kind("static")
    add_files("window.cpp")
    add_headerfiles("window.h")
    add_packages("glfw")
    set_targetdir("build")
target_end()

-- Target 2: Librairie mock (fonctions GLFW mockées)
target("mock")
    set_kind("static")
    add_files("mock_glfw.c")
    add_headerfiles("mock_glfw.h")
    -- Note: pas besoin de lier GLFW ici car on remplace les fonctions
    set_targetdir("build")
target_end()

-- Target 3: Application principale (utilise vraie GLFW via window.a)
target("app")
    set_kind("binary")
    add_files("app.cpp")
    add_deps("window")
    add_packages("glfw")
    set_targetdir("build")

    -- Configurations spécifiques par plateforme
    if is_plat("windows") then
        add_syslinks("user32", "gdi32", "shell32")
    elseif is_plat("linux") then
        add_syslinks("pthread", "dl", "X11", "Xrandr", "Xi", "Xcursor", "Xinerama")
    elseif is_plat("macosx") then
        add_frameworks("Cocoa", "IOKit", "CoreVideo")
    end
target_end()

-- Target 4: Tests unitaires (utilise mocks via mock.a)
target("test")
    set_kind("binary")
    add_files("test.cpp")

    -- S'assurer que mock est correctement lié
    add_deps("mock")

    -- Ajouter spécifiquement les objets de mock
    add_linkdirs("build")
    add_links("mock")

    -- Utiliser une version spéciale de window qui n'inclut pas GLFW
    add_files("window.cpp")
    add_includedirs(".")  -- Pour l'inclusion de window.h

    -- Ne pas ajouter add_deps("window") car cela tirerait GLFW avec lui
    -- Ne pas ajouter add_packages("glfw")

    set_targetdir("build")
target_end()

-- Configuration globale
-- set_languages("c++20", "c99")  -- C++20 pour les fichiers cpp, C99 pour les fichiers C
set_warnings("all", "extra")

-- Règles de build personnalisées
rule("show_info")
    on_build(function (target)
        print("Building target: " .. target:name())
        print("Target kind: " .. target:kind())
        print("Target files: " .. table.concat(target:sourcefiles(), ", "))
    end)
rule_end()

-- Appliquer la règle d'info à tous les targets (optionnel)
-- add_rules("show_info")

-- Tâche personnalisée pour nettoyer
task("clean_all")
    set_menu {
        usage = "xmake clean_all",
        description = "Clean all build artifacts",
        options = {}
    }
    on_run(function ()
        os.rmdir("build")
        os.rmdir(".xmake")
        print("All build artifacts cleaned!")
    end)
task_end()

-- Tâche pour exécuter les tests
task("run_tests")
    set_menu {
        usage = "xmake run_tests",
        description = "Build and run unit tests",
        options = {}
    }
    on_run(function ()
        -- Build d'abord le target test
        os.exec("xmake build test")
        -- Puis l'exécuter
        if is_plat("windows") then
            os.exec("build/test.exe")
        else
            os.exec("build/test")
        end
    end)
task_end()

-- Tâche pour exécuter l'application
task("run_app")
    set_menu {
        usage = "xmake run_app",
        description = "Build and run main application",
        options = {}
    }
    on_run(function ()
        -- Build d'abord le target app
        os.exec("xmake build app")
        -- Puis l'exécuter
        if is_plat("windows") then
            os.exec("build/app.exe")
        else
            os.exec("build/app")
        end
    end)
task_end()

-- Configuration pour différents modes de build
if is_mode("debug") then
    set_cleasymbols("debug")
    set_optimize("none")
    add_defines("DEBUG")
elseif is_mode("release") then
    set_symbols("hidden")
    set_optimize("fastest")
    add_defines("NDEBUG")
    set_strip("all")
end

-- Affichage d'informations de configuration
after_load(function ()
    print("=== Configuration du projet ===")
    print("Plateforme: " .. get_config("plat"))
    print("Architecture: " .. get_config("arch"))
    print("Mode: " .. get_config("mode"))
    -- print("Compilateur: " .. get_config("cc"))
    print("Répertoire de build: build/")
    print("")
    print("Targets disponibles:")
    print("  - window: Librairie d'abstraction GLFW")
    print("  - mock: Librairie de mocks GLFW")
    print("  - app: Application principale")
    print("  - test: Tests unitaires")
    print("")
    print("Commandes utiles:")
    print("  xmake build [target]  - Compiler un target spécifique")
    print("  xmake run_app         - Compiler et exécuter l'application")
    print("  xmake run_tests       - Compiler et exécuter les tests")
    print("  xmake clean_all       - Nettoyer tous les artefacts")
    print("================================")
end)

--[[
Structure attendue du projet:
project/
├── xmake.lua
├── window.h
├── window.c
├── mock_glfw.h
├── mock_glfw.c
├── app.c
├── test.c
└── build/ (créé automatiquement)
    ├── window.a
    ├── mock.a
    ├── app(.exe)
    └── test(.exe)

Commandes principales:
- xmake                    # Build tous les targets
- xmake build app          # Build seulement l'application
- xmake build test         # Build seulement les tests
- xmake run_app           # Build et exécute l'application
- xmake run_tests         # Build et exécute les tests
- xmake clean             # Nettoie les fichiers de build
- xmake clean_all         # Nettoie tout (y compris cache xmake)

Configuration et debug:
- xmake f -m debug        # Configure en mode debug
- xmake f -m release      # Configure en mode release
- xmake f --help          # Voir toutes les options de configuration
- xmake show              # Afficher la configuration actuelle
--]]

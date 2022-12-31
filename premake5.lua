workspace "G"
    location "build"

    startproject "g"

    configurations { "Debug", "Release", "DebugDLL", "ReleaseDLL" }
    platforms { "Win32" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        kind "StaticLib"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        kind "StaticLib"

    filter "configurations:DebugDLL"
        defines { "DEBUG", "DLL_EXPORTS" }
        symbols "On"
        kind "SharedLib"

    filter "configurations:ReleaseDLL"
        defines { "NDEBUG", "DLL_EXPORTS" }
        optimize "On"
        kind "SharedLib"

    filter "platforms:Win32"
        system "Windows"
        architecture "x86"

    filter "platforms:x64"
        system "Windows"
        architecture "x86_64"

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

    includedirs { "include" }

    libdirs { "bin/lib/%{cfg.buildcfg}" }

--    cppdialect "C++2a" -- GCC
    staticruntime "On"
    systemversion "latest"

group "Libraries"

    project "nonstd"
        location "build/lib/nonstd"

        language "C++"
        characterset ("MBCS")

        includedirs { "include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/nonstd/%{cfg.buildcfg}"

        files {
            "include/nonstd/**.h",
            "lib/nonstd/**.cpp"
        }

        filter { "platforms:Static" }
            kind "StaticLib"

        filter { "platforms:DLL" }
            kind "SharedLib"
            defines { "DLL_EXPORTS" }

    project "g-lib"
        location "build/lib/g"

        language "C++"
        characterset ("MBCS")

        includedirs { ".", "include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/%{cfg.buildcfg}"

        dependson { "nonstd" }

        files {
            "include/g/*.h",
            "lib/g/*.cpp"
        }

        filter { "platforms:Static" }
            kind "StaticLib"

        filter { "platforms:DLL" }
            kind "SharedLib"
            defines { "DLL_EXPORTS" }

    project "Runtime"
        location "build/runtime"

        language "C++"
        characterset ("MBCS")

        includedirs { "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/lib/g/TextualTemplateGenerator/%{cfg.buildcfg}"

        files {
            "runtime/Buffer.h",
            "runtime/Pairs.h",
            "runtime/Stack.h",
            "runtime/lexer/Lexer.h",
            "runtime/lexer/Lexer.cpp",
            "runtime/parser/Parser.cpp",
            "runtime/parser/Parser.h",
            "runtime/parser/State.h",
            "runtime/parser/Tables.h"
        }

        filter { "platforms:Static" }
            kind "StaticLib"

        filter { "platforms:DLL" }
            kind "SharedLib"
            defines { "DLL_EXPORTS" }
    project "LexicalAnalyserGenerator"
        location "build/lib/g/LexicalAnalyserGenerator"

        language "C++"
        characterset ("MBCS")

        includedirs { ".", "include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/LexicalAnalyserGenerator/%{cfg.buildcfg}"

        dependson { "nonstd" }

        files {
            "include/g/LexicalAnalyserGenerator/**.h",
            "lib/g/LexicalAnalyserGenerator/**.cpp"
        }

        filter { "platforms:Static" }
            kind "StaticLib"

        filter { "platforms:DLL" }
            kind "SharedLib"
            defines { "DLL_EXPORTS" }


    project "Grammar"
        location "build/lib/g/Grammar"

        language "C++"

        includedirs { "include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/Grammar/%{cfg.buildcfg}"

        dependson { "nonstd" }

        files {
            "include/g/Grammar/**.h",
            "lib/g/Grammar/**.cpp"
        }

        filter { "platforms:Static" }
            kind "StaticLib"

        filter { "platforms:DLL" }
            kind "SharedLib"
            defines { "DLL_EXPORTS" }


    project "Generator"
        location "build/lib/g/Generator"

        dependson { "nonstd" }

        language "C++"
        characterset ("MBCS")

        includedirs { "include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/lib/g/Generator/%{cfg.buildcfg}"

        files {
            "include/g/Generator/**.h",
            "lib/g/Generator/**.cpp"
        }

        filter { "platforms:Static" }
            kind "StaticLib"

        filter { "platforms:DLL" }
            kind "SharedLib"
            defines { "DLL_EXPORTS" }


    project "ParserGenerator"
        location "build/lib/g/ParserGenerator"

        dependson { "nonstd", "Grammar" }

        language "C++"
        characterset ("MBCS")

        includedirs { ".", "include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/lib/g/ParserGenerator/%{cfg.buildcfg}"

        files {
            "include/g/ParserGenerator/**.h",
            "lib/g/ParserGenerator/**.cpp"
        }

        filter { "platforms:Static" }
            kind "StaticLib"

        filter { "platforms:DLL" }
            kind "SharedLib"
            defines { "DLL_EXPORTS" }

    project "AbstractSyntaxTreeGenerator"
        location "build/lib/g/AbstractSyntaxTreeGenerator"

        dependson { "nonstd", "Grammar" }

        language "C++"
        characterset ("MBCS")

        includedirs { "include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/lib/g/AbstractSyntaxTreeGenerator/%{cfg.buildcfg}"

        files {
            "include/g/AbstractSyntaxTreeGenerator/**.h",
            "lib/g/AbstractSyntaxTreeGenerator/**.cpp"
        }

        filter { "platforms:Static" }
            kind "StaticLib"

        filter { "platforms:DLL" }
            kind "SharedLib"
            defines { "DLL_EXPORTS" }


    project "TextualTemplateGenerator"
        location "build/lib/g/TextualTemplateGenerator"

        dependson { "nonstd", "Grammar" }

        language "C++"
        characterset ("MBCS")

        includedirs { "include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/lib/g/TextualTemplateGenerator/%{cfg.buildcfg}"

        files {
            "include/g/TextualTemplateGenerator/**.h",
            "lib/g/TextualTemplateGenerator/**.cpp"
        }

        filter { "platforms:Static" }
            kind "StaticLib"

        filter { "platforms:DLL" }
            kind "SharedLib"
            defines { "DLL_EXPORTS" }


group "flex-bison-bootstrap"

    include "flex-bison.lua"

    project "lg-bootstrap-flex-bison"
        location "build/bootstrap/flex-bison-bootstrap/lg-boostrap-flex-bison"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { ".", "include", "build/bootstrap/flex-bison-bootstrap/lg-boostrap-flex-bison" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/flex-bison-bootstrap/lg-bootstrap-flex-bison/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "LexicalAnalyserGenerator",
            "Generator"
        }

        rules {
            "flex",
            "bison"
        }

        filter { "system:windows" }
            disablewarnings { "4005", "5033", "6011", "6387", "4996"}

        defines {"YY_NO_UNISTD_H"}

        files {
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-flex-bison/LexicalGenerator.flex",
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-flex-bison/LexicalGenerator.bison",
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-flex-bison/LexicalGenerator.tab.h",
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-flex-bison/main.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/LexicalAnalyserGenerator.lib",
            "bin/%{cfg.buildcfg}/Generator.lib"
        }

        debugargs { "\"$(SolutionDir)../src/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-bison/lg.lg\"" }


    rule "lg_bootstrap_flex_bison"
        location "build/bootstrap/flex-bison-bootstrap/lg-boostrap-flex-bison"

        display "lg-bootstrap-flex-bison"
        fileextension { ".lg" }

        buildmessage 'Compiling %(Filename).lg with lg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/lg-bootstrap-flex-bison" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).lg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).lg.h' }

        propertydefinition {
            name = "output",
            kind = "string",
            display = "Output File Name",
            description = "Specify the file for the parser implementation file. --output=value",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).lg.cpp",
            switch = " "
        }
        propertydefinition {
            name = "header",
            kind = "string",
            display = "Output header File Name",
            description = "Specify the file for the parser implementation file. --output=value",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).lg.h",
            switch = " "
        }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }


    project "lg-bootstrap-lg-bison"
        location "build/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-bison"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { ".", "include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-bison/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "LexicalAnalyser",
            "Generator",
            "lg-bootstrap-flex-bison"
        }

        rules {
            "lg_bootstrap_flex_bison",
            "bison"
        }

        defines {"BISON", "YY_NO_UNISTD_H"}

        files {
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-bison/LexicalGenerator.bison",
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-bison/LexicalGenerator.tab.h",
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-bison/lg.lg",
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-bison/lg.lg.h",
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-bison/main.cpp",
            "runtime/lexer/Lexer.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/LexicalAnalyserGenerator.lib",
            "bin/%{cfg.buildcfg}/Generator.lib"
        }

        debugargs { "\"$(SolutionDir)../src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-bison/lg.lg\"" }

    rule "lg_bootstrap_lg_bison"
        location "build/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-bison"

        display "lg-bootstrap-lg-bison"
        fileextension { ".lg" }

        buildmessage 'Compiling %(Filename) with lg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/lg-bootstrap-lg-bison" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).lg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).lg.h' }

        propertydefinition {
            name = "output",
            kind = "string",
            display = "Output File Name",
            description = "Specify the file for the parser implementation file.",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).lg.cpp",
            switch = " "
        }
        propertydefinition {
            name = "header",
            kind = "string",
            display = "Output header File Name",
            description = "Specify the file for the parser implementation file.",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).lg.h",
            switch = " "
        }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }


    project "pg-bootstrap-lg-bison"
        location "build/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-bison"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { ".", "include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-bison/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Grammar",
            "ParserGenerator"
        }

        rules {
            "lg_bootstrap_lg_bison",
            "bison"
        }

        defines {"BISON", "YY_NO_UNISTD_H"}

        files {
            "src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-bison/pg.bison",
            "src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-bison/pg.tab.h",
            "src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-bison/pg.lg",
            "src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-bison/pg.lg.h",
            "src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-bison/main.cpp",
            "runtime/lexer/Lexer.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Grammar.lib",
            "bin/%{cfg.buildcfg}/ParserGenerator.lib"
        }

        debugargs { "\"$(SolutionDir)../src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-pg/pg.pg\"" }

    rule "pg_bootstrap_lg_bison"
        location "build/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-bison"

        display "pg-bootstrap-lg-bison"
        fileextension { ".pg" }

        buildmessage 'Compiling %(Filename) with pg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/pg-bootstrap-lg-bison" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).pg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).pg.h' }

        propertydefinition {
            name = "output",
            kind = "string",
            display = "Output File Name",
            description = "Specify the file for the parser implementation file.",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).pg.cpp",
            switch = " "
        }
        propertydefinition {
            name = "header",
            kind = "string",
            display = "Output header File Name",
            description = "Specify the file for the parser implementation file.",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).pg.h",
            switch = " "
        }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }


    project "lg-bootstrap-lg-pg"
        location "build/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-pg"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { ".", "include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-pg/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "LexicalAnalyser",
            "Generator",
            "lg-bootstrap-lg-bison",
            "pg-bootstrap-lg-bison"
        }

        rules {
            "lg_bootstrap_lg_bison",
            "pg_bootstrap_lg_bison"
        }

        files {
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-pg/lg.lg",
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-pg/lg.lg.h",
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-pg/lg.pg",
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-pg/lg.pg.h",
            "src/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-pg/main.cpp"
        }
        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/LexicalAnalyserGenerator.lib",
            "bin/%{cfg.buildcfg}/Generator.lib"
        }

        debugargs { "\"$(SolutionDir)../src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-pg/pg.pg\"" }

    rule "lg_bootstrap_lg_pg"
        location "build/bootstrap/flex-bison-bootstrap/lg-bootstrap-lg-pg"

        display "lg-bootstrap-lg-pg"
        fileextension { ".lg" }

        buildmessage 'Compiling %(Filename) with lg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/lg-bootstrap-lg-pg" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).lg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).lg.h' }

        propertydefinition {
            name = "output",
            kind = "string",
            display = "Output File Name",
            description = "Specify the file for the parser implementation file. --output=value",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).lg.cpp",
            switch = " "
        }
        propertydefinition {
            name = "header",
            kind = "string",
            display = "Output header File Name",
            description = "Specify the file for the parser implementation file. --output=value",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).lg.h",
            switch = " "
        }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }


    project "pg-bootstrap-lg-pg"
        location "build/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-pg"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { ".", "include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-pg/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "Grammar",
            "ParserGenerator",
            "lg-bootstrap-lg-pg",
            "pg-bootstrap-lg-bison"
        }

        rules {
            "lg_bootstrap_lg_pg",
            "pg_bootstrap_lg_bison"
        }

        files {
            "src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-pg/pg.lg",
            "src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-pg/pg.lg.h",
            "src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-pg/pg.pg",
            "src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-pg/pg.pg.h",
            "src/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-pg/main.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/Grammar.lib",
            "bin/%{cfg.buildcfg}/ParserGenerator.lib"
        }

        debugargs { "\"$(SolutionDir)../src/bootstrap/self-bootstrap/pg-generate-bootstrap/pg.pg\"" }

    rule "pg_bootstrap_lg_pg"
        location "build/bootstrap/flex-bison-bootstrap/pg-bootstrap-lg-pg"

        display "pg-bootstrap-lg-pg"
        fileextension { ".pg" }

        buildmessage 'Compiling %(Filename) with pg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/pg-bootstrap-lg-pg" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).pg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).pg.h' }

        propertydefinition {
            name = "output",
            kind = "string",
            display = "Output File Name",
            description = "Specify the file for the parser implementation file. --output=value",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).pg.cpp",
            switch = " "
        }
        propertydefinition {
            name = "header",
            kind = "string",
            display = "Output header File Name",
            description = "Specify the file for the parser implementation file. --output=value",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).pg.h",
            switch = " "
        }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }

group "self-bootstrap"

    project "lg-generate-bootstrap"
        location "build/bootstrap/self-bootstrap/lg-generate-bootstrap"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { ".", "include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/self-bootstrap/lg-generate-bootstrap/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "LexicalAnalyser",
            "Generator",
            "lg-bootstrap-lg-pg",
            "pg-bootstrap-lg-pg"
        }

        rules {
            "lg_bootstrap_lg_pg",
            "pg_bootstrap_lg_pg"
        }

        files {
            "src/bootstrap/self-bootstrap/lg-generate-bootstrap/lg.lg",
            "src/bootstrap/self-bootstrap/lg-generate-bootstrap/lg.lg.h",
            "src/bootstrap/self-bootstrap/lg-generate-bootstrap/lg.pg",
            "src/bootstrap/self-bootstrap/lg-generate-bootstrap/lg.pg.h",
            "src/bootstrap/self-bootstrap/lg-generate-bootstrap/main.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/LexicalAnalyserGenerator.lib",
            "bin/%{cfg.buildcfg}/Generator.lib"
        }

        debugargs { "\"$(SolutionDir)../src/bootstrap/self-bootstrap/lg-bootstrap-lg/lg.lg\"" }

    rule "lg_generate_bootstrap"
        location "build/bootstrap/self-bootstrap/lg-generate-bootstrap"

        display "lg-generate-bootstrap"
        fileextension { ".lg" }

        buildmessage 'Compiling %(Filename) with lg-generate-bootstrap'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/lg-generate-bootstrap" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).lexer.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).lexer.h' }

        propertydefinition {
            name = "output",
            kind = "string",
            display = "Output File Name",
            description = "Specify the file for the parser lexer file.",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).lexer.cpp",
            switch = ""
        }
        propertydefinition {
            name = "header",
            kind = "string",
            display = "Output header File Name",
            description = "Specify the neader file for the lexer implementation file.",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).lexer.h",
            switch = ""
        }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }


    project "pg-generate-bootstrap"
        location "build/bootstrap/self-bootstrap/pg-generate-bootstrap"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/self-bootstrap/pg-generate-bootstrap/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "Grammar",
            "ParserGenerator",
            "lg-bootstrap-lg-pg",
            "pg-bootstrap-lg-pg"
        }

        rules {
            "lg_bootstrap_lg_pg",
            "pg_bootstrap_lg_pg"
        }

        files {
            "src/bootstrap/self-bootstrap/pg-generate-bootstrap/pg.lg",
            "src/bootstrap/self-bootstrap/pg-generate-bootstrap/pg.lg.h",
            "src/bootstrap/self-bootstrap/pg-generate-bootstrap/pg.pg",
            "src/bootstrap/self-bootstrap/pg-generate-bootstrap/pg.pg.h",
            "src/bootstrap/self-bootstrap/pg-generate-bootstrap/main.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/Grammar.lib",
            "bin/%{cfg.buildcfg}/ParserGenerator.lib"
        }

        debugargs { "\"$(SolutionDir)../src/bootstrap/self-bootstrap/pg-bootstrap-pg/pg.pg\"" }

    rule "pg_generate_bootstrap"
        location "build/bootstrap/self-bootstrap/pg-generate-bootstrap"

        display "pg-generate-bootstrap"
        fileextension { ".pg" }

        buildmessage 'Compiling %(Filename) with pg-generate-bootstrap'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/pg-generate-bootstrap" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).parser.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).parser.h' }

        propertydefinition {
            name = "output",
            kind = "string",
            display = "Output File Name",
            description = "Specify the file for the parser implementation file.",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).parser.cpp",
            switch = ""
        }
        propertydefinition {
            name = "header",
            kind = "string",
            display = "Output header File Name",
            description = "Specify the neader file for the parser implementation file.",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).parser.h",
            switch = ""
        }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }

    project "lg-bootstrap-lg"
        location "build/bootstrap/self-bootstrap/lg-bootstrap-lg"

        kind "ConsoleApp"

        language "C++"

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/self-bootstrap/lg-bootstrap-lg/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "LexicalAnalyser",
            "Generator",
            "lg-generate-bootstrap"
        }

        rules {
            "lg_generate_bootstrap"
        }

        files {
            "src/bootstrap/self-bootstrap/lg-bootstrap-lg/lg.lg",
            "src/bootstrap/self-bootstrap/lg-bootstrap-lg/main.cpp"
        }
        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/LexicalAnalyserGenerator.lib",
            "bin/%{cfg.buildcfg}/Generator.lib"
        }

        debugargs { "\"$(SolutionDir)../src/bootstrap/self-bootstrap/lg-bootstrap/lg.lg\"" }

    rule "lg_bootstrap_lg"
        location "build/bootstrap/self-bootstrap/lg-bootstrap-lg"

        display "lg-bootstrap-lg"
        fileextension { ".lg" }

        buildmessage 'Compiling %(Filename) with lg-bootstrap-lg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/lg-bootstrap-lg" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).lg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).lg.h' }

        propertydefinition {
            name = "output",
            kind = "string",
            display = "Output File Name",
            description = "Specify the file for the parser implementation file.",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).lg.cpp",
            switch = ""
        }
        propertydefinition {
            name = "header",
            kind = "string",
            display = "Output header File Name",
            description = "Specify the neader file for the parser implementation file.",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).lg.h",
            switch = ""
        }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }

    project "pg-bootstrap-lg"
        location "build/bootstrap/self-bootstrap/pg-bootstrap-lg"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/self-bootstrap/pg-bootstrap-lg/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "Grammar",
            "ParserGenerator",
            "pg-generate-bootstrap"
        }

        rules {
            "pg_generate_bootstrap"
        }

        files {
            "src/bootstrap/self-bootstrap/pg-bootstrap-lg/lg.pg",
            "src/bootstrap/self-bootstrap/pg-bootstrap-lg/lg.pg.h",
            "src/bootstrap/self-bootstrap/pg-bootstrap-lg/main.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/Grammar.lib",
            "bin/%{cfg.buildcfg}/ParserGenerator.lib"
        }

        debugargs { "\"$(SolutionDir)../src/bootstrap/self-bootstrap/lg-bootstrap/lg.pg\"" }

    rule "pg_bootstrap_lg"
        location "build/bootstrap/self-bootstrap/pg-bootstrap-lg"

        display "pg-bootstrap-lg"
        fileextension { ".pg" }

        buildmessage 'Compiling %(Filename) with pg-bootstrap-lg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/pg-bootstrap-lg" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).pg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).pg.h' }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives. (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }

    project "lg-bootstrap-pg"
        location "build/bootstrap/self-bootstrap/lg-bootstrap-pg"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/self-bootstrap/lg-bootstrap-pg/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "LexicalAnalyser",
            "Generator",
            "lg-generate-bootstrap"
        }

        rules {
            "lg_generate_bootstrap"
        }

        files {
            "src/bootstrap/self-bootstrap/lg-bootstrap-pg/pg.lg",
            "src/bootstrap/self-bootstrap/lg-bootstrap-pg/pg.lg.h",
            "src/bootstrap/self-bootstrap/lg-bootstrap-pg/main.cpp"
        }
        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/LexicalAnalyserGenerator.lib",
            "bin/%{cfg.buildcfg}/Generator.lib"
        }

        debugargs { "\"$(SolutionDir)../src/bootstrap/self-bootstrap/pg-bootstrap/pg.lg\"" }

    rule "lg_bootstrap_pg"
        location "build/bootstrap/self-bootstrap/lg-bootstrap-pg"

        display "lg-bootstrap-pg"
        fileextension { ".lg" }

        buildmessage 'Compiling %(Filename) with lg-bootstrap-pg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/lg-bootstrap-pg" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).lg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).lg.h' }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives. (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }

    project "pg-bootstrap-pg"
        location "build/bootstrap/self-bootstrap/pg-bootstrap-pg"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/self-bootstrap/pg-bootstrap-pg/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "Grammar",
            "ParserGenerator",
            "pg-generate-bootstrap"
        }

        rules {
            "pg_generate_bootstrap"
        }

        files {
            "src/bootstrap/self-bootstrap/pg-bootstrap-pg/pg.pg",
            "src/bootstrap/self-bootstrap/pg-bootstrap-pg/main.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/Grammar.lib",
            "bin/%{cfg.buildcfg}/ParserGenerator.lib"
        }

        debugargs { "\"$(SolutionDir)../src/bootstrap/self-bootstrap/pg-bootstrap/pg.pg\"" }

    rule "pg_bootstrap_pg"
        location "build/bootstrap/self-bootstrap/pg-bootstrap-pg"

        display "pg-bootstrap-pg"
        fileextension { ".pg" }

        buildmessage 'Compiling %(Filename) with pg-bootstrap-pg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/pg-bootstrap-pg" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).pg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).pg.h' }

        propertydefinition {
            name = "output",
            kind = "string",
            display = "Output File Name",
            description = "Specify the file for the parser implementation file. --output=value",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).pg.cpp",
            switch = ""
        }
        propertydefinition {
            name = "header",
            kind = "string",
            display = "Output header File Name",
            description = "Specify the file for the parser implementation file. --output=value",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).pg.h",
            switch = ""
        }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }

    project "lg-bootstrap"
        location "build/bootstrap/flex-bison-bootstrap/lg-bootstrap"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/flex-bison-bootstrap/lg-bootstrap/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "LexicalAnalyser",
            "Generator",
            "lg-bootstrap-lg",
            "pg-bootstrap-lg"
        }

        rules {
            "lg_bootstrap_lg",
            "pg_bootstrap_lg"
        }

        files {
            "src/bootstrap/self-bootstrap/lg-bootstrap/lg.lg",
            "src/bootstrap/self-bootstrap/lg-bootstrap/lg.lg.h",
            "src/bootstrap/self-bootstrap/lg-bootstrap/lg.pg",
            "src/bootstrap/self-bootstrap/lg-bootstrap/lg.pg.h",
            "src/bootstrap/self-bootstrap/lg-bootstrap/main.cpp"
        }
        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/LexicalAnalyserGenerator.lib",
            "bin/%{cfg.buildcfg}/Generator.lib"
        }

        debugargs { "\"$(SolutionDir)../src/bootstrap/self-bootstrap/lg-self-bootstrap-lg-pg/lg.pg\"" }

    rule "lg_bootstrap"
        location "build/bootstrap/self-bootstrap/lg-bootstrap"

        display "lg-bootstrap"
        fileextension { ".lg" }

        buildmessage 'Compiling %(Filename) with lg-bootstrap'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/lg-bootstrap" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).lg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).lg.h' }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }


    project "pg-bootstrap"
        location "build/bootstrap/flex-bison-bootstrap/pg-bootstrap"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/self-bootstrap/pg-bootstrap/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "Grammar",
            "ParserGenerator",
            "lg-bootstrap-pg",
            "pg-bootstrap-pg"
        }

        rules {
            "lg_bootstrap_pg",
            "pg_bootstrap_pg"
        }

        files {
            "src/bootstrap/self-bootstrap/pg-bootstrap/pg.lg",
            "src/bootstrap/self-bootstrap/pg-bootstrap/pg.lg.h",
            "src/bootstrap/self-bootstrap/pg-bootstrap/pg.pg",
            "src/bootstrap/self-bootstrap/pg-bootstrap/pg.pg.h",
            "src/bootstrap/self-bootstrap/pg-bootstrap/main.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/Grammar.lib",
            "bin/%{cfg.buildcfg}/ParserGenerator.lib"
        }

        debugargs { "\"$(SolutionDir)../src/bootstrap/self-bootstrap/pg-self-bootstrap/pg.pg\"" }

    rule "pg_bootstrap"
        location "build/bootstrap/self-bootstrap/pg-bootstrap"

        display "pg-bootstrap"
        fileextension { ".pg" }

        buildmessage 'Compiling %(Filename) with pg-bootstrap'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/pg-bootstrap" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).pg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).pg.h' }

        propertydefinition {
            name = "output",
            kind = "string",
            display = "Output File Name",
            description = "Specify the file for the parser implementation file. --output=value",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).pg.cpp",
            switch = ""
        }
        propertydefinition {
            name = "header",
            kind = "string",
            display = "Output header File Name",
            description = "Specify the file for the parser implementation file. --output=value",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).pg.h",
            switch = ""
        }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }

    project "lg-self-bootstrap-lg-pg"
        location "build/bootstrap/self-bootstrap/lg-self-bootstrap-lg-pg"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/self-bootstrap/lg-self-bootstrap-lg-pg/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "LexicalAnalyser",
            "Generator",
            "lg-bootstrap",
            "pg-bootstrap"
        }

        rules {
            "lg_bootstrap",
            "pg_bootstrap"
        }

        files {
            "src/bootstrap/self-bootstrap/lg-self-bootstrap-lg-pg/lg.lg",
            "src/bootstrap/self-bootstrap/lg-self-bootstrap-lg-pg/lg.lg.h",
            "src/bootstrap/self-bootstrap/lg-self-bootstrap-lg-pg/lg.pg",
            "src/bootstrap/self-bootstrap/lg-self-bootstrap-lg-pg/lg.pg.h",
            "src/bootstrap/self-bootstrap/lg-self-bootstrap-lg-pg/main.cpp"
        }
        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/LexicalAnalyserGenerator.lib",
            "bin/%{cfg.buildcfg}/Generator.lib"
        }

    rule "lg_self_bootstrap_lg_pg"
        location "build/bootstrap/self-bootstrap/lg-self-bootstrap-lg-pg"

        display "lg-self-bootstrap-lg-pg"
        fileextension { ".lg" }

        buildmessage 'Compiling %(Filename) with lg-self-bootstrap-lg-pg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/lg-self-bootstrap-lg-pg" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).lg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).lg.h' }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }


    project "pg-self-bootstrap-lg-pg"
        location "build/bootstrap/self-bootstrap/pg-self-bootstrap-lg-pg"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/bootstrap/self-bootstrap/pg-self-bootstrap-lg-pg/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "Grammar",
            "ParserGenerator",
            "lg-bootstrap",
            "pg-bootstrap"
        }

        rules {
            "lg_bootstrap",
            "pg_bootstrap"
        }

        files {
            "src/bootstrap/self-bootstrap/pg-self-bootstrap-lg-pg/pg.lg",
            "src/bootstrap/self-bootstrap/pg-self-bootstrap-lg-pg/pg.lg.h",
            "src/bootstrap/self-bootstrap/pg-self-bootstrap-lg-pg/pg.pg",
            "src/bootstrap/self-bootstrap/pg-self-bootstrap-lg-pg/pg.pg.h",
            "src/bootstrap/self-bootstrap/pg-self-bootstrap-lg-pg/main.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/Grammar.lib",
            "bin/%{cfg.buildcfg}/ParserGenerator.lib"
        }

    rule "pg_self_bootstrap_lg_pg"
        location "build/bootstrap/self-bootstrap/pg-self-bootstrap-lg-pg"

        display "pg-self-bootstrap-lg-pg"
        fileextension { ".pg" }

        buildmessage 'Compiling %(Filename) with pg-self-bootstrap-lg-pg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/pg-self-bootstrap-lg-pg" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).pg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).pg.h' }

        propertydefinition {
            name = "output",
            kind = "string",
            display = "Output File Name",
            description = "Specify the file for the parser implementation file.",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).pg.cpp",
            switch = ""
        }
        propertydefinition {
            name = "header",
            kind = "string",
            display = "Output header File Name",
            description = "Specify the file for the parser implementation file.",
            value = "$(HOMEDRIVE)/%(Directory)%(Filename).pg.h",
            switch = ""
        }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }

group "unittests"

    project "unittests"

        location "build/unittests"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "../include", "../../include", ".", "../gtest-1.7.0 - premake/include" }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/unittests/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "Runtime",
            "g-lib",
            "LexicalAnalyserGenerator",
            "Generator",
            "ParserGenerator"
        }

        files {
            "unittests/*.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/LexicalAnalyserGenerator.lib",
            "bin/%{cfg.buildcfg}/Generator.lib",
            "bin/%{cfg.buildcfg}/Grammar.lib",
            "bin/%{cfg.buildcfg}/ParserGenerator.lib",
            "../gtest-1.7.0 - premake/bin/%{cfg.buildcfg}/gtest.lib"

        }

group "tools"

    project "lg"
        location "build/tools/lg"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/tools/lg/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "LexicalAnalyser",
            "Generator",
            "lg-self-bootstrap-lg-pg",
            "pg-self-bootstrap-lg-pg"
        }

        rules {
            "lg_self_bootstrap_lg_pg",
            "pg_self_bootstrap_lg_pg"
        }

        files {
            "src/tools/lg/lg.lg",
            "src/tools/lg/lg.lg.h",
            "src/tools/lg/lg.pg",
            "src/tools/lg/lg.pg.h",
            "src/tools/lg/main.cpp"
        }
        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/LexicalAnalyserGenerator.lib",
            "bin/%{cfg.buildcfg}/Generator.lib"
        }

    rule "lg"
        location "build/tools/lg"

        display "lg"
        fileextension { ".lg" }

        buildmessage 'Compiling %(Filename) with lg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/lg" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).lg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).lg.h' }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }


    project "pg"
        location "build/tools/pg"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/tools/pg/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "Grammar",
            "ParserGenerator",
            "lg-self-bootstrap-lg-pg",
            "pg-self-bootstrap-lg-pg",
            "lg"
        }

        rules {
            "lg_self_bootstrap_lg_pg",
            "pg_self_bootstrap_lg_pg"
        }

        files {
            "src/tools/pg/pg.lg",
            "src/tools/pg/pg.lg.h",
            "src/tools/pg/pg.pg",
            "src/tools/pg/pg.pg.h",
            "src/tools/pg/main.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/Grammar.lib",
            "bin/%{cfg.buildcfg}/ParserGenerator.lib"
        }

    rule "pg"
        location "build/tools/pg"

        display "pg"
        fileextension { ".pg" }

        buildmessage 'Compiling %(Filename) with pg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/pg" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).pg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).pg.h' }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }

    project "ag"
        location "build/tools/pg"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/tools/ag/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "Grammar",
            "AbstractSyntaxTreeGenerator",
            "lg",
            "pg"
        }

        rules {
            "lg",
            "pg"
        }

        files {
            "src/tools/ag/AbstractSyntaxTreeGenerator.h",
            "src/tools/ag/AbstractSyntaxTreeGenerator.cpp",
            "src/tools/ag/ag.lg",
            "src/tools/ag/ag.lg.h",
            "src/tools/ag/ag.pg",
            "src/tools/ag/ag.pg.h",
            "src/tools/ag/main.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/Grammar.lib",
--                "bin/%{cfg.buildcfg}/AbstractSyntaxTreeGenerator.lib"
        }

    rule "ag"
        location "build/tools/pg"

        display "ag"
        fileextension { ".ag" }

        buildmessage 'Compiling %(Filename) with ag'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/ag" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).ag.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).ag.h' }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }

    project "g"
        location "build/tools/g"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/tools/g/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "Grammar",
            "ParserGenerator",
            "lg",
            "pg"
        }

        rules {
            "lg",
            "pg"
        }

        files {
            "src/tools/g/g.lg",
            "src/tools/g/g.lg.h",
            "src/tools/g/g.pg",
            "src/tools/g/g.pg.h",
            "src/tools/g/main.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/Grammar.lib",
            "bin/%{cfg.buildcfg}/ParserGenerator.lib"
        }

    rule "g"
        location "build/tools/g"

        display "g"
        fileextension { ".g" }

        buildmessage 'Compiling %(Filename) with g'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/g" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).g.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).g.h' }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }

    project "ttg"
        location "build/tools/ttg"

        kind "ConsoleApp"

        language "C++"
        characterset ("MBCS")

        includedirs { "include", "." }

        targetdir "bin/%{cfg.buildcfg}"
        objdir "bin/obj/g/tools/ttg/%{cfg.buildcfg}"

        dependson {
            "nonstd",
            "g-lib",
            "Runtime",
            "Grammar",
            "TextualTemplateGenerator",
            "lg",
            "pg"
        }

        rules {
            "lg",
            "pg"
        }

        files {
            "src/tools/ttg/TextualTemplateGenerator.h",
            "src/tools/ttg/TextualTemplateGenerator.cpp",
            "src/tools/ttg/ttg.lg",
            "src/tools/ttg/ttg.lg.h",
            "src/tools/ttg/ttg.pg",
            "src/tools/ttg/ttg.pg.h",
            "src/tools/ttg/main.cpp"
        }

        links {
            "bin/%{cfg.buildcfg}/nonstd.lib",
            "bin/%{cfg.buildcfg}/g-lib.lib",
            "bin/%{cfg.buildcfg}/Runtime.lib",
            "bin/%{cfg.buildcfg}/Grammar.lib",
            "bin/%{cfg.buildcfg}/TextualTemplateGenerator.lib"
        }

    rule "ttg"
        location "build/tools/ttg"

        display "ttg"
        fileextension { ".ttg" }

        buildmessage 'Compiling %(Filename) with ttg'
        buildcommands '"$(SolutionDir)../bin/$(Configuration)/ttg" [debug] [noline] "%(FullPath)"'
        buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).ttg.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).ttg.h' }

        propertydefinition {
            name = "noline",
            kind = "boolean",
            display = "No #line Directives",
            description = "Instructs lg not to generate #line directives.            (--noline)",
            value = false,
            switch = "--noline"
        }
        propertydefinition {
            name = "debug",
            kind = "boolean",
            display = "Debug Mode",
            description = "Makes the generated scanner run in debug mode.",
            value = false,
            switch = "--debug"
        }

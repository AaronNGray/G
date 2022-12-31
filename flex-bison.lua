rule "flex"
    location "build/bootstrap/flex-bison-bootstrap"

    display "flex"
    fileextension { ".l", ".flex" }

    buildmessage 'Compiling %(Filename) with flex'
    buildcommands 'win_flex [debug] [noline] [outfile] "%(FullPath)"'
    buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).flex.cpp' }

    propertydefinition {
        name = "outfile",
        kind = "string",
        display = "Output File Name",
        description = "Specify the file for the parser implementation file. --output=value",
        value = "$(HOMEDRIVE)/%(Directory)%(Filename).flex.cpp",
        switch = "--outfile=&quot;[value]&quot;"
    }
    propertydefinition {
        name = "noline",
        kind = "boolean",
        display = "No #line Directives",
        description = "Instructs flex not to generate #line directives.            (--noline)",
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

rule "bison"
    location "build/bootstrap/flex-bison-bootstrap"

    display "bison"
    fileextension { ".y", ".bison" }

    buildmessage 'Compiling %(Filename) with bison'
    buildcommands 'win_bison [debug] [nolines] [output] [defines] "%(FullPath)"'
    buildoutputs { '$(HOMEDRIVE)/%(Directory)%(Filename).tab.cpp', '$(HOMEDRIVE)/%(Directory)%(Filename).tab.h' }

    propertydefinition {
        name = "defines",
        kind = "string",
        display = "Defines File Name",
        description = "Pretend that %defines was specified, i.e., write an extra output file containing macro definitions for the token type names defined in the grammar, as well as a few other declarations. --defines=value",
        value = "$(HOMEDRIVE)/%(Directory)%(Filename).tab.h",
        switch = "--defines=&quot;[value]&quot;"
    }
    propertydefinition {
        name = "output",
        kind = "string",
        display = "Output File Name",
        description = "Specify the file for the parser implementation file. --output=value",
        value = "$(HOMEDRIVE)/%(Directory)%(Filename).tab.cpp",
        switch = "--output=&quot;[value]&quot;"
    }
    propertydefinition {
        name = "nolines",
        kind = "boolean",
        display = "No #line Directives",
        description = "Instructs flex not to generate #line directives.            (--no-lines)",
        value = false,
        switch = "--no-lines"
    }
    propertydefinition {
        name = "debug",
        kind = "boolean",
        display = "Debug Mode",
        description = "In the parser implementation file, define the macro YYDEBUG to 1 if it is not already defined, so that the debugging facilities are compiled. (--debug)",
        value = false,
        switch = "--debug"
    }

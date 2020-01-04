import qbs
//TODO: find path to the libraries on win and macos too

Module {
    Depends { name: "cpp" }

    Properties {
        condition: qbs.targetOS.contains("linux")
        cpp.defines: ["ON_LINUX"]
        cpp.includePaths: ["/usr/include"]
        cpp.dynamicLibraries: ["/usr/lib/x86_64-linux-gnu/libboost_program_options.so"]
    }
    Properties {
        condition: qbs.targetOS.contains("windows")
        cpp.defines: ["ON_WINDOWS"]
        //cpp.includePaths: [""]
        //cpp.dynamicLibraries: [""]
    }
    Properties {
        condition: qbs.targetOS.contains("macos")
        cpp.defines: ["ON_MACOS"]
        //cpp.includePaths: [""]
        //cpp.dynamicLibraries: [""]
    }
}

import qbs

Module {
    Depends { name: "cpp" }

    Properties {
        condition: qbs.targetOS.contains("linux")
        cpp.defines: ["ON_LINUX"]
        cpp.includePaths: ["/usr/include"]
    }
    Properties {
        condition: qbs.targetOS.contains("macos")
        cpp.defines: ["ON_MACOS"]
        cpp.includePaths: ["/usr/local/Cellar"]
    }
}
import qbs
Project {
    StaticLibrary {
        Depends { name: "cpp" }
        name: "headers"
        cpp.includePaths: product.sourceDirectory
        files: [
            "package.h",
            "station.h",
            "train.h",
            "wagon.h"
        ]
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: product.sourceDirectory
       }
    }
}

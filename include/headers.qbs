import qbs
Project {
    StaticLibrary {
        Depends { name: "cpp" }
        name: "headers"
        cpp.includePaths: product.sourceDirectory
        files: [
            "package.hpp",
            "station.hpp",
            "train.hpp",
            "wagon.hpp"
        ]
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: product.sourceDirectory
       }
    }
}

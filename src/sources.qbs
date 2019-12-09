import qbs
Project {
    StaticLibrary {
        Depends { name: "cpp" }
	Depends { name: "headers" }
        name: "sources"
        cpp.includePaths: product.sourceDirectory
        files: [
            "mypackage.hpp",
            "mystation.hpp",
            "mytrain.hpp",
            "mywagon.hpp",
            "mypackage.cpp",
            "mystation.cpp",
            "mytrain.cpp",
            "mywagon.cpp"
        ]
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: product.sourceDirectory
       }
    }
}

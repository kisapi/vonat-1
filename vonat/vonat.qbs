import qbs

Project {
    minimumQbsVersion: "1.7.1"

    CppApplication {
        cpp.cxxLanguageVersion: "c++14"
        cpp.enableRtti: "true"
        consoleApplication: true
        files: "main.cpp"

        Group {     // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
        }
        Depends { name: "headers" }
        Depends { name: "sources" }
    }
    SubProject {
        filePath: "../include/headers.qbs"
        Properties {
            name: "Headers"
        }
    }
    SubProject {
        filePath: "../src/sources.qbs"
        Properties {
            name: "Sources"
        }
    }
}

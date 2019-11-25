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
        Depends {name: "headers"}
    }
    SubProject {
        filePath: "../include/headers.qbs"
        Properties {
            name: "Headers"
        }
    }
}

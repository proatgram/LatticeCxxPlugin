module;

#include <cstdlib>
#include <yaml-cpp/yaml.h>

module LatticeCxxPlugin.CxxToolchain;

import LatticeCxxPlugin.CxxLibrary;
import LatticeCxxPlugin.CxxBinary;

import Lattice.Registry;

using namespace LatticeCxxPlugin;


CxxToolchain::CxxToolchain(Lattice::Object::IToolchain::Constructable constructable, const std::string &identifier) :
    Lattice::Object::IToolchain(constructable, identifier) {}


auto CxxToolchain::ProvidesImpl(const std::type_index &type) const -> bool {
    if (type == typeid(std::shared_ptr<CxxLibraryFactory::FactoryType>) ||
        type == typeid(std::shared_ptr<CxxBinaryFactory::FactoryType>))

        return true;

    return false;
}

auto CxxToolchain::GetImpl(const std::type_index &type) const -> std::optional<std::any> {
    if (!ProvidesImpl(type))
        return {};

    if (type == typeid(std::shared_ptr<CxxLibraryFactory::FactoryType>)) {
        return CxxLibraryFactory::GetInstance();
    } else if (type == typeid(std::shared_ptr<CxxBinaryFactory::FactoryType>)) {
        return CxxBinaryFactory::GetInstance();
    }


    return {};
}
 
CxxToolchainFactory::CxxToolchainFactory(Constructable) {
    SetSupportedLanguages({"c", "cc", "C", "CC", "cpp", "cxx", "c++", "Cpp", "Cxx", "C++", "CPP", "CXX"});
}

auto CxxToolchainFactory::Create(const std::string &identifier, const std::optional<std::string> &objectData) -> std::shared_ptr<Lattice::Object::IToolchain> {
    std::shared_ptr<CxxToolchain> cxxToolchain = std::make_shared<CxxToolchain>(CxxToolchain::Constructable(), identifier);

    cxxToolchain->SetSupportedLanguages({"c", "cc", "C", "CC", "cpp", "cxx", "c++", "Cpp", "Cxx", "C++", "CPP", "CXX"});

    return cxxToolchain;
}
auto FindFile(const std::set<std::string> &filenames) -> std::optional<std::filesystem::path> {
#if defined _WIN
        static_assert(false);
#elif defined __linux__
    if (const char *pathEnvcstr = getenv("PATH"); pathEnvcstr) {
        std::string pathEnv(pathEnvcstr);
        
        std::size_t previousIndex = 0;
        std::size_t index = pathEnv.find_first_of(':');
        while (index != std::string::npos) {
            std::filesystem::path path = pathEnv.substr(previousIndex, index - previousIndex);

            if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
                for (const auto &file : std::filesystem::recursive_directory_iterator(path)) {
                    if (file.is_regular_file()) {
                        if (filenames.contains(file.path().filename()))
                            return file.path();
                    }
                }
            }

            previousIndex = index + 1;
            index = pathEnv.find(':', previousIndex);
        }

    }
#endif
    return {};
}


auto LatticeCxxPlugin::SetupDefaultCcToolchain() -> void {
    std::string compilerPath;
    std::string compilerName;
    std::string defaultToolchainId;
    if (const char *cxxEnv = getenv("CC"); cxxEnv) {
        compilerPath = cxxEnv;

        if (!std::filesystem::exists(compilerPath)) {
            compilerName = compilerPath;
            std::optional<std::filesystem::path> path = FindFile({compilerPath});

            if (!path.has_value()) {
                std::cout << "WARN: Unable to find the compiler specified in $CC: " << compilerName << '.' << std::endl;
                return;
            }

            compilerPath = path.value();

        } else {
            compilerName = std::filesystem::path(compilerPath).filename().string();
        }

        defaultToolchainId = std::format("{}-default", compilerName);
    } else {
        std::optional<std::filesystem::path> pathToCompiler = FindFile({"gcc", "clang"});
        if (!pathToCompiler.has_value())
            return; // Unable to get a default compiler without finding executables :/

        compilerPath = pathToCompiler->string();
        compilerName = pathToCompiler->filename();
        defaultToolchainId = std::format("{}-default", compilerName);

    }

    YAML::Node compilerConfig;

    compilerConfig["toolchain"][compilerName]["compiler"] = compilerName;
    compilerConfig["toolchain"][compilerName]["languages"] = std::list<std::string>{{"c", "cc", "C", "CC"}};
    compilerConfig["toolchain"][compilerName]["paths"]["compiler"] = compilerPath;
    compilerConfig["toolchain"][compilerName]["flags"]["compiler"] = 
        std::list<std::string>{
            "-Wall",
            "-Wextra",
            "-Wpedantic",
            "-O2"
        };

    Lattice::Registry::GetInstance()->Register<std::shared_ptr<Lattice::Object::IToolchain>>(defaultToolchainId, CxxToolchainFactory::GetInstance()->Create(defaultToolchainId, YAML::Dump(compilerConfig)));

    Lattice::Registry::GetInstance()->Register<LatticeCxxPlugin::ToolchainDefault>("cxx-plugin-default-cc", {
        .toolchainID = defaultToolchainId,
        .fileExtentions = {".cc", ".c", ".h"}
    });
}

auto LatticeCxxPlugin::SetupDefaultCxxToolchain() -> void {
    std::string compilerPath;
    std::string compilerName;
    std::string defaultToolchainId;
    if (const char *cxxEnv = getenv("CXX"); cxxEnv) {
        compilerPath = cxxEnv;

        if (!std::filesystem::exists(compilerPath)) {
            compilerName = compilerPath;
            std::optional<std::filesystem::path> path = FindFile({compilerPath});

            if (!path.has_value()) {
                std::cout << "WARN: Unable to find the compiler specified in $CXX: " << compilerName <<  '.' << std::endl;
                return;
            }

            compilerPath = path.value();

        } else {
            compilerName = std::filesystem::path(compilerPath).filename().string();
        }

        defaultToolchainId = std::format("{}-default", compilerName);
    } else {
        std::optional<std::filesystem::path> pathToCompiler = FindFile({"g++", "clang++"});
        if (!pathToCompiler.has_value())
            return; // Unable to get a default compiler without finding executables :/

        compilerPath = pathToCompiler->string();
        compilerName = pathToCompiler->filename();
        defaultToolchainId = std::format("{}-default", compilerName);

    }

    YAML::Node compilerConfig;

    compilerConfig["toolchain"][compilerName]["compiler"] = compilerName;
    compilerConfig["toolchain"][compilerName]["languages"] = std::list<std::string>{"cpp", "cxx", "c++", "Cpp", "Cxx", "C++", "CPP", "CXX"};
    compilerConfig["toolchain"][compilerName]["paths"]["compiler"] = compilerPath;
    compilerConfig["toolchain"][compilerName]["flags"]["compiler"] = 
        std::list<std::string>{
            "-std=c++17",
            "-pipes",
            "-Wall",
            "-Wextra",
            "-Wpedantic",
            "-O2"
        };

    Lattice::Registry::GetInstance()->Register<std::shared_ptr<Lattice::Object::IToolchain>>(defaultToolchainId, CxxToolchainFactory::GetInstance()->Create(defaultToolchainId, YAML::Dump(compilerConfig)));

    Lattice::Registry::GetInstance()->Register<LatticeCxxPlugin::ToolchainDefault>("cxx-plugin-default-cxx", {
        .toolchainID = defaultToolchainId,
        .fileExtentions = {".cpp", ".cxx", ".hpp", ".cppm"}
    });
}

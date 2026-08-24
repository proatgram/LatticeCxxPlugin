module LatticeCxxPlugin.CxxToolchain;

import LatticeCxxPlugin.CxxLibrary;
import LatticeCxxPlugin.CxxBinary;

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

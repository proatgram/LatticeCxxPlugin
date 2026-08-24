module LatticeCxxPlugin.CxxToolchain;

using namespace LatticeCxxPlugin;

CxxToolchain::CxxToolchain(Lattice::Object::IToolchain::Constructable constructable, const std::string &identifier) :
    Lattice::Object::IToolchain(constructable, identifier){}

CxxToolchainFactory::CxxToolchainFactory(Constructable) {
    SetSupportedLanguages({"c", "cc", "C", "CC", "cpp", "cxx", "c++", "Cpp", "Cxx", "C++", "CPP", "CXX"});
}

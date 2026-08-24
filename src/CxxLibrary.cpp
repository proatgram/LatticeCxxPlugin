module LatticeCxxPlugin.CxxLibrary;

using namespace LatticeCxxPlugin;

CxxLibrary::CxxLibrary(Constructable constructable, const std::string &identifier) :
    Lattice::Object::ILibrary(constructable, identifier) {}

CxxLibraryFactory::CxxLibraryFactory(Constructable) {}

auto CxxLibraryFactory::Create(const std::string &identifier, const std::optional<std::string> &objectData) -> std::shared_ptr<Lattice::Object::ILibrary> {
    std::shared_ptr<CxxLibrary> cxxLibrary = std::make_shared<CxxLibrary>(CxxLibrary::Constructable(), identifier);

    return cxxLibrary;
}

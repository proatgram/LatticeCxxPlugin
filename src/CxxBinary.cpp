module LatticeCxxPlugin.CxxBinary;

using namespace LatticeCxxPlugin;

CxxBinary::CxxBinary(Constructable constructable, const std::string &identifier) :
    Lattice::Object::IBinary(constructable, identifier) {}

CxxBinaryFactory::CxxBinaryFactory(Constructable) {}

auto CxxBinaryFactory::Create(const std::string &identifier, const std::optional<std::string> &obejctData) -> std::shared_ptr<Lattice::Object::IBinary> {
    std::shared_ptr<CxxBinary> cxxBinary = std::make_shared<CxxBinary>(CxxBinary::Constructable(), identifier);

    return cxxBinary;
}

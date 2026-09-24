module LatticeCxxPlugin.CxxBinary;

using namespace LatticeCxxPlugin;

CxxBinary::CxxBinary(Constructable constructable, const std::string &identifier) :
    Lattice::Object::IBinary(constructable, identifier) {}

auto CxxBinary::Configure() -> void {
    AddStep(Step::Create(shared_from_this()->GetCapability<Schedulable>().value(), []() -> bool {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return true;
    }, "id", StepDescription("Testing", "building")));
}

CxxBinaryFactory::CxxBinaryFactory(Constructable) {}

auto CxxBinaryFactory::Create(const std::string &identifier, const std::optional<std::string> &obejctData) -> std::shared_ptr<Lattice::Object::IBinary> {
    std::shared_ptr<CxxBinary> cxxBinary = std::make_shared<CxxBinary>(CxxBinary::Constructable(), identifier);
    
    cxxBinary->Configure();

    return cxxBinary;
}

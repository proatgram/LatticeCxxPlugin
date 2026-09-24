module LatticeCxxPlugin.CxxLibrary;

using namespace LatticeCxxPlugin;

CxxLibrary::CxxLibrary(Constructable constructable, const std::string &identifier) :
    Lattice::Object::ILibrary(constructable, identifier) {}

auto CxxLibrary::Configure() -> void {
    AddStep(Step::Create(shared_from_this()->GetCapability<Schedulable>().value(), []() -> bool {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        return true;
    }, "id", StepDescription("Testing", "building")));
}

CxxLibraryFactory::CxxLibraryFactory(Constructable) {}

auto CxxLibraryFactory::Create(const std::string &identifier, const std::optional<std::string> &objectData) -> std::shared_ptr<Lattice::Object::ILibrary> {
    std::shared_ptr<CxxLibrary> cxxLibrary = std::make_shared<CxxLibrary>(CxxLibrary::Constructable(), identifier);

    cxxLibrary->Configure();

    return cxxLibrary;
}

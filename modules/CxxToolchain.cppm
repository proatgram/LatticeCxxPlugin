export module LatticeCxxPlugin.CxxToolchain;

import Lattice.Object.IToolchain;

export namespace LatticeCxxPlugin {
    class CxxToolchain final : public Lattice::Object::IToolchain {
        public:
            CxxToolchain(Lattice::Object::IToolchain::Constructable, const std::string &identifier);

        protected:
            friend class CxxToolchainFactory;

            auto ProvidesImpl(const std::type_index &type) const -> bool override {

                return false;
            }

            auto GetImpl(const std::type_index &type) const -> std::optional<std::any> override {
                if (!ProvidesImpl(type))
                    return {};

                return {};
            }
    };

    class CxxToolchainFactory final : public Lattice::Object::ToolchainFactory<CxxToolchainFactory> {
        public:
            CxxToolchainFactory(Constructable);

            auto Create(const std::string &identifier, const std::optional<std::string> &objectData) -> std::shared_ptr<Lattice::Object::IToolchain> final {
                std::cout << "CxxToolchain being created!" << std::endl;
                std::shared_ptr<CxxToolchain> cxxToolchain = std::make_shared<CxxToolchain>(CxxToolchain::Constructable(), identifier);

                cxxToolchain->SetSupportedLanguages({"c", "cc", "C", "CC", "cpp", "cxx", "c++", "Cpp", "Cxx", "C++", "CPP", "CXX"});

                return cxxToolchain;
            }

        private:
    };
}  // export namespace LatticeCxxPlugin

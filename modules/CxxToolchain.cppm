export module LatticeCxxPlugin.CxxToolchain;

import Lattice.Object.IToolchain;
import Lattice.Object.ILibrary;

export namespace LatticeCxxPlugin {
    using Lattice::Object::ToolchainDefault;

    class CxxToolchain final : public Lattice::Object::IToolchain {
        public:
            CxxToolchain(Lattice::Object::IToolchain::Constructable, const std::string &identifier);

        protected:
            friend class CxxToolchainFactory;

            auto ProvidesImpl(const std::type_index &type) const -> bool final; 
            auto GetImpl(const std::type_index &type) const -> std::optional<std::any> final;
    };

    class CxxToolchainFactory final : public Lattice::Object::ToolchainFactory<CxxToolchainFactory> {
        public:
            CxxToolchainFactory(Constructable);

            auto Create(const std::string &identifier, const std::optional<std::string> &objectData) -> std::shared_ptr<Lattice::Object::IToolchain> final;

        private:
    };

    auto SetupDefaultCcToolchain() -> void;
    auto SetupDefaultCxxToolchain() -> void;
}  // export namespace LatticeCxxPlugin

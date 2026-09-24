export module LatticeCxxPlugin.CxxLibrary;

import std;

import Lattice.Object.ILibrary;
import Lattice.Object.Capabilities.Schedulable;

export namespace LatticeCxxPlugin {
    class CxxLibrary final : public Lattice::Object::ILibrary, public Lattice::Object::Capabilities::Schedulable {
        public:
            CxxLibrary(Constructable, const std::string &identifier);

            auto Configure() -> void final;

        protected:
            friend class CxxLibraryFactory;

        private:
    };

    class CxxLibraryFactory final : public Lattice::Object::LibraryFactory<CxxLibraryFactory> {
        public:
            CxxLibraryFactory(Constructable);

            auto Create(const std::string &identifier, const std::optional<std::string> &objectData = {}) -> std::shared_ptr<Lattice::Object::ILibrary> final;
    };
}

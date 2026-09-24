export module LatticeCxxPlugin.CxxBinary;

import std;

import Lattice.Object.IBinary;
import Lattice.Object.Capabilities.Schedulable;

export namespace LatticeCxxPlugin {
    class CxxBinary final : public Lattice::Object::IBinary, public Lattice::Object::Capabilities::Schedulable {
        public:
            CxxBinary(Constructable, const std::string &identifier);

            auto Configure() -> void final;

        protected:
            friend class CxxBinaryFactory;

        private:
    };

    class CxxBinaryFactory : public Lattice::Object::BinaryFactory<CxxBinaryFactory> {
        public:
            CxxBinaryFactory(Constructable);

            auto Create(const std::string &identifier, const std::optional<std::string> &objectData = {}) -> std::shared_ptr<Lattice::Object::IBinary> final;
    };
}  // export namespace LatticeCxxPlugin

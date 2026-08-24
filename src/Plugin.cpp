module LatticeCxxPlugin.Plugin;

import Lattice.Registry;

import LatticeCxxPlugin.CxxToolchain;
import LatticeCxxPlugin.CxxLibrary;
import LatticeCxxPlugin.CxxBinary;

auto Initialize() -> void {
    Lattice::Registry::GetInstance()->Register<std::shared_ptr<LatticeCxxPlugin::CxxToolchainFactory::FactoryType>>("cxx-toolchain-factory", LatticeCxxPlugin::CxxToolchainFactory::GetInstance());
    Lattice::Registry::GetInstance()->Register<std::shared_ptr<LatticeCxxPlugin::CxxLibraryFactory::FactoryType>>("cxx-library-factory", LatticeCxxPlugin::CxxLibraryFactory::GetInstance());
    Lattice::Registry::GetInstance()->Register<std::shared_ptr<LatticeCxxPlugin::CxxBinaryFactory::FactoryType>>("cxx-binary-factory", LatticeCxxPlugin::CxxBinaryFactory::GetInstance());
}

auto GetID() -> const char* {
    return "cxx-plugin";
}

auto GetPluginVersionSupport() -> Lattice::Plugins::PluginVersionSupport {
    return {
        .targetedLatticeVersion = "0.0.1"
    };
}

extern "C" {
    export auto GetPluginInstance() -> Lattice::Plugins::PluginInstance {
        return {
            .Initialize = &Initialize,
            .GetID = &GetID,
            .GetPluginVersionSupport = &GetPluginVersionSupport
        };
    }
}

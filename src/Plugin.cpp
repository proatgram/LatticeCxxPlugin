module LatticeCxxPlugin.Plugin;

import Lattice.Registry;
import LatticeCxxPlugin.CxxToolchain;

auto Initialize() -> void {
    std::cout << "Initializing C/C++ Plugin!" << std::endl;

    Lattice::Registry::GetInstance()->Register<std::shared_ptr<LatticeCxxPlugin::CxxToolchainFactory::FactoryType>>("cxx-ifactory", LatticeCxxPlugin::CxxToolchainFactory::GetInstance());
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

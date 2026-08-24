export module LatticeCxxPlugin.Plugin;

import Lattice.Plugins.Plugin;

export extern "C" {
    auto GetPluginInstance() -> Lattice::Plugins::PluginInstance;
}

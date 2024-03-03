# <img src="./assets/icon.png" alt="Replication enabler icon" width="32"> Replication enabler

A mod for enabling replication for user created actors in Palworld.

## Why?

Palworld uses a custom optimized replication graph for deciding which actors replicate and which not, this mod detours some functions from it and allows every actor from `/Game/Mods` to replicate if they have replication enabled.

## Usage

Install this mod from [Thunderstore](https://thunderstore.io/c/palworld/p/localcc/ReplicationEnabler/) or from GitHub releases.

If you download the mod from github releases, it should be installed into `Binaries/Win64/Mods`.

### For developers

If you want your actor to replicate with this mod, jsut enable `Replicates` in Unreal Editor, this will make the actor relevant to players who see it. If you want the actor to be always relevant enable the `Always Relevant` option. Other options might not work in the editor (not tested).


## Credits

@yangff - For figuring out a lot of stuff regarding replication
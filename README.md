# Antares

[![Workflow](https://img.shields.io/github/actions/workflow/status/chaserli/Ares-archived/nightly.yml?branch=develop)](https://github.com/chaserli/Ares-archived/actions)
[![license](https://img.shields.io/github/license/chaserli/Ares-archived.svg)](https://www.gnu.org/licenses/gpl-3.0.en.html)

This repo is a gravyard of the source code of [Ares](https://github.com/Ares-Developers/Ares) versions past 0.A.

Save/Load is restored on the branch [Ares0A-SL](https://github.com/chaserli/Ares-archived/tree/Ares0A-SL). No more futher changes compared with Ares 0.A.

Usage
------------------
Syringe targeting your YR executable (usually `gamemd.exe`). **Make sure that `Ares.dll` is NOT present, as Antares by nature is incompatible with Ares!**

You can also get an automatic build. There are two ways to do that.
- **Get an artifact via nightly.link**. This is a service that allows guests to download automatic builds from GitHub. You can get a build for the latest successful (marked with a green tick) `master` branch commit via [this link](https://nightly.link/chaserli/Ares-archived/blob/Ares0A-SL/.github/workflows/build.yml), or get a build for any up-to-date pull request via an automatic comment that would appear in it.
- **Get an artifact manually from GitHub Actions runs**. You can get an artifact for a specific commit which is built automatically with a GitHub Actions workflow, just press on a green tick, open the workflow, find and download the build artifact. This is limited to authorized users only.

Credits
-------
**Ares developer team** - creation of Ares
**AlexB** - development of closed-source Ares past 0.A

Legal
-----

This project as well as Ares has no direct affiliation with Electronic Arts Inc. Command & Conquer, Command & Conquer Red Alert 2, Command & Conquer Yuri's Revenge are registered trademarks of Electronic Arts Inc. All Rights Reserved.

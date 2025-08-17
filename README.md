# PocketWorldsUI
<h1> Overview </h1>
This project aims to demonstrate how to use the Pocket Worlds plugin from Epic Games (used in the sample project Lyra) to create an inventory with 3D previewable items. Most of the work is done in C++ to be able to visualise it on GitHub, but the project can be entirely done in blueprints.
> [!NOTE]
> This project was based on the example provided by Josh - https://github.com/JoshLmao/UE5PocketWorlds.
> All assets used in the making of this project are provided by Epic Games (Templates, plugins, sample models) or created by me (UI flourishes).
<h2> What is Pocket Worlds? </h2>
Pocket Worlds is a plugin that can be independently copied from the Lyra sample project. Currently (2025), the plugin is NOT publicly available to enable directly from Unreal Engine. The plugin allows us to stream additional level(s) in the current level, and project one or multiple objects from the streamed level onto a Render Target texture. Using this texture, we can then create a material, which can subsequently be used in UI or other systems to visualise the captured object.

<h1> Project structure </h1>
For demonstration purposes, this project uses the Vehicle Template offered by Unreal. GitHub ignores any other files other than code and configurations, but the whole project will be available for preview and download below. For the sake of simplicity, I created a simple UI System utilising the Common UI plugin (Activatable Widgets, Common UI Inputs) so the player can open and close screens from a certain layer. This approach is a simplified version of Lyra's UI, on top of which I added a UI Instance Subsystem that manages the layers and push/pop functionality. 

Below is a step-by-step explanation of how I created this example, because gatekeeping is not cool.
<h2>UI Structure</h2>
@todo
<h2>Inventory UI & Inventory Component</h2>
@todo
<h2>Pocket Worlds RT</h2>
@todo
<h2>UI Navigation on the grid</h2>
@todo

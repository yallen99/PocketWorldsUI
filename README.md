# PocketWorldsUI
<h1> Overview </h1>
This project aims to demonstrate how to use the Pocket Worlds plugin from Epic Games (used in the sample project Lyra) to create an inventory with 3D previewable items. Most of the work is done in C++ to be able to visualise it on GitHub, but the project can be entirely done in blueprints.
I have made some small modifications (additions) to the plugin to allow the inventory to preview to display multiple items identified by gameplay tags. The plugin is still using the same dependencies as before, and can be copy pasted from the repository into your own project.

> [!NOTE]
> This project was based on the example provided by Josh - https://github.com/JoshLmao/UE5PocketWorlds.
> All assets used in the making of this project are provided by Epic Games (Templates, plugins, sample models) or created by me (UI flourishes).

<h2> What is Pocket Worlds? </h2>
Pocket Worlds is a plugin that can be independently copied from the Lyra sample project. Currently (2025), the plugin is NOT publicly available to enable directly from Unreal Engine. 
The plugin allows us to stream additional level(s) in the current level, and project one or multiple objects from the streamed level onto a Render Target texture. Using this texture, we can then create a material, which can subsequently be used in UI or other systems to visualise the captured object.

<h1> Project structure </h1>
For demonstration purposes, this project uses the Vehicle Template offered by Unreal. I purposely set up GitHub to ignore any other files other than code and configurations, but the whole project will be available for preview and download below. 
For the sake of simplicity, I created a simple UI System utilising the Common UI plugin (Activatable Widgets, Common UI Inputs) so the player can open and close screens on a certain layer. This approach is a simplified version of Lyra's UI, on top of which I added a UI Instance Subsystem that manages the layers and push/pop functionality. 

Below is a step-by-step explanation of how I created this example, because gatekeeping is not cool.
<h2>UI Structure</h2>

@todo Add Links hyperlinks

Small overview - Lyra project (Provided by Epic) uses Common Activatable stacks to add and remove Activatable Widgets on separate layers of the Game. The simplest example is to imagine the in-game HUD of a Game and a Settings or Iventory menu. Each of those menus would be opened on their own respective stacks.
If you are unfamiliar with the Activatable Widget behaviour, Epic provides some documentation here [link]. On the top level, an Activatable widget can be activated and deactivated, and while active, it can direct input to itself.

I set up a Game Instance Subsystem to act as my UI Manager. I want this class to be the "manager" of the Layout Widget, which is created when the game starts. 
<b>NOTE</b> This Layout widget could be optimized by being constructed only when we load a level that uses UI, otherwise is useless. For simplicity, mine always exists.
The Layout Widget is Lyra's approach of Layer handling - it contains the activatable widget stacks where we can push "Screens" or "Menus". My Layout only has one Layer - a Menu layer - again, for simplicity's sake.
Thus, the UI Manager creates an instance of the Layout Widget based on a template stored in the Default Settings (a bespoke developer class I created to hold onto all my default UI data). Once the Layout is added to the viewport, we can use the static functions `OpenMenu` & `CloseMenu` to open menus on the stack.

The Layout Widget has an important role in <b>adding the global Input mapping context</b> for UI. My project uses Enahnced Input in the UI, hence any action I want to perform, including the default Back and Confirm actions from the Common UI configuration (if you are unsure what this is, check this [link]), have to be mapped into an IMC. 
When the Layout widget is added to viewport (in its Construct), it grabs the Default UI Actions IMC from the Default Settings (again, a place for all my defaults) and adds it to the Local Player Enhanced Input Subsystem.
The Default actions IMC contains only my Default Confirm & Default Back actions, because I want to the other inventory menu actions to only be available when the menu is active, and not all the time.

To make it simple to add global properties to any menu, I added a base class, `UBaseMenu` which extends from `UActivatableWidget` and would be the parent of any menu I want to add to the stacks.
@todo Add Info about navigating back and restoring imput.

<h2>Inventory UI & Inventory Component</h2>
@todo
<h2>Pocket Worlds RT</h2>
<h3> Shortcut to Code </h3>
The PR below has the information on how to set up the most basic version of the Pocket Worlds with the UI:
First Implementation PR >> https://github.com/yallen99/PocketWorldsUI/pull/2

<h3>How it works: the basics</h3>
What the Pocket Worlds plugin provides is easily streaming additional levels into the curren world and capturing a set Actor onto a render target. 
The flow is:
1. The "Pocket" Level is created and streamed in

2. The Level contains an actor which we want to capture, which is passed to the Pocket Capture

3. The Pocket Capture takes a "capture" / snapshot of this object (only!) and gives us back the Render Target Texture.

With the Render Texture from the Pocket Capture object we can then create a (masked) material to display in the UI (or anywhere else).

<h3>What the plugin <i>didn't</i> provide </h3>
The good part about the Pocket Worlds is that it is managed by a World Subsystem which can be retrieved from anywhere. In the subsystem we have an array of the Pocket Captures created so far.
<i>However</i>, the Pocket captures have no unique identifier, and the array is private, with no getter, in the subsystem.
To be able to differentiate between different captures, I added:
* A Gameplay Tag Id to the Pocket Capture object (similar to Josh's approach, who extended the class and made his own. I did think, however, this is a trivial, useful change, that deserves to exist in the plugin)
* A getter by id in the subsystem so we can retrieve the exact capture that we want from the list

<h2>UI Navigation on the grid</h2>
@todo

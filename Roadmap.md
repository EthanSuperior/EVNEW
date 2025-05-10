# ROADMAP (No Set Order):

### Features
- Finish Links
- Saving w/ Nova Running should prompt to quit it
- Update Readme to markdown
- Workspaces
	- Allow to switch between plugins within same EV Nova Folder
	- Tabs for open files
	- Make Load detect if within same folder as the plugin and not reload library
	- Make Linkers have Rez(Src) or at least * for outside resources
	- Distinguish between current & all plugins
	- Add Plugins to Library
	- Add run btn if corresponding .exe/.nplay file
	- Add View as Reference; Opens file from lib without saving;
	- Move m_iIsDirty to the plugins
	- Custom Default Values?
- Refactor Options (Like Move w/ Refs, and w/ Sub Resources, All Plugins)
- Availability
	- NCB usage/names(?)/as a type?
	- Check Availablity of ID
	- Set/Test/Desc Parser/Checker
	- Create/Nag if you enter a resource ID that doesn't exist
	- Add restrictions to IDs outside of the range of the resource type
- Resources
	- Add Edit btn to more than just desc (See Links)
	- Add dividers/headers to reserved types; ie desc3xxx should say Outfit Description somewhere....
	- Soft enforced reserved types; Hard(?) Enforced outside of bounds
		- See https://andrews05.github.io/evstuff/guides/resourceidguide.html
		- (Kestrel allows for more than short....Maybe something in NovaResource for Setting/Validating?)
		- Maybe divides within catagories; like a ----- between outfit picts and ship picts
	- Expanded Resource Types
		- Add DITL, DLOG, 
		- Import/Export Kestrel markup
		- Add Hexadecimal/char Editor for CResourceUkn
		- Add pilot editor (.plt) {NpïL Type}
- Add Embeded Bible? FAQ? Info.md?
	- Make Tooltips sourced from Bible?
- Double Check Cron Timeline (some were not what I remembered)
	- Specifically Cron X Y 0 & X 0 Z & X 0 0; differed in length of 'Pre-Init'
	- Output text had a for-loops starting at 1 at one point...y/n
- Add cron RANC utils; (Creating, Checking, Bi-Directional Etc. Overflow protection)
	- let bN be high or low bit
	- Allow Setting N-bits with bXXX or oXXX for counting;
		- Bi-Directional adds 1 cron (Reset)
		- Overflow protection adds 1 for max and 1 for min(if bi-directional)
		- Use loops for oXXX version on Reset and No Inc/Dec on same eval
- Modernize UI
	- Move most code inside of DLGProccess Functions into other functions in prep for change of ui
	- Dark Mode
- Add misn chain viewer; like: https://escape-velocity.games/EVN_Walkthroughs/html/polaris.html

### Fixes
- Modernize code (c++ 17)
- Allow Workspace to work with Unk
- IMG encoding things?
- Fix destroying CResourceUnk, such as DITL and DLOG.
- All lints
- Links display Data before Plugin Resources
- "CEditor::GetCurrentEditor()->ResourceExtra(...);" Loads a blank resource, even if one exists.

##### Links:
- Cron: Govt Names
- Dude: Ship Name
- Flet: Ship&Govt Names;System
- Misn: MOSTLY
- Outf: WeapName; Other stuff
- Pers: ship
- Ship: Cost; weaps;outf; do the stats
- Shob: tech lvls?
- Syst: Links; spobs;dudes;pers;reinforce
- Weap: ammo;jam names;

### Testing
- Multi-Window Libraries (Current is Seperate; should they be together)
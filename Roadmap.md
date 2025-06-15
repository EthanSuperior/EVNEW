# ROADMAP (No Set Order):

### TODO NEXT
- Make CPlugin's m\_vResources be a std::vector< std::map<short, CNovaResource*> > rather than a vector
- Have it keep track of it's own m\_iIsDirty
- Get ID of selected resource
- Add Multiple ways to fetch from Workspace::All;
	- IE ALL(CNR_SHIP\_TYPE, LOAD\_ORDER) -> Which has the plugins > data, id order, no dups
	- IE ALL(CNR_SHIP\_TYPE, LOAD\_ALL) -> Which has the data < plugins, id order, yes dups
	- IE ALL(CNR_SHIP\_TYPE, LOAD\_DATA) -> Which has only data, id order, no dups
	- IE ALL(CNR_SHIP\_TYPE, LOAD\_PLUGIN) -> Which has only plugins, id order, no dups
- Add a Create Workspace from Existing button to the main menu; And make it no longer auto open a plugin...
- Fix the bugs where I can't open a plugin by itself

### Features
- Make a .REZA_(rchive)_ type which is the entire workspace folder, then it exports out to:
	- WORKSPACE\_NAME\_data1.rez, ''\_data2.rez, ''\_data3.rez, etc
		- How does Nova export the data? How do TC's like WhiteDwarf and AAPRIA
		- What is the size limit that they are avoiding?
	- Add the workspace specific settings to the .REZA file
	- Have it do the same for plugins, so a workspace is represented by a single file
	- Assume Nova does not load -ids and use that to split between plugin/data files
	- Find what is in Nova.rez and see if we need to deal with that (Seems like a bunch of Unkn's)
	- Have an add Existing Data/Plugin btn to the workspace
	- Split Adds into Data and Plugin; Make dflt be a setting
- Add a Create Workspace button to the main menu
- Add a Create TC button to the main menu? which is the base tc
- Add ability to open and edit pilot files (.plt) directly and in a workspace

- Finish Links
- Saving w/ Nova Running should prompt to quit it
- Update Readme to markdown
- Templating thigs from out of plugin broken
	- Templeting Missions from wethere they are in a string; 
	- ie if my mission is Auroran 1; naming it Auroran 2 should auto chain
- Do Bit Sets check work for ( [(b1&b2) b3 b4]>3)
- Govt Map (implied Allies)
	- Implied Meaning G1 Enemies w/2 G2 will atk (back?) G1
	- If G2 will atk G1 unprovoked
	- Implied Allies? What if both?
- Search Bar for Rez List
- Auto Sandbox?
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
- Seceret Mission btn; Make more boxes searchable....
- Availability
	- NCB usage/names(?)/as a type?
	- Check Availablity of ID
	- Set/Test/Desc Parser/Checker
	- Create/Nag if you enter a resource ID that doesn't exist
	- Add restrictions to IDs outside of the range of the resource type
	- Be able to ask who uses XXXX
- Syst -> Spob & Spob -> Syst; 
- Tech Tracker; Give Lvlv see Outf Ship Spob/Syst etc
- Trades; if syst contains a trade route within it
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
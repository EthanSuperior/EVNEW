# ROADMAP (No Set Order):

### Features
- Finish Links
- Saving w/ Nova Running should prompt to quit it
- Update Readme to markdown
- Allow for searching in dropdown boxes
- Change NovaLib to a 'workspace'
	- Allow to switch between plugins within same EV Nova Folder
	- Make Load detect if within same folder as the plugin and not reload library
	- Change NovaLib to CPlugin*s? For hotswaps?
	- Make Linkers have Rez(Src) or at least * for outside resources
- NCB usage/names(?)/as a type?
- Set/Test/Desc Parser/Checker
- Resources
	- Allow creation of more than just desc (See Links)
	- Create/Nag if you enter a resource ID that doesn't exist
	- Add restrictions to IDs outside of the range of the resource type
	- Add headers to reserved types; ie desc3xxx should say Outfit Description somewhere....
	- Soft enforced reserved types; Hard(?) Enforced outside of bounds
		- (Kestrel allows for more than short....Maybe something in NovaResource for Setting/Validating?)
	- Expanded Resource Types
		- Add DITL, DLOG, 
		- Import/Export Kestrel markup
		- Add Hexadecimal/char Editor for CResourceUkn
		- Add pilot editor (.plt) {NpïL Type}
- Add Embeded Bible? FAQs?
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

### Fixes
- Borked when plugin is not in a Nova Folder
	- ie fix autoload Nova Files to only work when Parent
	- Disable run btn if no corrisponding .exe/.nplay file
- IMG encoding things?
- Unknown resource types
	- Fix it so it doesn't destroy any,	including (but not limited to) DITL and DLOG.
- All lints
- Modernize code (c++ 17)

### Links:
- Cron: Govt Names
- Dude: Ship Name
- Flet: Ship&Govt Names;System
- Misn: MOSTLY
- Outf: WeapName; Other stuff
- Pers: ship
- Ship: Cost; weaps;outf; do the stats
- Shob tech lvls?
- Syst: Links; spobs;dudes;pers;reinforce
- Weap: ammo;jam names;
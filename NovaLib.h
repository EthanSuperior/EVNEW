#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <vector>

#include "CPlugIn.h"

class CEditor;

//std::ofstream ofstream("log.txt", std::ios::app);
//ofstream << iNotifyCode << std::endl;

/*
TODO LINKERS:
-Cron: Govt Names
-Dude: Ship Name
-Flet: Ship&Govt Names;System
-Misn: MOSTLY
-Outf: WeapName; Other stuff
-Pers: ship
-Ship: Cost; weaps;outf; do the stats
-Shob tech lvls?
-Syst: Links; spobs;dudes;pers;reinforce
-Weap: ammo;jam names;

-Dark mode
-Nag if you enter a resource ID that doesn't exist.
-import/export Kestrel markup
-IMG encoding things?
-Fix it so it doesn't destroy any resource types that it doesn't know about,
	including (but not limited to) DITL and DLOG.

# Document Stuff I Learn
-Bit Counting ( [b1 b2 b3 b4 b5 b6 b7]=x): <=> supported; x must be literal; ( [space required
-Text Box pop-ups; Undocumented behavior.

-Is there a way to make a mission not show "mission failed"?
	Have a Qxxxx in the OnFail to overwrite the fail text
-Conditionals:
	To do a conditional in a set expression you need a mission that represents your condition,
	with "true" meaning the mission is active and "false" meaning it isn't. Put your conditional
	statements in the missions OnAbort field, then in your set expression Axxx the mission.
	If the mission is active the OnAbort statements will be executed.
-Countdown: What it does is Gxxx the player a number of outfits equal to the number of missions the
	player needs to complete for the counter to detect it, and then Dxxx at the end of each mission 
-Bi-Directional Counters: If you want a bidirectional counter, you can either just use Gxxx to count in the opposite direction or you can have an "anti counter" outfit
	and a cron that deletes one from your counter if there is both a counter and an anti counter to "cancel each other out":
			cron id [whatever]
			ActivateOn: Oxxx Oyyy
			OnStart: Dxxx Dyyy
-Desc (Comments): Use {b9999 "text" ""} to leave comments in descs that will never be displayed
	(use whatever your 'always false' bit is if you're using b9999 for something else)
-Red Arrows: Make an invisble mission with the return location set to the spob
-Detect Exploring Sector: Nebulas have a OnRevealed set expression; but it tiggers multiple times
-Unconquerable Systems: Set the defence dude to an out of bound value
-Cron Repeat Delay Fix: Create a misn with: Not appear; Abortable; 1-day time limit; OnFail: S201 XXXXXXX 
-In-Flight Adjustments of Stats: To recalc the players stats just Gxxx Dxxx; Runs till A201
-No Pesky Astroids:  The "Passes Over Asteroids" flag works on any kind of projectile
-Buying Air: Including a GXXX in the OnPurchase field of an outfit makes it so you do not get the outfit; add
		GOutfID to the OnPurchase to make it so that you actually get one (this doesn't trigger OnSell).
-RANC Counter: A counter using cron and N-bits to store a (N-1) bit number
	NOTE: Order matters as cron 128 is executed before cron 129
	Cron(X):
	- EnableOn: ( [!b0 !b2 !b3 !b4]=0) // or ( [b0 b1 b2 b3]=4)
	- OnStart: ^b1
	Cron(X+1):
	- EnableOn: ( [b0 b3 b4]=3)
	- OnStart: ^b2
	Cron(X+2):
	- EnableOn: b0 & b4
	- OnStart: ^b3
	Cron(X+3)
	- EnableOn: b0
	- OnStart: ^b4 !b0
- Time Flys when you're having fun: http://asw.forums.cytheraguides.com/topic/20232/
	In the char field, have it start a misn, say 100. The misn creates an invisible special ship,
	armor 0, 0 turning&accell, no fuel, with a death delay of several hundred. The goal is to destroy the ship.
	The onshipdone field contains A100 S100 S101. Misn 101 is autoaborting with a datepostinc of 1, and,
	to be fancy, Q*** in the onabord field where STR# *** is some greeting like "Good morning, captain."
	The use here is clear, make it so when the player is spending ages in a system, he is really spending ages.
// Extra Facts http://asw.forums.cytheraguides.com/topic/21842/esoteric-nova-knowledge-compendium
//GOT TO PAGE 41 on DrFive's posts on discord
// http://asw.forums.cytheraguides.com/topic/22193/cool-nova-hacks/
	Disabled sprites: 28
	Untargable Spobs: 41
	Negative Fallout: 81-85
	Multi-Fighter Bays: 135 (Making fighters take tons is bad idea; no worky)
	Peirceing Weapons: 144
	Ramming Weapons: 148
	Bunch: 152
	Fake Afterburners: 122
	Outfits for Changing Engine Color: 123
// BITEC [BROKEN]: http://asw.forums.cytheraguides.com/topic/18965/how-do-yall-deal-with-specialty-ammo-/3
// Legal System: http://asw.forums.cytheraguides.com/topic/22062/complete-legal-details-/3
// Multi-Ammo Weapons: http://asw.forums.cytheraguides.com/topic/20902/ev-nova--weap-resource-question---/
	http://asw.forums.cytheraguides.com/topic/18965/how-do-yall-deal-with-specialty-ammo-/
// Negative Inaccuracy: http://asw.forums.cytheraguides.com/topic/19922/weapon-special-effects/58
// Swappable Fighters: http://asw.forums.cytheraguides.com/topic/20360/revamping-the-mechanics-of-evo/
// Flet Scatter On Misn Ship Death: http://asw.forums.cytheraguides.com/topic/19732/fleet-combat-trick/
// Beam Weapons: http://asw.forums.cytheraguides.com/topic/20831/an-insight-on-beam-display/
// Delay Guidance: http://asw.forums.cytheraguides.com/topic/19791/-evn--unguided----guided-submunitioning-/


 // http://asw.forums.cytheraguides.com/topic/20221/no-jumping-here-/
 // http://asw.forums.cytheraguides.com/topic/19947/random-idea-about-inter-planetary-combat---/
 My (nearly) complete guide to when spobs shoot:
A spob will fire its weapon at the closest target ship (see below), no matter what type (ship/planet) of weapon the spob has.

If the "fires when provoked" flag is not set,
A spob will fire at the player if either of the following conditions are true:

The player is disliked by the system's govt ( not the spob's!), or
The player's ship has an inherent combat government that is an enemy of the spob.
A spob will only fire at an AI ship if the ship's dude's govt is an enemy of the spob (the attitude of the system has no effect).

A spob will never fire its weapon at another spob, even if the weapon is planet-type.

As far as I can tell from accidental testing, the "fires when provoked" flag should actually be called the "fires only when provoked". I think that it limits the spob to only firing when it (or possibly a ship of its govt) is shot at.
 */

class NovaLib
{
public:
	static NovaLib& Get();
	void AddFolder(std::string path, CWindow* pWndParent);
	void AddRezFile(std::string filename, CWindow* pWndParent);
	static CNovaResource* At(int type, int id);
	static char* RezName(int type, int id);
	static std::string RezStr(int type, int id, bool addType=false);
	static std::vector<CNovaResource*> GetAllOf(int type);
	void Clear();
	std::map<int, CNovaResource*> rez[NUM_RESOURCE_TYPES] = {};

private:
	NovaLib() = default;
	~NovaLib();
	static NovaLib* instance;
};


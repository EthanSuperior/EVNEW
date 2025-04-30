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
-Reopen last closed
-Run Nova Btn

-Dark mode
-Nag if you enter a resource ID that doesn't exist.
-import/export Kestrel markup
-IMG encoding things?
-Fix it so it doesn't destroy any resource types that it doesn't know about,
	including (but not limited to) DITL and DLOG.

# QUESTIONS:
- How cron; with 0s and negs and repeats?
- How make single time event (Im looking at you crons)?
- Can you make something run on startup (crons? Remove the limit of starting char)?
- Make a cron run daily?
- Make a cron run each time with on/offs?
- How do loop crons work?
- If you have a cron that modfies bits, does it trigger prior crons?
- Does Fxxx do anything on planet? How about off?
- Does buying something then leaving a planet double trigger crons? (seems yes)
- Do crons trigger on land and on leave or just one and if so which?
- If I set both itters, do they check 1 run both or check between, which runs first?
- Detect Return Stellar/Misn Stellar
- If Else with misn
- Check Fxxx again and Fxxx vs Axxx
- Make Dev Branch
- Do failed missions progress time?


# Set Expression Behavior:
- Sxxx: Start mission ID xxx automatically.
	- Does so immediatly before exaluating the rest of the expression, taking priority over any other event
	- Always Shows the Breifing Dialog
	- Ignores All Avalibility Requirements
	- Runs OnAccept
	- Aborting a mission will prevent queued Dialogs and OnXXXX from running
	- OnAccept Runs before the Breif Dialog; OnShipDone runs before Ship Dialog
	- OnShipDone runs in any system of the goal once completed.
	- The Ship having No Goal really just means always completed.
	- You can have multiple of the same mission at the same time.

- Leaving progresses time, not landing.
- Large Negative Time Limit; Same as 0

# TIPS & TRICKS
	ESOTERIC: //http://asw.forums.cytheraguides.com/topic/21842/esoteric-nova-knowledge-compendium
- 30 FPS: 30 frames is 1 second
- Comments within desc: Use {b9999 "text" ""} to leave comments in descs that will never be displayed
	(use whatever your 'always false' bit is if you're using b9999 for something else)
- Hidden Failure: A misn with Qxxx in the OnFail will override the "mission failed" text
- Unconquerable Systems: Set the defence dude to an out of bound value
- Red Arrows: Make an invisble mission with the return location set to the spob
- Detect Exploring Sector: Nebulas have a OnRevealed set expression; but it tiggers multiple times
- What Astroids:  The "Passes Over Asteroids" flag works on any kind of projectile
- Buying Air: Including a Gxxx in the OnPurchase field of an outfYYY makes it so you do not get
	the outfit; add Gyyy to the OnPurchase to fix this.
- One-Way Doors: If the hyperlink/wormhole targets a planet, it will only work one way
- Time Warp: If you buy/sell outfits while on a planet then it will  advance two days when you leave.
- Slow Start: AI fighters with mass >=200 will not attack until the parent's shields drop below 2/3
- One Time Shields: 0 shields: no regen; <100 shield: Once no shields, no shield regen.
- Creating Dialog: Running Sxxx will show the Breifing dialog;
	OnShipDone will run afterwards if not on a planet
- Did You Leave: To detect leaving a planet start a misn with no ShipGoal, then use OnShipDone.

	CRONS:
- Execution: Crons run OnLand&OnDateChange
- Grounded: Triggering a Date Advance; even when on a planet will reruns crons
- Witchcraft: Umm good luck but negatives do weird things... http://asw.forums.cytheraguides.com/topic/20361/crons-give-me-headaches/

	LOGICAL: 
- NCB Set Counting: ( [b1 b2 b3 b4 b5 b6 b7]=x); =<> supported; x must be literal; the '( [' part is required.
	a bunch of &s is ( [b1 b2 ...bN]=N) |s is ( [b1 b2 ...bN]>0); >= not supported
- Conditionals: To make one in a set expression, you need to have a mission that represents your condition,
	Active being true and Inactive being false. Put your True expression in the missions OnAbort field,
	then in your set expression Axxx the mission. OnAbort only triggers if the misn is active.

	COUNTERS:
- Outfit: A countdown counter; Gxxx the player a number equal to the goal to complete
	Then Dxxx to decrement, Oxxx to detect when its 0 and Gxxx to add one.
- Bi-Directional BORC: If you want to support negative values make an "anti counter" outfit
	Then have cronXXX: ActivateOn: Oxxx Oyyy OnStart: Dxxx Dyyy to decrement while negative
- Misn Counter: http://asw.forums.cytheraguides.com/topic/22110/cron-less-counting
	Works within outfitter & http://asw.forums.cytheraguides.com/topic/22158/multiple-ammo-types
- RANC: A counter using Ncron and N+1 NCB to store a N bit number [0b1000 would be b4=1]
	In this example b0 is the toggle bit.
	NOTE: cron order matters as cron 128 is executed before cron 129
	cronXX0: EnableOn: ( [b0 b1 b2 b3]=4)	OnStart: ^b4     OR: EnableOn: ( [!b0 !b1 !b2 !b3]=0)
	cronXX1: EnableOn: ( [b0 b1 b2]=3)		OnStart: ^b3
	cronXX2: EnableOn: b0 & b1				OnStart: ^b2
	cronXX3: EnableOn: b0					OnStart: ^b1 !b0
- Bi-Directional RANC: http://asw.forums.cytheraguides.com/topic/19025/
- BONC [http://asw.forums.cytheraguides.com/topic/19004/new-counter-method/]

	TIMER:
- Cron Pwrs:
- Daily Runner: Create a hidden abortable misnXXX with a 1-day time limit; OnFail: Sxxx; Start/End w/ Sxxx/Axxx
- Inflight Timer: Sxxx a misn that spawns an invisible ship, with 0 armor&turn&accel&fuel. Give the ship a
	death delay of X, this will be your timer. In the OnShipDone field you can add your effects; If you want
	the timer to be repeating add Axxx Sxxx for the misn of the timer. Calling Axxx will stop the timer.

	EXTRAS:
- In-Flight Stat Recalc: To recalc the players stats just Gxxx Dxxx any outfit on timer;
- Time Flys when you're having fun: http://asw.forums.cytheraguides.com/topic/20232/
	Create a repeating timer as above, have the OnShipDone Syyy a misn, which is  is autoaborting
	with a datepostinc of 1, and to be fancy, Qzzz in the OnAbort field where STR#zzz is some greeting like
	"Good morning, captain.". The use here is so when the player is spending ages in a system, time passes.
//GOT TO PAGE 41 on DrFive's posts on discord
// http://asw.forums.cytheraguides.com/topic/22193/cool-nova-hacks/
	Disabled sprites: 28
	Secret Spobs: 41
	Negative Fallout: 81-85
	Multi-Fighter Bays: 135 (Making fighters take tons is bad idea; no worky)
	Peirceing Weapons: 144
	Ramming Weapons: 148
	Bunch: 152
	Fake Afterburners: 122
	Outfits for Changing Engine Color: 123
// BITEC: http://asw.forums.cytheraguides.com/topic/18955/spobs--visbits--and-nested-loops/
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
// Spob Atks: http://asw.forums.cytheraguides.com/topic/19947/random-idea-about-inter-planetary-combat---/4
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


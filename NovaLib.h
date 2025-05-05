#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <vector>

#include "CPlugIn.h"

class CEditor;

// std::ofstream ofstream("log.txt", std::ios::app);
// ofstream << iNotifyCode << std::endl;

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
- Do multi days run all crons in order or 1 at a time just x times?
- Does Fxxx do anything on planet? How about off?
- Check Fxxx again and Fxxx vs Axxx
- Detect Return Stellar/Misn Stellar
- Do failed missions progress time?
- If Else with misn

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
	- Large Negative Time Limit; Same as 0
	- Auto-Aborted mission progress time by Date Increment, but Axxx and Fxxx do not
- Fxxx: Fails a mission; notice fail dialog is only shown are the return stellar and only for failed shipgoals/cargo

# Cron Witchcrafty:
	- Modifying bit does not change for crons of lower IDs but does effect crons of higher values
	- Crons do not run Day 0; IE the day the game starts; use the char OnStart instead
	- Execution: Crons are evaluated OnDateChange (IE when you leave a planet or a mission is completed/auto-aborted).
	- Crons run for each day that passes, meaning if 10 days pass they will run 10 times.
	- 0 means 0 days after OnEnabled returns true; ie the day of 3 would be 3 days after(4 total)
	- ALL CRONS TAKE A MINIMUM OF 2 DAYS to evaluate;
		If you need to check daily for changes use a self-restarting misn OR
		2 crons both 0 1 0; one set to Continuous OnStart; the other OnEnd and some complex bit logic
	- A=OnStart B=OnEnd ' '=Next Iteration (Number order is Pre Duration Post)
	- If Duration is less than 0: Never Execute
	- Pre-Holdoff = max(0, Pre-Holdoff)
	- Post-Holdoff = max(0,  Post-Holdoff)
	- Cron 0 0 0: 0:AB 1:B; Repeat {0 0 0: AB B;}
	- Cron 0 0 Z: 0:AB Z:_; Repeat {0 0 3: AB _ _;} * The only time Z's value is actually used
	- Cron 0 Y 0: 0:A Y:B; Repeat {0 3 0: A _ _ B;}
	- Cron X 0 0: 0:_ X:AB (X+1):B; Repeat {3 0 0: _ _ AB B;}    !!!!!!!!!!!!! WHY does this differ from X0Z is this correct?
	- Cron 0 Y Z: 0:A Y:B (Y+1):B ... INF {0 2 Z: A _ B B ... B}
	- Cron X 0 Z: 0:_ X:AB X+1:B (2X+1):_; Repeat {2 0 X: _ _ AB B _ _;}
	- Cron X Y 0: 0:_ X:A (X+Y):B; Repeat {2 3 0: _ _ A _ _ B;}
	- Cron X Y Z: 0:_ X:A (X+Y):B (2X+Y):AB (2X+Y+1):B (3X+Y+1):_; Repeat {2 5 Z: _ _ A _ _ _ _ B _ AB B _ _;}
	- Continuous Iterative is a while loop
	- If Both Continuous Iterative as set it will execute All OnStarts and then All OnEnds (Basically skipping the OnEnd all together);
	- CRONs evaluate for each day passed; one at a time ie 3 days will do: c1 c2 c1 c2 c1 c2
	- Leaving progresses time, not landing; and as such crons execute on leaving a planet.
	- To force a cron to only run once;	set a bit during it's OnStart and Check during its OnEnable

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

	LOGICAL:
- NCB Set Counting: ( [b1 b2 b3 b4 b5 b6 b7]=x); =<> supported; x must be literal; the '( [' part is required.
	a bunch of &s is ( [b1 b2 ...bN]=N) |s is ( [b1 b2 ...bN]>0); >= not supported
	alternativly &s can be ( [!b1 !b2 ...!bN]=0) |s can be ( [!b1 !b2 ...!bN]<N)
	[b1 b2 ...bN]<N
- Conditionals: To make one, you need to have a mission that represents your condition,
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
	In this example b10 is the increment bit. http://asw.forums.cytheraguides.com/topic/16686/
	RANC counters are limited to +/- 1 at a time; an outfit can be used to trigger the +/- if multi +/- is needed; be sure to add the (b10&b11) safegaurd
	NOTE: cron order matters as cron 128 is executed before cron 129
	cronXX0: EnableOn: ( [!b10 !b1 !b2 !b3]=0)		OnStart: ^b4
	cronXX1: EnableOn: ( [!b10 !b1 !b2]=0)			OnStart: ^b3
	cronXX2: EnableOn: ( [!b10 !b1]=0)				OnStart: ^b2
	cronXX3: EnableOn: ( [!b10]=0)					OnStart: ^b1 !b10
- Bi-Directional RANC: http://asw.forums.cytheraguides.com/topic/19025/    This seems to invalidate the first bit and regulates it to be just (N-1)+1
	cronXX0: EnableOn: b10 & b11											OnStart: !b10 !b11
	cronXX1: EnableOn: ( [!b10 !b3 !b2 !b1]=0)|( [!b11 b3 b2 b1]=0)			OnStart: ^b4
	cronXX2: EnableOn: ( [!b10 !b2 !b1]=0)|( [!b11 b2 b1]=0)	 			OnStart: ^b3
	cronXX3: EnableOn: ( [!b10 !b1]=0)|( [!b11 b1]=0)	 					OnStart: ^b2
	cronXX4: EnableOn: ( [!b10]=0)|( [!b11]=0)								OnStart: ^b1 !b10 !b11
	- If you have multiple counters you can combine the first cron; see the forum for how they did it
	- Roll-over can be prevented by adding (...&!( b3 b4....)) and (...&( [b3 b4...]>0)) etc to all the conditional
		Warning however this limits the max and the minimums to [1, ((N-1)+1)] additionally it seems that once you reach max it freezes the value.
		This is because the transitionary state b1111{from b0111->b1000} is indisigishable from the actual b1111
- BONC [http://asw.forums.cytheraguides.com/topic/19004/new-counter-method/]

	TIMER:
- Cron Pwrs: See Cron Witchcrafty
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
	static NovaLib &Get();
	void AddFolder(std::string path, CWindow *pWndParent);
	void AddRezFile(std::string filename, CWindow *pWndParent);
	static CNovaResource *At(int type, int id);
	static char *RezName(int type, int id);
	static std::string RezStr(int type, int id, bool addType = false);
	static std::vector<CNovaResource *> GetAllOf(int type);
	void Clear();
	std::map<int, CNovaResource *> rez[NUM_RESOURCE_TYPES] = {};

private:
	NovaLib() = default;
	~NovaLib();
	static NovaLib *instance;
};

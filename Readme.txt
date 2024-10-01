************************************************
*                                              *
*                    EVNEW                     *
*                                              *
*   Escape Velocity: Nova Editor for Windows   *
*                Release 1.0.4                 *
*                                              *
************************************************


+-------------------+
| Table of Contents |
+-------------------+

1. About EVN Plugins
2. Using EVNEW
3. EVN Resources
4. Miscellaneous
5. History
6. Legalese


+----------------------+
| 1. About EVN Plugins |
+----------------------+

As you probably already know, EVN originated as a Macintosh game.  The entire original scenario was created using ResEdit, and a plugin
for ResEdit called NovaTools, a simple but powerful resource editor available only on Macs.  On Macs, the Nova data files and plugins are
stored entirely as resource files, which ResEdit loads, edits, and saves.  Macs and Windows use a completely different file architecture.
On Windows, files can only have one "fork," where as on Macs files usually have two, but can have as many as you want.  A "fork" is just a
fancy name for a chunk of data stored in part of a file.  Most Mac files consist of a data fork and a resource fork.  The Nova files and
plugins have an empty data fork.  That's the basic structure of Mac plugins.

Because Windows files do not have resource forks, an alternative had to be found to allow EVN to load data files and plugins.  When
decompressing Mac files on a Windows platform, most decompression utilities only decompress the data fork and nuke the resource fork.
Obviously, this is a very bad thing for EVN.  Fortunately, StuffIt 7.5 for Windows has an option to preserve the resource fork of files,
but in a different format.  This format is known as MacBinary, and EVN doesn't like MacBinary either.  In addition, MacBinary files seem
to be rather unstable on Windows, especially when being transferred between computers.  In order to get around this, Contrband created a
nice little conversion program that took MacBinary files and converted them into a data file that has a similar architecture to the
original resource fork on Macs.  These are the .rez files that EVN can actually load.

EVNEW natively loads, edits, and saves .rez files.  If you're wondering how Mac users can use plugins created on Windows, don't sweat.
EVONE, created by Arios Software, is a shareware Mac plugin editor that can read and write .rez files.  If you can't afford to shell out
the money for EVONE, David Arthur has also created a free utility to do the conversion, available from the EVN add-ons page.  Converting
from .rez to the Mac format is much simpler, because converters don't have to deal with MacBinary.


+----------------+
| 2. Using EVNEW |
+----------------+

Plugin creation is an art, as is utilizing all of the Nova engine's features to thier fullest extents.  This readme will not explain how
to do that.  Plenty of guides already exist for those purposes, although you will have to be able to guess what some things mean when
they address using Mac plugin editors to do specific things, but that's pretty easy to do.


Loading and Saving Plugins:

EVN plugins are saved in .rez files.  Additionally, EVNEW has the functionality of the Mac programs ConText and ResStore - it can export
plugins into a tab-delimited text file and import them back in.  With this, you can copy and paste the data into a spreadsheet program
such as Microsoft Excel and perform large-scale editing quickly and easily with the raw data.  Note that right now, EVNEW is not capable
of loading files created by ConText, nor can ResStore load text files created by EVNEW.  Hopefully, this will change in the future.

To load a plugin, simply go to File -> Open, or just type Ctrl+O.  Choose either the .rez filter or the .txt filter, and then choose the
file.  Additionally, you can drag and drop a plugin file onto the EVNEW icon, or you can even create a file association for .rez files to
open them with a simple double-click.  See section 4 (Miscellaneous) for details on that.

To save a plugin, choose File -> Save, File -> Save As, or just hit Ctrl+S.  If the current plugin is untitled, you will be asked to
choose a filename.  You can choose to save it as a .rez file or a tab-separated text file using the combo box in the dialog.  Note that
if a plugin contains graphics (cicn, pict, rle8, or rleD resources) or sounds (snd resources), they will not be saved in the text file.
You will be given a warning message if you try to do that, with the option to turn that message off for the future.


Editing Resources:

To create a new resource, you can double-click a resource type in the resource type list on the left of the main interface.  You can
also single-click a resource type and click the New button or go to Resource -> New in the menu.  When a new resource is created, an
editing dialog comes up automatically for the new resource containing default values.  It is also given a unique resource ID (RID)
within that type of resource.  RIDs must be between 128 and 32767 inclusive, and they must all be unique for a given resource type.

To edit an existing resource, you must first single-click a resource type in the resource type list, which will bring up a list of all
of the resources of that type in the list on the right of the main interface.  Then, you can double-click a resource or single-click a
resource and then hit the Edit button or go to Resource -> Edit in the menu to edit that resource.  Most fields in a resource are
numbers, text strings, flags (check boxes), or combo boxes where there are only a few possible values of something, but there are a few
other types of fields: hex fields and color fields.  A hex field is really a collection of either 16 or 64 bits, and they can all be
edited either using hexadecimal (for advanced users) or by clicking the associated edit button to give a subdialog with 16 or 64 check
boxes so you can choose any combination of bits.  A color field is a button showing the current color that, when clicked, brings up a
color selection dialog where you can easily pick any 24-bit color.  When you're finished editing the fields of a resource, hit OK (or
Enter on your keyboard) to save your changes, or hit cancel, the X button in the top-right corner, or the Escape button on your
keyboard to not save changes.

Resources can be cut, copied, pasted, and deleted to your heart's content with Ctrl+X, Ctrl+C, Ctrl+V, and Del, or through the Edit menu.


+------------------+
| 3. EVN Resources |
+------------------+

All EVN data files and plugins are composed of a set of resources compiled into a few large files.  Each file can contain hundreds or
thousands of resources.  EVN uses 23 resource types created just for use with EVN, and it also uses a number of standard Mac resource
types.  You are STRONGLY encouraged to read the EVN Bible, which can be found in the Documentation folder of your EVN folder.  I can not
stress how important it is to read the Bible.  The Bible contains very detailed explanations of all the fields of the 23 Nova resources
and how they all interact.  A lot of that information can be found in tooltips while using EVNEW, but far from all of it.  Go read the
Bible now, and don't come back until you've read all 183 kilobytes of information.  The non-Nova-specific resources are described below.

i. cicn

The cicn (color icon) resource is a small, low-color image.  Cicns are used for smoke trails, the variously colored L-shaped pieces that
appear when you select a ship or planet, the alert symbol shown when a hostile ship is detected, and the x2 symbol shown when running at
double speed.  Cicns can only be imported from a Windows bitmap file (.bmp) with 8 bits per pixel or fewer.  Cicn masks can only be
imported from monochrome (1-bit) bitmaps.

ii. pict

Pict resources are single-frame images stored in a Mac-native format.  They do not have masks, but they often exist in pairs, of which
one is the image and the other is the mask for that image.  You can import any image file the QuickTime can read into a pict, and you can
export to .bmp, .png, .jpg, .pic, .tiff, and .tga.  Picts are used for almost all still images, buttons, menu items, and other things.

iii. rle8 / rleD

rle8 and rleD resources represent compressed multi-frame animations.  They are used for ship, weapon, and planet graphics.  They contain
masks built into them.  You can import graphics into one from an image file that contains all the frames layed out in a grid, or you can
import the frames one by one from seperate files.  When you select File -> Import, enter the width and height of each frame, the number of
frames across a row in the image file, the number of frames down a column in the image file, the number of frames to import from the file,
and the 1-based index that the frame in the upper-left of the image will be loaded as.  For example, if you have 108 frames for a ship
layed out in three separate files, where each file contains a 6x6 grid of 100x100 sprites, you would do three imports.  You would set
Width and Height to 100 and X Frames and Y Frames to 6 for all three imports.  For the first file, you'd enter 1 as the first frame, For
the second, you'd enter 37 as the first frame, and for the third you'd enter 73 as the first frame.  You'd enter 36 as the number of
frames for all of them.  You then do likewise for the masks.  Exporting works very similarly to importing.  Like picts, rle resources can
be imported from any image file QuickTime can read, and they can be exported to a variety of different formats.

Many rle resources will have too many frames to fit on one screen.  You can enter different values in the X Frames and Y Frames fields and
hit the Update button to rearrange the frames.  This does not affect the internal storage of the frames, as they are all stored as a bunch
of smaller images strung together linearly.  You can then use the Prev Page and Next Page buttons to look at all of the frames.

See section 4 (Miscellaneous) for more details on rle8s and rleDs.

iv. snd

snd resources are Mac-formatted sounds used throughout EVN.  You can only import uncompressed .wav files, and likewise you can only export
snds as uncompressed .wav files.  Sounds are automatically converted into 8-bit mono format, which EVN likes.

v. str

str resources are simply strings.  They are limited to 255 characters.  They are only used to patch str# resources.  See the appendix in
the Bible.

vi. str#

str# resources are lists of strings.  They can contain up to 32767 strings, but each string can only have 255 characters.  They are used
to store hundreds of small text strings used in EVN, such as button labels, communication strings, message buoys, and so on.


+------------------+
| 4. Miscellaneous |
+------------------+

i. Creating a .rez file association

To create a file association for EVNEW with .rez files, perform the following steps:
  a. Open up any folder and click the Tools -> Folder Options menu
  b. Click the File Types tab
  c. After Windows generates a list of all file associations (this shouldn't take more than a few seconds), click the New button
  d. Type rez into the box and hit OK
  e. Select rez from the list, and in the box that says "Details for 'REZ' extension", click the "Change..." button
  f. Click the "Other" button and locate and choose EVNEW.exe, and hit OK
  g. Click Close, and you're done!

You should now be able to double-click a .rez file and have EVNEW automatically open it.


ii. rle8 / rleD

rleD resources store multi-frame animations in a 16-bit (actually 15-bit with one unused bit) direct RGB format, and rle8 resources store
them in an 8-bit pallettized format.  Unfortunately, the pallette data is not store in the images, so EVNEW cannot display the images
properly.  On Windows, EVN only uses the rleD resources, regardless of the user's monitor's color mode.  If the user is in an 8-bit mode,
EVN converts the 16-bit data into 8-bit data at runtime and completely disregards any rle8 data, if it exists at all.  On Macs, though, it 
is different.  The resources used depend on the user's color depth.  In high-color modes (16-bit, 24-bit, and 32-bit), the rleDs are used
as expected, but in 8-bit modes, the rle8s are used.  If the rle8s don't exist, EVN will not run and spit out an error message saying it
couldn't find the required resources, or something like that.  Thus, a plugin created using only rleDs will work perfectly for all Windows
users and for the vast majority of Mac users, since very few people nowadays can't use color depths higher than 8-bit.  If you want your
plugin to work for all users, you, or a friend with a Mac, must convert your plugin into the Mac format and use the program EnRLE created
by w00tWare.  EVNEW is not capable of displaying rle8's properly: the pallette indices are converted to grayscale, and any images imported
into an rle8 will be grayscaled, with the resulting grayscale converted into pallette indices.  The result is that, although you can view,
import, and export rle8s using EVNEW, they will look completely messed up if you try to use them on a Mac in 8-bit color.  The moral of
the story is that if you're creating ship, weapon, or planet graphics for a Windows plugins, don't worry about creating rle8s and make
only rleDs.



iii. EVNEW text feature

Plugins can now be exported into a text format useful for low-level mass-editing and batch image imports and exports.  When you save a
plugin as a text file, every resource will have all of its fields dumped, separated by tabs, and text fields will be quoted.  In addition,
text fields will have newlines converted to \n, tabs converted to \t, backslashes converted to \\, and internal quotes converted to \q.  This
is so that when the text file is copied and pasted into a spreadsheet program such as Microsoft Excel, all formatting is preserved without
screwing up the spreadsheet (which figures out what goes in what cells based on tabs and newlines).  When reloaded back into EVNEW, all of
this data is converted back into its proper form.  Be careful when editing resource data in a text file, since if you accidentally delete
something, add in something extra, or otherwise mess up the data, it can get really screwed up when it is reloaded into EVNEW.

If a plugin has graphics or sounds (cicn, PICT, rle8, rleD, or snd resources), a dialog box will come up prompting the user to select some
options for batch exporting these items.  He can choose the subdirectory (if any) they will be saved to, a prefix each filename will be
assigned, type of file if necessary, (e.g. .bmp, .png, or .jpg, among others) and the corresponding items for the image masks for cicns,
rle8s, and rleDs.  He will also be asked the number of frames to store in one row across for rle8s and rleDs.  He can also choose to not
export each of these.  All filenames will be of the form (prefix)(RID), and if necessary, an underscore followed by a number will follow if
the filename already exists.  For example, if a PICT with RID 128 were exported with a subdirectory of "My plugin's PICTs" and a prefix of
"pict ", then the filename would be "My plugin's PICTs\pict128".  If that file already existed, then the filename would be
"My plugin's PICTs\pict128_2", and so on until an unused filename is found.  The text file will contain the relative path, not the absolute
path, of the image files, so that the text file and the folder containing the graphics or sounds can easily be transferred between folders
on one computer or between multiple computers and they will still load correctly.

A note of caution: batch exporting graphics and sounds via the EVNEW text feature will take a huge amount of memory and time.  It takes a
lot of memory and computing power to perform these operations.  This is the most apparent when exporting rle8s and rleDs.  First the RLE data
has to be decompressed into raw data, it has to be arranged into tiles, and then QuickTime has to change that back into the image file.  Most
of the time spent performing these operations is actually spent just allocating the memory needed.  If you're having trouble batch exporting
rle8s and rleDs, try breaking up your plugin into several smaller files.  This shouldn't take too long using cut and paste (Ctrl+X and
Ctrl+V).



iv. Command line interface

EVNEW can now perform .rez to EVNEW text conversions and back using the command line.  This could be used in batch scripts (.bat files) or
other applications for large-scale plugin developers, or for other things.  To use it, do one of the following:

.rez to .txt:
"C:\...\EVNEW.exe" -totxt "source.rez" "destination.txt"

.txt to .rez:
"C:\...\EVNEW.exe" -torez "source.txt" "destination.rez"

-totxt and -torez must be all lowercase, with a hypen at the beginning.  If the destination does not have the appropriate extension, it will
be automatically appended.  Keep in mind that if an error occurs, it will happen silently and will be logged to log.txt when using this
feature.  This is to not interrupt the calling process.  EVNEW will quit immediately upon executing the conversion.  Be sure that there are
no errors in your source files, otherwise things could get ugly.  Both the source and destination filenames must be absolute, not relative.
Also, make sure to use backslashes, not forward slashes, to delineate a path.  EVNEW may get confused and put things in the wrong directory
if you use forward slashes instead of backslashes in filenames.



v. Character codes

The fonts used by Macs and Windows are completely different.  Pretty much all standard ASCII characters (32 to 127), which include a to z, A
to Z, 0 to 9, and all of the commonly used punctuation marks, are the same, but beyond that they are completely different.  A lot of the same characters exist in both sets but have different codes, and some characters exist in one but not in the other.  EVNEW automatically converts
the characters that exist in both sets but have different codes.  A list of those characters, and their _Windows_ codes follows.  Note that
to type these in, you must type the numbers using the keypad on the right-hand side of the keyboard, NOT the top row, and you must also type
the leading zero.  Otherwise, you will get different characters.

Characters that can be converted into Mac fonts:

 Char   Windows code
 -------------------
  ¡      Alt+0161

  ¢      Alt+0162

  £      Alt+0163

  ¥      Alt+0165

  §      Alt+0167

  ©      Alt+0169

  «      Alt+0171

  ¬      Alt+0172

  ®      Alt+0174

  ¯      Alt+0175

  ±      Alt+0177

  ´      Alt+0180

  µ      Alt+0181

  »      Alt+0187

  ¿      Alt+0191

  À      Alt+0192

  Á      Alt+0193

  Â      Alt+0194

  Ä      Alt+0196

  Ç      Alt+0199

  È      Alt+0200

  É      Alt+0201

  Ê      Alt+0202

  Ë      Alt+0203

  Ì      Alt+0204

  Í      Alt+0205

  Î      Alt+0206

  Ï      Alt+0207

  Ñ      Alt+0209

  Ò      Alt+0210

  Ó      Alt+0211

  Ô      Alt+0212

  Õ      Alt+0213

  Ö      Alt+0214

  Ø      Alt+0216

  Ù      Alt+0217

  Û      Alt+0219

  Ü      Alt+0220

  à      Alt+0224

  á      Alt+0225

  â      Alt+0226

  ã      Alt+0227

  ä      Alt+0228

  å      Alt+0229

  æ      Alt+0230

  ç      Alt+0231

  è      Alt+0232

  é      Alt+0233

  ê      Alt+0234

  ë      Alt+0235

  ì      Alt+0236

  í      Alt+0237

  î      Alt+0238

  ï      Alt+0239

  ñ      Alt+0241

  ò      Alt+0242

  ó      Alt+0243

  ô      Alt+0244

  ö      Alt+0246

  ÷      Alt+0247

  ø      Alt+0248

  ü      Alt+0252



The following characters exist in Mac fonts but not in Windows fonts.  You can use these in plugins, but they will not display correctly
in EVNEW (or in this text document).

 Character description             Character code
 ------------------------------------------------
 Dagger                               Alt+0160
 Paragraph symbol                     Alt+0166
 Superscript trademark symbol (TM)    Alt+0170


Most, if not all, other characters above ASCII 128 will likely not display correctly and may even cause EVN to behave oddly.

Note that these lists may not be complete.  If you find any characters that exists in both fonts but that EVNEW does not convert, find
any characters that are converted incorrectly, or anything else that might be useful for EVNEW users, be sure to let me know.


+------------+
| 5. History |
+------------+

11/11/03: Public Beta 1.0.0 - First public release

11/28/03: Public Beta 1.0.1

-- Bug Fixes --

* Fixed a bug causing a crash when pasting text from the clipboard in a plugin with a str# resource that did not have an open editing window
* Fixed a bug causing the last character of a desc to be cut off when saved
* Fixed a bug that displayed weapon exit point positions in shans as all copies of the first exit point of each type
* Fixed a bug where you could type text into Ship Probability 11 in dudes
* Fixed a bug where you couldn't type A-F into the require field for misns
* Fixed a bug where you couldn't type text into Short Name in ranks
* Fixed a bug where scan fines, smuggling penalties, and disabling penalties in govts were loaded incorrectly
* Fixed a bug loading certain color icons (cicns)
* Fixed a bug where misn ship starts were saved incorrectly

-- Feature Changes --

* Can now translate most character codes between Windows and Mac fonts, such as accented characters and various symbols
* Increased tool tip display time to 10 seconds


1/1/04: Public Beta 1.0.2

-- Bug Fixes --

* Fixed a typo in several AI type combo boxes
* Changed all numeric fields to allow negative numbers to be entered, even if they would be incorrect
* Fixed a rare bug where occasionally certain cicns, when copying or saving them, would trash some memory
* Fixed a bug causing a hang when loading text plugins containing govts
* Fixed a bug where opening a plugin with unsorted resources and immediately saving it as text would cause the resources to remain unsorted
* Fixed a bug where certain rare picts would appear stretched

-- Feature Changes --

* Added command-line support for rez <-> txt conversion
* Added ability to batch-export images and sounds via saving plugins as text
* Added some header data to text plugin format
* Added ability to open selected resource with the Enter key
* Set focus to resource list (instead of resource type list) after closing an editing window, allowing the user to quickly select a new resource using the keyboard


1/30/04: Public Beta 1.0.3

-- Feature Changes --

* Switched temporary file folder from using the system temp folder to a local one


7/28/04: Release 1.0.4

-- Bug Fixes --

* Fixed a bug when importing certain rare sounds

-- Feature Changes --

* Added the ability to choose between using more memory for faster performance when viewing RLE resources (the previous default behavior) or to use less memory for slower performance
* Added the ability to choose the color to display transparent pixels of RLE resources (the previous was always gray, 0x808080)
* RLE masks are now automatically generated after imports, using black as transparent pixels (but masks can still be imported separately, too)


+-------------+
| 6. Legalese |
+-------------+

You use EVNEW at your own risk.  Any crashes, data corruption, or loss of data I will not be held responsible for.

EVNEW is an open-source project.  You may freely use, modify, and distribute the source code, under the conditions that:
(1) The comments at the top of every source file are left unaltered
(2) This Readme.txt file is distributed along with it with this section unaltered
(3) I, Adam Rosenfield, am cited as the original author
(4) You do not sell any part, including the source and executable, for profit.

Escape Velocity and Escape Velocity: Nova are copyrights of Ambrosia Software and ATMOS, et al.


I cannot thank Ambrosia, ATMOS, and Contraband Entertainment enough for making EVN and porting it to Windows.  More thanks go to:

Mehrunes of the Ambrosia webboards, who posted a lot of detailed information on the rez file format
The makers of the open-source projects SpriteWorld and BlitPixie, who helped me understand and work with the RLE image data format
All of the beta testers who have been especially helpful in finding bugs and suggesting new features
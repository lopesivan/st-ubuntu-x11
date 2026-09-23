/* See LICENSE file for copyright and license details. */

#ifndef ST_CONFIG_H
#define ST_CONFIG_H

#include "config/fonts.h"

/* Kerning / character bounding-box multipliers */
static float cwscale = 1.0;
static float chscale = 1.08;

static int borderpx = 2;

/*
 * What program is execed by st depends of these precedence rules:
 * 1: program passed with -e
 * 2: scroll and/or utmp
 * 3: SHELL environment variable
 * 4: value of shell in /etc/passwd
 * 5: value of shell in config.h
 */
static char* shell = "/bin/sh";
char* utmp = NULL;
char* scroll = NULL;
char* stty_args = "stty raw pass8 nl -echo -iexten -cstopb 38400";

/* identification sequence returned in DA and DECID */
char* vtiden = "\033[?6c";

wchar_t* worddelimiters = L" ";

/* selection timeouts (in milliseconds) */
static unsigned int doubleclicktimeout = 300;
static unsigned int tripleclicktimeout = 600;

/* alt screens */
int allowaltscreen = 1;

int allowwindowops = 0;

/*
 * draw latency range in ms - from new content/keypress/etc until drawing.
 * low minlatency will tear/flicker more, as it can "detect" idle too early.
 */
static double minlatency = 2;
static double maxlatency = 16;

/*
 * Synchronized-Update timeout in ms
 * https://gitlab.com/gnachman/iterm2/-/wikis/synchronized-updates-spec
 */
static uint su_timeout = 100;

/*
 * blinking timeout (set to 0 to disable blinking) for the terminal blinking
 * attribute.
 */
static unsigned int blinktimeout = 800;

/*
 * thickness of underline and bar cursors
 */
static unsigned int cursorthickness = 2;

/*
 * 1: render most of the lines/blocks characters without using the font for
 *    perfect alignment between cells
 * 0: disable
 */
const int boxdraw = 1;
const int boxdraw_bold = 0;
const int boxdraw_braille = 0;

/*
 * bell volume. It must be a value between -100 and 100. Use 0 for disabling
 * it
 */
static int bellvolume = 0;

/* default TERM value */
char* termname = "st-256color";

/*
 * spaces per tab
 */
unsigned int tabspaces = 4;

#include "config/colors.h"

/*
 * Default shape of cursor
 * 2: Block ("█")
 * 4: Underline ("_")
 * 6: Bar ("|")
 * 7: Snowman ("☃")
 */
static unsigned int cursorshape = 2;

/*
 * Default columns and rows numbers
 */
static unsigned int cols = 80;
static unsigned int rows = 24;

/*
 * Default colour and shape of the mouse cursor
 */
static unsigned int mouseshape = XC_xterm;
static unsigned int mousefg = 7;
static unsigned int mousebg = 0;

/*
 * Color used to display font attributes when fontconfig selected a font which
 * doesn't match the ones requested.
 */
static unsigned int defaultattr = 11;

/*
 * Force mouse select/shortcuts while mask is active (when MODE_MOUSE is set).
 * Note that if you want to use ShiftMask with selmasks, set this to another
 * modifier, set to 0 to not use it.
 */
static uint forcemousemod = ShiftMask;

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    {"font", STRING, &font},
    {"fontalt0", STRING, &font2[0]},
    {"color0", STRING, &colorname[0]},
    {"color1", STRING, &colorname[1]},
    {"color2", STRING, &colorname[2]},
    {"color3", STRING, &colorname[3]},
    {"color4", STRING, &colorname[4]},
    {"color5", STRING, &colorname[5]},
    {"color6", STRING, &colorname[6]},
    {"color7", STRING, &colorname[7]},
    {"color8", STRING, &colorname[8]},
    {"color9", STRING, &colorname[9]},
    {"color10", STRING, &colorname[10]},
    {"color11", STRING, &colorname[11]},
    {"color12", STRING, &colorname[12]},
    {"color13", STRING, &colorname[13]},
    {"color14", STRING, &colorname[14]},
    {"color15", STRING, &colorname[15]},
    {"foreground", STRING, &colorname[256]},
    {"cursorColor", STRING, &colorname[257]},
    {"background", STRING, &colorname[258]},
    {"revCursorColor", STRING, &colorname[259]},
    {"termname", STRING, &termname},
    {"shell", STRING, &shell},
    {"minlatency", INTEGER, &minlatency},
    {"maxlatency", INTEGER, &maxlatency},
    {"blinktimeout", INTEGER, &blinktimeout},
    {"bellvolume", INTEGER, &bellvolume},
    {"tabspaces", INTEGER, &tabspaces},
    {"borderpx", INTEGER, &borderpx},
    {"cwscale", FLOAT, &cwscale},
    {"chscale", FLOAT, &chscale},
    {"alpha", FLOAT, &alpha},
};

/*
 * Internal mouse shortcuts.
 * Beware that overloading Button1 will disable the selection.
 */
static MouseShortcut mshortcuts[] = {
    /* mask          button   function   argument       release */
    {XK_ANY_MOD, Button2, selpaste, {.i = 0},           1},
    {XK_ANY_MOD, Button4, ttysend,  {.s = "\031"},      0},
    {XK_ANY_MOD, Button5, ttysend,  {.s = "\005"},      0},
};

/* Internal keyboard shortcuts. */
#define MODKEY Mod1Mask
#define TERMMOD (ControlMask | ShiftMask)

#include "config/cmdpipe.h"

#include "config/shortcuts.h"

#include "config/keys.h"

/*
 * Selection types' masks.
 * Use the same masks as usual.
 * Button1Mask is always unset, to make masks match between ButtonPress.
 * ButtonRelease and MotionNotify.
 * If no match is found, regular selection is used.
 */
static uint selmasks[] = {
    [SEL_RECTANGULAR] = Mod1Mask,
};

/*
 * Printable characters in ASCII, used to estimate the advance width
 * of single wide characters.
 */
static char ascii_printable[] = " !\"#$%&'()*+,-./0123456789:;<=>?"
                                "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
                                "`abcdefghijklmnopqrstuvwxyz{|}~";

#endif		// ST_CONFIG_H

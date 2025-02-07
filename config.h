/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 25;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int showdock			= 1;
static const int user_dh			= 80;
static const int docklrmargin		= 64;
static const int user_bh			= 40;		/* 0 means normal bar height, >1 means user bar height */
static const char *fonts[]          = { "JetBrains Mono:style=Regular:size=16", "Symbols Nerd Font:style=2048-em:size=20","JoyPixels:size=16:antialias=true:autohint=true"};
static char dmenufont[]             = "JetBrains Mono:style=Regular:size=16";
static char dmenuh[] = "40";

#include "patches/themes/catpuccin.h"
#define selbordercolor blue
#define normbordercolor gray2

#define tagbarstextcolor black
#define tagbarsbgcolor blue
#define tagbarustextcolor blue
#define tagbarusbgcolor black

#define statustextcolor black
#define statusbgcolor black

#define infobarstextcolor blue
#define infobarsbgcolor black
#define infobarustextcolor black

#define selbgcolor blue2

static char normbgcolor[]           = "#222222";
static char normfgcolor[]           = "#121212";
static char selfgcolor[]            = "#e0ffff";
// static char infobarusbgcolor[]	    = "#878787";

/* Status bar left logo sizes */
static const unsigned int sb_logo_w = 35;
static const unsigned int sb_logo_h = 30;
static const unsigned int sb_logo_y_margin = 5;

/* Default icon width, height, margin and delimiter width */
static const unsigned int sb_icon_wh = 32;
static const unsigned int sb_icon_x_margin = 12;
static const unsigned int sb_delimiter_w = 4;

/* Status bar x  y margin */
static const unsigned int sb_margin = 12;

/* Icon size for status text */
#define ICONSIZE sb_icon_wh
#define ICONSPACING sb_icon_x_margin

static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { blue2,  green,  selbordercolor  },
	   [SchemeStatus] = { statustextcolor, statusbgcolor, "#000000" },
	   [SchemeTagsSel] = { tagbarstextcolor, tagbarsbgcolor, "#000000" },
	   [SchemeTagsNorm] = { tagbarustextcolor, tagbarusbgcolor, "#000000" },
	   [SchemeInfoSel] = { infobarstextcolor, infobarsbgcolor, "#000000" },
	   [SchemeInfoNorm] = { infobarustextcolor, infobarsbgcolor, "#000000" },
	   [SchemeOptimal] = { green, statusbgcolor, "#000000" },
	   [SchemeCritical] = { red, statusbgcolor, "#000000" },
};

const char *key_pdf[] = {TERMINAL, "-n", "key_pdf", "-g", "120x34", "-e", "zathura", "/usr/share/phyos/dwm/keys-dwm.pdf", NULL };

const Config config[] = {
	{key_pdf, "Keys"},
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };

static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "patches/vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */
 	{ "[M]",	monocle },		/* All windows on top of eachother */
	{ "H[]",	deck },			/* Master on left, slaves in monocle-like mode on right */
	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */
	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */
	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL }
};

/* key definitions */
#define MODKEY Mod4Mask
#define MOD2KEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|MOD2KEY,				KEY, 	  swaptags,		  {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", "#000000", "-nf", tagbarustextcolor, "-sb", tagbarsbgcolor, "-sf", tagbarstextcolor, "-h", dmenuh,  NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *layoutmenu_cmd = "layoutmenu.sh";

#include <X11/XF86keysym.h>
#include "patches/shiftview.c"

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
#endif
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MOD2KEY,        Button3,        toggledock,		{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MOD2KEY,        Button1,        hide,			{.i = -1} },
	{ ClkRootWin,			MOD2KEY,  		Button3,		toggledock,		{0} },
	{ ClkLtSymbol,			0,				Button3,		layoutmenu,		{0}	},
	{ ClkRootWin,			MODKEY,			Button4,		shiftview,		{.i = +1} },
	{ ClkRootWin,			MODKEY,			Button5,		shiftview,		{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,			0,				Button4,		shiftview,		{.i = -1} },
	{ ClkTagBar,			0,				Button5,		shiftview,		{.i = 1} },
};

#include "keys.h"


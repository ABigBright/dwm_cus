#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx    = 1;        /* border pixel of windows */
static const unsigned int snap        = 32;       /* snap pixel */
static const unsigned int gappih      = 3;       /* horiz inner gap between windows */
static const unsigned int gappiv      = 3;       /* vert inner gap between windows */
static const unsigned int gappoh      = 3;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov      = 3;       /* vert outer gap between windows and screen edge */
static const int smartgaps            = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar              = 1;        /* 0 means no bar */
static const int topbar               = 0;        /* 0 means bottom bar */
static const Bool viewontag           = True;     /* Switch view on tag switch */
static const int decorhints           = 1;        /* 1 means respect decoration hints */
static const char *fonts[]            = {"FiraCode Nerd Font:size=12"};
static const char dmenufont[]         = "FiraCode Nerd Font:size=12";
static const char col_gray1[]         = "#222222";
static const char col_gray2[]         = "#444444";
static const char col_gray3[]         = "#bbbbbb";
static const char col_gray4[]         = "#ffffff";
static const char col_cyan[]          = "#37474f";
static const char col_black[]         = "#000000";
static const char col_yellow[]        = "#EEB422";
static const char col_green[]         = "#00ff00";
static const char col_border[]        = "#42A5F5";
static const unsigned int baralpha    = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]        = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_border },
	[SchemeHid]  = { col_cyan,  col_gray1, col_border },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeHid]  = { OPAQUE, baralpha, borderalpha },
};

/*  - E5FE */
/*  - E615 */
/*  - E62B */
/*  - E702 */
/*  - E703 */
/*  - E709 */
/*  - E743 */
/*  - E795 */
/*  - F015 */
/* 嗢-FA7B */

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9"}; */

// this icon can be support by nerd font
/* static const char *tags[] = {  */
    /* "", "", "", "", "", "", "", "", "嗢", "" */
/* }; */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp"     , NULL, NULL, 0     , 1, -1 },
	{ "Firefox"  , NULL, NULL, 1 << 1, 0, -1 },
	{ "chromium" , NULL, NULL, 1 << 1, 0, -1 }, // start chrome in tag 1
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2]               = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]         = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]          = { "alacritty", NULL };
static const char *albertcmd[]        = { "albert", "show", NULL };
static const char *rangercmd[]        = { "alacritty", "-e", "ranger", NULL };
static const char *trayercmd[]        = { "/home/briq/.dwm/scripts/trayertoggle.sh", NULL };
static const char *i3lockcmd[]        = { "i3lock", "-i", "~/.dwm/scripts/lock.png", NULL };
static const char* audiomute[]        = {"/home/briq/.dwm/scripts/audiomute.sh", NULL};
static const char* audioraise[]       = {"/home/briq/.dwm/scripts/audioraise.sh", "10"};
static const char* audiolower[]       = {"/home/briq/.dwm/scripts/audiolower.sh", "10"};
static const char* brightnessinc[]    = {"/home/briq/.dwm/scripts/brightnessinc.sh", "10"};
static const char* brightnessdec[]    = {"/home/briq/.dwm/scripts/brightnessdec.sh", "10"};
static const char* touchpadtoggle[]   = {"/home/briq/.dwm/scripts/touchpad_opr.sh", "0"};
static const char* screenshottoggle[] = {"flameshot", "gui",  NULL};


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = albertcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_f,      spawn,          {.v = rangercmd } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = trayercmd } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = i3lockcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
	{ 0,                            XF86XK_AudioMute,          spawn,          {.v = audiomute } },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,          {.v = audiolower } },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,          {.v = audioraise } },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,          {.v = brightnessinc } },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,          {.v = brightnessdec } },
	{ 0,                            XK_Super_L,                spawn,          {.v = touchpadtoggle } },
	{ 0,                            XK_Print,                  spawn,          {.v = screenshottoggle } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


#include "../config.h"

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int bar_height          = BAR_HEIGHT;
static const char *fonts[]          = { FONT };
static const char col_gray1[]       = COL_GRAY1;
static const char col_gray2[]       = COL_GRAY2;
static const char col_gray3[]       = COL_GRAY3;
static const char col_gray4[]       = COL_GRAY4;
static const char col_high[]        = COL_HIGH;
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_high,  col_high  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class                    instance    title       tags mask     isfloating   monitor */
    { "Gnome-calculator",       NULL,       NULL,       0,            1,           -1 },
    { "SimpleScreenRecorder",   NULL,       NULL,       0,            1,           -1 },
    { "java-lang-Thread",       NULL,       "win0",     0,            1,           -1 }, // CLion startup window
    { "jetbrains-toolbox",      NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "gaplessgrid.c"
#include "bottomstack.c"
#include "columns.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[>]",      tile },    /* first entry is default */
    { "[#]",      gaplessgrid },
    { "[v]",      bstack },
    { "[c]",      columns },
    { NULL,       NULL },
    { "[+]",      monocle },
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "j4-dmenu-desktop.sh", dmenumon, NULL };
static const char *termcmd[]  = { "tabbed.sh", NULL };
static const char *fmcmd[]    = { "nautilus", "-w", NULL };
static const char *txtcmd[]    = { "gedit", NULL };
static const char *calccmd[]    = { "gnome-calculator", NULL };
static const char *wwwcmd[]   = { "x-www-browser", NULL };
static const char *wwwicmd[]  = { "x-www-browser", "--incognito", NULL };

static const char *settingscmd[] = { "gnome-control-center", "-o", NULL };
static const char *displaycmd[] = { "gnome-control-center", "display", NULL };

#include "movestack.c"
#include "cyclelayout.c"
#include "shiftview.c"
#include "shiftviewandwindow.c"
#include "combokey.c"

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },      // Run
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },       // Launch terminal
    { MODKEY,                       XK_e,      spawn,          {.v = fmcmd } },         // Launch file manager
    { MODKEY,                       XK_t,      spawn,          {.v = txtcmd } },        // Launch text editor
    { MODKEY,                       XK_c,      spawn,          {.v = calccmd } },       // Launch calculator
    { MODKEY,                       XK_n,      spawn,          {.v = wwwcmd } },        // Launch browser
    { MODKEY|ShiftMask,             XK_n,      spawn,          {.v = wwwicmd } },       // Launch browser incognito
    { MODKEY,                       XK_s,      spawn,          {.v = settingscmd } },   // Settings
    { MODKEY,                       XK_d,      spawn,          {.v = displaycmd } },    // Display settings

    { MODKEY,                       XK_b,      togglebar,      {0} },                   // Toggle bar visibility

    { MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },            // Focus next window
    { MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },            // Focus previous window
    { MODKEY|ShiftMask,             XK_Down,   movestack,      {.i = +1 } },            // Move window forward
    { MODKEY|ShiftMask,             XK_Up,     movestack,      {.i = -1 } },            // Move window backward

    { Mod1Mask,                     XK_Tab,    focusstack,     {.i = +1 } },            // Focus next window

    { MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },          // Decrease master width
    { MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },          // Increase master width

    { MODKEY,                       XK_period, incnmaster,     {.i = +1 } },            // Increase number of master windows
    { MODKEY,                       XK_comma,  incnmaster,     {.i = -1 } },            // Decrease number of master windows

    { MODKEY,                       XK_Return, zoom,           {0} },                   // Swap master window
    { MODKEY,                       XK_q,      killclient,     {0} },                   // Close window
    //{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },    // Set layout to "tile"
    { MODKEY,                       XK_space,  cyclelayout,    {.i = +1 } },            // Cycle tiled layouts
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[LENGTH(layouts) - 2]} },    // Set layout to "monocle"

    { MODKEY,                       XK_f,      togglefloating, {0} },                   // Toggle window floating

    { MODKEY,                       XK_Tab,    focusmon,       {.i = +1 } },            // Focus next monitor
    { MODKEY|ShiftMask,             XK_Tab,    tagmon,         {.i = +1 } },            // Move window to next monitor

    { MODKEY,                       XK_Next,   shiftview,      {.i = +1 } },            // Focus next tag
    { MODKEY,                       XK_Prior,  shiftview,      {.i = -1 } },            // Focus previous tag

    { MODKEY|ShiftMask,             XK_Next,   shiftviewandwindow, {.i = +1 } },        // Focus next tag bringing window
    { MODKEY|ShiftMask,             XK_Prior,  shiftviewandwindow, {.i = -1 } },        // Focus previous tag bringing window

    { MODKEY,                       XK_r,      reset,          {0} },                   // Reset settings for current tag

    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },                   // Quit DWM

    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)

    { MODKEY,                       XK_x,       combokey,      {.i = +1 } },            // Combo key for mouse: zoom in tiling layouts, focusstack in monocle
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1 } },           // Cycle tiled layouts
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[LENGTH(layouts) - 2]} },   // Set layout to "monocle"
    { ClkWinTitle,          0,              Button1,        focusstack,     {.i = +1 } },           // Focus next window
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


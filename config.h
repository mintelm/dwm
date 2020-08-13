#include <X11/XF86keysym.h>

/* general */
static const int nmaster           = 1;         /* number of clients in master area */
static const int resizehints       = 0;         /* 1 means respect size hints in tiled resizals */
static const float mfact           = 0.55;      /* factor of master area size [0.05..0.95] */
static const unsigned int borderpx = 3;         /* border pixel of windows */
static const unsigned int snap     = 32;        /* snap pixel */

/* gaps */
static const int smartgaps       = 0;           /* 1 means no outer gap when there is only one window */
static const unsigned int gappih = 30;          /* horiz inner gap between windows */
static const unsigned int gappiv = 30;          /* vert inner gap between windows */
static const unsigned int gappoh = 20;          /* horiz outer gap between windows and screen edge */
static const unsigned int gappov = 30;          /* vert outer gap between windows and screen edge */

/* status bar */
static const int showbar = 1;                   /* 0 means no bar */
static const int topbar  = 1;                   /* 0 means bottom bar */
static const int user_bh = 30;                  /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

/* systray */
static const int showsystray             = 1;   /* 0 means no systray */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const unsigned int systraypadding = 12;  /* systray padding */

/* fonts */
static const char *fonts[]          = {
        "Fiora Code:style:Medium:size=10:antialias=true:autohint=true",
        "Symbols Nerd Font:size=13:antialias=true:autohint=true",
};

/* colors */
static const char col_fg[]          = "#ebdbb2";
static const char col_fg2[]         = "#987c76";
static const char col_bg[]          = "#1d2021";
static const char col_bg2[]         = "#3c3836";
static const char col_sel[]         = "#fe8019";
static const char *colors[][3]      = {
        /*                   fg         bg         border   */
        [SchemeNorm]     = { col_fg,    col_bg,    col_bg2 },
        [SchemeSel]      = { col_bg2,   col_sel,   col_sel },
        [SchemeTaskNorm] = { col_fg,    col_bg,    col_bg2 },
        [SchemeTaskSel]  = { col_fg,    col_bg2,   col_sel },
        [SchemeTaskHid]  = { col_fg2,   col_bg,    col_sel },
};

/* autostart */
static const char *const autostart[] = {
        "element-desktop", "--hidden", NULL,
        "nm-applet", NULL,
        "redshift-gtk", NULL,
        "feh", "--bg-max", "/usr/share/backgrounds/sunset.png", NULL,
        "pulse_daemon", NULL,
        "dwmblocks", NULL,
        // "picom", "--experimental-backends", NULL,
        NULL /* terminate */
};

/* tags */
static const char *tags[] = { "", "", "", "" };

/* rules */
static const Rule rules[] = {
        /* xprop(1):
         *      WM_CLASS(STRING) = instance, class
         *      WM_NAME(STRING) = title
         */
        /* class        instance    title       tags mask     isCentered   isFloating   monitor */
        { "Galculator", NULL,       NULL,       0,            1,           1,           -1 },
        { "Gpick",      NULL,       NULL,       0,            1,           1,           -1 },
        { "Pavucontrol",NULL,       NULL,       0,            0,           1,           -1 },
};

/* layouts */
static const Layout layouts[] = {
        /* symbol     arrange function */
        { "[]=",      tile },    /* first entry is default */
        { "TTT",      bstack },
        { "[M]",      monocle },
        { "><>",      NULL },    /* no layout function means floating behavior */
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
static const char *roficmd[]    = { "rofi", "-show", "run", "-theme", "gruvbox.rasi", "-lines", "7", NULL };
static const char *browsercmd[] = { "google-chrome-stable", NULL };
static const char *calccmd[]    = { "galculator", NULL };

static Key keys[] = {
        /* modifier                     key                     function        argument */
        TAGKEYS(                        XK_1,                                   0)
        TAGKEYS(                        XK_2,                                   1)
        TAGKEYS(                        XK_3,                                   2)
        TAGKEYS(                        XK_4,                                   3)
        { MODKEY,                       XK_r,                   spawn,          {.v = roficmd } },
        { MODKEY,                       XK_Return,              spawn,          SHCMD("st") },
        { MODKEY,                       XK_w,                   spawn,          {.v = browsercmd } },
        { MODKEY,                       XK_c,                   spawn,          {.v = calccmd } },
        { MODKEY,                       XK_j,                   focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,                   focusstack,     {.i = -1 } },
        { MODKEY,                       XK_a,                   incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_x,                   incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,                   setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,                   setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_t,                   setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_b,                   setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_m,                   setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_f,                   setlayout,      {.v = &layouts[3]} },
        { MODKEY|ShiftMask,             XK_f,                   togglefloating, {0} },
        { MODKEY,                       XK_Tab,                 view,           {0} },
        { MODKEY,                       XK_space,               zoom,           {0} },
        { MODKEY|ShiftMask,             XK_q,                   killclient,     {0} },
        { MODKEY,                       XK_comma,               focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period,              focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_r,                   quit,           {0} },
        { 0,                    XF86XK_MonBrightnessDown,       spawn,          SHCMD("dec_brightness") },
        { 0,                    XF86XK_MonBrightnessUp,         spawn,          SHCMD("inc_brightness") },
        { 0,                    XF86XK_AudioLowerVolume,        spawn,          SHCMD("pamixer -d 5") },
        { 0,                    XF86XK_AudioRaiseVolume,        spawn,          SHCMD("pamixer -i 5") },
        { 0,                    XF86XK_AudioMute,               spawn,          SHCMD("pamixer --toggle-mute") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
        /* click                event mask      button          function        argument */
        { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
        { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
        { ClkWinTitle,          0,              Button2,        zoom,           {0} },
        { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
        { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
        { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
        { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
        { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
        { ClkWinTitle,          0,              Button1,        togglewin,      {0} },
        { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
        { ClkTagBar,            0,              Button1,        view,           {0} },
        { ClkTagBar,            0,              Button3,        toggleview,     {0} },
        { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
        { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


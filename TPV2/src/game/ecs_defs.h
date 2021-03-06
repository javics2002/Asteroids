// This file is part of the course TPV2@UCM - Samir Genaim


#pragma once

// Components list - must have at least one element
//
#define _CMPS_LIST_ \
	_TRANSFORM, \
	_IMAGE, \
	_FIGHTERCTRL, \
	_STARMOTION, \
	_GAMECTRL, \
	_STOPONBORDER, \
	_SHOWATOPPOSITESIDE, \
	_DISABLEONEXIT, \
	_FRAMEDIMAGE, \
	_FOLLOW, \
	_GENERATIONS, \
	_HEALTH, \
	_DEACCELERATION, \
	_GUN, \
	_GAMESTATE


// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	_grp_ASTEROIDS, \
	_grp_STARS, \
	_grp_BULLETS

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    _hdlr_CAZA, \
	_hdlr_GAMEINFO

// Systems list - must have at least one element
//
#define _SYS_LIST_ \
    _hdlr_COLLISION, \
	_hdlr_RENDER, \
	_hdlr_GAMECTRL, \
	_hdlr_ASTEROIDS, \
	_hdlr_BULLETS, \
	_hdlr_FIGHTER, \
	_hdlr_FIGHTERGUN
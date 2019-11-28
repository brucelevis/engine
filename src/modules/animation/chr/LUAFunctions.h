/**
 * @file
 */

#pragma once

#include "CharacterSettings.h"
#include "commonlua/LUA.h"
#include "core/String.h"
#include "animation/LUAShared.h"

namespace animation {

static CharacterSettings* luaGetAnimationSettings(lua_State * l) {
	return lua::LUA::globalData<CharacterSettings>(l, "Settings");
}

static int luaChr_SetRace(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->race = luaL_checkstring(l, 1);
	return 0;
}

static int luaChr_SetGender(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->gender = luaL_checkstring(l, 1);
	return 0;
}

static int luaChr_SetChest(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->setPath(CharacterMeshType::Chest, luaL_checkstring(l, 1));
	return 0;
}

static int luaChr_SetBelt(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->setPath(CharacterMeshType::Belt, luaL_checkstring(l, 1));
	return 0;
}

static int luaChr_SetPants(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->setPath(CharacterMeshType::Pants, luaL_checkstring(l, 1));
	return 0;
}

static int luaChr_SetHand(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->setPath(CharacterMeshType::Hand, luaL_checkstring(l, 1));
	return 0;
}

static int luaChr_SetFoot(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->setPath(CharacterMeshType::Foot, luaL_checkstring(l, 1));
	return 0;
}

static int luaChr_SetHead(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->setPath(CharacterMeshType::Head, luaL_checkstring(l, 1));
	return 0;
}

static int luaChr_SetShoulder(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->setPath(CharacterMeshType::Shoulder, luaL_checkstring(l, 1));
	return 0;
}

static int luaChr_SetScaler(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.scaler = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetHeadScale(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.headScale = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetNeckHeight(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.neckHeight = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetNeckForward(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.neckForward = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetNeckRight(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.neckRight = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetHandForward(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.handForward = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetHandRight(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.handRight = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetShoulderForward(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.shoulderForward = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetShoulderRight(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.shoulderRight = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetToolForward(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.toolForward = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetToolRight(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.toolRight = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetToolScale(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.toolScale = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetShoulderScale(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.shoulderScale = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetHeadHeight(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.headHeight = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetFootRight(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.footRight = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetChestHeight(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.chestHeight = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetBeltHeight(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.beltHeight = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetPantsHeight(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.pantsHeight = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetInvisibleLegHeight(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.invisibleLegHeight = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetFootHeight(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.footHeight = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetOrigin(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.origin = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetHipOffset(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.hipOffset = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetJumpTimeFactor(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.jumpTimeFactor = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetIdleTimeFactor(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.idleTimeFactor = luaL_checknumber(l, 1);
	return 0;
}

static int luaChr_SetRunTimeFactor(lua_State * l) {
	CharacterSettings *settings = luaGetAnimationSettings(l);
	settings->skeletonAttr.runTimeFactor = luaL_checknumber(l, 1);
	return 0;
}

}
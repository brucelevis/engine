/**
 * @file
 */

#include "Zone.h"
#include "core/Trace.h"
#include "backend/entity/ai/tree/TreeNode.h"

namespace backend {

Zone::~Zone() {
	_threadPool.shutdown();
	for (const auto& e : _ais) {
		e.second->setZone(nullptr);
		_groupManager.removeFromAllGroups(e.second);
	}
	for (const auto& ai : _scheduledAdd) {
		ai->setZone(nullptr);
		_groupManager.removeFromAllGroups(ai);
	}
	for (const auto& ai : _scheduledRemove) {
		doRemoveAI(ai);
	}
	_ais.clear();
}

AIPtr Zone::getAI(ai::CharacterId id) const {
	core::ScopedLock scopedLock(_lock);
	auto i = _ais.find(id);
	if (i == _ais.end()) {
		return AIPtr();
	}
	const AIPtr& ai = i->second;
	return ai;
}

size_t Zone::size() const {
	core::ScopedLock scopedLock(_lock);
	return _ais.size();
}

bool Zone::doAddAI(const AIPtr& ai) {
	if (ai == nullptr) {
		return false;
	}
	const ai::CharacterId& id = ai->getCharacter()->getId();
	if (_ais.find(id) != _ais.end()) {
		return false;
	}
	_ais.insert(std::make_pair(id, ai));
	ai->setZone(this);
	return true;
}

bool Zone::doRemoveAI(const ai::CharacterId& id) {
	AIMapIter i = _ais.find(id);
	if (i == _ais.end()) {
		return false;
	}
	i->second->setZone(nullptr);
	_groupManager.removeFromAllGroups(i->second);
	_ais.erase(i);
	return true;
}

bool Zone::doDestroyAI(const ai::CharacterId& id) {
	AIMapIter i = _ais.find(id);
	if (i == _ais.end()) {
		return false;
	}
	_ais.erase(i);
	return true;
}

bool Zone::addAI(const AIPtr& ai) {
	if (!ai) {
		return false;
	}
	core::ScopedLock scopedLock(_scheduleLock);
	_scheduledAdd.push_back(ai);
	return true;
}

bool Zone::destroyAI(const ai::CharacterId& id) {
	core::ScopedLock scopedLock(_scheduleLock);
	_scheduledDestroy.push_back(id);
	return true;
}

bool Zone::removeAI(const ai::CharacterId& id) {
	core::ScopedLock scopedLock(_scheduleLock);
	_scheduledRemove.push_back(id);
	return true;
}

void Zone::update(int64_t dt) {
	core_trace_scoped(ZoneUpdate);
	{
		CharacterIdList scheduledRemove;
		AIScheduleList scheduledAdd;
		CharacterIdList scheduledDestroy;
		{
			core::ScopedLock scopedLock(_scheduleLock);
			scheduledAdd.swap(_scheduledAdd);
			scheduledRemove.swap(_scheduledRemove);
			scheduledDestroy.swap(_scheduledDestroy);
		}
		core::ScopedLock scopedLock(_lock);
		for (const AIPtr& ai : scheduledAdd) {
			doAddAI(ai);
		}
		scheduledAdd.clear();
		for (auto id : scheduledRemove) {
			doRemoveAI(id);
		}
		scheduledRemove.clear();
		for (auto id : scheduledDestroy) {
			doDestroyAI(id);
		}
		scheduledDestroy.clear();
	}

	auto func = [&] (const AIPtr& ai) {
		if (ai->isPause()) {
			return;
		}
		ai->update(dt, _debug);
		ai->getBehaviour()->execute(ai, dt);
	};
	executeParallel(func);
	_groupManager.update(dt);
}

}

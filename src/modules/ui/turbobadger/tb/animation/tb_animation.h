/**
 * @file
 */

#pragma once

#include "tb_linklist.h"
#include "tb_object.h"

namespace tb {

class TBAnimationObject;

/** Defines how the animation progress value is interpolated. */
enum ANIMATION_CURVE {
	ANIMATION_CURVE_LINEAR,	///< Linear
	ANIMATION_CURVE_SLOW_DOWN, ///< Fast start, slow end
	ANIMATION_CURVE_SPEED_UP,  ///< Slow start, fast end
	ANIMATION_CURVE_BEZIER,	///< Slow start, slow end. Almost linear.
	ANIMATION_CURVE_SMOOTH	 ///< Slow start, slow end. Stronger than ANIMATION_CURVE_BEZIER.
};

/** Defines what the animation duration time is relative to. */
enum ANIMATION_TIME {

	/** The start time begins when the animation start in TBAnimationManager::startAnimation. */
	ANIMATION_TIME_IMMEDIATELY,

	/** The animation start in StartAnimation just as with ANIMATION_TIME_IMMEDIATELY,
		but the start time is adjusted to when the animations Update is about to be called
		the first time since it was started.

		Using this is most often preferable since starting a animation is often accompanied
		with some extra work that might eat up a considerable time of the total duration (and
		chop of the beginning of it).

		F.ex: Creating a window and starting its appearance animation. During initialization
		of the window, you might initiate loading of additional resources. When that is done
		and you finally end up updating animations, most of the animation time might already
		have passed. If the animation start time is adjusted to the first update, the whole
		animation will run from 0.0 - 1.0 smoothly when the initialization is done. */
	ANIMATION_TIME_FIRST_UPDATE
};

#define ANIMATION_DEFAULT_CURVE ANIMATION_CURVE_SLOW_DOWN
#define ANIMATION_DEFAULT_DURATION 200

/** TBAnimationListener - Listens to the progress of TBAnimationObject. */

class TBAnimationListener : public TBLinkOf<TBAnimationListener> {
public:
	virtual ~TBAnimationListener(){};

	/** Called after the animation object handled its own OnAnimationStart.
		See TBAnimationObject::onAnimationStart for details. */
	virtual void onAnimationStart(TBAnimationObject *obj) = 0;

	/** Called after the animation object handled its own OnAnimationStart.
		See TBAnimationObject::onAnimationUpdate for details. */
	virtual void onAnimationUpdate(TBAnimationObject *obj, float progress) = 0;

	/** Called after the animation object handled its own OnAnimationStart.
		See TBAnimationObject::onAnimationStop for details. */
	virtual void onAnimationStop(TBAnimationObject *obj, bool aborted) = 0;
};

/** TBAnimationObject - Base class for all animated object */

class TBAnimationObject : public TBTypedObject, public TBLinkOf<TBAnimationObject> {
public:
	ANIMATION_CURVE animation_curve;
	double animation_start_time;
	double animation_duration;
	bool adjust_start_time;

public:
	// For safe typecasting
	TBOBJECT_SUBCLASS(TBAnimationObject, TBTypedObject);

	virtual ~TBAnimationObject() {
	}

	/** Return true if the object is currently animating. */
	bool isAnimating() const {
		return linklist ? true : false;
	}

	/** Called on animation start */
	virtual void onAnimationStart() = 0;

	/** Called on animation update. progress is current progress from 0 to 1.
		Note that it isn't called on start, so progress 0 might not happen.
		It will be called with progress 1 before the animation is completed normally (not aborted) */
	virtual void onAnimationUpdate(float progress) = 0;

	/** Called on animation stop. aborted is true if it was aborted before completion.
		Note that if a animation is started when it's already running, it will first
		be aborted and then started again. */
	virtual void onAnimationStop(bool aborted) = 0;

	/** Add an listener to this animation object. */
	void addListener(TBAnimationListener *listener) {
		m_listeners.addLast(listener);
	}

	/** Remove an listener from this animation object. */
	void removeListener(TBAnimationListener *listener) {
		m_listeners.remove(listener);
	}

private:
	friend class TBAnimationManager;
	TBLinkListOf<TBAnimationListener> m_listeners;
	void invokeOnAnimationStart();
	void invokeOnAnimationUpdate(float progress);
	void invokeOnAnimationStop(bool aborted);
};

/** TBAnimationManager - System class that manages all animated object */

class TBAnimationManager {
private:
	static TBLinkListOf<TBAnimationObject> animating_objects;

public:
	/** Update all running animations. */
	static void update();

	/** Return true if there are running animations. */
	static bool hasAnimationsRunning();

	static void startAnimation(TBAnimationObject *obj, ANIMATION_CURVE animation_curve = ANIMATION_DEFAULT_CURVE,
							   double animation_duration = ANIMATION_DEFAULT_DURATION,
							   ANIMATION_TIME animation_time = ANIMATION_TIME_FIRST_UPDATE);
	/** Abort the animation. If delete_animation is true, the animation will be deleted in
		this call after running callbacks and listeners callbacks. In rare situations,
		you might want to keep the animation around and delete it later (or start it
		again). */
	static void abortAnimation(TBAnimationObject *obj, bool delete_animation);

	/** Abort and delete all animations. */
	static void abortAllAnimations();

	/** Return true if new animations are blocked. */
	static bool isAnimationsBlocked();

	/** Begin a period of blocking new animations. End the period with EndBlockAnimations.
		If StartAnimation is called during the blocked period, the animation object will
		finish the next animation update as it completed normally. */
	static void beginBlockAnimations();

	/** End a period of blocking new animations that was started with BeginBlockAnimations. */
	static void endBlockAnimations();
};

/** TBAnimationBlocker blocks new animations during its lifetime.
	It's convenient to put on the stack to block new animations
	within a scope of code. */
class TBAnimationBlocker {
public:
	TBAnimationBlocker() {
		TBAnimationManager::beginBlockAnimations();
	}
	~TBAnimationBlocker() {
		TBAnimationManager::endBlockAnimations();
	}
};

} // namespace tb

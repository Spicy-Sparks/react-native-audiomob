package com.audiomob

import com.audiomob.sdk.AudiomobPlugin
import com.audiomob.sdk.data.responses.AdAvailability
import com.audiomob.sdk.data.responses.AudioAd
import com.audiomob.sdk.enums.AdPlaybackResult
import com.audiomob.sdk.enums.AdRequestResult
import com.audiomob.sdk.enums.PauseAdEnum
import com.audiomob.sdk.enums.Placement
import com.audiomob.sdk.interfaces.managers.IAudiomobCallback
import com.facebook.react.bridge.Arguments
import com.facebook.react.bridge.LifecycleEventListener
import com.facebook.react.bridge.Promise
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactContext
import com.facebook.react.bridge.ReactContextBaseJavaModule
import com.facebook.react.bridge.ReactMethod
import com.facebook.react.bridge.WritableMap
import com.facebook.react.modules.core.DeviceEventManagerModule

class AudiomobModule(reactContext: ReactApplicationContext) : ReactContextBaseJavaModule(reactContext),
  LifecycleEventListener, IAudiomobCallback {

  private var audiomobPlugin: AudiomobPlugin? = null

  override fun getName(): String {
    return NAME
  }

  companion object {
    const val NAME = "Audiomob"
  }

  init {
    reactContext.addLifecycleEventListener(this)
  }

  private fun sendEvent(reactContext: ReactContext, eventName: String, params: WritableMap?) {
    reactContext
      .getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter::class.java)
      .emit(eventName, params)
  }

  @ReactMethod
  fun init(apiKey: String, bundleId: String, promise: Promise) {
    audiomobPlugin = AudiomobPlugin(reactApplicationContext)
    audiomobPlugin?.initialise(apiKey, bundleId)
    audiomobPlugin?.setCallbacks(this)
    audiomobPlugin?.getAdAvailability(Placement.SKIPPABLE)
    promise.resolve(null)
  }

  @ReactMethod
  fun showAd(promise: Promise) {
    audiomobPlugin?.requestAndPlayAd()
  }

  @ReactMethod
  fun play(promise: Promise) {
    audiomobPlugin?.resumePausedAd()
    promise.resolve(null);
  }

  @ReactMethod
  fun pause(promise: Promise) {
    audiomobPlugin?.pauseAd();
    promise.resolve(null);
  }

  @ReactMethod
  fun isPaused(promise: Promise) {
    promise.resolve(audiomobPlugin?.isAdPaused());
  }

  override fun onHostResume() {
    audiomobPlugin?.resumeLifeCycle()
  }

  override fun onHostPause() {
    audiomobPlugin?.pauseLifeCycle()
  }

  override fun onHostDestroy() {
    audiomobPlugin?.removeCallbacks(this)
    audiomobPlugin?.release()
  }

  override fun onAdAvailabilityRetrieved(result: AdAvailability) {
    if (BuildConfig.DEBUG || result.adsAvailable == true) {
      sendEvent(reactApplicationContext, "INIT_COMPLETED", null)
    }
  }

  override fun onAdPlaybackCompleted(adPlaybackResult: AdPlaybackResult) {
    sendEvent(reactApplicationContext, "AUDIOAD_ENDED", null)
  }

  override fun onAdPlaybackPaused(pauseReason: PauseAdEnum) {
    sendEvent(reactApplicationContext, "AUDIOAD_PAUSED", null)
  }

  override fun onAdPlaybackResumed() {
    sendEvent(reactApplicationContext, "AUDIOAD_RESUMED", null)
  }

  override fun onAdPlaybackStarted(audioAd: AudioAd) {
    sendEvent(reactApplicationContext, "AUDIOAD_OPENED", null)
  }

  override fun onAdRequestCompleted(adRequestResult: AdRequestResult, audioAd: AudioAd?) {
    if (adRequestResult != AdRequestResult.FINISHED) {
      val args = Arguments.createMap()
      if (audioAd != null) {
        args.putString("bannerImage", audioAd.companionBanner?.image.toString())
        args.putLong("estimatedCpm", audioAd.estimatedCpm.toLong())
        args.putLong("estimatedRevenue", audioAd.estimatedRevenue.toLong())
        args.putLong("duration", audioAd.duration.toLong())
      }
      sendEvent(reactApplicationContext, "AUDIOAD_LOADED", args)
    }
    else sendEvent(reactApplicationContext, "AUDIOAD_FAILED_TO_LOAD", null)
  }

  override fun onAdRequestStarted() {
  }
}

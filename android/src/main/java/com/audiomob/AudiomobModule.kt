package com.audiomob

import com.audiomob.sdk.AudiomobPlugin
import com.audiomob.sdk.data.responses.AdAvailability
import com.audiomob.sdk.data.responses.AudioAd
import com.audiomob.sdk.enums.AdPlaybackResult
import com.audiomob.sdk.enums.AdRequestResult
import com.audiomob.sdk.enums.PauseAdEnum
import com.audiomob.sdk.enums.Placement
import com.audiomob.sdk.interfaces.managers.IAudiomobCallback
import com.facebook.react.bridge.LifecycleEventListener
import com.facebook.react.bridge.Promise
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactContextBaseJavaModule
import com.facebook.react.bridge.ReactMethod

class AudiomobModule(reactContext: ReactApplicationContext) : ReactContextBaseJavaModule(reactContext),
  LifecycleEventListener, IAudiomobCallback {

  private var audiomobPlugin: AudiomobPlugin? = null

  override fun getName(): String {
    return NAME
  }

  init {
    reactContext.addLifecycleEventListener(this)
  }

  @ReactMethod
  fun init(apiKey: String, bundleId: String, promise: Promise) {
    audiomobPlugin = AudiomobPlugin(reactApplicationContext)
    audiomobPlugin?.initialise(apiKey, bundleId)
    audiomobPlugin?.setCallbacks(this)
    promise.resolve(null)
  }

  @ReactMethod
  fun showAd(promise: Promise) {
    audiomobPlugin?.getAdAvailability(Placement.REWARDED)
  }

  @ReactMethod
  fun play(promise: Promise) {
    audiomobPlugin?.resumePausedAd()
  }

  @ReactMethod
  fun pause(promise: Promise) {
    audiomobPlugin?.pauseAd();
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

  companion object {
    const val NAME = "Audiomob"
  }

  override fun onAdAvailabilityRetrieved(result: AdAvailability) {
    if (BuildConfig.DEBUG || result.adsAvailable == true)
      audiomobPlugin?.requestAndPlayAd()
  }

  override fun onAdPlaybackCompleted(adPlaybackResult: AdPlaybackResult) {
  }

  override fun onAdPlaybackPaused(pauseReason: PauseAdEnum) {
  }

  override fun onAdPlaybackResumed() {
  }

  override fun onAdPlaybackStarted(audioAd: AudioAd) {
  }

  override fun onAdRequestCompleted(adRequestResult: AdRequestResult, audioAd: AudioAd?) {
  }

  override fun onAdRequestStarted() {
  }
}

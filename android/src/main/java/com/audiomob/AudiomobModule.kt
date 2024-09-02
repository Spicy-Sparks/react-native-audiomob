package com.audiomob

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.os.StrictMode
import android.util.Base64
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
import com.facebook.react.bridge.UiThreadUtil.runOnUiThread
import com.facebook.react.bridge.WritableMap
import com.facebook.react.modules.core.DeviceEventManagerModule
import java.io.ByteArrayOutputStream
import java.net.URL


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
    runOnUiThread {
      audiomobPlugin?.resumePausedAd()
      promise.resolve(null);
    }
  }

  @ReactMethod
  fun pause(promise: Promise) {
    runOnUiThread {
      audiomobPlugin?.pauseAd()
      promise.resolve(null);
    }
  }

  @ReactMethod
  fun isPaused(promise: Promise) {
    runOnUiThread {
      promise.resolve(audiomobPlugin?.isAdPaused());
    }
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
    if (adRequestResult == AdRequestResult.FINISHED) {
      val args = Arguments.createMap()
      if (audioAd != null) {
        if(audioAd.companionBanner?.image != null) {
          val outputStream = ByteArrayOutputStream()
          audioAd.companionBanner?.image?.compress(Bitmap.CompressFormat.PNG, 100, outputStream)
          args.putString("bannerImage", "data:image/png;base64," + Base64.encodeToString(outputStream.toByteArray(), Base64.DEFAULT))
        }
        args.putDouble("estimatedCpm", audioAd.estimatedCpm.toDouble())
        args.putDouble("estimatedRevenue", audioAd.estimatedRevenue.toDouble())
        args.putDouble("duration", audioAd.duration.toDouble())
      }
      sendEvent(reactApplicationContext, "AUDIOAD_LOADED", args)
    }
    else sendEvent(reactApplicationContext, "AUDIOAD_FAILED_TO_LOAD", null)
  }

  override fun onAdRequestStarted() {
  }
}

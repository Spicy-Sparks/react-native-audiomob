package com.audiomob

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.os.Build
import android.os.StrictMode
import android.util.Base64
import androidx.annotation.RequiresApi
import com.audiomob.sdk.AudiomobConfig
import com.audiomob.sdk.AudiomobPlugin
import com.audiomob.sdk.data.callbacks.AdPlaybackStatus
import com.audiomob.sdk.data.callbacks.AudiomobAdData
import com.audiomob.sdk.data.callbacks.AudiomobAdEcpm
import com.audiomob.sdk.data.callbacks.AudiomobAdSequence
import com.audiomob.sdk.data.enums.AdPlaybackResult
import com.audiomob.sdk.data.enums.AdStatus
import com.audiomob.sdk.data.enums.FailureReason
import com.audiomob.sdk.data.enums.InitializationStatus
import com.audiomob.sdk.data.enums.PauseAdEnum
import com.audiomob.sdk.data.responses.AdAvailability
import com.audiomob.sdk.data.responses.AudioAd
import com.audiomob.sdk.interfaces.managers.IAudiomobCallback
import com.audiomob.sdk.managers.AdUnitIds
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
    AudiomobPlugin.initialize(reactApplicationContext, apiKey, bundleId, true);
    AudiomobPlugin.getInstance().setCallbacks(this)
    promise.resolve(null)
  }

  @ReactMethod
  fun showAd(promise: Promise) {
    AudiomobPlugin.getInstance().playBackgroundAd(AdUnitIds.BACKGROUND)
  }

  @ReactMethod
  fun play(promise: Promise) {
    runOnUiThread {
      AudiomobPlugin.getInstance().resumePausedAd()
      promise.resolve(null);
    }
  }

  @ReactMethod
  fun pause(promise: Promise) {
    runOnUiThread {
      AudiomobPlugin.getInstance().pauseAd()
      promise.resolve(null);
    }
  }

  @ReactMethod
  fun isPaused(promise: Promise) {
    runOnUiThread {
      promise.resolve(AudiomobPlugin.getInstance().getAdStatus() == AdStatus.PAUSED);
    }
  }

  override fun onHostResume() {
    AudiomobPlugin.getInstance().resumeLifeCycle()
  }

  override fun onHostPause() {
    AudiomobPlugin.getInstance().pauseLifeCycle()
  }

  override fun onHostDestroy() {
    AudiomobPlugin.getInstance().release()
  }

  override fun onAdClicked(adUnitId: String) {
  }

  override fun onAdDataAvailable(adData: AudiomobAdData) {
    // Show the banner image in the media controls.
    /*if (adData.adCompanionBanner != null) {
      val banner = adData.adCompanionBanner!!.image
    }*/

    val args = Arguments.createMap()

    if (adData.adCompanionBanner?.image != null) {
      val outputStream = ByteArrayOutputStream()
      adData.adCompanionBanner?.image?.compress(Bitmap.CompressFormat.PNG, 100, outputStream)
      args.putString("bannerImage", "data:image/png;base64," + Base64.encodeToString(outputStream.toByteArray(), Base64.DEFAULT))
    }
    args.putDouble("estimatedCpm", AudiomobPlugin.getInstance().getAdEcpm(AdUnitIds.BACKGROUND).value.toDouble())
    args.putDouble("estimatedRevenue", AudiomobPlugin.getInstance().getAdEcpm(AdUnitIds.BACKGROUND).value.toDouble() / 1000)
    //args.putDouble("duration",)
    sendEvent(reactApplicationContext, "AUDIOAD_LOADED", args)
  }

  override fun onAdFailed(adUnitId: String, failureReason: FailureReason) {
    sendEvent(reactApplicationContext, "AUDIOAD_FAILED_TO_LOAD", null)
  }

  override fun onAdPaid(audiomobAdEcpm: AudiomobAdEcpm) {
  }

  override fun onAdPlaybackPaused(pauseReason: PauseAdEnum) {
  }

  override fun onAdPlaybackStatusChanged(
    adSequence: AudiomobAdSequence?,
    status: AdPlaybackStatus
  ) {
    when (status) {
      AdPlaybackStatus.STARTED -> {
        // The ad has been started.
        val args = Arguments.createMap()
        if(adSequence != null) {
          args.putDouble("duration", adSequence.duration.toDouble())
        }

        sendEvent(reactApplicationContext, "AUDIOAD_OPENED", args)
      }

      AdPlaybackStatus.PAUSED -> {
        // The ad has been paused.
        sendEvent(reactApplicationContext, "AUDIOAD_PAUSED", null)
      }

      AdPlaybackStatus.RESUMED -> {
        // The ad has been resumed.
        sendEvent(reactApplicationContext, "AUDIOAD_RESUMED", null)
      }

      AdPlaybackStatus.STOPPED -> {
        // The ad has been stopped.
        //sendEvent(reactApplicationContext, "AUDIOAD_FAILED_TO_LOAD", null)
      }
      AdPlaybackStatus.FAILED -> {
        // The ad has been failed.
        //sendEvent(reactApplicationContext, "AUDIOAD_FAILED_TO_LOAD", null)
      }
      AdPlaybackStatus.SKIPPED -> {
        // The ad has been skipped.
        sendEvent(reactApplicationContext, "AUDIOAD_ENDED", null)
      }
      AdPlaybackStatus.CANCELED -> {
        // The ad has been canceled.
        //sendEvent(reactApplicationContext, "AUDIOAD_FAILED_TO_LOAD", null)
      }
      AdPlaybackStatus.FINISHED ->{
        // The ad has been FINISHED.
        sendEvent(reactApplicationContext, "AUDIOAD_ENDED", null)
      }
    }
  }

  override fun onSDKInitialized(status: InitializationStatus) {
    val args = Arguments.createMap()
    args.putBoolean("available", AudiomobPlugin.getInstance().isAdAvailable(AdUnitIds.BACKGROUND))
    sendEvent(reactApplicationContext, "INIT_COMPLETED", args)
  }

}

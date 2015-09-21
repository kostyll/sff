/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class TranscodingContext : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal TranscodingContext(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(TranscodingContext obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~TranscodingContext() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          simple_ffmpegPINVOKE.delete_TranscodingContext(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public SWIGTYPE_p_SwrContext swr_ctx {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_swr_ctx_set(swigCPtr, SWIGTYPE_p_SwrContext.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_swr_ctx_get(swigCPtr);
      SWIGTYPE_p_SwrContext ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_SwrContext(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_SwsContext sws_ctx {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_sws_ctx_set(swigCPtr, SWIGTYPE_p_SwsContext.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_sws_ctx_get(swigCPtr);
      SWIGTYPE_p_SwsContext ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_SwsContext(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_AVPacket curr_packet {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_curr_packet_set(swigCPtr, SWIGTYPE_p_AVPacket.getCPtr(value));
      if (simple_ffmpegPINVOKE.SWIGPendingException.Pending) throw simple_ffmpegPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      SWIGTYPE_p_AVPacket ret = new SWIGTYPE_p_AVPacket(simple_ffmpegPINVOKE.TranscodingContext_curr_packet_get(swigCPtr), true);
      if (simple_ffmpegPINVOKE.SWIGPendingException.Pending) throw simple_ffmpegPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public SWIGTYPE_p_AVPacket video_packet {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_video_packet_set(swigCPtr, SWIGTYPE_p_AVPacket.getCPtr(value));
      if (simple_ffmpegPINVOKE.SWIGPendingException.Pending) throw simple_ffmpegPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      SWIGTYPE_p_AVPacket ret = new SWIGTYPE_p_AVPacket(simple_ffmpegPINVOKE.TranscodingContext_video_packet_get(swigCPtr), true);
      if (simple_ffmpegPINVOKE.SWIGPendingException.Pending) throw simple_ffmpegPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public SWIGTYPE_p_AVPacket copy_current_packet {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_copy_current_packet_set(swigCPtr, SWIGTYPE_p_AVPacket.getCPtr(value));
      if (simple_ffmpegPINVOKE.SWIGPendingException.Pending) throw simple_ffmpegPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      SWIGTYPE_p_AVPacket ret = new SWIGTYPE_p_AVPacket(simple_ffmpegPINVOKE.TranscodingContext_copy_current_packet_get(swigCPtr), true);
      if (simple_ffmpegPINVOKE.SWIGPendingException.Pending) throw simple_ffmpegPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public SWIGTYPE_p_AVPacket audio_packet {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_audio_packet_set(swigCPtr, SWIGTYPE_p_AVPacket.getCPtr(value));
      if (simple_ffmpegPINVOKE.SWIGPendingException.Pending) throw simple_ffmpegPINVOKE.SWIGPendingException.Retrieve();
    } 
    get {
      SWIGTYPE_p_AVPacket ret = new SWIGTYPE_p_AVPacket(simple_ffmpegPINVOKE.TranscodingContext_audio_packet_get(swigCPtr), true);
      if (simple_ffmpegPINVOKE.SWIGPendingException.Pending) throw simple_ffmpegPINVOKE.SWIGPendingException.Retrieve();
      return ret;
    } 
  }

  public SWIGTYPE_p_AVFrame ivframe {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_ivframe_set(swigCPtr, SWIGTYPE_p_AVFrame.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_ivframe_get(swigCPtr);
      SWIGTYPE_p_AVFrame ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_AVFrame(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_AVFrame ovframe {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_ovframe_set(swigCPtr, SWIGTYPE_p_AVFrame.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_ovframe_get(swigCPtr);
      SWIGTYPE_p_AVFrame ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_AVFrame(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_AVFrame iaframe {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_iaframe_set(swigCPtr, SWIGTYPE_p_AVFrame.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_iaframe_get(swigCPtr);
      SWIGTYPE_p_AVFrame ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_AVFrame(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_AVFrame oaframe {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_oaframe_set(swigCPtr, SWIGTYPE_p_AVFrame.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_oaframe_get(swigCPtr);
      SWIGTYPE_p_AVFrame ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_AVFrame(cPtr, false);
      return ret;
    } 
  }

  public int dest_pict_buffer_size {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_dest_pict_buffer_size_set(swigCPtr, value);
    } 
    get {
      int ret = simple_ffmpegPINVOKE.TranscodingContext_dest_pict_buffer_size_get(swigCPtr);
      return ret;
    } 
  }

  public SWIGTYPE_p_uint8_t dest_pict_buffer {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_dest_pict_buffer_set(swigCPtr, SWIGTYPE_p_uint8_t.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_dest_pict_buffer_get(swigCPtr);
      SWIGTYPE_p_uint8_t ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_uint8_t(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_void internal_ptr {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_internal_ptr_set(swigCPtr, SWIGTYPE_p_void.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_internal_ptr_get(swigCPtr);
      SWIGTYPE_p_void ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_void(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int before_decode_video {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_before_decode_video_set(swigCPtr, SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_before_decode_video_get(swigCPtr);
      SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int after_decode_video {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_after_decode_video_set(swigCPtr, SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_after_decode_video_get(swigCPtr);
      SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int after_convert_video {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_after_convert_video_set(swigCPtr, SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_after_convert_video_get(swigCPtr);
      SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int before_encode_video {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_before_encode_video_set(swigCPtr, SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_before_encode_video_get(swigCPtr);
      SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int after_encode_video {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_after_encode_video_set(swigCPtr, SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_after_encode_video_get(swigCPtr);
      SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int before_decode_audio {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_before_decode_audio_set(swigCPtr, SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_before_decode_audio_get(swigCPtr);
      SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int after_decode_audio {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_after_decode_audio_set(swigCPtr, SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_after_decode_audio_get(swigCPtr);
      SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int after_convert_audio {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_after_convert_audio_set(swigCPtr, SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_after_convert_audio_get(swigCPtr);
      SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int before_encode_audio {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_before_encode_audio_set(swigCPtr, SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_before_encode_audio_get(swigCPtr);
      SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int(cPtr, false);
      return ret;
    } 
  }

  public SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int after_encode_audio {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_after_encode_audio_set(swigCPtr, SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int.getCPtr(value));
    } 
    get {
      IntPtr cPtr = simple_ffmpegPINVOKE.TranscodingContext_after_encode_audio_get(swigCPtr);
      SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_p_f_p_SourceOrDestinatio_p_SourceOrDestinatio_p_TranscodingContext__int(cPtr, false);
      return ret;
    } 
  }

  public int first_vpts {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_first_vpts_set(swigCPtr, value);
    } 
    get {
      int ret = simple_ffmpegPINVOKE.TranscodingContext_first_vpts_get(swigCPtr);
      return ret;
    } 
  }

  public int first_apts {
    set {
      simple_ffmpegPINVOKE.TranscodingContext_first_apts_set(swigCPtr, value);
    } 
    get {
      int ret = simple_ffmpegPINVOKE.TranscodingContext_first_apts_get(swigCPtr);
      return ret;
    } 
  }

  public TranscodingContext() : this(simple_ffmpegPINVOKE.new_TranscodingContext(), true) {
  }

}
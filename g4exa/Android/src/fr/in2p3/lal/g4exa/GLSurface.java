// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file exlib.license for terms.

package fr.in2p3.lal.g4exa;

import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.view.SurfaceView;
import android.view.SurfaceHolder;
import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGL11;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.egl.EGLSurface;
import javax.microedition.khronos.opengles.GL;
import android.util.Log;

import java.io.*;

public class GLSurface extends SurfaceView implements SurfaceHolder.Callback {

  //////////////////////////////////////////////////////////////////
  /// Chooser //////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////
  public interface EGLConfigChooser {
    EGLConfig chooseConfig(EGL10 egl, EGLDisplay display);
  }

  private abstract class BaseConfigChooser implements EGLConfigChooser {
    public BaseConfigChooser(int[] configSpec) {
      mConfigSpec = filterConfigSpec(configSpec);
    }

    public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {
            int[] num_config = new int[1];
            if (!egl.eglChooseConfig(display, mConfigSpec, null, 0,
                    num_config)) {
                throw new IllegalArgumentException("eglChooseConfig failed");
            }

            int numConfigs = num_config[0];

            if (numConfigs <= 0) {
                throw new IllegalArgumentException(
                        "No configs match configSpec");
            }

            EGLConfig[] configs = new EGLConfig[numConfigs];
            if (!egl.eglChooseConfig(display, mConfigSpec, configs, numConfigs,
                    num_config)) {
                throw new IllegalArgumentException("eglChooseConfig#2 failed");
            }
            EGLConfig config = chooseConfig(egl, display, configs);
            if (config == null) {
                throw new IllegalArgumentException("No config chosen");
            }
            return config;
    }

    abstract EGLConfig chooseConfig(EGL10 egl, EGLDisplay display,
                EGLConfig[] configs);

    protected int[] mConfigSpec;

    private int[] filterConfigSpec(int[] configSpec) {
            if (mEGLContextClientVersion != 2) {
                return configSpec;
            }
            /* We know none of the subclasses define EGL_RENDERABLE_TYPE.
             * And we know the configSpec is well formed.
             */
            int len = configSpec.length;
            int[] newConfigSpec = new int[len + 2];
            System.arraycopy(configSpec, 0, newConfigSpec, 0, len-1);
            newConfigSpec[len-1] = EGL10.EGL_RENDERABLE_TYPE;
            newConfigSpec[len] = 4; /* EGL_OPENGL_ES2_BIT */
            newConfigSpec[len+1] = EGL10.EGL_NONE;
            return newConfigSpec;
    }
  }

  private class ComponentSizeChooser extends BaseConfigChooser {
    public ComponentSizeChooser(int redSize, int greenSize, int blueSize,
                                int alphaSize, int depthSize, int stencilSize){
      super(new int[] {
                    EGL10.EGL_RED_SIZE, redSize,
                    EGL10.EGL_GREEN_SIZE, greenSize,
                    EGL10.EGL_BLUE_SIZE, blueSize,
                    EGL10.EGL_ALPHA_SIZE, alphaSize,
                    EGL10.EGL_DEPTH_SIZE, depthSize,
                    EGL10.EGL_STENCIL_SIZE, stencilSize,
                    EGL10.EGL_NONE});
      mValue = new int[1];
      mRedSize = redSize;
      mGreenSize = greenSize;
      mBlueSize = blueSize;
      mAlphaSize = alphaSize;
      mDepthSize = depthSize;
      mStencilSize = stencilSize;
    }

    @Override
    public EGLConfig chooseConfig(EGL10 egl,
                                  EGLDisplay display,EGLConfig[] configs) {
      for (EGLConfig config : configs) {
        int d = findConfigAttrib(egl,display,config,EGL10.EGL_DEPTH_SIZE,0);
        int s = findConfigAttrib(egl,display,config,EGL10.EGL_STENCIL_SIZE,0);
        if ((d >= mDepthSize) && (s >= mStencilSize)) {
          int r = findConfigAttrib(egl,display,config,EGL10.EGL_RED_SIZE,0);
          int g = findConfigAttrib(egl,display,config,EGL10.EGL_GREEN_SIZE,0);
          int b = findConfigAttrib(egl,display,config,EGL10.EGL_BLUE_SIZE,0);
          int a = findConfigAttrib(egl,display,config,EGL10.EGL_ALPHA_SIZE,0);
          if ((r == mRedSize) && (g == mGreenSize) && 
              (b == mBlueSize) && (a == mAlphaSize)) {
            return config;
          }
        }
      }
      return null;
    }

    private int findConfigAttrib(EGL10 egl,
                                 EGLDisplay display,
                                 EGLConfig config,
                                 int attribute, int defaultValue) {

      if (egl.eglGetConfigAttrib(display, config, attribute, mValue)) {
        return mValue[0];
      }
      return defaultValue;
    }

    private int[] mValue;
    // Subclasses can adjust these values:
    protected int mRedSize;
    protected int mGreenSize;
    protected int mBlueSize;
    protected int mAlphaSize;
    protected int mDepthSize;
    protected int mStencilSize;
  }

  private class SimpleEGLConfigChooser extends ComponentSizeChooser {
    public SimpleEGLConfigChooser(boolean withDepthBuffer) {
      super(5, 6, 5, 0, withDepthBuffer ? 16 : 0, 0);
    }
  }

  //////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////

  public GLSurface(Context context) {
    super(context);
    //System.err.println("debug : GLSurface::cstor.");
    SurfaceHolder holder = getHolder();
    holder.addCallback(this);

    mEgl = null;
    mEglDisplay = null;

    mEGLConfigChooser = new SimpleEGLConfigChooser(true);

    mEglConfig = null;
    mEglContext = null;
    mEglSurface = null;

    mEGLContextClientVersion = 0; //???

    if(!start()) {}
  }

  protected void finalize() throws Throwable {
    try {
      //System.err.println("debug : GLSurface::finalize.");
      if(mEglContext != null) {
        if(!mEgl.eglDestroyContext(mEglDisplay,mEglContext)) {
          System.out.println
            ("GLSurface::finalize : eglDestroyContext failed.");
        }
        mEglContext = null;
      }
      if (mEglDisplay != null) {
        mEgl.eglTerminate(mEglDisplay);
        mEglDisplay = null;
      }
    } finally {
      super.finalize();
    }
  }

  //////////////////////////////////////////////////////////////////
  /// SurfaceHolder.Callback interface : ///////////////////////////
  //////////////////////////////////////////////////////////////////
  public void surfaceCreated(SurfaceHolder holder) {
    //System.err.println("debug : GLSurface::surfaceCreated.");
    //NOTE : createSurface not done here in case we want to do all the EGL
    //       in another thread (see Main.java).
    //createSurface(getHolder());
  }
  public void surfaceDestroyed(SurfaceHolder holder) {
    //System.err.println("debug : GLSurface::surfaceDestroyed.");
    //deleteSurface();
  }

  public void surfaceChanged(SurfaceHolder holder,int format,int w,int h) {
    //System.err.println("debug : GLSurface::surfaceChanged.");
  }

  //////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////
  private int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

  private boolean start() {
    mEgl = (EGL10) EGLContext.getEGL();
    mEglDisplay = mEgl.eglGetDisplay(EGL10.EGL_DEFAULT_DISPLAY);
    if (mEglDisplay == EGL10.EGL_NO_DISPLAY) {
      System.out.println("GLSurface::start : eglGetDisplay failed.");
      return false;
    }
    int[] version = new int[2];
    if(!mEgl.eglInitialize(mEglDisplay, version)) {
      mEgl = null;
      System.out.println("GLSurface::start : eglInitialize failed.");
      return false;
    }
    mEglConfig = mEGLConfigChooser.chooseConfig(mEgl, mEglDisplay);
    if(mEglConfig==null) {
      System.out.println("GLSurface::start : chooseConfig failed.");
      return false;
    }
    //mEglContext = 
    //  mEGLContextFactory.createContext(mEgl, mEglDisplay, mEglConfig);

    int[] attrib_list = {
       EGL_CONTEXT_CLIENT_VERSION,
       mEGLContextClientVersion,
       EGL10.EGL_NONE
    };
    mEglContext = 
      mEgl.eglCreateContext(mEglDisplay,mEglConfig,
                            EGL10.EGL_NO_CONTEXT,
                            mEGLContextClientVersion!=0? attrib_list : null);

    if (mEglContext == null || mEglContext == EGL10.EGL_NO_CONTEXT) {
      mEglContext = null;
      System.out.println("GLSurface::start : createContext failed.");
      return false;
    }
    mEglSurface = null;
    return true;
  }

  public /*synchronized*/ EGLSurface getSurface() {return mEglSurface;}

  public /*synchronized*/ GL createSurface(SurfaceHolder holder) {
    if (mEgl == null) {
      System.out.println("GLSurface::createSurface : mEgl is null.");
      return null;
    }
    if (mEglDisplay == null) {
      System.out.println("GLSurface::createSurface : mEglDisplay is null.");
      return null;
    }
    if (mEglConfig == null) {
      System.out.println("GLSurface::createSurface : mEglConfig is null.");
      return null;
    }
    // The window size has changed, so we need to create a new surface.
    if (mEglSurface != null && mEglSurface != EGL10.EGL_NO_SURFACE) {
      // Unbind and destroy the old EGL surface, if there is one.
      mEgl.eglMakeCurrent(mEglDisplay, EGL10.EGL_NO_SURFACE,
                          EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_CONTEXT);
      mEgl.eglDestroySurface(mEglDisplay,mEglSurface);
    }
    // Create an EGL surface we can render into.
    mEglSurface = 
      mEgl.eglCreateWindowSurface(mEglDisplay,mEglConfig,holder,null);

    if (mEglSurface == null || mEglSurface == EGL10.EGL_NO_SURFACE) {
      //int error = mEgl.eglGetError();
      //if (error == EGL10.EGL_BAD_NATIVE_WINDOW) return null;
      System.out.println
        ("GLSurface::createSurface : createWindowSurface failed.");
      return null;
    }
    // Before we can issue GL commands, we need to make sure
    // the context is current and bound to a surface.
    if(!mEgl.eglMakeCurrent(mEglDisplay,mEglSurface,mEglSurface,mEglContext)) {
      System.out.println("GLSurface::createSurface : eglMakeCurrent failed.");
      return null;
    }

    return mEglContext.getGL();
  }

  public /*synchronized*/ void deleteSurface() {
    //System.err.println("debug : GLSurface::deleteSurface.");
    if (mEglSurface != null && mEglSurface != EGL10.EGL_NO_SURFACE) {
      mEgl.eglMakeCurrent(mEglDisplay, EGL10.EGL_NO_SURFACE,
                          EGL10.EGL_NO_SURFACE,
                          EGL10.EGL_NO_CONTEXT);
      mEgl.eglDestroySurface(mEglDisplay,mEglSurface);
      mEglSurface = null;
    }
  }

  public /*synchronized*/ boolean swap() {
    if (! mEgl.eglSwapBuffers(mEglDisplay, mEglSurface)) {
      System.out.println("GLSurface::swap : eglSwapBuffers failed.");
      // Check for EGL_CONTEXT_LOST, which means the context
      // and all associated data were lost (For instance because
      // the device went to sleep). We need to sleep until we
      // get a new surface.
      int error = mEgl.eglGetError();
      switch(error) {
      case EGL11.EGL_CONTEXT_LOST:
        System.out.println("GLSurface::swap : EGL11.EGL_CONTEXT_LOST.");
        return false;
      case EGL10.EGL_BAD_SURFACE:
        System.out.println("GLSurface::swap : EGL11.EGL_BAD_SURFACE.");
        return false;
      case EGL10.EGL_BAD_NATIVE_WINDOW:
        System.out.println("GLSurface::swap : EGL_BAD_NATIVE_WINDOW.");
        // The native window is bad, probably because the
        // window manager has closed it. Ignore this error,
        // on the expectation that the application will be closed soon.
        break;
      default:
        System.out.println("GLSurface::swap : error "+error);
        return false;
      }
    }
    return true;
  }

  //////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////

  //fields :
  private EGL10 mEgl;
  private EGLDisplay mEglDisplay;

  private EGLConfigChooser mEGLConfigChooser;

  private EGLConfig mEglConfig;
  private EGLContext mEglContext;
  private EGLSurface mEglSurface;
  private int mEGLContextClientVersion;

  private int mDebugFlags;
  public final static int DEBUG_CHECK_GL_ERROR = 1;
  public final static int DEBUG_LOG_GL_CALLS = 2;
}




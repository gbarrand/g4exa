LOCAL_PATH := $(call my-dir)

INEXLIB_INC := ../../inexlib
INEXLIB_SRC := ../../../inexlib
OUREX_DIR := ../../../inexlib/ourex

#/////////////////////////////////
#/// Geant4 : ////////////////////
#/////////////////////////////////

#/////////////////////////////////
#/////////////////////////////////
#include $(CLEAR_VARS)
#LOCAL_MODULE := g4exa_g4
#LOCAL_SRC_FILES := $(G4HOME)/bin_sdk_android/libourex_geant4.a
#include $(PREBUILT_STATIC_LIBRARY)

#/////////////////////////////////
#/////////////////////////////////
include jni/geant4.mk

GEANT4_CFLAGS := \
 -DG4VERBOSE -DG4_STORE_TRAJECTORY\
 -I../../inexlib/ourex/expat/include\
 -I../../inexlib/ourex/zlib/include\
 -I$(G4HOME)/include/Geant4

#GEANT4_CPPFLAGS := -fexceptions -frtti
GEANT4_CPPFLAGS := -std=c++11 -fexceptions -frtti

#/////////////////////////////////
#/////////////////////////////////
#/////////////////////////////////
include $(CLEAR_VARS)

LOCAL_MODULE := g4exa_g4_1
LOCAL_CPP_EXTENSION := .cc
LOCAL_CFLAGS := $(GEANT4_CFLAGS)
LOCAL_CPPFLAGS := $(GEANT4_CPPFLAGS)
LOCAL_SRC_FILES := $(GEANT4_1_SRC_FILES)
include $(BUILD_STATIC_LIBRARY)

#/////////////////////////////////
#/////////////////////////////////
#/////////////////////////////////
include $(CLEAR_VARS)

LOCAL_MODULE := g4exa_g4_2
LOCAL_CPP_EXTENSION := .cc
LOCAL_CFLAGS := $(GEANT4_CFLAGS)
LOCAL_CPPFLAGS := $(GEANT4_CPPFLAGS)
LOCAL_SRC_FILES := $(GEANT4_2_SRC_FILES)
include $(BUILD_STATIC_LIBRARY)

#/////////////////////////////////
#/////////////////////////////////
#/////////////////////////////////
include $(CLEAR_VARS)

LOCAL_MODULE := g4exa_g4_3
LOCAL_CPP_EXTENSION := .cc
LOCAL_CFLAGS := $(GEANT4_CFLAGS)
LOCAL_CPPFLAGS := $(GEANT4_CPPFLAGS)
LOCAL_SRC_FILES := $(GEANT4_3_SRC_FILES)
include $(BUILD_STATIC_LIBRARY)

#/////////////////////////////////
#/////////////////////////////////
#/////////////////////////////////

THIS_CFLAGS := \
 -I../../inexlib/inlib\
 -I../../inexlib/exlib\
 \
 -I../../inexlib/ourex/expat/include\
 \
 -I../../inexlib/ourex/freetype/include\
 -I../../inexlib/ourex/freetype/include/freetype\
 -I../../inexlib/ourex/freetype/src/builds\
 \
 -I../../inexlib/ourex/jpeg/jpeg\
 \
 -I../../inexlib/ourex/png/png\
 \
 -I../../inexlib/ourex/zlib/include\
 \
 -I../../inexlib/ourex/zip/include

EXPAT_SRC_FILES := \
 $(subst jni,.,$(wildcard $(LOCAL_PATH)/../../../inexlib/ourex/expat/source/*.cpp))

FREETYPE_SRC_FILES := \
 ../../../inexlib/ourex/freetype/src/builds/unix/ftsystem.c\
 ../../../inexlib/ourex/freetype/src/base/ftdebug.c\
 ../../../inexlib/ourex/freetype/src/base/ftinit.c\
 ../../../inexlib/ourex/freetype/src/base/ftbase.c\
 ../../../inexlib/ourex/freetype/src/base/ftbbox.c\
 ../../../inexlib/ourex/freetype/src/base/ftbdf.c\
 ../../../inexlib/ourex/freetype/src/base/ftglyph.c\
 ../../../inexlib/ourex/freetype/src/base/ftmm.c\
 ../../../inexlib/ourex/freetype/src/base/ftpfr.c\
 ../../../inexlib/ourex/freetype/src/base/ftstroke.c\
 ../../../inexlib/ourex/freetype/src/base/fttype1.c\
 ../../../inexlib/ourex/freetype/src/base/ftwinfnt.c\
 ../../../inexlib/ourex/freetype/src/base/ftxf86.c\
 ../../../inexlib/ourex/freetype/src/gzip/ftgzip.c\
 ../../../inexlib/ourex/freetype/src/autohint/autohint.c\
 ../../../inexlib/ourex/freetype/src/bdf/bdf.c\
 ../../../inexlib/ourex/freetype/src/cache/ftcache.c\
 ../../../inexlib/ourex/freetype/src/cff/cff.c\
 ../../../inexlib/ourex/freetype/src/cid/type1cid.c\
 ../../../inexlib/ourex/freetype/src/lzw/ftlzw.c\
 ../../../inexlib/ourex/freetype/src/pcf/pcf.c\
 ../../../inexlib/ourex/freetype/src/pfr/pfr.c\
 ../../../inexlib/ourex/freetype/src/psaux/psaux.c\
 ../../../inexlib/ourex/freetype/src/pshinter/pshinter.c\
 ../../../inexlib/ourex/freetype/src/psnames/psmodule.c\
 ../../../inexlib/ourex/freetype/src/raster/raster.c\
 ../../../inexlib/ourex/freetype/src/sfnt/sfnt.c\
 ../../../inexlib/ourex/freetype/src/smooth/smooth.c\
 ../../../inexlib/ourex/freetype/src/truetype/truetype.c\
 ../../../inexlib/ourex/freetype/src/type1/type1.c\
 ../../../inexlib/ourex/freetype/src/type42/type42.c\
 ../../../inexlib/ourex/freetype/src/winfonts/winfnt.c

JPEG_SRC_FILES := \
 ../../../inexlib/ourex/jpeg/source/cdjpeg.c\
 ../../../inexlib/ourex/jpeg/source/jcapimin.c\
 ../../../inexlib/ourex/jpeg/source/jcapistd.c\
 ../../../inexlib/ourex/jpeg/source/jccoefct.c\
 ../../../inexlib/ourex/jpeg/source/jccolor.c\
 ../../../inexlib/ourex/jpeg/source/jcdctmgr.c\
 ../../../inexlib/ourex/jpeg/source/jchuff.c\
 ../../../inexlib/ourex/jpeg/source/jcinit.c\
 ../../../inexlib/ourex/jpeg/source/jcmainct.c\
 ../../../inexlib/ourex/jpeg/source/jcmarker.c\
 ../../../inexlib/ourex/jpeg/source/jcmaster.c\
 ../../../inexlib/ourex/jpeg/source/jcomapi.c\
 ../../../inexlib/ourex/jpeg/source/jcparam.c\
 ../../../inexlib/ourex/jpeg/source/jcphuff.c\
 ../../../inexlib/ourex/jpeg/source/jcprepct.c\
 ../../../inexlib/ourex/jpeg/source/jcsample.c\
 ../../../inexlib/ourex/jpeg/source/jctrans.c\
 ../../../inexlib/ourex/jpeg/source/jdapimin.c\
 ../../../inexlib/ourex/jpeg/source/jdapistd.c\
 ../../../inexlib/ourex/jpeg/source/jdatadst.c\
 ../../../inexlib/ourex/jpeg/source/jdatasrc.c\
 ../../../inexlib/ourex/jpeg/source/jdcoefct.c\
 ../../../inexlib/ourex/jpeg/source/jdcolor.c\
 ../../../inexlib/ourex/jpeg/source/jddctmgr.c\
 ../../../inexlib/ourex/jpeg/source/jdhuff.c\
 ../../../inexlib/ourex/jpeg/source/jdinput.c\
 ../../../inexlib/ourex/jpeg/source/jdmainct.c\
 ../../../inexlib/ourex/jpeg/source/jdmarker.c\
 ../../../inexlib/ourex/jpeg/source/jdmaster.c\
 ../../../inexlib/ourex/jpeg/source/jdmerge.c\
 ../../../inexlib/ourex/jpeg/source/jdphuff.c\
 ../../../inexlib/ourex/jpeg/source/jdpostct.c\
 ../../../inexlib/ourex/jpeg/source/jdsample.c\
 ../../../inexlib/ourex/jpeg/source/jdtrans.c\
 ../../../inexlib/ourex/jpeg/source/jerror.c\
 ../../../inexlib/ourex/jpeg/source/jfdctflt.c\
 ../../../inexlib/ourex/jpeg/source/jfdctfst.c\
 ../../../inexlib/ourex/jpeg/source/jfdctint.c\
 ../../../inexlib/ourex/jpeg/source/jidctflt.c\
 ../../../inexlib/ourex/jpeg/source/jidctfst.c\
 ../../../inexlib/ourex/jpeg/source/jidctint.c\
 ../../../inexlib/ourex/jpeg/source/jidctred.c\
 ../../../inexlib/ourex/jpeg/source/jmemansi.c\
 ../../../inexlib/ourex/jpeg/source/jmemmgr.c\
 ../../../inexlib/ourex/jpeg/source/jquant1.c\
 ../../../inexlib/ourex/jpeg/source/jquant2.c\
 ../../../inexlib/ourex/jpeg/source/jutils.c\
 ../../../inexlib/ourex/jpeg/source/rdbmp.c\
 ../../../inexlib/ourex/jpeg/source/rdcolmap.c\
 ../../../inexlib/ourex/jpeg/source/rdgif.c\
 ../../../inexlib/ourex/jpeg/source/rdppm.c\
 ../../../inexlib/ourex/jpeg/source/rdrle.c\
 ../../../inexlib/ourex/jpeg/source/rdswitch.c\
 ../../../inexlib/ourex/jpeg/source/rdtarga.c\
 ../../../inexlib/ourex/jpeg/source/transupp.c\
 ../../../inexlib/ourex/jpeg/source/wrbmp.c\
 ../../../inexlib/ourex/jpeg/source/wrgif.c\
 ../../../inexlib/ourex/jpeg/source/wrppm.c\
 ../../../inexlib/ourex/jpeg/source/wrrle.c\
 ../../../inexlib/ourex/jpeg/source/wrtarga.c

PNG_SRC_FILES := \
 ../../../inexlib/ourex/png/source/png.c\
 ../../../inexlib/ourex/png/source/pngerror.c\
 ../../../inexlib/ourex/png/source/pngget.c\
 ../../../inexlib/ourex/png/source/pngmem.c\
 ../../../inexlib/ourex/png/source/pngpread.c\
 ../../../inexlib/ourex/png/source/pngread.c\
 ../../../inexlib/ourex/png/source/pngrio.c\
 ../../../inexlib/ourex/png/source/pngrtran.c\
 ../../../inexlib/ourex/png/source/pngrutil.c\
 ../../../inexlib/ourex/png/source/pngset.c\
 ../../../inexlib/ourex/png/source/pngtrans.c\
 ../../../inexlib/ourex/png/source/pngwio.c\
 ../../../inexlib/ourex/png/source/pngwrite.c\
 ../../../inexlib/ourex/png/source/pngwtran.c\
 ../../../inexlib/ourex/png/source/pngwutil.c\
 ../../../inexlib/ourex/png/source/pnggccrd.c

CSZ_SRC_FILES := \
 ../../../inexlib/ourex/csz/src/inflate.c

# zlib exists on Android, but for consistency with other platforms
# we take our own.
#LOCAL_CFLAGS += -DEXLIB_USE_NATIVE_ZLIB
#LOCAL_CXXFLAGS += -DEXLIB_USE_NATIVE_ZLIB
ZLIB_SRC_FILES := \
 ../../../inexlib/ourex/zlib/source/adler32.c\
 ../../../inexlib/ourex/zlib/source/compress.c\
 ../../../inexlib/ourex/zlib/source/crc32.c\
 ../../../inexlib/ourex/zlib/source/deflate.c\
 ../../../inexlib/ourex/zlib/source/gzio.c\
 ../../../inexlib/ourex/zlib/source/infblock.c\
 ../../../inexlib/ourex/zlib/source/infcodes.c\
 ../../../inexlib/ourex/zlib/source/inffast.c\
 ../../../inexlib/ourex/zlib/source/inflate.c\
 ../../../inexlib/ourex/zlib/source/inftrees.c\
 ../../../inexlib/ourex/zlib/source/infutil.c\
 ../../../inexlib/ourex/zlib/source/trees.c\
 ../../../inexlib/ourex/zlib/source/uncompr.c\
 ../../../inexlib/ourex/zlib/source/zutil.c

ZIP_SRC_FILES := \
 ../../../inexlib/ourex/zip/source/zip.c\
 ../../../inexlib/ourex/zip/source/unzip.c\
 ../../../inexlib/ourex/zip/source/ioapi.c

YACC_SRC_FILES := \
  $(INEXLIB_SRC)/inlib/inlib/yacc/cexpr_lexer.cpp\
  $(INEXLIB_SRC)/inlib/inlib/yacc/cexpr_eval.cpp

A01_CFLAGS := \
 -I../../inexlib/exlib/examples/geant4/A01/include\
 -I../../inexlib/exlib/examples/geant4/A01

A01_SRC_FILES := $(subst jni,.,$(wildcard $(LOCAL_PATH)/../../../inexlib/exlib/examples/geant4/A01/src/*.cc))

#/////////////////////////////////
#/////////////////////////////////
#/////////////////////////////////

include $(CLEAR_VARS)

LOCAL_MODULE := g4exa

LOCAL_CPP_EXTENSION := .cpp .cc

LOCAL_CFLAGS := \
 $(GEANT4_CFLAGS)\
 $(A01_CFLAGS)\
 $(THIS_CFLAGS)\
 -DEXLIB_HAS_GL_VBO\
 -DEXLIB_ANDROID_MAIN_DO_STD_EXIT

LOCAL_CPPFLAGS := $(GEANT4_CPPFLAGS)

LOCAL_SRC_FILES := \
 $(ZIP_SRC_FILES)\
 $(EXPAT_SRC_FILES)\
 $(FREETYPE_SRC_FILES)\
 $(JPEG_SRC_FILES)\
 $(ZLIB_SRC_FILES)\
 $(YACC_SRC_FILES)\
 $(PNG_SRC_FILES)\
 $(CSZ_SRC_FILES)\
 $(A01_SRC_FILES)\
 ../main.cpp

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv1_CM

LOCAL_STATIC_LIBRARIES := g4exa_g4_3 g4exa_g4_2 g4exa_g4_1 android_native_app_glue

#LOCAL_STATIC_LIBRARIES := g4exa_g4 android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)

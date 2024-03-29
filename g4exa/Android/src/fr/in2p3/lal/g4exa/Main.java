// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file exlib.license for terms.

package fr.in2p3.lal.g4exa;

import android.app.NativeActivity;

import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;

// for load resource :
import android.content.Context;
import android.content.res.Resources;
import java.io.File;
import java.lang.reflect.Field;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.OutputStream;

// for send mail :
import java.io.File;
import android.content.Intent;
import android.net.Uri;
import android.support.v4.content.FileProvider;
//import androidx.core.content.FileProvider

// for ACTION_VIEW :
import android.content.ContentResolver;
import android.util.Log;
import android.provider.MediaStore;
import android.database.Cursor;
//import android.app.DownloadManager;

public class Main extends NativeActivity {
  @Override
  protected void onCreate(Bundle savedInstanceState) {
    //System.err.println("g4exa : debug : Main::onCreate : 015");

    super.onCreate(savedInstanceState);

    Intent intent = getIntent();
    String action = intent.getAction();

    if(action.compareTo(Intent.ACTION_VIEW)==0) {
      String scheme = intent.getScheme();
      Uri uri = intent.getData();
      if(scheme.compareTo(ContentResolver.SCHEME_FILE)==0) {
        //String name = uri.getLastPathSegment();
        //Log.v("g4exa::Main::onCreate","File intent : "+
        //      action+" : "+intent.getDataString()+" : "+intent.getType()+" : "+name);
        String document_path = "/sdcard/Android/data/fr.in2p3.lal.g4exa/DOCUMENT";
        uri_to_file(uri,document_path);

      } else if (scheme.compareTo(ContentResolver.SCHEME_CONTENT) == 0) {
        ContentResolver resolver = getContentResolver();
        String name = get_content_name(resolver, uri);
        //Log.v("g4exa::Main::onCreate","Content intent : "+
        //      action+" : "+intent.getDataString()+" : "+intent.getType()+" : "+name);
        String document_path = "/sdcard/Android/data/fr.in2p3.lal.g4exa/DOCUMENT";
        uri_to_file(uri,document_path);

/*
      } else if (scheme.compareTo("http") == 0) {
        Log.v("g4exa::Main::onCreate","http intent : "+
              action+" : "+intent.getDataString()+" : "+intent.getType());
        DownloadManager.Request r = new DownloadManager.Request(uri);
        r.setDestinationInExternalPublicDir("/sdcard/Android/data/fr.in2p3.lal.g4exa","DOCUMENT");
        //r.allowScanningByMediaScanner();
        //r.setNotificationVisibility(DownloadManager.Request.VISIBILITY_VISIBLE_NOTIFY_COMPLETED);
        DownloadManager dm = (DownloadManager)getSystemService(DOWNLOAD_SERVICE);
        dm.enqueue(r);
*/
      }
    }

    //System.err.println("debug : Main::onCreate : end");
  }


  private void load_resources() {
    //final Object saved_object = getLastNonConfigurationInstance(); //deprecated.
    //if(saved_object!=null) return; //done

    //First load of Activity.

    String app_dir = getFilesDir().getPath();
    // app_dir is : /data/data/fr.in2p3.lal.g4exa/files

    Field[] fields = R.raw.class.getFields();
    for(Field f : fields) {
      try {
        String name = f.getName();

        //NOTE :
        // if resource is xxx_ext then name is xxx_ext
        // if resource is xxx_yyy.ext then name is xxx_yyy

        //NOTE :
        //  in softinex apps, for an original Name.ext file,
        //  we have built :
        //    name_ext.ext
        //  and for big files (sizeof(Name.ext) > 1 Mbytes) :
        //    name_ext.jet
        //  .jet being a known extension that the Android apk
        //  builder will not compress. We do that because for
        //  Android < 2.3, the uncompression of big files is not
        //  guaranteed to work!

        //System.out.println("load_resources : "+f.getName());

        int pos = name.lastIndexOf("_");
        if(pos!=(-1)) {
          String ext = name.substring(pos+1,name.length());
          String fname = name.substring(0,pos);

        //System.out.println("debug : ext "+ext+" fname "+fname);

          if((ext.equals("dst"))     || //for pmx,agora data
             (ext.equals("bsg"))     || //for pmx detector
             (ext.equals("cdf"))     || //for pmx mag field
             (ext.equals("gdml"))    || //for g4view
             (ext.equals("mac"))     || //for g4view
             (ext.equals("cmnd"))    || //for g4view
             (ext.equals("jive"))    || //for agora vis event file.
             (ext.equals("xml"))     || //for agora JiveXML event file.
             (ext.equals("iv"))      || //for ioda built with CoinGL and HEPVis.
             (ext.equals("hiv"))     || //for ioda built with CoinGL and HEPVis.
             (ext.equals("wrl"))     || //for ioda built with CoinGL and HEPVis.
             (ext.equals("heprep"))  || //for ioda.
             (ext.equals("zheprep")) || //for ioda.
             (ext.equals("shp"))     || //for ioda.
             (ext.equals("shx"))     || //for ioda.
             (ext.equals("g4m"))     || //for MEMPHYS init.g4m
             (ext.equals("memphys")) || //for MEMPHYS input event file.
             (ext.equals("ttf"))     ||
             (ext.equals("otf"))     ||
             (ext.equals("jpg"))     ||
             (ext.equals("jpeg"))    ||
             (ext.equals("png"))     ||
             (ext.equals("fog"))     ||
             (ext.equals("dot"))     ||
             (ext.equals("dcm"))     || //for DICOM
             (ext.equals("dic"))     || //for DICOM
             (ext.equals("fits"))    ||
             (ext.equals("insh"))    ||
             (ext.equals("style"))   ||
             (ext.equals("ftp"))     ||
             (ext.equals("srv"))     ||
             (ext.equals("hdf5"))    ||
             (ext.equals("root"))    ||
             (ext.equals("lua"))     ||
             (ext.equals("py"))      ||
             (ext.equals("kumac"))   ||
             (ext.equals("vds"))       ||
             (ext.equals("zip"))       ||
             (ext.equals("zvid"))      ||
             (ext.equals("scenarios")) ||
             (ext.equals("gz"))        || //for TouchSky.
             (ext.equals("slides"))    ){

            if(ext.equals("fog")) {
              //fog file name is expected to be in upper cases.
              fname = fname.toUpperCase();
            }

            load_resource_file(f.getInt(null),app_dir+"/"+fname+"."+ext);
          } else {
            System.out.println("load_resources : unknown res "+name);
          }
        }

      } catch (IllegalAccessException e) { }
    }
  }
  private void load_resource_file(int a_id,String a_file) {
    //NOTE : how to read a res/raw/<font file> from native ?
    //       For the moment we use the below to copy the font file
    //       under a_file.
    File file = new File(a_file);
    if(!file.exists()) {
      try {
        Resources ress = getResources();
        InputStream in = ress.openRawResource(a_id);
        int sz = in.available();
        //System.out.println("debug : load_res "+a_file);
        //System.out.println("debug : load_res sz "+sz);
        byte[] buf = new byte[sz];
        in.read(buf);
        in.close();
        OutputStream out = new FileOutputStream(a_file);
        out.write(buf);
        out.close();
      } catch(FileNotFoundException ex){
        System.out.println(ex.getMessage());
      } catch(IOException e){
        System.out.println(e.getMessage());
      }
    }
  }

  public void send_mail(String a_to,
                        String a_subject,
                        String a_msg,
                        String a_path,
                        String a_mime) {
    //System.err.println
    //  ("debug : jni_send_mail "+a_to+" "+a_subject+" "+a_msg+" "+a_path+" "+a_mime);

    Intent intent = new Intent(Intent.ACTION_SEND);
    if(a_to.length()!=0) {
      intent.putExtra(Intent.EXTRA_EMAIL,a_to);
    }
    intent.putExtra(Intent.EXTRA_SUBJECT,a_subject);
    intent.putExtra(Intent.EXTRA_TEXT,a_msg);
    intent.setType("message/rfc822");
    if(a_path.length()!=0) {
    /*
      File file = new File(a_path);
      if(file.exists()) {
        intent.setType(a_mime);
        //Uri uri = Uri.fromFile(file);
        Uri uri = Uri.parse("file://" + file.getAbsolutePath());
        intent.putExtra(Intent.EXTRA_STREAM,uri);
      }
      */
      File file = new File(a_path);
      if(file.exists()) {
        intent.setType(a_mime);
        Uri uri = FileProvider.getUriForFile(this,"fr.in2p3.lal.g4exa.provider",file);
        intent.putExtra(Intent.EXTRA_STREAM,uri);
      }
    }
    startActivity(Intent.createChooser(intent,"Choose an Email client :"));
  }

  private void uri_to_file(Uri a_uri,String a_file) {
    try {
      ContentResolver resolver = getContentResolver();
      InputStream input = resolver.openInputStream(a_uri);
      OutputStream out = new FileOutputStream(new File(a_file));
      int size = 0;
      byte[] buffer = new byte[1024];
      while ((size = input.read(buffer)) != -1) {out.write(buffer,0,size);}
      out.close();
      input.close();
    } catch (Exception e) {
      Log.e("g4exa::uri_to_file "," exception: " + e.getMessage());
    }
  }

  private String get_content_name(ContentResolver resolver, Uri uri){
    Cursor cursor = resolver.query(uri, null, null, null, null);
    cursor.moveToFirst();
    int nameIndex = cursor.getColumnIndex(MediaStore.MediaColumns.DISPLAY_NAME);
    if (nameIndex >= 0) {
        return cursor.getString(nameIndex);
    } else {
        return null;
    }
  }

}



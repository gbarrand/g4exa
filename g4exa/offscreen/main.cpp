// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file g4exa.license for terms.

#include "../g4exa/main"

#include <exlib/app/offscreen/main_cpp>

int main(int argc,char** argv) {return exlib_main<g4exa::context,g4exa::main>("g4exa",argc,argv);}

//exlib_build_use inlib expat
//exlib_build_use exlib png jpeg zlib inlib_glutess freetype kernel

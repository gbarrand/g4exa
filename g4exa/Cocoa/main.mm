// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file g4exa.license for terms.

#define pi messy_pi
#define perThousand messy_perThousand

#import <Cocoa/Cocoa.h>

#undef pi
#undef perThousand
#undef pascal
#undef negativeInfinity

#include "../g4exa/main"

typedef g4exa::main app_main_t;

#import <exlib/app/Cocoa/main.mm>

int main(int argc,char** argv) {return exlib_main<g4exa::main>("g4exa",argc,argv);}

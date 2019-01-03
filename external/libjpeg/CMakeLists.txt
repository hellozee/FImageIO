cmake_minimum_required(VERSION 3.2)

project(libjpeg)

include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckCSourceCompiles)

check_include_file(stddef.h HAVE_STDDEF_H)
check_include_file(stdlib.h HAVE_STDLIB_H)
check_include_file(string.h HAVE_STRING_H)
check_symbol_exists(size_t stddef.h stdlib.h stdio.h HAVE_ANSI_SIZE_T)
check_symbol_exists(setmode io.h USE_SETMODE)
check_c_source_compiles(
"
void f()
{
    char x[ (char)0xff ]; /* x[-1] if signed */
}
"
CHAR_IS_UNSIGNED)

check_c_source_compiles(
"
void f()
{
    char x[ ((signed char)0xff) >> 1 ]; /* x[-1] if signed */
}
"
RIGHT_SHIFT_IS_UNSIGNED)

if(NOT HAVE_STRING_H)
    set(NEED_BSD_STRINGS TRUE)
else()
    set(NEED_BSD_STRINGS FALSE)
endif()

if(NOT HAVE_ANSI_SIZE_T)
    set(NEED_SYS_TYPES_H TRUE)
else()
    set(NEED_SYS_TYPES_H FALSE)
endif()


add_library(
    libjpeg
    STATIC
    jcapimin.c
    jcapistd.c
    jctrans.c
    jcparam.c
    jdatadst.c
    jcinit.c
    jcmaster.c
    jcmarker.c
    jcmainct.c
    jcprepct.c
    jccoefct.c
    jccolor.c
    jcsample.c
    jchuff.c
    jcphuff.c
    jcdctmgr.c
    jfdctfst.c
    jfdctflt.c
    jfdctint.c
    jdapimin.c
    jdapistd.c
    jdtrans.c
    jdatasrc.c
    jdmaster.c
    jdinput.c
    jdmarker.c
    jdhuff.c
    jdphuff.c
    jdmainct.c
    jdcoefct.c
    jdpostct.c
    jddctmgr.c
    jidctfst.c
    jidctflt.c
    jidctint.c
    jidctred.c
    jdsample.c
    jdcolor.c
    jquant1.c
    jquant2.c
    jdmerge.c
    jcomapi.c
    jutils.c
    jerror.c
    jmemmgr.c
    jmemnobs.c
)

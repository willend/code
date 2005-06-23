/*---------------------------------------------------------------------------
  NeXus - Neutron & X-ray Common Data Format
  
  Application Program Interface Header File
  
  Copyright (C) 2000-2005 Mark Koennecke, Uwe Filges
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.
 
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
 
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
  For further information, see <http://www.neutron.anl.gov/NeXus/>
  
  $Id$

 ----------------------------------------------------------------------------*/
  
#ifndef NEXUSAPI
#define NEXUSAPI

/* NeXus HDF45 */
#define NEXUS_VERSION   "3.0.0"                /* major.minor.patch */

#define CONSTCHAR       const char

#if defined(_WIN32) && defined(_DLL)
#	ifdef NX45DLL_EXPORTS
#		define NX_EXTERNAL __declspec(dllexport)
#	else
#		define NX_EXTERNAL __declspec(dllimport)
#	endif
#else
#	define NX_EXTERNAL
#endif

#ifdef _WIN32
#define snprintf nxisnprintf
extern int nxisnprintf(char* buffer, int len, const char* format, ... );
#endif /* _WIN32 */

typedef void* NXhandle;         /* really a pointer to a NexusFile structure */
typedef int NXstatus;
typedef char NXname[128];

/* 
 * Any new NXaccess options should be numbered in 2^n format 
 * (8, 16, 32, etc) so that they can be bit masked and tested easily.
 *
 * To test older non bit masked options (values below 8) use e.g.
 *
 *       if ( (mode & NXACCMASK_REMOVEFLAGS) == NXACC_CREATE )
 *
 * To test new (>=8) options just use normal bit masking e.g.
 * 
 *       if ( mode & NXACC_NOSTRIP )
 *
 */
#define NXACCMASK_REMOVEFLAGS (0x7) /* bit mask to remove higher flag options */

typedef enum {NXACC_READ=1, NXACC_RDWR=2, NXACC_CREATE=3, NXACC_CREATE4=4, 
	      NXACC_CREATE5=5, NXACC_CREATEXML=6, NXACC_NOSTRIP=128} NXaccess;

typedef struct {
                char *iname;
                int   type;
               }info_type, *pinfo;  
 
#define NX_OK 1
#define NX_ERROR 0
#define NX_EOD -1

#define NX_UNLIMITED -1

#define NX_MAXRANK 32
#define NX_MAXNAMELEN 64

/*-------------------------------------------------------------------------
                HDF Datatype values for datatype parameters 
                       in the Nexus API

  NX_FLOAT32     32 bit float
  NX_FLOAT64     64 nit float == double
  NX_INT8        8 bit integer == byte
  NX_UINT8       8 bit unsigned integer
  NX_INT16       16 bit integer
  NX_UINT16      16 bit unsigned integer
  NX_INT32       32 bit integer
  NX_UINT32      32 bit unsigned integer
  NX_CHAR        8 bit character
  NX_BINARY      lump of binary data == NX_UINT8

--------------------------------------------------------------------------*/ 

/* Map NeXus to HDF types */
#define NX_FLOAT32   5
#define NX_FLOAT64   6
#define NX_INT8     20  
#define NX_UINT8    21
#define NX_BOOLEAN NX_UINT
#define NX_INT16    22  
#define NX_UINT16   23
#define NX_INT32    24
#define NX_UINT32   25
#define NX_CHAR      4
#define NX_BINARY   21

/* Map NeXus compression methods to HDF compression methods */
#define NX_COMP_NONE 100
#define NX_COMP_LZW 200
#define NX_COMP_RLE 300
#define NX_COMP_HUF 400  

typedef struct {
                long iTag;          /* HDF4 variable */
                long iRef;          /* HDF4 variable */
                char iTag5[1024];     /* HDF5 variable */ 
                char iRef5[1024];     /* HDF5 variable */
                char iRefd[1024];     /* HDF5 variable */
                char targetPath[1024]; /* XML path */
               } NXlink;

#define NXMAXSTACK 50

#define CONCAT(__a,__b) __a##__b        /* token concatenation */

#if defined(__unix) || defined(__unix__) || defined (__VMS) || defined(__APPLE__)

#    ifdef __VMS
#        define MANGLE(__arg)	__arg 
#    else
#        define MANGLE(__arg)   CONCAT(__arg,_)
#    endif

#    define CALLING_STYLE   /* blank */

#    define NXopen              MANGLE(nxiopen)
#    define NXclose             MANGLE(nxiclose)
#    define NXmakegroup         MANGLE(nximakegroup)
#    define NXopengroup         MANGLE(nxiopengroup)
#    define NXopenpath          MANGLE(nxiopenpath)
#    define NXopengrouppath     MANGLE(nxiopengrouppath)
#    define NXclosegroup        MANGLE(nxiclosegroup)
#    define NXmakedata          MANGLE(nximakedata)
#    define NXcompmakedata      MANGLE(nxicompmakedata)
#    define NXcompress          MANGLE(nxicompress)
#    define NXopendata          MANGLE(nxiopendata)
#    define NXclosedata         MANGLE(nxiclosedata)
#    define NXputdata           MANGLE(nxiputdata)
#    define NXputslab           MANGLE(nxiputslab)
#    define NXputattr           MANGLE(nxiputattr)
#    define NXgetdataID         MANGLE(nxigetdataid)
#    define NXmakelink          MANGLE(nximakelink)
#    define NXopensourcegroup   MANGLE(nxiopensourcegroup)
#    define NXmalloc            MANGLE(nximalloc)
#    define NXfree              MANGLE(nxifree)
#    define NXflush             MANGLE(nxiflush)

#    define NXgetinfo           MANGLE(nxigetinfo)
#    define NXgetnextentry      MANGLE(nxigetnextentry)
#    define NXgetdata           MANGLE(nxigetdata)

#    define NXgetslab           MANGLE(nxigetslab)
#    define NXgetnextattr       MANGLE(nxigetnextattr)
#    define NXgetattr           MANGLE(nxigetattr)
#    define NXgetattrinfo       MANGLE(nxigetattrinfo)
#    define NXgetgroupID        MANGLE(nxigetgroupid)
#    define NXgetgroupinfo      MANGLE(nxigetgroupinfo)
#    define NXsameID            MANGLE(nxisameid)
#    define NXinitgroupdir      MANGLE(nxiinitgroupdir)
#    define NXinitattrdir       MANGLE(nxiinitattrdir)
#    define NXsetnumberformat       MANGLE(nxisetnumberformat)
#    define NXsetcache          MANGLE(nxisetcache)
/* FORTRAN helpers - for NeXus internal use only */
#    define NXfopen             MANGLE(nxifopen)
#    define NXfclose            MANGLE(nxifclose)
#    define NXfflush            MANGLE(nxifflush)
#    define NXfmakedata         MANGLE(nxifmakedata)
#    define NXfcompmakedata     MANGLE(nxifcompmakedata)
#    define NXfcompress         MANGLE(nxifcompress)
#    define NXfputattr          MANGLE(nxifputattr)

#elif defined(_WIN32)
/* 
 * START OF WINDOWS SPECIFIC CONFIGURATION
 *
 * Added by Freddie Akeroyd 9/8/2002
 *
 * Various PC calling conventions - you need only uncomment one of the following definitions of MANGLE()
 * anlong with the appropriate CALLING_STYLE
 * The choice arises because under Windows the default way FORTRAN calls FORTRAN is different
 * from the dafault way C calls C, and so when you need to have FORTRAN calling C you must
 * force them to use the same convention. Notice the use of "default way" above ... by choice
 * of compiler options (or compiler vendor) you may actually have FORTRAN calling in the C way 
 * etc., so you might need to experiment with the options below until you get no "unresolved symbols" 
 *
 * Choice 1: Should allow both FORTRAN and C NeXus interfaces to work in a "default" setup 
 * Choice 2: For when choice 1: gives problems and you only require the C interface
 * Choice 3: An alternative to 1: which may allow both FORTRAN and C in a non-default setup
 */
#	define MANGLE(__arg)		__arg				/* Choice 1 */
#	define CALLING_STYLE		__stdcall			/* Choice 1 */
/* #	define MANGLE(__arg)		__arg				/* Choice 2 */
/* #    define CALLING_STYLE						/* Choice 2 */
/* #	define MANGLE(__arg)		CONCAT(__arg,_)			/* Choice 3 */
/* #    define CALLING_STYLE		__stdcall			/* Choice 3 */
/* 
 * END OF WINDOWS SPECIFIC CONFIGURATION 
 */
#       define NXopen 			MANGLE(NXIOPEN)
#       define NXclose 			MANGLE(NXICLOSE)
#       define NXflush                  MANGLE(NXIFLUSH)
#       define NXmakegroup 		MANGLE(NXIMAKEGROUP)
#       define NXopengroup 		MANGLE(NXIOPENGROUP)
#       define NXopenpath 		MANGLE(NXIOPENPATH)
#       define NXopengrouppath 		MANGLE(NXIOPENGROUPPATH)
#       define NXclosegroup 		MANGLE(NXICLOSEGROUP)
#       define NXmakedata 		MANGLE(NXIMAKEDATA)
#       define NXcompress 		MANGLE(NXICOMPRESS)
#       define NXopendata 		MANGLE(NXIOPENDATA)
#       define NXclosedata 		MANGLE(NXICLOSEDATA)
#       define NXgetdata 		MANGLE(NXIGETDATA)
#       define NXgetslab 		MANGLE(NXIGETSLAB)
#       define NXgetattr 		MANGLE(NXIGETATTR)
#       define NXgetdim 		MANGLE(NXIGETDIM)
#       define NXputdata 		MANGLE(NXIPUTDATA)
#       define NXputslab 		MANGLE(NXIPUTSLAB)
#       define NXputattr 		MANGLE(NXIPUTATTR)
#       define NXputdim 		MANGLE(NXIPUTDIM)
#       define NXgetinfo 		MANGLE(NXIGETINFO)
#       define NXgetgroupinfo 		MANGLE(NXIGETGROUPINFO)
#       define NXsameID            MANGLE(NXISAMEID)
#       define NXinitgroupdir 		MANGLE(NXIINITGROUPDIR)
#       define NXgetnextentry 		MANGLE(NXIGETNEXTENTRY)
#       define NXgetattrinfo 		MANGLE(NXIGETATTRINFO)
#       define NXinitattrdir 		MANGLE(NXIINITATTRDIR)
#       define NXsetnumberformat 	MANGLE(NXISETNUMBERFORMAT)
#       define NXgetnextattr 		MANGLE(NXIGETNEXTATTR)
#       define NXgetgroupID 		MANGLE(NXIGETGROUPID)
#       define NXgetdataID 		MANGLE(NXIGETDATAID)
#       define NXmakelink 		MANGLE(NXIMAKELINK)
#       define NXopensourcegroup        MANGLE(NXIOPENSOURCEGROUP)
#       define NXmalloc 		MANGLE(NXIMALLOC)
#       define NXfree 			MANGLE(NXIFREE)
/* FORTRAN helpers - for NeXus internal use only */
#	define NXfopen 			MANGLE(NXIFOPEN)
#	define NXfclose			MANGLE(NXIFCLOSE)
#       define NXfflush                 MANGLE(NXIFFLUSH)
#	define NXfmakedata		MANGLE(NXIFMAKEDATA)
#   define NXfcompmakedata  MANGLE(NXIFCOMPMAKEDATA)
#	define NXfcompress		MANGLE(NXIFCOMPRESS)
#	define NXfputattr		MANGLE(NXIFPUTATTR)
#else
#   error Cannot compile - unknown operating system
#endif


/* 
 * Standard interface 
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
NX_EXTERNAL  NXstatus CALLING_STYLE NXopen(CONSTCHAR * filename, NXaccess access_method, NXhandle* pHandle);
NX_EXTERNAL  NXstatus CALLING_STYLE NXclose(NXhandle* pHandle);
NX_EXTERNAL  NXstatus CALLING_STYLE NXflush(NXhandle* pHandle);
  
NX_EXTERNAL  NXstatus CALLING_STYLE NXmakegroup (NXhandle handle, CONSTCHAR *name, CONSTCHAR* NXclass);
NX_EXTERNAL  NXstatus CALLING_STYLE NXopengroup (NXhandle handle, CONSTCHAR *name, CONSTCHAR* NXclass);
NX_EXTERNAL  NXstatus CALLING_STYLE NXopenpath (NXhandle handle, CONSTCHAR *path);
NX_EXTERNAL  NXstatus CALLING_STYLE NXopengrouppath (NXhandle handle, CONSTCHAR *path);

NX_EXTERNAL  NXstatus CALLING_STYLE NXclosegroup(NXhandle handle);
  
NX_EXTERNAL  NXstatus CALLING_STYLE NXmakedata (NXhandle handle, CONSTCHAR* label, int datatype, int rank, int dim[]);
NX_EXTERNAL  NXstatus CALLING_STYLE NXcompmakedata (NXhandle handle, CONSTCHAR* label, int datatype, int rank, int dim[], int comp_typ, int bufsize[]);
NX_EXTERNAL  NXstatus CALLING_STYLE NXcompress (NXhandle handle, int compr_type);
NX_EXTERNAL  NXstatus CALLING_STYLE NXopendata (NXhandle handle, CONSTCHAR* label);
NX_EXTERNAL  NXstatus CALLING_STYLE NXclosedata(NXhandle handle);
NX_EXTERNAL  NXstatus CALLING_STYLE NXputdata(NXhandle handle, void* data);

NX_EXTERNAL  NXstatus CALLING_STYLE NXputattr(NXhandle handle, CONSTCHAR* name, void* data, int iDataLen, int iType);
NX_EXTERNAL  NXstatus CALLING_STYLE NXputslab(NXhandle handle, void* data, int start[], int size[]);    

NX_EXTERNAL  NXstatus CALLING_STYLE NXgetdataID(NXhandle handle, NXlink* pLink);
NX_EXTERNAL  NXstatus CALLING_STYLE NXmakelink(NXhandle handle, NXlink* pLink);
NX_EXTERNAL  NXstatus CALLING_STYLE NXopensourcegroup(NXhandle handle);

NX_EXTERNAL  NXstatus CALLING_STYLE NXgetdata(NXhandle handle, void* data);
NX_EXTERNAL  NXstatus CALLING_STYLE NXgetinfo(NXhandle handle, int* rank, int dimension[], int* datatype);
NX_EXTERNAL  NXstatus CALLING_STYLE NXgetnextentry(NXhandle handle, NXname name, NXname nxclass, int* datatype);

NX_EXTERNAL  NXstatus CALLING_STYLE NXgetslab(NXhandle handle, void* data, int start[], int size[]);
NX_EXTERNAL  NXstatus CALLING_STYLE NXgetnextattr(NXhandle handle, NXname pName, int *iLength, int *iType);
NX_EXTERNAL  NXstatus CALLING_STYLE NXgetattr(NXhandle handle, char* name, void* data, int* iDataLen, int* iType);
NX_EXTERNAL  NXstatus CALLING_STYLE NXgetattrinfo(NXhandle handle, int* no_items);
NX_EXTERNAL  NXstatus CALLING_STYLE NXgetgroupID(NXhandle handle, NXlink* pLink);
NX_EXTERNAL  NXstatus CALLING_STYLE NXgetgroupinfo(NXhandle handle, int* no_items, NXname name, NXname nxclass);
NX_EXTERNAL  NXstatus CALLING_STYLE NXsameID(NXhandle handle, NXlink* pFirstID, NXlink* pSecondID);

NX_EXTERNAL  NXstatus CALLING_STYLE NXinitgroupdir(NXhandle handle);
NX_EXTERNAL  NXstatus CALLING_STYLE NXinitattrdir(NXhandle handle);
NX_EXTERNAL  NXstatus CALLING_STYLE NXsetnumberformat(NXhandle handle,
						      int type, char *format);

NX_EXTERNAL  NXstatus CALLING_STYLE NXmalloc(void** data, int rank, int dimensions[], int datatype);
NX_EXTERNAL  NXstatus CALLING_STYLE NXfree(void** data);


/*-----------------------------------------------------------------------
    NAPI internals 
------------------------------------------------------------------------*/
NX_EXTERNAL  void CALLING_STYLE NXMSetError(void *pData, void (*ErrFunc)(void *pD, char *text));
extern void (*NXIReportError)(void *pData,char *text);
extern void *NXpData;
extern char *NXIformatNeXusTime();


/*
  another special function for setting the default cache size for HDF-5
*/
NX_EXTERNAL  NXstatus CALLING_STYLE NXsetcache(long newVal);

/*
 * We need to include CALLING_STYLE in the function pointer definition
 * or else we get a type mismatch on Win32
 */
  typedef struct {
        NXhandle *pNexusData;   
        int stripFlag;
        NXstatus (CALLING_STYLE *nxclose)(NXhandle* pHandle);
        NXstatus (CALLING_STYLE *nxflush)(NXhandle* pHandle);
        NXstatus (CALLING_STYLE *nxmakegroup) (NXhandle handle, CONSTCHAR *name, CONSTCHAR* NXclass);
        NXstatus (CALLING_STYLE *nxopengroup) (NXhandle handle, CONSTCHAR *name, CONSTCHAR* NXclass);
        NXstatus (CALLING_STYLE *nxclosegroup)(NXhandle handle);
        NXstatus (CALLING_STYLE *nxmakedata) (NXhandle handle, CONSTCHAR* label, int datatype, int rank, int dim[]);
        NXstatus (CALLING_STYLE *nxcompmakedata) (NXhandle handle, CONSTCHAR* label, int datatype, int rank, int dim[], int comp_typ, int bufsize[]);
        NXstatus (CALLING_STYLE *nxcompress) (NXhandle handle, int compr_type);
        NXstatus (CALLING_STYLE *nxopendata) (NXhandle handle, CONSTCHAR* label);
        NXstatus (CALLING_STYLE *nxclosedata)(NXhandle handle);
        NXstatus (CALLING_STYLE *nxputdata)(NXhandle handle, void* data);
        NXstatus (CALLING_STYLE *nxputattr)(NXhandle handle, CONSTCHAR* name, void* data, int iDataLen, int iType);
        NXstatus (CALLING_STYLE *nxputslab)(NXhandle handle, void* data, int start[], int size[]);    
        NXstatus (CALLING_STYLE *nxgetdataID)(NXhandle handle, NXlink* pLink);
        NXstatus (CALLING_STYLE *nxmakelink)(NXhandle handle, NXlink* pLink);
        NXstatus (CALLING_STYLE *nxgetdata)(NXhandle handle, void* data);
        NXstatus (CALLING_STYLE *nxgetinfo)(NXhandle handle, int* rank, int dimension[], int* datatype);
        NXstatus (CALLING_STYLE *nxgetnextentry)(NXhandle handle, NXname name, NXname nxclass, int* datatype);
        NXstatus (CALLING_STYLE *nxgetslab)(NXhandle handle, void* data, int start[], int size[]);
        NXstatus (CALLING_STYLE *nxgetnextattr)(NXhandle handle, NXname pName, int *iLength, int *iType);
        NXstatus (CALLING_STYLE *nxgetattr)(NXhandle handle, char* name, void* data, int* iDataLen, int* iType);
        NXstatus (CALLING_STYLE *nxgetattrinfo)(NXhandle handle, int* no_items);
        NXstatus (CALLING_STYLE *nxgetgroupID)(NXhandle handle, NXlink* pLink);
        NXstatus (CALLING_STYLE *nxgetgroupinfo)(NXhandle handle, int* no_items, NXname name, NXname nxclass);
        NXstatus (CALLING_STYLE *nxsameID)(NXhandle handle, NXlink* pFirstID, NXlink* pSecondID);
        NXstatus (CALLING_STYLE *nxinitgroupdir)(NXhandle handle);
        NXstatus (CALLING_STYLE *nxinitattrdir)(NXhandle handle);
        NXstatus (CALLING_STYLE *nxsetnumberformat)(NXhandle handle,
						    int type,char *format);
  } NexusFunction, *pNexusFunction;
  /*---------------------*/
  extern long nx_cacheSize;
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*NEXUSAPI*/


/*
 * This is the header file for the NeXus XML file driver. 
 *
 *   Copyright (C) 2004 Mark Koennecke
 * 
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  For further information, see <http://www.neutron.anl.gov/NeXus/>
 */
#ifndef NEXUSXML
#define NEXUSXML

extern  NXstatus  NXXopen(CONSTCHAR *filename, 
					    NXaccess access_method, 
					    NXhandle* pHandle);
extern  NXstatus  NXXclose(NXhandle* pHandle);
extern  NXstatus  NXXflush(NXhandle* pHandle);

NXstatus  NXXmakegroup (NXhandle fid, CONSTCHAR *name, 
				     CONSTCHAR *nxclass);
NXstatus  NXXopengroup (NXhandle fid, CONSTCHAR *name, 
				     CONSTCHAR *nxclass);
NXstatus  NXXclosegroup (NXhandle fid);

NXstatus  NXXcompmakedata (NXhandle fid, CONSTCHAR *name, 
					int datatype, 
					int rank, 
					int dimensions[],
					int compress_type, int chunk_size[]);
NXstatus  NXXmakedata (NXhandle fid, 
				    CONSTCHAR *name, int datatype, 
				    int rank, int dimensions[]);
NXstatus  NXXopendata (NXhandle fid, CONSTCHAR *name);
NXstatus  NXXclosedata (NXhandle fid);
NXstatus  NXXputdata (NXhandle fid, void *data);
NXstatus  NXXgetdata (NXhandle fid, void *data);
NXstatus  NXXgetinfo (NXhandle fid, int *rank, 
				   int dimension[], int *iType);
NXstatus  NXXputslab (NXhandle fid, void *data, 
				   int iStart[], int iSize[]);
NXstatus  NXXgetslab (NXhandle fid, void *data, 
				   int iStart[], int iSize[]);
NXstatus  NXXputattr (NXhandle fid, CONSTCHAR *name, void *data, 
				   int datalen, int iType);
NXstatus  NXXgetattr (NXhandle fid, char *name, 
				   void *data, int* datalen, int* iType);

NXstatus  NXXgetnextentry (NXhandle fid,NXname name, 
					NXname nxclass, int *datatype);
extern  NXstatus  NXXgetnextattr(NXhandle handle, 
				NXname pName, int *iLength, int *iType);
extern  NXstatus  NXXinitgroupdir(NXhandle handle);
extern  NXstatus  NXXinitattrdir(NXhandle handle);
extern  NXstatus  NXXgetattrinfo (NXhandle fid, int *iN);
extern  NXstatus  NXXgetgroupinfo (NXhandle fid, int *iN, 
					NXname pName, NXname pClass);

extern NXstatus  NXXgetdataID (NXhandle fid, NXlink* sRes);
extern NXstatus  NXXgetgroupID (NXhandle fid, NXlink* sRes);
extern NXstatus  NXXmakelink (NXhandle fid, NXlink* sLink);
extern NXstatus  NXXprintlink (NXhandle fid, NXlink* sLink);
extern NXstatus  NXXsameID (NXhandle fileid, 
					      NXlink* pFirstID, NXlink* pSecondID);

void NXXassignFunctions(pNexusFunction fHandle);
#endif

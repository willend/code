# - Find python interpreter
# This module finds if Python interpreter is installed and determines where the
# executables are. This code sets the following variables:
#
#  PYTHONINTERP_FOUND - Was the Python executable found
#  PYTHON_EXECUTABLE  - path to the Python interpreter
#  PYTHON_DOC  - path to the Python documentation generator
#  PYTHON_COMPILE  - path to the Python compilerr
#

#=============================================================================
# Copyright 2005-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distributed this file outside of CMake, substitute the full
#  License text for the above reference.)
#
# Updated to find pydoc and pycompile. Stephen Rankin (STFC) 2011.
#
#
#

set(MS_PATHS   
  [HKEY_LOCAL_MACHINE\\SOFTWARE\\Python\\PythonCore\\2.6\\InstallPath]
  [HKEY_LOCAL_MACHINE\\SOFTWARE\\Python\\PythonCore\\2.5\\InstallPath]
  [HKEY_LOCAL_MACHINE\\SOFTWARE\\Python\\PythonCore\\2.4\\InstallPath]
  [HKEY_LOCAL_MACHINE\\SOFTWARE\\Python\\PythonCore\\2.3\\InstallPath]
  [HKEY_LOCAL_MACHINE\\SOFTWARE\\Python\\PythonCore\\2.2\\InstallPath]
  [HKEY_LOCAL_MACHINE\\SOFTWARE\\Python\\PythonCore\\2.1\\InstallPath]
  [HKEY_LOCAL_MACHINE\\SOFTWARE\\Python\\PythonCore\\2.0\\InstallPath]
  [HKEY_LOCAL_MACHINE\\SOFTWARE\\Python\\PythonCore\\1.6\\InstallPath]
  [HKEY_LOCAL_MACHINE\\SOFTWARE\\Python\\PythonCore\\1.5\\InstallPath])

set(PYTHON_NAMES python2.6 python2.5 python2.4 python2.3 python2.2 python2.1 python2.0 python1.6 python1.5 python)
set(PYTHON_DOC_NAMES pydoc2.6 pydoc2.5 pydoc2.4 pydoc2.3 pydoc2.2 pydoc2.1 pydoc2.0 pydoc1.6 pydoc1.5 pydoc)
set(PYTHON_COMPILE_NAMES pycompile2.6 pycompile2.5 pycompile2.4 pycompile2.3 pycompile2.2 pycompile2.1 pycompile2.0 pycompile1.6 pycompile1.5 pycompile)

FIND_PROGRAM(PYTHON_EXECUTABLE
  NAMES ${PYTHON_NAMES}
  PATHS
  ${MS_PATHS}
  )

FIND_PROGRAM(PYTHON_DOC
  NAMES ${PYTHON_DOC_NAMES}
  PATHS
  ${MS_PATHS}
  )

FIND_PROGRAM(PYTHON_COMPILE
  NAMES ${PYTHON_COMPILE_NAMES}
  PATHS
  ${MS_PATHS}
  )

# handle the QUIETLY and REQUIRED arguments and set PYTHONINTERP_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PythonInterp DEFAULT_MSG PYTHON_EXECUTABLE PYTHON_DOC PYTHON_COMPILE)

MARK_AS_ADVANCED(PYTHON_EXECUTABLE PYTHON_DOC PYTHON_COMPILE)


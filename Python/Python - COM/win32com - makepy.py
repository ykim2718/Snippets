"""
y, 2022.7.27
win32com - makepy.py
https://wikidocs.net/72461
https://docs.microsoft.com/en-us/windows/win32/learnwin32/what-is-a-com-interface-
"""

import sys
from win32com.client import makepy

sys.argv += [r'c:\y\eBEST\xingAPI\xingAPI\XA_Session.dll']
makepy.main()

"""
Generating to C:\y\Anaconda3\lib\site-packages\win32com\gen_py\F5CC65C5-2965-451B-A6C4-CBC7B8B4AE08x0x1x0.py
Building definitions from type library...
Generating...
Importing module
"""

""" C:\y\Anaconda3\lib\site-packages\win32com\gen_py\F5CC65C5-2965-451B-A6C4-CBC7B8B4AE08x0x1x0.py
# -*- coding: mbcs -*-
# Created by makepy.py version 0.5.01
# By python version 3.9.7 (default, Sep 16 2021, 16:59:28) [MSC v.1916 64 bit (AMD64)]
# From type library 'XA_Session.dll'
# On Wed Jul 27 20:48:57 2022
'eBest Xing Session Lib'
makepy_version = '0.5.01'
python_version = 0x30907f0

import win32com.client.CLSIDToClass, pythoncom, pywintypes
import win32com.client.util
from pywintypes import IID
from win32com.client import Dispatch

# The following 3 lines may need tweaking for the particular server
# Candidates are pythoncom.Missing, .Empty and .ArgNotFound
defaultNamedOptArg=pythoncom.Empty
defaultNamedNotOptArg=pythoncom.Empty
defaultUnnamedArg=pythoncom.Empty

CLSID = IID('{F5CC65C5-2965-451B-A6C4-CBC7B8B4AE08}')
MajorVersion = 1
MinorVersion = 0
LibraryFlags = 8
LCID = 0x0

class constants:
	XA_FAILED                     =-1         # from enum XA_MESSAGE_ID
	XA_SUCCESS                    =0          # from enum XA_MESSAGE_ID
	XA_NOSELECTED_SERVER          =-1         # from enum XA_SERVER_TYPE
	XA_REAL_SERVER                =0          # from enum XA_SERVER_TYPE
	XA_SIMUL_SERVER               =1          # from enum XA_SERVER_TYPE

from win32com.client import DispatchBaseClass
class IXASession(DispatchBaseClass):
	'IXASession Interface'
	CLSID = IID('{8C0F4618-3BAB-4F19-A59B-A32E08EA711F}')
	coclass_clsid = IID('{7FEF321C-6BFD-413C-AA80-541A275434A1}')

	def ConnectServer(self, szServerIP=defaultNamedNotOptArg, nServerPort=defaultNamedNotOptArg):
		'method ConnectServer'
		return self._oleobj_.InvokeTypes(2, LCID, 1, (11, 0), ((8, 0), (3, 0)),szServerIP
			, nServerPort)

	def DisconnectServer(self):
		'method DisConnectServer'
		return self._oleobj_.InvokeTypes(3, LCID, 1, (24, 0), (),)

	def GetAccountList(self, nIndex=defaultNamedNotOptArg):
		'method GetAccountList'
		# Result is a Unicode object
		return self._oleobj_.InvokeTypes(16, LCID, 1, (8, 0), ((3, 0),),nIndex
			)

	def GetAccountListCount(self):
		'method GetAccountListCount'
		return self._oleobj_.InvokeTypes(17, LCID, 1, (3, 0), (),)

	def GetAccountName(self, szAcc=defaultNamedNotOptArg):
		'method GetAccountName'
		# Result is a Unicode object
		return self._oleobj_.InvokeTypes(18, LCID, 1, (8, 0), ((8, 0),),szAcc
			)

	def GetAcctDetailName(self, szAcc=defaultNamedNotOptArg):
		'method GetAcctDetailName'
		# Result is a Unicode object
		return self._oleobj_.InvokeTypes(19, LCID, 1, (8, 0), ((8, 0),),szAcc
			)

	def GetAcctNickname(self, szAcc=defaultNamedNotOptArg):
		'method GetAcctNickname'
		# Result is a Unicode object
		return self._oleobj_.InvokeTypes(20, LCID, 1, (8, 0), ((8, 0),),szAcc
			)

	def GetClientIP(self):
		'method GetClientIP'
		# Result is a Unicode object
		return self._oleobj_.InvokeTypes(14, LCID, 1, (8, 0), (),)

	def GetCommMedia(self):
		'method GetCommMedia'
		# Result is a Unicode object
		return self._oleobj_.InvokeTypes(12, LCID, 1, (8, 0), (),)

	def GetETKMedia(self):
		'method GetETKMedia'
		# Result is a Unicode object
		return self._oleobj_.InvokeTypes(13, LCID, 1, (8, 0), (),)

	def GetErrorMessage(self, nErrorCode=defaultNamedNotOptArg):
		'method GetErrorMessage'
		# Result is a Unicode object
		return self._oleobj_.InvokeTypes(11, LCID, 1, (8, 0), ((3, 0),),nErrorCode
			)

	def GetLastError(self):
		'method GetLastError'
		return self._oleobj_.InvokeTypes(10, LCID, 1, (3, 0), (),)

	def GetPath(self):
		'method GetPath'
		# Result is a Unicode object
		return self._oleobj_.InvokeTypes(21, LCID, 1, (8, 0), (),)

	def GetServerName(self):
		'method GetServerName'
		# Result is a Unicode object
		return self._oleobj_.InvokeTypes(15, LCID, 1, (8, 0), (),)

	def IsConnected(self):
		'method IsConnected'
		return self._oleobj_.InvokeTypes(4, LCID, 1, (11, 0), (),)

	def IsLoadAPI(self):
		'method IsLoadAPI'
		return self._oleobj_.InvokeTypes(1, LCID, 1, (11, 0), (),)

	def Login(self, szID=defaultNamedNotOptArg, szPwd=defaultNamedNotOptArg, szCertPwd=defaultNamedNotOptArg, nServerType=defaultNamedNotOptArg
			, bShowCertErrDlg=defaultNamedNotOptArg):
		'method Login'
		return self._oleobj_.InvokeTypes(5, LCID, 1, (11, 0), ((8, 0), (8, 0), (8, 0), (3, 0), (11, 0)),szID
			, szPwd, szCertPwd, nServerType, bShowCertErrDlg)

	def Logout(self):
		'method Logout'
		return self._oleobj_.InvokeTypes(7, LCID, 1, (11, 0), (),)

	def SetMode(self, szMode=defaultNamedNotOptArg, szValue=defaultNamedNotOptArg):
		'method SetMode'
		return self._oleobj_.InvokeTypes(23, LCID, 1, (11, 0), ((8, 1), (8, 0)),szMode
			, szValue)

	def SetPath(self, szPath=defaultNamedNotOptArg):
		'method SetPath'
		return self._oleobj_.InvokeTypes(22, LCID, 1, (24, 0), ((8, 1),),szPath
			)

	_prop_map_get_ = {
		"ConnectTimeOut": (8, 2, (3, 0), (), "ConnectTimeOut", None),
		"SendPacketSize": (9, 2, (3, 0), (), "SendPacketSize", None),
	}
	_prop_map_put_ = {
		"ConnectTimeOut": ((8, LCID, 4, 0),()),
		"SendPacketSize": ((9, LCID, 4, 0),()),
	}
	def __iter__(self):
		"Return a Python iterator for this object"
		try:
			ob = self._oleobj_.InvokeTypes(-4,LCID,3,(13, 10),())
		except pythoncom.error:
			raise TypeError("This object does not support enumeration")
		return win32com.client.util.Iterator(ob, None)

class _IXASessionEvents:
	'_IXASessionEvents Interface'
	CLSID = CLSID_Sink = IID('{6D45238D-A5EB-4413-907A-9EA14D046FE5}')
	coclass_clsid = IID('{7FEF321C-6BFD-413C-AA80-541A275434A1}')
	_public_methods_ = [] # For COM Server support
	_dispid_to_func_ = {
		        1 : "OnLogin",
		        2 : "OnLogout",
		        3 : "OnDisconnect",
		}

	def __init__(self, oobj = None):
		if oobj is None:
			self._olecp = None
		else:
			import win32com.server.util
			from win32com.server.policy import EventHandlerPolicy
			cpc=oobj._oleobj_.QueryInterface(pythoncom.IID_IConnectionPointContainer)
			cp=cpc.FindConnectionPoint(self.CLSID_Sink)
			cookie=cp.Advise(win32com.server.util.wrap(self, usePolicy=EventHandlerPolicy))
			self._olecp,self._olecp_cookie = cp,cookie
	def __del__(self):
		try:
			self.close()
		except pythoncom.com_error:
			pass
	def close(self):
		if self._olecp is not None:
			cp,cookie,self._olecp,self._olecp_cookie = self._olecp,self._olecp_cookie,None,None
			cp.Unadvise(cookie)
	def _query_interface_(self, iid):
		import win32com.server.util
		if iid==self.CLSID_Sink: return win32com.server.util.wrap(self)

	# Event Handlers
	# If you create handlers, they should have the following prototypes:
#	def OnLogin(self, szCode=defaultNamedNotOptArg, szMsg=defaultNamedNotOptArg):
#		'method OnLogIn'
#	def OnLogout(self):
#		'method OnLogOut'
#	def OnDisconnect(self):
#		'method OnDisConnect'


from win32com.client import CoClassBaseClass
# This CoClass is known by the name 'XA_Session.XASession'
class XASession(CoClassBaseClass): # A CoClass
	# XASession Class
	CLSID = IID('{7FEF321C-6BFD-413C-AA80-541A275434A1}')
	coclass_sources = [
		_IXASessionEvents,
	]
	default_source = _IXASessionEvents
	coclass_interfaces = [
		IXASession,
	]
	default_interface = IXASession

IXASession_vtables_dispatch_ = 1
IXASession_vtables_ = [
	(( 'IsLoadAPI' , 'bIsInit' , ), 1, (1, (), [ (16395, 10, None, None) , ], 1 , 1 , 4 , 0 , 56 , (3, 0, None, None) , 0 , )),
	(( 'ConnectServer' , 'szServerIP' , 'nServerPort' , 'bIsConnected' , ), 2, (2, (), [ 
			 (8, 0, None, None) , (3, 0, None, None) , (16395, 10, None, None) , ], 1 , 1 , 4 , 0 , 64 , (3, 0, None, None) , 0 , )),
	(( 'DisconnectServer' , ), 3, (3, (), [ ], 1 , 1 , 4 , 0 , 72 , (3, 0, None, None) , 0 , )),
	(( 'IsConnected' , 'bIsConnected' , ), 4, (4, (), [ (16395, 10, None, None) , ], 1 , 1 , 4 , 0 , 80 , (3, 0, None, None) , 0 , )),
	(( 'Login' , 'szID' , 'szPwd' , 'szCertPwd' , 'nServerType' , 
			 'bShowCertErrDlg' , 'bResult' , ), 5, (5, (), [ (8, 0, None, None) , (8, 0, None, None) , 
			 (8, 0, None, None) , (3, 0, None, None) , (11, 0, None, None) , (16395, 10, None, None) , ], 1 , 1 , 4 , 0 , 88 , (3, 0, None, None) , 0 , )),
	(( 'Logout' , 'bResult' , ), 7, (7, (), [ (16395, 10, None, None) , ], 1 , 1 , 4 , 0 , 96 , (3, 0, None, None) , 0 , )),
	(( 'ConnectTimeOut' , 'pVal' , ), 8, (8, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 104 , (3, 0, None, None) , 0 , )),
	(( 'ConnectTimeOut' , 'pVal' , ), 8, (8, (), [ (3, 1, None, None) , ], 1 , 4 , 4 , 0 , 112 , (3, 0, None, None) , 0 , )),
	(( 'SendPacketSize' , 'pVal' , ), 9, (9, (), [ (16387, 10, None, None) , ], 1 , 2 , 4 , 0 , 120 , (3, 0, None, None) , 0 , )),
	(( 'SendPacketSize' , 'pVal' , ), 9, (9, (), [ (3, 1, None, None) , ], 1 , 4 , 4 , 0 , 128 , (3, 0, None, None) , 0 , )),
	(( 'GetLastError' , 'ErrorCode' , ), 10, (10, (), [ (16387, 10, None, None) , ], 1 , 1 , 4 , 0 , 136 , (3, 0, None, None) , 0 , )),
	(( 'GetErrorMessage' , 'nErrorCode' , 'szErrorMsg' , ), 11, (11, (), [ (3, 0, None, None) , 
			 (16392, 10, None, None) , ], 1 , 1 , 4 , 0 , 144 , (3, 0, None, None) , 0 , )),
	(( 'GetCommMedia' , 'szCommMedia' , ), 12, (12, (), [ (16392, 10, None, None) , ], 1 , 1 , 4 , 0 , 152 , (3, 0, None, None) , 0 , )),
	(( 'GetETKMedia' , 'szETKMedia' , ), 13, (13, (), [ (16392, 10, None, None) , ], 1 , 1 , 4 , 0 , 160 , (3, 0, None, None) , 0 , )),
	(( 'GetClientIP' , 'szClientIP' , ), 14, (14, (), [ (16392, 10, None, None) , ], 1 , 1 , 4 , 0 , 168 , (3, 0, None, None) , 0 , )),
	(( 'GetServerName' , 'szServerName' , ), 15, (15, (), [ (16392, 10, None, None) , ], 1 , 1 , 4 , 0 , 176 , (3, 0, None, None) , 0 , )),
	(( 'GetAccountList' , 'nIndex' , 'szAcc' , ), 16, (16, (), [ (3, 0, None, None) , 
			 (16392, 10, None, None) , ], 1 , 1 , 4 , 0 , 184 , (3, 0, None, None) , 0 , )),
	(( 'GetAccountListCount' , 'nCount' , ), 17, (17, (), [ (16387, 10, None, None) , ], 1 , 1 , 4 , 0 , 192 , (3, 0, None, None) , 0 , )),
	(( 'GetAccountName' , 'szAcc' , 'szAccName' , ), 18, (18, (), [ (8, 0, None, None) , 
			 (16392, 10, None, None) , ], 1 , 1 , 4 , 0 , 200 , (3, 0, None, None) , 0 , )),
	(( 'GetAcctDetailName' , 'szAcc' , 'szAcctDetailName' , ), 19, (19, (), [ (8, 0, None, None) , 
			 (16392, 10, None, None) , ], 1 , 1 , 4 , 0 , 208 , (3, 0, None, None) , 0 , )),
	(( 'GetAcctNickname' , 'szAcc' , 'szAcctNickname' , ), 20, (20, (), [ (8, 0, None, None) , 
			 (16392, 10, None, None) , ], 1 , 1 , 4 , 0 , 216 , (3, 0, None, None) , 0 , )),
	(( 'GetPath' , 'szPath' , ), 21, (21, (), [ (16392, 10, None, None) , ], 1 , 1 , 4 , 0 , 224 , (3, 0, None, None) , 0 , )),
	(( 'SetPath' , 'szPath' , ), 22, (22, (), [ (8, 1, None, None) , ], 1 , 1 , 4 , 0 , 232 , (3, 0, None, None) , 0 , )),
	(( 'SetMode' , 'szMode' , 'szValue' , 'bSetMode' , ), 23, (23, (), [ 
			 (8, 1, None, None) , (8, 0, None, None) , (16395, 10, None, None) , ], 1 , 1 , 4 , 0 , 240 , (3, 0, None, None) , 0 , )),
]

RecordMap = {
}

CLSIDToClassMap = {
	'{6D45238D-A5EB-4413-907A-9EA14D046FE5}' : _IXASessionEvents,
	'{8C0F4618-3BAB-4F19-A59B-A32E08EA711F}' : IXASession,
	'{7FEF321C-6BFD-413C-AA80-541A275434A1}' : XASession,
}
CLSIDToPackageMap = {}
win32com.client.CLSIDToClass.RegisterCLSIDsFromDict( CLSIDToClassMap )
VTablesToPackageMap = {}
VTablesToClassMap = {
	'{8C0F4618-3BAB-4F19-A59B-A32E08EA711F}' : 'IXASession',
}


NamesToIIDMap = {
	'_IXASessionEvents' : '{6D45238D-A5EB-4413-907A-9EA14D046FE5}',
	'IXASession' : '{8C0F4618-3BAB-4F19-A59B-A32E08EA711F}',
}

win32com.client.constants.__dicts__.append(constants.__dict__)
"""
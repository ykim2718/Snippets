#if !defined(CreateProcessWithRedirectedIO_HEADER_INSTALLED)
#define CreateProcessWithRedirectedIO_HEADER_INSTALLED

/////////////////////////////////////////////////////////////////////////////
// shik96

//2001.0609
void CreateProcessWithRedirectedIO(
   const char *qCommand,
   CString &sReturn,
   int bWindowless
   );

/////////////////////////////////////////////////////////////////////////////
#endif
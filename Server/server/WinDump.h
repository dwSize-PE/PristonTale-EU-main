#ifdef WIN32

LONG WINAPI unhandled_handler( struct _EXCEPTION_POINTERS* apExceptionInfo );

void create_minidump(struct _EXCEPTION_POINTERS* apExceptionInfo);

#endif // WIN32
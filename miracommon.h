#ifndef __MIRA_COMMON_H_
#define __MIRA_COMMON_H_

#ifdef __linux__

#define MMAP_LENGTH 1 << 30 // 1GB mapped LOL

#define ERROR_DEBUG_FORMAT "Error in file: %s, line: %d\n"

#define GET_ERROR( format, ... ) fprintf( stdout, format, __VA_ARGS__ ) 

#endif // __linux__

#endif

#ifndef _MIRASTRING_H_
#define _MIRASTRING_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>

#include "miracommon.h"

typedef struct {
  char*    _s;
  uint32_t offset;
  uint32_t used_bytes;
} string;

  
string* s_init() {
  string* s = ( string* )malloc( sizeof( string ) );
  if( s == NULL ) {
    fprintf( stderr, "ERROR allocating struct string\n" );
    return NULL;
  }

  s->_s = ( char* )mmap( NULL, MMAP_LENGTH,
			 PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0 );

  s->offset     = 0;
  s->used_bytes = 0;
    
  if( s->_s == MAP_FAILED ) {
    GET_ERROR( ERROR_DEBUG_FORMAT, __FILE__, __LINE__ );
    free( s );
    return NULL;
  }

  return s;
}

int s_destroy( string* s ) {
  if( munmap( s->_s, MMAP_LENGTH ) != 0 ) {
    GET_ERROR( ERROR_DEBUG_FORMAT, __FILE__, __LINE__ );
    return -1;
  } else {
    if( s != NULL ) {
      free( s );
    }
    return 0;
  }
}

int s_strlen( const char* val ) {
  if( val != NULL ) {
    int count = 0;
    while( *(val + count) != '\0' ) {
      count++;
    }
    return count;
  }
  return -1;
}

// off_start: if set as -1, it inserts from string->offset ), else
// it uses off_start as starting offset

void s_insert( string* s, const char* val, int off_start ) {
  if( val == NULL || s == NULL ) {
    GET_ERROR( ERROR_DEBUG_FORMAT, __FILE__, __LINE__ );
    exit( 1 );
  }
  
  int val_length = s_strlen( val );
  
  if( val_length != -1 ) {

    if( off_start == -1 ) {

      off_start = s->offset;
      s->offset += val_length;

    } else {

      if( ( uint32_t )off_start >= s->offset ) {

	s->offset = off_start + val_length;
	
      } else if ( ( uint32_t )off_start + val_length > s->offset ) {

	s->offset -= ( off_start + val_length );

      } else {

	// s->offset = s->offset
	
      } // if( off_start >= s->offset )

    } // if( off_start == -1 )

    s->used_bytes += val_length;

    if( off_start + val_length >= MMAP_LENGTH ) {

      GET_ERROR( "offset + string_length exceeds MAP length, offset %d, length %d, map length %d", off_start, val_length, MMAP_LENGTH );

    } else {

      int cnt = 0;

      while( cnt < val_length ) {
	*( s->_s + off_start + cnt ) = val[cnt];
	cnt++;
      }
      
    } // if( off_start + val_length >= MMAP_LENGTH )
    
  } // if( val_length != -1 )
  
}
   
#endif // __MIRASTRING_H_

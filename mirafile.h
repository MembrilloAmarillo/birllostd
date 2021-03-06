#ifndef _MIRAFILE_H_
#define _MIRAFILE_H_

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>

#include "miracommon.h"
#include "mirastring.h"

typedef enum {
	      RD   = O_RDONLY,
	      WR   = O_WRONLY,
	      RDWR = O_RDWR
} m_flags;

typedef struct {

  void* file;
  int fd;
  int length;
  
} m_file;

m_file* f_init( const char* path, m_flags mf  ) {

  m_file* f = ( m_file* )malloc( sizeof( m_file ) );
  if( f == NULL ) {
    GET_ERROR( ERROR_DEBUG_FORMAT, __FILE__, __LINE__ );
    exit( 1 );    
  }

  f->fd = open( path, mf );
  if( f->fd == -1 ) {
    GET_ERROR( ERROR_DEBUG_FORMAT, __FILE__, __LINE__ );
    exit( 1 );    
  }

  f->file = mmap( NULL, MMAP_LENGTH, PROT_READ | PROT_WRITE, MAP_PRIVATE, f->fd, 0 );
  if( f->file == MAP_FAILED ) {
    GET_ERROR( ERROR_DEBUG_FORMAT, __FILE__, __LINE__ );
    exit( 1 );
  }

  f->length = lseek( f->fd, 0, SEEK_END );
  if( f->length == -1 ) {
    GET_ERROR( ERROR_DEBUG_FORMAT, __FILE__, __LINE__ );
    exit( 1 );
  }

  // Rewind file
  lseek( f->fd, 0, SEEK_SET);
  
  return f;
  
}


// string s must be initiated before calling this function
void f_read( m_file* f, string* s ) {

  if( f == NULL || s == NULL ) {
    GET_ERROR( ERROR_DEBUG_FORMAT, __FILE__, __LINE__ );
    exit( 1 );
  }
  
  lseek( f->fd, 0, SEEK_CUR );
  char* buf = ( char* )malloc( f->length * sizeof( char ) + 1 );
  
  if( buf == NULL ) {
    GET_ERROR( ERROR_DEBUG_FORMAT, __FILE__, __LINE__ );
    exit( 1 );
  }
  
  read( f->fd, ( char* )buf, f->length );
  
  s_insert( s, buf, -1 );


#if 0
  fprintf( stdout, "File length: %d\n", f->length );
  fprintf( stdout, "File desc  : %d\n", f->fd     );
  fprintf( stdout, "Buf description: %s\n", ( char* )buf   );
#endif  
  
  free( buf );
}

void f_write( m_file* f, string* s ) {

  ssize_t return_write = write( f->fd, s->_s, s->offset );
  f->length += s->offset;
}

void f_destroy( m_file* f ) {
  if( f != NULL ) {
    if( munmap( f->file, MMAP_LENGTH == 0 ) ) {
      free( f );
    } else {
      GET_ERROR( ERROR_DEBUG_FORMAT, __FILE__, __LINE__ );
      exit( 1 );      
    }
  }
}

#endif // _MIRAFILE_H_

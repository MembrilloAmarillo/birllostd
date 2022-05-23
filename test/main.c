#include "../mirastring.h"
#include "../mirafile.h"

int main( void )
{
  string* s = s_init();
  m_file* f = f_init( "test/file_test.txt", RDWR );

  s_insert( s, "HOLA BUENAS TETAS", -1 );
  s_insert( s, " No me comas los webos porfa", -1 );
  s_insert( s, "adios", 0 );
  s_insert( s, " muere", -1 );
  s_insert( s, "chao chao", 10 );
  s_insert( s, "veo", 0 );
  s_insert( s, " nada", -1 );

  f_read( f, s );
  
  fprintf( stdout, "%s", s->_s );
  fprintf( stdout, "\nBytes (re)written: %d",   s->used_bytes );
  fprintf( stdout, "\nOffset:            %d\n", s->offset     );  
  
  s_destroy( s );
  f_destroy( f );

  
  return 0;
}

#include "../miracommon.h"
#include "../mirastring.h"
#include "../mirafile.h"

int main( void )
{
  string* s = s_init();
  m_file* f = f_init( "test/big.txt", RDWR );

  /******************************************************/
  /* s_insert( s, "HOLA BUENAS", -1 );		        */
  /* s_insert( s, " Sadge anime moment", -1 ); */
  /* s_insert( s, "adios", 0 );			        */
  /* s_insert( s, " shine", -1 );		        */
  /* s_insert( s, "chao chao", 10 );		        */
  /* s_insert( s, "veo", 0 );			        */
  /* s_insert( s, " nada", -1 );		        */
  /******************************************************/
  
  f_read( f, s );
  
  /**************************************/
  /* s_insert( s, "NO SE NADA\n", -1 ); */
  /* f_write( f, s );		        */
  /**************************************/

  /********************************************************************/
  /* fprintf( stdout, "%s", s->_s );				      */
  /* fprintf( stdout, "\nBytes (re)written: %d",   s->used_bytes );   */
  /* fprintf( stdout, "\nOffset:            %d\n", s->offset     );   */
  /********************************************************************/

  // while( getchar() != 's' );
  
  s_destroy( s );
  f_destroy( f );

  return 0;
}

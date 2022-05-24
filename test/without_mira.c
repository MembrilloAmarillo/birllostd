#include <stdio.h>
#include <stdlib.h>

int main( void )
{

  FILE* f = fopen( "test/big.txt", "r" );

  int size = fseek( f, 0, SEEK_END );
  size     = ftell( f );

  char* s = ( char* )malloc( size * sizeof( char ) + 1 );

  rewind( f );
  fread( s, sizeof( char ), size, f ); 

  //printf( "%s", s );
  
  //while( getchar() != 's' );
  
  free( s );
  fclose( f );
}

/* This file contains text copied from the (generated) file mp0.c with
 * FIXPT tests removed and `z...' names changed to `q...'.
 * This is needed for time.c and mathtest.c
 */
#define EXTERN extern
#include "test_mpd.h"

fraction qmakefraction ( p , q ) 
integer p ; 
integer q ; 
{register fraction Result; integer f  ; 
  integer n  ; 
  boolean negative  ; 
  integer becareful  ; 
  if ( p >= 0 ) 
  negative = false ; 
  else {
      
    p = - (integer) p ; 
    negative = true ; 
  } 
  if ( q <= 0 ) 
  {
	;
#ifdef DEBUG
    if ( q == 0 ) 
    confusion ( 47 ) ; 
#endif /* DEBUG */
    q = - (integer) q ; 
    negative = ! negative ; 
  } 
  n = p / q ; 
  p = p % q ; 
  if ( n >= 8 ) 
  {
    aritherror = true ; 
    if ( negative ) 
    Result = -2147483647L ; 
    else Result = 2147483647L ; 
  } 
  else {
      
    n = ( n - 1 ) * 268435456L ; 
    f = 1 ; 
    do {
	becareful = p - q ; 
      p = becareful + p ; 
      if ( p >= 0 ) 
      f = f + f + 1 ; 
      else {
	  
	f = f + f ; 
	p = p + q ; 
      } 
    } while ( ! ( f >= 268435456L ) ) ; 
    becareful = p - q ; 
    if ( becareful + p >= 0 ) 
    incr ( f ) ; 
    if ( negative ) 
    Result = - (integer) ( f + n ) ; 
    else Result = f + n ; 
  } 
  return(Result) ; 
} 
integer qtakefraction ( q , f ) 
integer q ; 
fraction f ; 
{register integer Result; integer p  ; 
  boolean negative  ; 
  integer n  ; 
  integer becareful  ; 
  if ( f >= 0 ) 
  negative = false ; 
  else {
      
    f = - (integer) f ; 
    negative = true ; 
  } 
  if ( q < 0 ) 
  {
    q = - (integer) q ; 
    negative = ! negative ; 
  } 
  if ( f < 268435456L ) 
  n = 0 ; 
  else {
      
    n = f / 268435456L ; 
    f = f % 268435456L ; 
    if ( q <= 2147483647L / n ) 
    n = n * q ; 
    else {
	
      aritherror = true ; 
      n = 2147483647L ; 
    } 
  } 
  f = f + 268435456L ; 
  p = 134217728L ; 
  if ( q < 1073741824L ) 
  do {
      if ( odd ( f ) ) 
    p = halfp ( p + q ) ; 
    else p = halfp ( p ) ; 
    f = halfp ( f ) ; 
  } while ( ! ( f == 1 ) ) ; 
  else do {
      if ( odd ( f ) ) 
    p = p + halfp ( q - p ) ; 
    else p = halfp ( p ) ; 
    f = halfp ( f ) ; 
  } while ( ! ( f == 1 ) ) ; 
  becareful = n - 2147483647L ; 
  if ( becareful + p > 0 ) 
  {
    aritherror = true ; 
    n = 2147483647L - p ; 
  } 
  if ( negative ) 
  Result = - (integer) ( n + p ) ; 
  else Result = n + p ; 
  return(Result) ; 
} 
integer qtakescaled ( q , f ) 
integer q ; 
scaled f ; 
{register integer Result; integer p  ; 
  boolean negative  ; 
  integer n  ; 
  integer becareful  ; 
  if ( f >= 0 ) 
  negative = false ; 
  else {
      
    f = - (integer) f ; 
    negative = true ; 
  } 
  if ( q < 0 ) 
  {
    q = - (integer) q ; 
    negative = ! negative ; 
  } 
  if ( f < 65536L ) 
  n = 0 ; 
  else {
      
    n = f / 65536L ; 
    f = f % 65536L ; 
    if ( q <= 2147483647L / n ) 
    n = n * q ; 
    else {
	
      aritherror = true ; 
      n = 2147483647L ; 
    } 
  } 
  f = f + 65536L ; 
  p = 32768L ; 
  if ( q < 1073741824L ) 
  do {
      if ( odd ( f ) ) 
    p = halfp ( p + q ) ; 
    else p = halfp ( p ) ; 
    f = halfp ( f ) ; 
  } while ( ! ( f == 1 ) ) ; 
  else do {
      if ( odd ( f ) ) 
    p = p + halfp ( q - p ) ; 
    else p = halfp ( p ) ; 
    f = halfp ( f ) ; 
  } while ( ! ( f == 1 ) ) ; 
  becareful = n - 2147483647L ; 
  if ( becareful + p > 0 ) 
  {
    aritherror = true ; 
    n = 2147483647L - p ; 
  } 
  if ( negative ) 
  Result = - (integer) ( n + p ) ; 
  else Result = n + p ; 
  return(Result) ; 
} 
scaled qmakescaled ( p , q ) 
integer p ; 
integer q ; 
{register scaled Result; integer f  ; 
  integer n  ; 
  boolean negative  ; 
  integer becareful  ; 
  if ( p >= 0 ) 
  negative = false ; 
  else {
      
    p = - (integer) p ; 
    negative = true ; 
  } 
  if ( q <= 0 ) 
  {
	;
#ifdef DEBUG
    if ( q == 0 ) 
    confusion ( 47 ) ; 
#endif /* DEBUG */
    q = - (integer) q ; 
    negative = ! negative ; 
  } 
  n = p / q ; 
  p = p % q ; 
  if ( n >= 32768L ) 
  {
    aritherror = true ; 
    if ( negative ) 
    Result = -2147483647L ; 
    else Result = 2147483647L ; 
  } 
  else {
      
    n = ( n - 1 ) * 65536L ; 
    f = 1 ; 
    do {
	becareful = p - q ; 
      p = becareful + p ; 
      if ( p >= 0 ) 
      f = f + f + 1 ; 
      else {
	  
	f = f + f ; 
	p = p + q ; 
      } 
    } while ( ! ( f >= 65536L ) ) ; 
    becareful = p - q ; 
    if ( becareful + p >= 0 ) 
    incr ( f ) ; 
    if ( negative ) 
    Result = - (integer) ( f + n ) ; 
    else Result = f + n ; 
  } 
  return(Result) ; 
} 

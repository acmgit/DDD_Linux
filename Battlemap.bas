  5 randomize
 10 for y=1 to 10
 20   for x=1 to 12
 25     Tile=getRandom
 26     select case Tile
 27       case Tile=0 to 59
 28         color 2 : print "G";
 29       case Tile=60 to 84
 30         color 10 : print "S";
 31       case Tile=85 to 93
 32         color 6 : print "W";
 33       case Tile=94 to 100
 34         color 7 : print "x";
 35       case else
 36         color 15 : print Tile;
 37     end select
 40   next x
 50   print
 60 next y
 61 color 15
500 function getRandom
510   getRandom=int((rnd*10000)mod 101)
515 end function

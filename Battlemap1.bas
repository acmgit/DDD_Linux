randomize
rgf = 0: rgt = 84: g$ = "G": rem Grasland
rsf = 85: rst = 92: s$ = "S": rem Gestrüpp
rwf = 93: rwt = 97: w$ = "W": rem Wald
rxf = 98: rxt = 100: x$ = "X": rem Geröll
for column=1 to 10
  for row=1 to 12
    Tile=getRandom
    select case Tile
      case Tile=rgf to rgt
        color 2 : print g$;
      case Tile=rsf to rst
        color 10 : print s$;
      case Tile=rwf to rwt
        color 6 : print w$;
      case Tile=rxf to rxt
        color 7 : print x$;
      case else
        color 15 : print Tile;
    end select
  next row
  print
next column
color 15
function getRandom
  getRandom=int((rnd*10000)mod 101)
end function

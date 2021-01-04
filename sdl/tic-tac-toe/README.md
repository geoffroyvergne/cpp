# Morpion game

# build

cmake . -B build/
cmake --build build/

# check memory footprint
top -pid $(pgrep -f tic-tac-toe)
top -pid $(pgrep -f vector-test)

# TODO

- [ X ] refactor methods to proper class
- [ ] refactor lineDone
- [ ] refactor getCaseNumberByTextureParams
- [ X ] add messages winner and score
- [ X ] add message class
- [ X ] fix memory leak
- [ X ] space == enter, esc quit
- [ X ] use destructor to help clean sdl objects
- [ ] add player object
- [ ] use more mario like sprites
- [ ] no cleanup in piece class
- [ ] 

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
- [ ] fix memory leak
- [ ] space == enter, esc quit
- [ ] use destructor to help clean sdl objects
- [ ] 
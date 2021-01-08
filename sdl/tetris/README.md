# Tetris

# build

cmake . -B build/
cmake --build build/

# check memory footprint
top -pid $(pgrep -f tetris)

# TODO
- [ ] Add title + score
- [ X ] Add reset key
- [ X ] Automate piece move down
- [ X ] finish linedone algorithm
- [ X ] add random new piece
- [ X ] add gameOver params
- [ X ] add pause function
- [ ] Wright pause message
- [ X ] remove blocks instead of move them
- [ ] Add score and score message
- [ X ] bug when rotate piece extrem left
- [ ] improve all for loops with 4 (dirty bug fix)


# Tetris

# build

cmake . -B build/
cmake --build build/

# check memory footprint
top -pid $(pgrep -f tetris)

# TODO
- [ ] Add title + score
- [ X ] Add reset key
- [ ] Automate piece move down
- [ ] finish linedone algorithm
- [ ] 
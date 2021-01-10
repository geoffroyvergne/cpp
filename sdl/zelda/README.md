# SDL Zelda

# build

cmake . -B build/
cmake --build build/

# check memory footprint
top -pid $(pgrep -f tetris)

# TODO
- [ ] Make infinit walk if extrem right goto extrem left
- [ ] Add blocks and sprites in levels
- [ ] 

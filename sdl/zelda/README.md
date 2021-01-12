# SDL Zelda

# build

cmake . -B build/
cmake --build build/

# check memory footprint
top -pid $(pgrep -f zelda)

# TODO
- [ X ] Make infinit walk if extrem right goto extrem left
- [ X ] Add blocks and sprites in levels
- [ x ] Add more levels around first one
- [ X ] Add enemys
- [ ] Make enemies move
- [ X ] Kill enemy
- [ ] Display lives

# Tetris

# build

cmake . -B build/
cmake --build build/

# check memory footprint
top -pid $(pgrep -f tetris)

# TODO
- [ ]

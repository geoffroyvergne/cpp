# Game of life

# build

cmake . -B build/
cmake --build build/

# check memory footprint
top -pid $(pgrep -f gameoflife)

# TODO
- [ ]
# Puissance4

# build

cmake . -B build/
cmake --build build/

# check memory footprint
top -pid $(pgrep -f puissance4)

# TODO
- [ ]
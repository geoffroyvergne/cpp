# SDL Mario

# build

cmake . -B build/
cmake --build build/

# check memory footprint
top -pid $(pgrep -f mario)

# TODO
- [ ]

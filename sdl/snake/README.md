# SDL Snake

# build

cmake . -B build/
cmake --build build/

# check memory footprint
top -pid $(pgrep -f snake)

# TODO
# SDL Mario

# build

cmake . -B build/
cmake --build build/

# check memory footprint
top -pid $(pgrep -f mario)

# TODO
- [ ] Improve collision detection, more accurate
- [ ] when jump, pass over pipe
- [ ] add enemies
- [ ] add level begin
- [ ] improve scrolling smoothness (sdl help)
- [ ] 

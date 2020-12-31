# SDL Mario portage

# technical specs
Resolution : 
NTSC 256 x 224  
PAL  256 x 240 

# build
cmake . -B build/
cmake --build build/

# TODO
- [ ] Add level begin and end so it is not possible to go out limits
- [ ] Add objects colision detections
- [ ] Add detection of multiple keyboard arrow key
- [ ] Make mario walk animation while walking
- [ ] Improve jump
- [ ] 
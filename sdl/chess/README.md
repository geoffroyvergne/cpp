# SDL Chess

# build

cmake . -B build/
cmake --build build/

# check memory footprint
top -pid $(pgrep -f chess)

# TODO
- [ ] Impossibility to taks same color
- [ ] Impossibility for cursor to get out the plateau
- [ ] Add case number around plateau
- [ ] Put deleted pieces on left and right sides
- [ ] Add validation move for pieces
- [ ] Add players
- [ ] Add game turn by turn
- [ ] Add winner and looser
- [ ] What happen if computer plays
- [ ] 

#ifndef TILETYPE
#define TILETYPE

enum TileType {
    none,           //00
    ground,         //01
    brick,          //02
    question_mark,  //03

    // pipe
    pipe_ul,        //04
    pipe_ur,        //05
    pipe_ll,        //06
    pipe_lr,        //07

    // hill
    hill_l,         
    hill_r,
    hill_cs,         
    hill_c,     
    hill_t,         

    // bush
    bush_l,         
    bush_c,        
    bush_r,         

    // cloud
    cloud_ul,       
    cloud_ur,       
    cloud_uc,       
    cloud_ll,       
    cloud_lr,       
    cloud_lc,       
};

#endif

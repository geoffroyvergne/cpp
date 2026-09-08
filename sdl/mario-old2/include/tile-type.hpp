
#ifndef TILETYPE
#define TILETYPE

enum TileType {

    // genral 00-09
    none            = 00,
    ground          = 01,
    brick           = 02,
    question_mark   = 03,

    // pipe 20-29
    pipe_ul         = 20,
    pipe_ur         = 21,
    pipe_ll         = 22,
    pipe_lr         = 23,

    // hill 30-39
    hill_l          = 30,
    hill_r          = 31,
    hill_cs         = 32,
    hill_c          = 33,
    hill_t          = 34,

    // bush 40-49
    bush_l          = 40,
    bush_c          = 41,
    bush_r          = 42,

    // cloud 50-59
    cloud_ul        = 50,
    cloud_ur        = 51,
    cloud_uc        = 52,
    cloud_ll        = 53,
    cloud_lr        = 54,
    cloud_lc        = 55,

    
};

#endif

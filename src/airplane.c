#include "airplane.h"

// Top speed 170 km/h, time to 3281 feet in 4:30 mins,
// time to 6562 7 mins, time to 9843 12:30 mins
struct airplane_kind Albatros_D2 = {
    "Albatros D.II",
    17060,
    {170, 162, 149, 128, 0},
    {2100, 1874, 1574, 1274, 0},
    TokenAlbatros_D2,
    6,
    340,
    6,
    3,
  AIRPLANE_FRONT_GUN | AIRPLANE_FRONT_GUNx2
};

// Top speed 186 km/h, climb rate 4.5 m/s, time to 3281 feet in 4 mins
struct airplane_kind Albatros_D5a = {
    "Albatros D.Va",
    18700,
    //{ 4.0, 3.8, 3.5, 3.0, 0 },
    { 186, 177, 163, 140, 0 },
    { 2360, 2108, 1770, 1432, 0 },
    TokenAlbatros_D5a,
    6,
    350,
    6,
    3,
    AIRPLANE_FRONT_GUN | AIRPLANE_FRONT_GUNx2
};

// Top speed 180 km/h, time to 10000 feet in 14 mins, 16100 in 35 min
struct airplane_kind SopwithPup = {
    "Sopwith Pup",
    17500,
    { 180, 171, 157, 134, 0 },
    { 1600, 1400, 1100, 1000, 0 },
    TokenSopwithPup,
    4,
    500,
    8,
    2,
    AIRPLANE_FRONT_GUN
};

struct airplane_kind *airplane_data[] = {
    & Albatros_D2, & Albatros_D5a, & SopwithPup
}

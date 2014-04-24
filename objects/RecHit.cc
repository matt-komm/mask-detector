#include "RecHit.hh"

RecHit::RecHit():
    _pos(0,0,0),
    _detId(0),
    _time(-1),
    _uncertainty(0,0,0),
    _simHitId(-1)
{
}

RecHit::~RecHit()
{
}



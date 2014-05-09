#ifndef DETID_H
#define DETID_H

#include <sstream>

class DetId
{
    public:
        enum Type {BARREL, ENDCAP};
    private:
        unsigned int _layer, _subid;
        Type _type;
        DetId():
            _layer(0),_subid(0)
        {
        }
    public:
        DetId(const DetId& detId):
            _layer(detId._layer),
            _subid(detId._subid)
        {
        }
        
        inline unsigned int layer() const
        {
            return _layer;
        }
        
        inline unsigned int subid() const
        {
            return _subid;
        }
        
        
        static DetId* barrelId(unsigned int layer, unsigned int subid)
        {
            DetId* detId = new DetId();
            detId->_layer=layer;
            detId->_subid=subid;
            detId->_type=BARREL;
            return detId;
        }
        
        static DetId* endcapId(unsigned int layer, unsigned int subid)
        {
            DetId* detId = new DetId();
            detId->_layer=layer;
            detId->_subid=subid;
            detId->_type=ENDCAP;
            return detId;
        }
        
        ~DetId()
        {
        }
        
        std::string GetDetName()
        {
            std::stringstream ss;
            if (_type==BARREL)
            {
                ss << "Barrel";
            }
            else if (_type==ENDCAP)
            {
                ss << "Endcap";
            }
            ss << "layer"<<_layer;
            ss << "subid"<<_subid;
            return ss.str();
        }
        
        std::string GetHitCollectionName()
        {
            return GetDetName()+"Hits";
        }
};

#endif


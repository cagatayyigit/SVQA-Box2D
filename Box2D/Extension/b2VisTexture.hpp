//
//  b2VisTexture.hpp
//  Box2D
//
//  Created by Tayfun Ateş on 6.10.2019.
//

#ifndef b2VisTexture_hpp
#define b2VisTexture_hpp

#include "Box2D/Common/b2Math.h"
#include <memory>

class b2VisTexture
{
public:
    b2VisTexture(const unsigned int& texId, const int& atlasWidth, const int& atlasHeight, const b2Vec2& upperLeftRatio, const b2Vec2& lowerRightRatio);
    virtual ~b2VisTexture();
    
    //Getters
    unsigned int getTextureId() const;
    int getWidth() const;
    int getHeight() const;
    int getAtlasWidth() const;
    int getAtlasHeight() const;
    b2Vec2 getUpperLeftCornerCoord() const;
    b2Vec2 getLowerRightCornerCoord() const;
    
    typedef std::shared_ptr<b2VisTexture> Ptr;
    
private:
    bool m_bOwner;
    unsigned int m_nTexId;
    int m_nWidth;
    int m_nHeight;
    int m_nAtlasWidth;
    int m_nAtlasHeight;
    
    b2Vec2 m_vUpperLeftCornerCoord;
    b2Vec2 m_vLowerRightCornerCoord;
};

#endif /* b2VisTexture_hpp */

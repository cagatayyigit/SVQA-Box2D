#pragma once

#include "Scene10Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
    class Scene10Simulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<Scene10Simulation> Ptr;
        Scene10Simulation(Scene10Settings::Ptr settings) : SimulationBase(settings)
        {
            SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_Scene10;
        }
        
        void InitializeScene() override {
            // Basket
            AddTargetBasket(b2Vec2(getExtremeCases(m_sStaticObjectOrientationType, 2.0, 6.0), -1.2f), 0.0f);
            
            // top
            float height = getExtremeCases(m_sStaticObjectOrientationType, 26, 30);
            AddStaticObject(b2Vec2(-8.0f, height),
                            44 * M_PI / getExtremeCases(m_sStaticObjectOrientationType, 51.2, 57.0),
                            SimulationObject::STATIC_PLATFORM);
            
            // Middle Right Floor dynamic basket
            AddStaticObject(b2Vec2(getExtremeCases(m_sStaticObjectOrientationType, 9, 13), getExtremeCases(m_sStaticObjectOrientationType, 16, 18)),
                            0, SimulationObject::STATIC_PLATFORM);
            
            
            // Middle Inclined Left  Floor
            AddStaticObject(b2Vec2(-17.0f, 17.0f),
                            43 * M_PI / getExtremeCases(m_sStaticObjectOrientationType, 51.2, 57.0),
                            SimulationObject::STATIC_PLATFORM);
            
            // Bottom Inclıned Right Floor
            float x = getExtremeCases(m_sStaticObjectOrientationType, 14, 18);
            AddStaticObject(b2Vec2(x, 10.0f),
                            -46 * M_PI / getExtremeCases(m_sStaticObjectOrientationType, 51.2, 57.0),
                            SimulationObject::STATIC_PLATFORM);
            
            // Bottom Left  Floor
            AddStaticObject(b2Vec2(getExtremeCases(m_sStaticObjectOrientationType, -10, -6), getExtremeCases(m_sStaticObjectOrientationType, 5, 10)),
                            0, SimulationObject::STATIC_PLATFORM);
            
            
            if (m_bIncludeDynamicObjects) {
                
                AddRandomDynamicObject(
                    b2Vec2(-8.0f, height + 4.0f),
                    b2Vec2(0.0f, 0.0f)
                );
                
                
                AddRandomDynamicObject(
                    b2Vec2(-19.0f,  22.0f),
                    b2Vec2(0.0f, 0.0f)
                );
                
                AddRandomDynamicObject(
                    b2Vec2(16.0f, 14.0f),
                    b2Vec2(0.0f, 0.0f)
                );
            }
            
            
        }
        
    private:
        bool m_bObstaclesCreated;
        int m_nNumberOfObjects;
        int m_nNumberOfObstacles;
        float32 m_fSpeed;
        b2Vec2 m_vMovingObjPosition;
        b2Vec2 m_vStagnantObjPosition;
        b2Vec2 m_vObstaclePosition;
        b2Vec2 m_vInitialDropVelocity;
    };
}

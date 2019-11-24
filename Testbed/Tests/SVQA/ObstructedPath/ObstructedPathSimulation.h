//
//  ObstructedPathSimulation.h
//  Testbed
//
//  Created by Tayfun Ateş on 24.11.2019.
//

#ifndef ObstructedPathSimulation_h
#define ObstructedPathSimulation_h

#include "SimulationColor.h"
#include "ObstructedPathSettings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h>

namespace svqa {
    class ObstructedPathSimulation : public SimulationBase
    {
    public:
        typedef std::shared_ptr<ObstructedPathSimulation> Ptr;
        
        ObstructedPathSimulation(ObstructedPathSettings::Ptr _settings_) : SimulationBase(_settings_)
        {
            m_nNumberOfObjects = _settings_->numberOfObjects;
            m_nNumberOfObstacles = _settings_->numberOfObstacles;
            
            m_vInitialDropVelocity = b2Vec2(0.0f, -20.0f);
            
            m_vThrowMin = b2Vec2(-10.0f, 40.0f);
            m_vThrowMax = b2Vec2(-5.0f, 40.0f);
            
            m_vObstacleMin = b2Vec2(-30.0f, 10.0f);
            m_vObstacleMax = b2Vec2(30.0f, 40.0f);
            
            m_bObstaclesCreated = false;
            
            {
                b2BodyDef bd;
                b2Body* ground = m_world->CreateBody(&bd);

                b2EdgeShape shape;
                shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
                ground->CreateFixture(&shape, 0.0f);
            }
            
            SET_FILE_OUTPUT_TRUE(m_pSettings->outputFilePath)
        }

        virtual void Step(SettingsBase* settings) override
        {
            if(!m_bObstaclesCreated) {
                createObstacles();
            }
            Simulation::Step(settings);
        }
        
        virtual SimulationID getIdentifier() override
        {
            return SimulationID::ID_ObstructedPath;
        }
        
    private:
        
        void createObstacles()
        {
            for(int i=0; i < m_nNumberOfObstacles; i++) {
                while(!createObstacle()) {
                    
                }
            }
            m_bObstaclesCreated = true;
        }
        
        bool createObstacle()
        {
            SimulationObject object = SimulationObject(SimulationObject::STANDARD_RECTANGLE);
            b2VisPolygonShape shape = object.getShape();
            
            float posX = RandomFloat(m_vObstacleMin.x, m_vObstacleMax.x);
            float posY = RandomFloat(m_vObstacleMin.y, m_vObstacleMax.y);
            float orientation = RandomFloat(-M_PI / 4, M_PI / 4);
            
            SimulationMaterial mat = SimulationMaterial(SimulationMaterial::RUBBER);
            
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position = b2Vec2(posX,posY);
            bd.angle = orientation;
            
            BODY* dynamicObstacle = (BODY*) m_world->CreateBody(&bd);
            dynamicObstacle->CreateFixture(&shape, mat.getDensity());
            m_world->Step(0.0f, 0, 0);
            
            b2ContactEdge* contact = dynamicObstacle->GetContactList();
            if(contact) {
                m_world->DestroyBody(dynamicObstacle);
                return false;
            } else {
                m_world->DestroyBody(dynamicObstacle);
                b2BodyDef bd;
                bd.type = b2_staticBody;
                bd.position = b2Vec2(posX,posY);
                bd.angle = orientation;
                
                BODY* staticObstacle = (BODY*) m_world->CreateBody(&bd);
                staticObstacle->CreateFixture(&shape, mat.getDensity());
                
                int colorIndex = randWithBound(m_nDistinctColorUsed);
                SimulationColor col = SimulationColor((SimulationColor::TYPE) colorIndex);
                staticObstacle->setTexture(mat.getTexture());
                staticObstacle->setColor(col.GetColor(mat.type));
            }
            return true;
        }
        
        bool m_bObstaclesCreated;
        int m_nNumberOfObjects;
        int m_nNumberOfObstacles;
        b2Vec2 m_vThrowMin;
        b2Vec2 m_vThrowMax;
        b2Vec2 m_vObstacleMin;
        b2Vec2 m_vObstacleMax;
        b2Vec2 m_vInitialDropVelocity;

        void addSimulationObject()
        {
        }
    };
}

#endif /* ObstructedPathSimulation_h */

#pragma once

#include "Scene7Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene7Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene7Simulation> Ptr;
		Scene7Simulation(Scene7Settings::Ptr settings) : SimulationBase(settings)
		{
            m_bIncludeDynamicObjects  = settings->includeDynamicObjects;
            m_nMin_mean_max_random = settings->min_mean_max_random;

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene7;
		}

		void InitializeScene() override {

            int c = m_nMin_mean_max_random;
            bool includeDynamicObjects = m_bIncludeDynamicObjects;
            
			// Basket
			AddTargetBasket(b2Vec2(getExtremeCases(c,17, 20), -1.2f), 0.0f); 
            
            // inclined
            AddStaticObject(b2Vec2(-13.0f, 17.0f), 7 * M_PI / 8, SimulationObject::STATIC_PLATFORM);  // -13 17
            
            AddStaticObject(b2Vec2(  7.0f, getExtremeCases(c,8, 9)), 7 * M_PI / 8, SimulationObject::STATIC_PLATFORM);  //  8 < y < 9

            // mid
            AddStaticObject(b2Vec2(-10.0f, 8.5f), M_PI, SimulationObject::STATIC_PLATFORM);
            
            float x = getExtremeCases(c,11, 33);
            AddStaticObject(b2Vec2(10.0f, 22.0f), - x * M_PI / (x+2), SimulationObject::STATIC_PLATFORM);  // -13 17
            
            
            if (includeDynamicObjects) {
                AddRandomDynamicObject(
                    b2Vec2(-12.0f, 25.0f),
                    b2Vec2(0.0f, 0.0f)
                );
                
                AddRandomDynamicObject(
                    b2Vec2(-15.0f, 38.0f),
                    b2Vec2(0.0f, 0.0f)
                );
                
                AddRandomDynamicObject(
                    b2Vec2(10.0f, 26.0f),
                    b2Vec2(0.0f, 0.0f)
                );
                
                AddRandomDynamicObject(
                    b2Vec2(-12.0f, 11.0f),
                    b2Vec2(getExtremeCases(c,3, 6), 0.0f),
                    0b110,
                    SimulationObject::CIRCLE,
                    SimulationObject::LARGE
                );
            }
            

		}

	private:
        
        bool m_bIncludeDynamicObjects;
        int  m_nMin_mean_max_random;
        
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

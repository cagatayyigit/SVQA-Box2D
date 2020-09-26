#pragma once

#include "Scene1Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene1Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene1Simulation> Ptr;
		Scene1Simulation(Scene1Settings::Ptr settings) : SimulationBase(settings)
		{
            m_bIncludeDynamicObjects  = settings->includeDynamicObjects;
            m_nMin_mean_max_random = settings->min_mean_max_random;

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene1;
		}

		void InitializeScene() override {  
			// Setup static objects.
            std::string c = m_nMin_mean_max_random;
            bool includeDynamicObjects = m_bIncludeDynamicObjects;


			// Basket
			AddTargetBasket(b2Vec2(getExtremeCases(c,-3.0, 3.0), -1.2f), 0.0f);

            // Bottom Left  Floor
            AddStaticObject(b2Vec2(-12.0f, 6.0f), 0, SimulationObject::STATIC_PLATFORM);
			
            // Bottom Right Floor
            AddStaticObject(b2Vec2(12.0f, 6.0f), 0, SimulationObject::STATIC_PLATFORM);
            

			// Bottom Left  Vertical Floor
			AddStaticObject(b2Vec2(-18.0f, 16.0f), 4 * M_PI / 5, SimulationObject::STATIC_PLATFORM);

			// Middle Left  Floor
			AddStaticObject(b2Vec2(-5.0f, 18.0f), 51 * M_PI / getExtremeCases(c,51.2, 57.0), SimulationObject::STATIC_PLATFORM);


			// Middle Right Floor
			AddStaticObject(b2Vec2(16.0f, getExtremeCases(c,22, 26)), 51 * M_PI / getExtremeCases(c,51.2, 57.0), SimulationObject::STATIC_PLATFORM);

            if (includeDynamicObjects){
                // Stationary Bottom-Left
                float32 leftBottomCircleCoorX = (getExtremeCases(c,-15.0, -10.0));
                AddRandomDynamicObject(
                    b2Vec2(leftBottomCircleCoorX, 9.0f),
                    b2Vec2(0.0f, 0.0f)
                );

                // Stationary Bottom-Right
                float32 rightBottomCircleCoorX = (getExtremeCases(c,10.0, 15.0));
                AddRandomDynamicObject(
                    b2Vec2(rightBottomCircleCoorX, 9.0f),
                    b2Vec2(0.0f, 0.0f)
                );

                // Moving on the Right Floor
                AddRandomDynamicObject(
                    b2Vec2(22.0f, 17.0f),
                    b2Vec2(-10.0f, -4.0f)
                );

                // Falling Circle from mid
                AddRandomDynamicObject(
                    b2Vec2(-10.0f, (getExtremeCases(c,35.0f, 45.0f))),
                    b2Vec2(3.0f, -8.0f)
                );

                // Falling Circle from right
                AddRandomDynamicObject(
                    b2Vec2(16.0f, 30.0f),
                    b2Vec2(-21.0f, -5.0f)
                );
            }
			

			
		}

	private:
        
        bool m_bIncludeDynamicObjects;
        std::string  m_nMin_mean_max_random;
        
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

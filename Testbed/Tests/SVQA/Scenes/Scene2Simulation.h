#pragma once

#include "Scene2Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene2Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene2Simulation> Ptr;
		Scene2Simulation(Scene2Settings::Ptr settings) : SimulationBase(settings)
		{
            m_bIncludeDynamicObjects  = settings->includeDynamicObjects;
            m_nMin_mean_max_random = settings->min_mean_max_random;
            
			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene2;
		}

		void InitializeScene() override {
            
            std::string  c = m_nMin_mean_max_random; 
            bool includeDynamicObjects = m_bIncludeDynamicObjects;
            
			std::vector<SimulationObject::Color> distinc_colors;
			while(distinc_colors.size() < 4) {
				SimulationObject::Color c = SimulationObject::getRandomColor();
				if (std::find(distinc_colors.begin(), distinc_colors.end(), c) == distinc_colors.end()) {
					distinc_colors.push_back(c);
				}
			}
			
			// Basket
			AddTargetBasket(b2Vec2(RandomFloatFromHardware(1.0, 7.0), -1.2f), 0.0f);


			// ------- Stack --------
			std::vector<SimulationObject::Color> stack_colors;
			while (stack_colors.size() < 6) {
				SimulationObject::Color c = SimulationObject::getRandomColor();
				if (std::find(stack_colors.begin(), stack_colors.end(), c) == stack_colors.end()) {
					stack_colors.push_back(c);
				}
			}

			// bottom left - mid - right
			AddDynamicObject(b2Vec2(3.0f, 20.0f),b2Vec2(0.0f, 0.0f),SimulationObject::Shape::CUBE, stack_colors[0],SimulationObject::Size::SMALL);
			AddDynamicObject(b2Vec2(5.2f, 20.0f),b2Vec2(0.0f, 0.0f),SimulationObject::Shape::CUBE, stack_colors[1],SimulationObject::Size::SMALL);
			AddDynamicObject(b2Vec2(7.4f, 20.0f),b2Vec2(0.0f, 0.0f),SimulationObject::Shape::CUBE, stack_colors[2],SimulationObject::Size::SMALL);
			// middle left - right
			AddDynamicObject(b2Vec2(4.0f, 22.0f), b2Vec2(0.0f, 0.0f), SimulationObject::Shape::CUBE, stack_colors[3], SimulationObject::Size::SMALL);
			AddDynamicObject(b2Vec2(6.2f, 22.0f), b2Vec2(0.0f, 0.0f), SimulationObject::Shape::CUBE, stack_colors[4], SimulationObject::Size::SMALL);
			// top
			AddDynamicObject(b2Vec2(5.0f, 24.0f), b2Vec2(0.0f, 0.0f), SimulationObject::Shape::CUBE, stack_colors[5], SimulationObject::Size::SMALL);




			// ------- Top Right Platform and Circle -------
			AddStaticObject(b2Vec2(17.0f, 19.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(9.0f, 19.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(11.0f, 19.0f), 0, SimulationObject::STATIC_RAMP);

			float32 tr_circle_velocities[5] = { -24.0f, -28.0f, -25.0f, -18.0f, -19.0f };
			
			AddDynamicObject(
				b2Vec2(22.0f, 20.0f),
				b2Vec2(tr_circle_velocities[(int)RandomFloatFromHardware(0.0, 5.0)], 0.0f),
				SimulationObject::Shape::CIRCLE,
				distinc_colors[0],
				SimulationObject::getRandomSize()
			);


			// ------- Inclined Platform and Rolling Circle -------
			AddStaticObject(b2Vec2(-26.5f, 12.0f), 6* M_PI / 7, SimulationObject::STATIC_PLATFORM);

			AddDynamicObject(
				b2Vec2(-22.0f, RandomFloatFromHardware(19.0, 35.0)),
				b2Vec2(0.0f, RandomFloatFromHardware(-9.0, 0.0)),
				SimulationObject::Shape::CIRCLE,
				distinc_colors[1],
				SimulationObject::getRandomSize()
			);



			// ------- Bottom Left Platform and Circle -------
			AddStaticObject(b2Vec2(-7.5f, 6.0f), 0, SimulationObject::STATIC_PLATFORM);



			AddDynamicObject(
				b2Vec2(RandomFloatFromHardware(-12.0, -4.0), 8.0f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::Shape::CIRCLE,
				distinc_colors[2],
				SimulationObject::getRandomSize()
			);



			
			// ------- Bottom Right Platform and Circle -------
			AddStaticObject(b2Vec2(17.0f, 6.0f), 0, SimulationObject::STATIC_PLATFORM);

			AddDynamicObject(
				b2Vec2(22.0f, 8.0f),
				b2Vec2(RandomFloatFromHardware(-29.0, -20.0), 0.0f),
				SimulationObject::Shape::CIRCLE,
				distinc_colors[3],
				SimulationObject::getRandomSize()
			);


			



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

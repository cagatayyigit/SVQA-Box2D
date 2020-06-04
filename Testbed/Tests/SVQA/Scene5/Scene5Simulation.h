#pragma once

#include "Scene5Settings.h"
#include "SimulationBase.h"
#include "Box2D/Extension/b2VisBody.hpp"
#include "Box2D/Extension/b2VisPolygonShape.hpp"
#include <math.h> 

namespace svqa {
	class Scene5Simulation : public SimulationBase
	{
	public:
		typedef std::shared_ptr<Scene5Simulation> Ptr;
		Scene5Simulation(Scene5Settings::Ptr settings) : SimulationBase(settings)
		{
			m_nNumberOfObjects = settings->numberOfObjects;
			m_nNumberOfObstacles = settings->numberOfObstacles;

			SET_FILE_OUTPUT_TRUE(m_pSettings->outputVideoPath)
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_Scene4;
		}

		void InitializeScene() override {

			std::vector<SimulationObject::Color> distinc_colors;
			while(distinc_colors.size() < 5) {
				SimulationObject::Color c = SimulationObject::getRandomColor();
				if (std::find(distinc_colors.begin(), distinc_colors.end(), c) == distinc_colors.end()) {
					distinc_colors.push_back(c);
				}
			}
			
			// Basket
			AddTargetBasket(b2Vec2(21.0f, -1.2f), 0.0f);



			AddDynamicObject(
				b2Vec2(RandomFloatFromHardware(-17.0f, -15.0f), 24.5f),
				b2Vec2(RandomFloatFromHardware(5.0f, 15.0f), 0.0f),
				SimulationObject::Shape::CIRCLE,
				distinc_colors[0],
				SimulationObject::getRandomSize());
			AddStaticObject(b2Vec2(-18.0f, 23.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-8.0f, 23.0f), 0, SimulationObject::STATIC_PLATFORM);
			AddStaticObject(b2Vec2(-2.0f, 23.0f), 0, SimulationObject::STATIC_PLATFORM);



			

			
			



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

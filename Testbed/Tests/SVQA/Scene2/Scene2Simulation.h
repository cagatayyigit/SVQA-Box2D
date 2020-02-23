#pragma once

#include "SimulationColor.h"
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
			SET_FILE_OUTPUT_TRUE(m_pSettings->outputFilePath);
		}

		void InitializeScene() override {
			debug::log("Initializing Scene2Simulation...");

			// Up  Floor
			AddStaticObject(
				b2Vec2(5.0f, 20.0f),
				0,
				std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(15.0f, 0.5f)),
				SimulationObject::CUSTOM_RECTANGLE,
				SimulationMaterial::METAL,
				SimulationColor::GRAY
			);

			// Down Floor
			AddStaticObject(
				b2Vec2(0, 14.0f),
				0,
				std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(10.0f, 0.5f)),
				SimulationObject::CUSTOM_RECTANGLE,
				SimulationMaterial::METAL,
				SimulationColor::GRAY
			);

			// First Rec
			AddStaticObject(
				b2Vec2(20, 0.0f),
				0,
				std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(1.5f, 6.0f)),
				SimulationObject::CUSTOM_RECTANGLE,
				SimulationMaterial::METAL,
				SimulationColor::GRAY
			);

			AddDynamicObject(
				b2Vec2(20.0f, 14.0f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::SMALL_CIRCLE,
				SimulationMaterial::RUBBER,
				SimulationColor::TYPE::BLUE
			);

			// Second Rec
			AddStaticObject(
				b2Vec2(28, 0.0f),
				0,
				std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(1.5f, 10.0f)),
				SimulationObject::CUSTOM_RECTANGLE,
				SimulationMaterial::METAL,
				SimulationColor::GRAY
			);

			AddDynamicObject(
				b2Vec2(28.0f, 11.0f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::SMALL_CIRCLE,
				SimulationMaterial::RUBBER,
				SimulationColor::TYPE::GREEN
			);

			// Third Rec
			AddStaticObject(
				b2Vec2(35, -2.0f),
				0,
				std::make_shared<b2PolygonShape>(SimulationObject::getRectangle(1.5f, 4.0f)),
				SimulationObject::CUSTOM_RECTANGLE,
				SimulationMaterial::METAL,
				SimulationColor::GRAY
			);

			AddDynamicObject(
				b2Vec2(35.0f, 4.0f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::SMALL_CIRCLE,
				SimulationMaterial::RUBBER,
				SimulationColor::TYPE::RED
			);

			//
			// Curved Ramp
			//
			ShapePtr chainShape = std::make_shared<b2ChainShape>(SimulationObject::getCurve(
				[](float x) {
					return std::pow(x, 2);
				}, -2, 0.5, 0.05f
			));

			AddStaticObject(
				b2Vec2(-35.0f, 14.0f),
				0,
				chainShape,
				SimulationObject::BIG_TRIANGLE,
				SimulationMaterial::METAL,
				SimulationColor::GRAY
			); 

			// Circles
			// Stationary Bottom-Left 
			AddDynamicObject(
				b2Vec2(7.0f, 22.0f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::SMALL_CIRCLE,
				SimulationMaterial::RUBBER,
				SimulationColor::TYPE::RED
			);

			AddDynamicObject(
				b2Vec2(5.0f, 16.0f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::SMALL_CIRCLE,
				SimulationMaterial::RUBBER,
				SimulationColor::TYPE::BLUE
			);

			AddDynamicObject(
				b2Vec2(-30.0f, 42.0f),
				b2Vec2(0.0f, 0.0f),
				SimulationObject::SMALL_CIRCLE,
				SimulationMaterial::RUBBER,
				SimulationColor::TYPE::BLACK
			);
		}

		virtual SimulationID getIdentifier() override
		{
			return SimulationID::ID_ObstructedPath;
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
